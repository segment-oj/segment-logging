// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_DEV_H
#define _SLOG_DEV_H

#include <queue>
#include <string>
#include <thread>
#include "slog/level.h"
#include "slog/message.h"

namespace slog {

class common_device {
public:
    common_device();
    ~common_device();

    virtual void write(const slog::message& msg);
    virtual void flush();
    void force_wait(const size_t min_length = 0);

protected:
    virtual void raw_write(const slog::message& msg) const;

    std::thread worker;
    std::queue< slog::message > message_queue;

private:
    bool _worker_destory_flag;
    void _log_write_worker_func();
};

class console : public common_device {
public:
    console();
    ~console();

    void flush() override;

protected:
    void raw_write(const slog::message& msg) const override;

private:
    static console* _instance;
};

} // namespace slog

#endif // #define _SLOG_DEV_H