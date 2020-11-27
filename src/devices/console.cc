#include <fmt/color.h>
#include <fmt/core.h>
#include "slog/dev.h"
#include "slog/level.h"
#include "slog/message.h"

slog::console::console() {}
slog::console::~console() {}

void slog::console::flush() { fflush(stdout); }

void slog::console::raw_write(const slog::message& msg) const {
    fmt::text_style style;
    if (msg.level == slog::severity_level::debug) {
        style = fmt::fg(fmt::color::gray);
    } else if (msg.level == slog::severity_level::info) {
        style = fmt::fg(fmt::color::white);
    } else if (msg.level == slog::severity_level::warning) {
        style = fmt::fg(fmt::color::orange) | fmt::emphasis::bold;
    } else if (msg.level == slog::severity_level::error) {
        style = fmt::fg(fmt::color::red) | fmt::emphasis::bold;
    }

    fmt::print(style, "{}\n", msg.content);
}