#include "vex.h"
#include <string>
#include "string.h"
#include <sstream>

using namespace vex;

#include "fc_instances.h"

#include "fc_log.h"

template <typename T>
std::string to_string( T value )
{
    std::ostringstream os;
    os << value;
    return os.str();
}

const char* to_char( double value )
{
  std::string str;
  str.append( to_string( value ) );
  return str.c_str();
}

const char* to_char( int value )
{
  std::string str;
  str.append( to_string( value ) );
  return str.c_str();
}

const char* logTypeNames[] = {
    "Debug",
    "Info",
    "Warning",
    "ERROR",
    "FATAL"
};

const color logColours[] = {
  white,
  white,
  orange,
  red,
  red
};

// #define DEBUG_LOG

const char* g_hexChars = "0123456789ABCDEF";

const char* __fc_log_parse_unsigned( unsigned long long number, int radix )
{
    char buffer[ 32 ];
    std::string output;
    output.clear();
    int pos = 0;

    do
    {
        unsigned long long rem = number % radix;
        number /= radix;
        buffer[ pos++ ] = g_hexChars[ rem ];
    } while ( number > 0 );

    // number is flipped after conversion, so we need another buffer to flip it back
    while ( --pos >= 0 )
        output += buffer[ pos ];

    return output.c_str();
}

void __fc_log_parse_unsigned_passthru( std::string str, bool sendToBrain, bool sendToController, unsigned long long number, int radix )
{
    str += __fc_log_parse_unsigned( number, radix );
}

void __fc_log_parse_signed( std::string str, bool sendToBrain, bool sendToController, long long number, int radix )
{
    if ( number < 0 )
    {
        str += "-";
        str += __fc_log_parse_unsigned( -number, radix );
    }
    else
        str += __fc_log_parse_unsigned( number, radix );
}

#define PARSER_STATE_NORMAL 0
#define PARSER_STATE_LENGTH 1
#define PARSER_STATE_LENGTH_SHORT 2
#define PARSER_STATE_LENGTH_LONG 3
#define PARSER_STATE_SPEC 4

#define PARSER_LENGTH_DEFAULT 0
#define PARSER_LENGTH_SHORT 1
#define PARSER_LENGTH_SHORT_SHORT 2
#define PARSER_LENGTH_LONG 3
#define PARSER_LENGTH_LONG_LONG 4

void __fc_log_print( std::string str, bool sendToBrain, bool sendToController )
{
    if ( sendToBrain ) g_brain.Screen.print( str.c_str() );
    if ( sendToController ) g_controller.Screen.print( str.c_str() );
    puts( str.c_str() );

    str.clear();
}

void __fc_log_parse( bool isFatal, bool sendToBrain, bool sendToController, const char* fmt, va_list args )
{
    int state = PARSER_STATE_NORMAL;
    int length = PARSER_LENGTH_DEFAULT;
    int radix = 10;
    bool sign = false;
    bool number = false;

    std::string tmp;

    while ( *fmt )
    {
        switch( state )
        {
            case PARSER_STATE_NORMAL:
                switch ( *fmt )
                {
                    case '%':
                        state = PARSER_STATE_LENGTH;
                        break;
                    
                    case '\n':
                        __fc_log_print( tmp, sendToBrain, sendToController );

                        if ( sendToBrain ) g_brain.Screen.newLine();
                        if ( sendToController ) g_controller.Screen.newLine();
                        putc( '\n', stdout );
                        break;

                    default:
                        tmp += *fmt;
                        break;
                }
                break;
            
            case PARSER_STATE_LENGTH:
                switch( *fmt )
                {
                    case 'h':
                        length = PARSER_LENGTH_SHORT;
                        state = PARSER_STATE_LENGTH_SHORT;
                        break;

                    case 'l':
                        length = PARSER_LENGTH_LONG;
                        state = PARSER_STATE_LENGTH_LONG;
                        break;

                    default:
                        goto _PARSER_STATE_SPEC;
                }
                break;

            case PARSER_STATE_LENGTH_SHORT:
                if ( *fmt == 'h' )
                {
                    length = PARSER_LENGTH_SHORT_SHORT;
                    state = PARSER_STATE_SPEC;
                }
                else goto _PARSER_STATE_SPEC;
                break;

            case PARSER_STATE_LENGTH_LONG:
                if ( *fmt == 'l' )
                {
                    length = PARSER_LENGTH_LONG_LONG;
                    state = PARSER_STATE_SPEC;
                }
                else goto _PARSER_STATE_SPEC;
                break;

            _PARSER_STATE_SPEC:
            case PARSER_STATE_SPEC:
                switch( *fmt )
                {
                    case 'c':
                        tmp += ( char )va_arg( args, int );
                        break;

                    case 's':
                        tmp += va_arg( args, const char* );
                        break;

                    case '%':
                        tmp += '%';
                        break;

                    case 'd':
                    case 'i':
                        radix = 10;
                        sign = true;
                        number = true;
                        break;

                    case 'u':
                        radix = 10;
                        sign = false;
                        number = true;
                        break;

                    case 'x':
                    case 'p':
                        radix = 16;
                        sign = false;
                        number = true;
                        break;

                    case 'o':
                        radix = 8;
                        sign = false;
                        number = true;
                        break;

                    case 'f':
                        if ( sendToBrain )
                        {
                            __fc_log_print( tmp, sendToBrain, sendToController );
                            g_brain.Screen.setPenColor( va_arg( args, uint32_t ) );
                        }
                        break;

                    case 'b':
                        if ( sendToBrain )
                        {
                            __fc_log_print( tmp, sendToBrain, sendToController );
                            g_brain.Screen.setFillColor( va_arg( args, uint32_t ) );
                        }
                        break;

                    default: break;
                }

                if ( number )
                {
                    if ( sign )
                    {
                        switch ( length )
                        {
                            case PARSER_LENGTH_SHORT_SHORT:
                            case PARSER_LENGTH_SHORT:
                            case PARSER_LENGTH_DEFAULT:
                                __fc_log_parse_signed( tmp, sendToBrain, sendToController, va_arg( args, int ), radix );
                                break;

                            case PARSER_LENGTH_LONG:
                                __fc_log_parse_signed( tmp, sendToBrain, sendToController, va_arg( args, long ), radix );
                                break;

                            case PARSER_LENGTH_LONG_LONG:
                                __fc_log_parse_signed( tmp, sendToBrain, sendToController, va_arg( args, long long ), radix );
                                break;

                            default: break;
                        }
                    }
                    else
                    {
                        switch ( length )
                        {
                            case PARSER_LENGTH_SHORT_SHORT:
                            case PARSER_LENGTH_SHORT:
                            case PARSER_LENGTH_DEFAULT:
                                __fc_log_parse_unsigned_passthru( tmp, sendToBrain, sendToController, va_arg( args, unsigned int ), radix );
                                break;

                            case PARSER_LENGTH_LONG:
                                __fc_log_parse_unsigned_passthru( tmp, sendToBrain, sendToController, va_arg( args, unsigned long ), radix );
                                break;

                            case PARSER_LENGTH_LONG_LONG:
                                __fc_log_parse_unsigned_passthru( tmp, sendToBrain, sendToController, va_arg( args, unsigned long long ), radix );
                                break;

                            default: break;
                        }
                    }
                }

                state = PARSER_STATE_NORMAL;
                length = PARSER_LENGTH_DEFAULT;
                radix = 10;
                sign = false;
                number = false;
                break;

            default: break;
        }

        fmt++;
    }

    __fc_log_print( tmp, sendToBrain, sendToController );
}

