#pragma once

#include <string>

namespace xfc {
    void fc_log_init();
    void fc_log_deinit();

    /// @brief XFC's custom logging function
    /// @param type Type of log (see the logTypes enum)
    /// @param sendToController Should this log be printed on the controller?
    /// @param usePrefix Should this log include the prefix ("<logtype - location>")?
    /// @param loc The location this message is called from (please only use __func__)
    /// @param fmt The base string to build the log message out of
    /// @param ... [Optional] Additional arguments to build the log message
    void fc_log( uint8_t type, bool sendToController, bool usePrefix, const char* loc, const char* fmt, ... );

    namespace fc_logProperties
    {
        extern int m_iCurrLine;
        extern int m_iCurrControllerLine;
    }

    enum logTypes
    {
        Debug,
        Info,
        Warning,
        ERROR,
        FATAL
    };
}

template <typename T>
std::string to_string( T value );
const char* to_char( double value );
const char* to_char( int value );