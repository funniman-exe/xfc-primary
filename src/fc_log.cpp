#include "main.h"
#include <cstring>

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

namespace xfc {
    const char* logTypeNames[] = {
        "Debug",
        "Info",
        "Warning",
        "ERROR",
        "FATAL"
    };

    const pros::Color logColours[] = {
        pros::Color::white,
        pros::Color::white,
        pros::Color::orange,
        pros::Color::red,
        pros::Color::red
    };

    namespace fc_logProperties
    {
        int m_iCurrLine;
        int m_iCurrCol;
        int m_iCurrControllerLine;
        int m_iCurrControllerCol;
        int m_iColChanged;
        pros::text_format_e_t m_iTextFmt;
    }

    #define brainMaxLines 8
    #define controllerMaxLines 3

    std::string brainLogConsole[ brainMaxLines ];
    std::string controllerLogConsole[ controllerMaxLines ];
    //lv_obj_t *text = nullptr;

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

    void fc_log_init()
    {
        fc_logProperties::m_iCurrLine = 0;
        fc_logProperties::m_iCurrCol = 0;
        fc_logProperties::m_iCurrControllerLine = 0;
        fc_logProperties::m_iCurrControllerCol = 0;
        fc_logProperties::m_iColChanged = 0;
        fc_logProperties::m_iTextFmt = pros::text_format_e_t::E_TEXT_MEDIUM;

        //pros::screen::erase();
        pros::lcd::clear();

        for ( int i = 0; i < brainMaxLines; i++ )
        {
            brainLogConsole[ i ] = "";
        }

        for ( int i = 0; i < controllerMaxLines; i++ )
        {
            controllerLogConsole[ i ] = "";
        }

        //text = lv_label_create( lv_screen_active() );
        //lv_label_set_long_mode( text, LV_LABEL_LONG_WRAP );
        //lv_obj_set_size( text, 480, 240 );
        //lv_label_set_text( text, brainLogConsole.c_str() );
    }

    void fc_log_deinit()
    {
        fc_logProperties::m_iCurrLine = 0;
        fc_logProperties::m_iCurrCol = 0;
        fc_logProperties::m_iCurrControllerLine = 0;
        fc_logProperties::m_iCurrControllerCol = 0;
        fc_logProperties::m_iColChanged = 0;
        fc_logProperties::m_iTextFmt = pros::text_format_e_t::E_TEXT_MEDIUM;
    }

