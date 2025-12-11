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

    std::string brainConsole;

    std::string brainLogConsole[ brainMaxLines ];
    std::string controllerLogConsole[ controllerMaxLines ];
    lv_obj_t *container = nullptr;
    lv_obj_t *text = nullptr;

    char prevCol[ 9 ];

    // #define DEBUG_LOG

    void fc_log_init()
    {
        fc_logProperties::m_iCurrLine = 0;
        fc_logProperties::m_iCurrCol = 0;
        fc_logProperties::m_iCurrControllerLine = 0;
        fc_logProperties::m_iCurrControllerCol = 0;
        fc_logProperties::m_iColChanged = 0;
        fc_logProperties::m_iTextFmt = pros::text_format_e_t::E_TEXT_MEDIUM;

        //pros::screen::erase();
        //pros::lcd::clear();

        strcpy( prevCol, "\0\0\0\0\0\0\0\0" );

        for ( int i = 0; i < brainMaxLines; i++ )
        {
            brainLogConsole[ i ] = "";
        }

        for ( int i = 0; i < controllerMaxLines; i++ )
        {
            controllerLogConsole[ i ] = "";
        }

        container = lv_obj_create( lv_scr_act() );
        lv_obj_set_size( container, 480, 240 );
        lv_obj_set_scroll_dir( container, LV_DIR_VER );
        lv_obj_set_style_pad_all( container, 5, LV_PART_MAIN );

        text = lv_label_create( container );
        lv_obj_set_width( text, lv_pct( 100 ) );
        lv_label_set_long_mode( text, LV_LABEL_LONG_WRAP );
        lv_obj_set_height( text, LV_SIZE_CONTENT );
        lv_label_set_recolor( text, true );
        lv_label_set_text( text, "" );
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

    void __fc_log_print( const char *str, bool sendToBrain, bool sendToController, bool isFatal )
    {
        std::cout << str;
        if ( sendToBrain )
        {
            if ( isFatal ) brainLogConsole[ fc_logProperties::m_iCurrLine ] += "    ";
            brainLogConsole[ fc_logProperties::m_iCurrLine ] += str;

            brainConsole.clear();
            for ( int i = 0; i < brainMaxLines; i++ )
            {
                brainConsole += brainLogConsole[ i ];
                brainConsole += "\n";
            }

            //std::cout << "DBG: printing string \"" << brainLogConsole[ fc_logProperties::m_iCurrLine ] << "\" to brain screen on line" << fc_logProperties::m_iCurrLine << ";;;;;";

            //pros::lcd::set_text( fc_logProperties::m_iCurrLine, brainLogConsole[ fc_logProperties::m_iCurrLine ] );
            //pros::screen::print( fc_logProperties::m_iTextFmt, fc_logProperties::m_iCurrLine, str );
            //brainLogConsole += str;
            lv_label_set_text( text, brainConsole.c_str() );
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

    void __fc_log_process( bool isFatal, bool sendToBrain, bool sendToController, const char* fmt )
    {
        std::string tmp;
        tmp.clear();

        while ( *fmt )
        {
            switch ( *fmt )
            {   
                case '\n':
                    if ( !tmp.empty() )
                    {
                        __fc_log_print( tmp.c_str(), sendToBrain, sendToController, isFatal );
                        tmp.clear();
                    }

                    if ( sendToBrain )
                    {
                        if ( ++fc_logProperties::m_iCurrLine >= brainMaxLines )
                        {
                            for ( int i = 0; i < brainMaxLines - 1; ++i )
                            {
                                brainLogConsole[ i ] = brainLogConsole[ i + 1 ];
                            }

                            brainLogConsole[ brainMaxLines - 1 ] = "";
                        }

                        brainLogConsole[ fc_logProperties::m_iCurrLine ] += prevCol;

                        brainConsole.clear();
                        for ( int i = 0; i < brainMaxLines; ++i )
                        {
                            brainConsole += brainLogConsole[ i ];
                            brainConsole += "\n";
                        }

                        lv_label_set_text( text, brainConsole.c_str() );
                    }

                    if ( sendToController )
                    {
                        if ( ++fc_logProperties::m_iCurrControllerLine >= controllerMaxLines )
                        {
                            for ( int i = 0; i < controllerMaxLines - 1; i++ )
                            {
                                controllerLogConsole[ i ] = controllerLogConsole[ i + 1 ];
                            }

                            controllerLogConsole[ controllerMaxLines - 1 ] = "";
                        }
                    }

                    std::cout << std::endl;
                    break;

                default:
                    tmp += *fmt;
                    break;
            }
            
            ++fc_logProperties::m_iColChanged;
            ++fmt;
        }

        if ( !tmp.empty() ) __fc_log_print( tmp.c_str(), sendToBrain, sendToController, isFatal );
        if ( !tmp.empty() ) tmp.clear();
    }

    /// @brief wrapper for vsprintf
    /// @param fmt format string
    /// @param va variable argument list
    /// @returns const char* containing the formatted string
    char* vsprintf_wrapper( const char* fmt, va_list va )
    {
        // kinda horrible, but i'm not sure if there's a better way
        char* tmp = new char[ sizeof( fmt ) + 256 ];
        vsprintf( tmp, fmt, va );

        return tmp;
    }

    /// @brief A wrapper for sprintf
    /// @param fmt Format String
    /// @param ... Variable Arguments
    /// @returns const char* containing the formatted string
    char* cFmt( const char* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );

        // kinda horrible, but i'm not sure if there's a better way
        char* tmp = new char[ sizeof( fmt ) + 256 ];
        vsprintf( tmp, fmt, args );

        va_end( args );

        return tmp;
    }

    void fc_log( uint8_t type, bool sendToController, bool usePrefix, const char* loc, const char* fmt, ... )
    {
#ifndef DEBUG_LOG
        bool sendToBrain = false;

        if ( type != logTypes::Debug ) sendToBrain = true;
#else
        bool sendToBrain = true;
#endif

        //pros::Color col;
        char printCol[ 6 ];
        char col[ 9 ];

        switch ( type )
        {
            case 0:
                //col = pros::Color::gray;
                strcpy( col, "#7f7f7f " );
                strcpy( printCol, "\033[37m" );
                break;

            case 1:
                //col = pros::Color::white;
                strcpy( col, "#ffffff " );
                strcpy( printCol, "\033[37m" );
                break;

            case 2:
                //col = pros::Color::orange;
                strcpy( col, "#ff7f00 " );
                strcpy( printCol, "\033[91m" );
                break;

            case 3:
            case 4:
                //col = pros::Color::red;
                strcpy( col, "#ff0000 " );
                strcpy( printCol, "\033[31m" );
                break;

            default:
                //col = pros::Color::white;
                strcpy( col, "#ffffff " );
                strcpy( printCol, "\033[37m" );
                break;
        }

        if ( sendToBrain )
        {
        //    pros::screen::set_pen( col );
            brainLogConsole[ fc_logProperties::m_iCurrLine ] += col;
            strcpy( prevCol, col );
        }

        std::cout << printCol;

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

                //pros::lcd::set_text( fc_logProperties::m_iCurrLine, brainLogConsole[ fc_logProperties::m_iCurrLine ] );
                //pros::screen::print( fc_logProperties::m_iTextFmt, fc_logProperties::m_iCurrLine, "<%s - %s>: ", logTypeNames[type], loc );
                //lv_label_set_text_fmt( text, "<%s - %s>: ", logTypeNames[type], loc );
                //brainLogConsole += "<";
                //brainLogConsole += logTypeNames[type];
                //brainLogConsole += " - ";
                //brainLogConsole += loc;
                //brainLogConsole += ">: ";

                brainConsole.clear();
                for ( int i = 0; i < brainMaxLines; i++ )
                {
                    brainConsole += brainLogConsole[ i ];
                    brainConsole += "\n";
                }

                lv_label_set_text( text, brainConsole.c_str() );
            }
            
            std::cout << prefix.c_str();

            prefix.clear();
        }

        if ( type == logTypes::FATAL )
        {
            //pros::screen::set_pen( pros::Color::red );
            //pros::screen::set_eraser( pros::Color::red );
            //pros::screen::erase();
            //pros::screen::set_pen( pros::Color::white );

            //pros::lcd::set_text( 0, "X(" );
            //pros::lcd::set_text( 2, "FATAL ERROR!" );
            //pros::lcd::print( 4, "Loc: %s", loc );

            brainLogConsole[ 0 ] = "X(";
            brainLogConsole[ 1 ] = "";
            brainLogConsole[ 2 ] = "FATAL ERROR @ ";
            brainLogConsole[ 2 ] += loc;
            brainLogConsole[ 3 ] = "";
            brainLogConsole[ 4 ] = "Details: ";
            brainLogConsole[ 5 ] = "";
            brainLogConsole[ 6 ] = "";
            brainLogConsole[ 7 ] = "";

            brainConsole.clear();
            for ( int i = 0; i < brainMaxLines; i++ )
            {
                brainConsole += brainLogConsole[ i ];
            }

            lv_label_set_text( text, brainConsole.c_str() );

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
            fc_logProperties::m_iCurrLine = 5;
            std::cout << "FATAL ERROR @ \"" << loc << "\"!\nDetails: ";
        }

        va_list args;
        va_start( args, fmt );

        const char* input = vsprintf_wrapper( fmt, args );

        //__fc_log_parse( ( type == logTypes::FATAL ), sendToBrain, sendToController, fmt, args );
        __fc_log_process( ( type == logTypes::FATAL ), sendToBrain, sendToController, input );

        delete[] input;
        input = nullptr;

        va_end( args );

        if ( type == logTypes::FATAL )
        {
            // kill the program
            while( true )
            {
                pros::delay( 10 );
            }
        }

        if ( sendToBrain )
        {
        //    pros::screen::set_pen( pros::Color::white );
            brainLogConsole[ fc_logProperties::m_iCurrLine ] += "#";
            strcpy( prevCol, "\0\0\0\0\0\0\0\0" );
        }

        std::cout << "\033[37m";
    }
}