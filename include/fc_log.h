#pragma once

#include <string>

enum logTypes {
    Debug,
    Info,
    Warning,
    ERROR,
    FATAL
};

template <typename T>
extern std::string to_string( T value );
extern const char* to_char( double value );
extern const char* to_char( int value );

/// @brief XFC's custom logging function
/// @param type Type of log (see the logTypes enum)
/// @param sendToController Should this log be printed on the controller?
/// @param usePrefix Should this log include the prefix ("<logtype - location>")?
/// @param loc The location this message is called from (please only use __func__)
/// @param fmt The base string to build the log message out of
/// @param ... [Optional] Additional arguments to build the log message
void fc_log( uint8_t type, bool sendToController, bool usePrefix, const char* loc, const char* fmt, ... );