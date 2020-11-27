#include "slog/message.h"

slog::message::message(const std::string& content, slog::severity_level level) {
    this->content = content;
    this->level = level;
}

slog::message::message() {}
slog::message::~message() {}

slog::full_message::full_message(const std::string& content, slog::severity_level level) {
    this->content = content;
    this->level = level;
    this->_init_time();
}

slog::full_message::~full_message() {}

slog::message slog::full_message::get(const slog::formatter& formatter) const {
    slog::message res;
    res.content = formatter(this->content, this->level, this->emit_time);
    res.level = this->level;
    return res;
}

void slog::full_message::_init_time() { this->emit_time = std::time(nullptr); }