#include <memory>
#include <string>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include "slog/format.h"

std::string slog::default_formatter(const std::string& content, slog::severity_level level,
                                    time_t emit_time, const std::string& source) {
    // eg. [E index.cc:955 (main)] 2021-01-01 00:00:00 UTC: Cannot create new file
    char severity_level_char;
    if (level == slog::severity_level::debug) { severity_level_char = 'D'; }
    if (level == slog::severity_level::info) { severity_level_char = 'I'; }
    if (level == slog::severity_level::warning) { severity_level_char = 'W'; }
    if (level == slog::severity_level::error) { severity_level_char = 'E'; }

    return fmt::format("[{}@{}] {:%Y-%m-%d %H:%M:%S %Z}: {}", severity_level_char, source,
                       fmt::localtime(emit_time), content);
}