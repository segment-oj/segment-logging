// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_FORMAT_H
#define _SLOG_FORMAT_H

#include <functional>
#include <string>
#include <ctime>
#include "slog/level.h"

namespace slog {

// (content, level, time)
using formatter = std::function< std::string(const std::string&, const slog::severity_level,
                                             const std::time_t) >;

std::string default_formatter(const std::string& content, const slog::severity_level level,
                              const std::time_t emit_time);
std::string simple_formatter(const std::string& content, const slog::severity_level level,
                              const std::time_t emit_time);
} // namespace slog

#endif // #define _SLOG_FORMAT_H