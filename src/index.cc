#include "slog/index.h"
#include "slog/format.h"

slog::logger::logger() {
    this->_formatter = slog::default_formatter;
    this->_min_log_level = slog::severity_level::debug;
}

slog::logger::~logger() {
    for (auto d : this->_devices) {
        d->force_wait();
    }
}

slog::logger::logger(std::shared_ptr< slog::common_device > device, slog::severity_level level,
                     const slog::formatter& formatter) {
    this->add_device(device);
    this->set_severity_level(level);
    this->_formatter = formatter;
}

slog::logger::logger(std::shared_ptr< slog::common_device > device, slog::severity_level level) {
    this->add_device(device);
    this->set_severity_level(level);
    this->_formatter = slog::default_formatter;
}

slog::logger::logger(slog::severity_level level) {
    this->set_severity_level(level);
    this->_formatter = slog::default_formatter;
}

slog::logger& slog::logger::add_device(std::shared_ptr< slog::common_device > device) {
    this->_devices.push_back(device);
    return *this;
}

slog::logger& slog::logger::set_severity_level(slog::severity_level level) {
    this->_min_log_level = level;
    return *this;
}

slog::logger& slog::logger::log(slog::severity_level level, const std::string& content) {
    if (level < this->_min_log_level) { return *this; }

    slog::full_message this_full_message(content, level);
    auto this_message = this_full_message.get(this->_formatter);
    for (auto d : this->_devices) {
        d->write(this_message);
    }

    return *this;
}

slog::logger& slog::logger::debug(const std::string& content) {
    return this->log(slog::severity_level::debug, content);
}

slog::logger& slog::logger::info(const std::string& content) {
    return this->log(slog::severity_level::info, content);
}

slog::logger& slog::logger::warning(const std::string& content) {
    return this->log(slog::severity_level::warning, content);
}

slog::logger& slog::logger::error(const std::string& content) {
    return this->log(slog::severity_level::error, content);
}