void fc_log( uint8_t type, bool sendToController, bool usePrefix, const char* loc, const char* fmt, ... )
{
#ifndef DEBUG_LOG
    bool sendToBrain = false;

    if ( type != logTypes::Debug ) sendToBrain = true;
#else
    bool sendToBrain = true;
#endif

    color col;
    char printCol[6];

    switch ( type )
    {
        case 0:
            col = color( 127, 127, 127 );
            strcpy( printCol, "\033[37m" );
            break;

        case 1:
            col = color( 255, 255, 255 );
            strcpy( printCol, "\033[37m" );
            break;

        case 2:
            col = color( 255, 127, 0 );
            strcpy( printCol, "\033[91m" );
            break;

        case 3:
        case 4:
            col = color( 255, 0, 0 );
            strcpy( printCol, "\033[31m" );
            break;

        default:
            col = color( 255, 255, 255 );
            strcpy( printCol, "\033[37m" );
            break;
    }

    if ( sendToBrain )
        g_brain.Screen.setPenColor( col );

    puts( printCol );

    if ( usePrefix && type != logTypes::FATAL )
    {
        if ( sendToController )
            g_controller.Screen.print( "<%s - %s>: ", logTypeNames[type], loc );

        if ( sendToBrain )
            g_brain.Screen.print( "<%s - %s>: ", logTypeNames[type], loc );
        
        printf( "<%s - %s>: ", logTypeNames[type], loc );
    }

    if ( type == logTypes::FATAL )
    {
        g_brain.Screen.setPenColor( red );
        g_brain.Screen.setFillColor( red );
        g_brain.Screen.clearScreen();
        g_brain.Screen.drawRectangle( 0, 0, 1000, 1000 );
        g_brain.Screen.setPenColor( white );
        g_brain.Screen.setCursor( 1, 1 );

        g_brain.Screen.print( "X(" );
        g_brain.Screen.newLine();
        g_brain.Screen.newLine();
        g_brain.Screen.print( "FATAL ERROR!" );
        g_brain.Screen.newLine();
        g_brain.Screen.newLine();
        g_brain.Screen.print( "Loc:" );
        g_brain.Screen.newLine();
        g_brain.Screen.print( "  %s", loc );
        g_brain.Screen.newLine();
        g_brain.Screen.newLine();
        g_brain.Screen.print( "Details:" );
        g_brain.Screen.newLine();
        printf( "%sFATAL ERROR @ \"%s\"!\nDetails: ", printCol, loc );
    }

    va_list args;
    va_start( args, fmt );

    __fc_log_parse( ( type == logTypes::FATAL ), sendToBrain, sendToController, fmt, args );

    va_end( args );

    if ( type == logTypes::FATAL )
    {
        thread::interruptAll();

        // kill the program
        while( true )
        {
            wait( 10, msec );
        }
    }

    if ( sendToBrain )
        g_brain.Screen.setPenColor( color::white );

    printf( "\033[37m" );
}