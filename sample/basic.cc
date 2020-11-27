#include <fmt/color.h>
#include <fmt/core.h>
#include <slog/index.h>
using namespace std;
using namespace slog;

int main() {
    slog::logger lg(make_shared< slog::console >(), slog::severity_level::debug);

    lg.debug("debug log");
    lg.info("info log..Done!");
    for (int i = 1; i <= 1e6; ++i) {
        lg.warning(fmt::format("Warning ID: {}", i));
    }
    lg.error("This is an error log");

    fmt::print(fmt::bg(fmt::color::red) | fmt::fg(fmt::color::white) | fmt::emphasis::bold
                   | fmt::emphasis::underline,
               "{}.", "LOG SEND DONE!.");
    return 0;
}