    void __fc_log_print( const char *str, bool sendToBrain, bool sendToController )
    {
        printf( str );
        if ( sendToBrain )
        {
            brainLogConsole[ fc_logProperties::m_iCurrLine ] += str;
            pros::lcd::print( fc_logProperties::m_iCurrLine, brainLogConsole[ fc_logProperties::m_iCurrLine ].c_str() );
            //pros::screen::print( fc_logProperties::m_iTextFmt, fc_logProperties::m_iCurrLine, str );
            //brainLogConsole += str;
            //lv_label_set_text( text, brainLogConsole.c_str() );
            //fc_logProperties::m_iCurrCol += fc_logProperties::m_iColChanged;
        }
        if ( sendToController )
        {
            controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ] += str;
            xfc::globals::g_cMaster->set_text( fc_logProperties::m_iCurrControllerLine, 0, controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ] );
            xfc::globals::g_cSlave->set_text( fc_logProperties::m_iCurrControllerLine, 0, controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ] );

            //fc_logProperties::m_iCurrControllerCol += fc_logProperties::m_iColChanged;
        }

        //fc_logProperties::m_iColChanged = 0;
    }

    void __fc_log_parse( bool isFatal, bool sendToBrain, bool sendToController, const char* fmt, va_list args )
    {
        int state = PARSER_STATE_NORMAL;
        int length = PARSER_LENGTH_DEFAULT;
        int radix = 10;
        bool sign = false;
        bool number = false;

        std::string tmp;
        fc_logProperties::m_iColChanged = 0;

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
                            __fc_log_print( tmp.c_str(), sendToBrain, sendToController );
                            tmp.clear();

                            if ( sendToBrain )
                            {
                                ++fc_logProperties::m_iCurrLine;
                                //brainLogConsole += "\n";

                                if ( fc_logProperties::m_iCurrLine >= brainMaxLines )
                                {
                                    for ( int i = 0; i < brainMaxLines - 1; i++ )
                                    {
                                        brainLogConsole[ i ] = brainLogConsole[ i + 1 ];
                                    }

                                    brainLogConsole[ brainMaxLines - 1 ] = "";
                                }
                            }
                            if ( sendToController )
                            {
                                ++fc_logProperties::m_iCurrControllerLine;

                                if ( fc_logProperties::m_iCurrControllerLine >= controllerMaxLines )
                                {
                                    for ( int i = 0; i < controllerMaxLines - 1; i++ )
                                    {
                                        controllerLogConsole[ i ] = controllerLogConsole[ i + 1 ];
                                    }

                                    controllerLogConsole[ controllerMaxLines - 1 ] = "";
                                }
                            }
                            printf( "\n" );
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
                                __fc_log_print( tmp.c_str(), sendToBrain, sendToController );
                                tmp.clear();
                                pros::screen::set_pen( va_arg( args, uint32_t ) );
                            }
                            break;

                        case 'b':
                            if ( sendToBrain )
                            {
                                __fc_log_print( tmp.c_str(), sendToBrain, sendToController );
                                tmp.clear();
                                pros::screen::set_eraser( va_arg( args, uint32_t ) );
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

            ++fc_logProperties::m_iColChanged;
            ++fmt;
        }

        __fc_log_print( tmp.c_str(), sendToBrain, sendToController );
        tmp.clear();
    }

    void fc_log( uint8_t type, bool sendToController, bool usePrefix, const char* loc, const char* fmt, ... )
    {
#ifndef DEBUG_LOG
        bool sendToBrain = false;

        if ( type != logTypes::Debug ) sendToBrain = true;
#else
        bool sendToBrain = true;
#endif

        pros::Color col;
        char printCol[6];

        switch ( type )
        {
            case 0:
                col = pros::Color::gray;
                strcpy( printCol, "\033[37m" );
                break;

            case 1:
                col = pros::Color::white;
                strcpy( printCol, "\033[37m" );
                break;

            case 2:
                col = pros::Color::orange;
                strcpy( printCol, "\033[91m" );
                break;

            case 3:
            case 4:
                col = pros::Color::red;
                strcpy( printCol, "\033[31m" );
                break;

            default:
                col = pros::Color::white;
                strcpy( printCol, "\033[37m" );
                break;
        }

        //if ( sendToBrain )
        //    pros::screen::set_pen( col );

        printf( printCol );

        if ( usePrefix && type != logTypes::FATAL )
        {
            std::string prefix = "<";
            prefix += logTypeNames[ type ];
            prefix += " - ";
            prefix += loc;
            prefix += ">: ";

            if ( sendToController )
            {
                controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ] += prefix;

                xfc::globals::g_cMaster->set_text( fc_logProperties::m_iCurrControllerLine, 0, controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ].c_str() );
                xfc::globals::g_cSlave->set_text( fc_logProperties::m_iCurrControllerLine, 0, controllerLogConsole[ fc_logProperties::m_iCurrControllerLine ].c_str() );
            }

            if ( sendToBrain )
            {
                brainLogConsole[ fc_logProperties::m_iCurrLine ] += prefix;

                pros::lcd::set_text( fc_logProperties::m_iCurrLine, brainLogConsole[ fc_logProperties::m_iCurrLine ] );
                //pros::screen::print( fc_logProperties::m_iTextFmt, fc_logProperties::m_iCurrLine, "<%s - %s>: ", logTypeNames[type], loc );
                //lv_label_set_text_fmt( text, "<%s - %s>: ", logTypeNames[type], loc );
                //brainLogConsole += "<";
                //brainLogConsole += logTypeNames[type];
                //brainLogConsole += " - ";
                //brainLogConsole += loc;
                //brainLogConsole += ">: ";
                //lv_label_set_text( text, brainLogConsole.c_str() );
            }
            
            printf( prefix.c_str() );

            prefix.clear();
        }

        if ( type == logTypes::FATAL )
        {
            //pros::screen::set_pen( pros::Color::red );
            //pros::screen::set_eraser( pros::Color::red );
            //pros::screen::erase();
            //pros::screen::set_pen( pros::Color::white );

            pros::lcd::set_text( 0, "X(" );
            pros::lcd::set_text( 2, "FATAL ERROR!" );
            pros::lcd::print( 4, "Loc: %s", loc );
            //pros::lcd::set_text( 6, "Details: " );
            //pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, 0, "X(" );
            //pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, 2, "FATAL ERROR!" );
            //pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, 4, "Loc:" );
            //pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, 5, "  %s", loc );
            //pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, 7, "Details: " );
            //brainLogConsole = "X(\n\n";
            //brainLogConsole += "FATAL ERROR!\n\n";
            //brainLogConsole += "Log:\n  ";
            //brainLogConsole += loc;
            //brainLogConsole += "\n\nDetails: ";
            //lv_label_set_text_static( text, brainLogConsole.c_str() );
            fc_logProperties::m_iCurrLine = 6;
            printf( "%sFATAL ERROR @ \"%s\"!\nDetails: ", printCol, loc );
        }

        va_list args;
        va_start( args, fmt );

        __fc_log_parse( ( type == logTypes::FATAL ), sendToBrain, sendToController, fmt, args );

        va_end( args );

        if ( type == logTypes::FATAL )
        {
            // kill the program
            while( true )
            {
                pros::delay( 10 );
            }
        }

        //if ( sendToBrain )
        //    pros::screen::set_pen( pros::Color::white );

        printf( "\033[37m" );
    }
}