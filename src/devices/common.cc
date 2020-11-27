#include <thread>
#include <chrono>
#include "slog/dev.h"

void slog::common_device::raw_write(const slog::message& msg) const { printf("PVFC!\n"); }

slog::common_device::~common_device() { this->_worker_destory_flag = true; }

void slog::common_device::force_wait(const size_t min_length) {
    static const unsigned wait_time{50};
    while (this->message_queue.size() > min_length) {
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
}

void slog::common_device::flush() {}

void slog::common_device::_log_write_worker_func() {
    unsigned lazy_sleep_ms{1};
    while (true) {
        if (this->_worker_destory_flag) { return; }

        if (this->message_queue.empty()) {
            if (lazy_sleep_ms < 512) { lazy_sleep_ms *= 2; }
        } else {
            lazy_sleep_ms = 1;
            while (!this->message_queue.empty()) {
                const auto& this_message{this->message_queue.front()};
                this->raw_write(this_message);
                this->message_queue.pop();
            }
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

void slog::common_device::write(const slog::message& msg) {
    // static const size_t max_queue_length{static_cast<size_t>(1000)};
    // this->force_wait(max_queue_length);
    this->message_queue.push(msg);
}