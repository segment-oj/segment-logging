#include "slog/source_point.h"
#include <fmt/core.h>

slog::source_point::source_point(const std::string& file, const unsigned line,
                                 const std::string& func) {
    this->_is_null = false;

    this->_file = file;
    this->_line = line;
    this->_func = func;
}

slog::source_point::source_point() {
    this->_is_null = true;
    this->_line = static_cast< unsigned >(-1);
}

slog::source_point::~source_point() {}

unsigned slog::source_point::get_line_number() const { return this->_line; }
std::string slog::source_point::get_file_name() const { return this->_file; }
std::string slog::source_point::get_function_name() const { return this->_func; }

void slog::source_point::set_line_number(const unsigned value) {
    this->_line = value;
    this->_is_null = false;
}

void slog::source_point::set_file_name(const std::string& value) {
    this->_file = value;
    this->_is_null = false;
}

void slog::source_point::set_function_name(const std::string& value) {
    this->_func = value;
    this->_is_null = false;
}

std::string slog::source_point::get() const {
    if (this->_is_null) { return ""; }
    return fmt::format("{}:{} ({})", this->_file, this->_line, this->_func);
}

void slog::source_point::clear() {
    this->_is_null = true;
    this->_file = "";
    this->_func = "";
    this->_line = static_cast< unsigned >(-1);
}