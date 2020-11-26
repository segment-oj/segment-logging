// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_INDEX_H
#define _SLOG_INDEX_H

#include <memory>
#include <vector>
#include "slog/dev.h"
#include "slog/format.h"
#include "slog/level.h"
#include "slog/source_point.h"

namespace slog {

class logger {
public:
    logger(std::shared_ptr< slog::common_device > device, slog::severity_level level,
           const slog::formatter& formatter);
    logger(std::shared_ptr< slog::common_device > device, slog::severity_level level);
    logger(slog::severity_level level);
    logger();
    ~logger();

    slog::logger& add_device(std::shared_ptr< slog::common_device > device);
    slog::logger& set_severity_level(slog::severity_level level);

    slog::logger& debug(const std::string& content);
    slog::logger& info(const std::string& content);
    slog::logger& warning(const std::string& content);
    slog::logger& error(const std::string& content);

    slog::logger& log(slog::severity_level level, const std::string& content);

private:
    slog::formatter _formatter;
    std::vector< std::shared_ptr< slog::common_device > > _devices;
    slog::severity_level _min_log_level;
};

} // namespace slog

#endif // #define _SLOG_TYPE_H