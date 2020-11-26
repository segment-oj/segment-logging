#include <thread>
#include <chrono>
#include "slog/dev.h"

slog::common_device::~common_device() {}
void slog::common_device::flush() {}

void slog::common_device::_log_write_worker_func() {
    unsigned lazy_sleep_ms = 1;
    while (true) {
        if (this->_worker_destory_flag) { return; }

        if (this->messages.empty()) {
            if (lazy_sleep_ms < 512) { lazy_sleep_ms *= 2; }
        } else {
            while (!this->messages.empty()) {
                auto this_message = this->messages.front();
                this->messages.pop();
                this->raw_write(this_message);
            }
            lazy_sleep_ms = 1;
        }

        if (lazy_sleep_ms >= 32) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lazy_sleep_ms));
        } else {
            std::this_thread::yield();
        }
    }
}

slog::common_device::common_device() {
    this->_worker_destory_flag = false;
    this->worker = std::thread([this] { this->_log_write_worker_func(); });
    this->worker.detach();
}

void slog::common_device::write(const slog::message& msg) { this->messages.push(msg); }