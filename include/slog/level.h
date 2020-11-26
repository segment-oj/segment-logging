// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_TYPE_H
#define _SLOG_TYPE_H

namespace slog {

enum class severity_level {
    none = 127,
    debug = 0,
    info = 1,
    warning = 2,
    error = 3,
};

} // namespace slog

#endif // #define _SLOG_TYPE_H