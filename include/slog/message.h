// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_MESSAGE_H
#define _SLOG_MESSAGE_H

#include <string>
#include <ctime>
#include "slog/format.h"
#include "slog/level.h"
#include "slog/source_point.h"

namespace slog {

class message {
public:
    message(const std::string& content, slog::severity_level level);
    message();
    ~message();

    std::string content;
    slog::severity_level level;
};

class full_message {
public:
    full_message(const std::string& content, slog::severity_level level,
                 slog::source_point source);
    full_message(const std::string& content, slog::severity_level level);
    ~full_message();

    slog::message get(const slog::formatter& formatter) const;

    std::string content;
    slog::severity_level level;
    std::time_t emit_time;
    slog::source_point source;

private:
    void _init_time();
};

} // namespace slog

#endif // #define _SLOG_MESSAGE_H