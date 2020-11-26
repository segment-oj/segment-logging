// -*- C++ -*- Part of the segment logging project

#ifndef _SLOG_SOURCE_POINT_H
#define _SLOG_SOURCE_POINT_H

#include <string>

namespace slog {

#define SLOG_SOURCE_CODE_POINT() source_point(__FILE__, __LINE__, __FUNCTION__)

class source_point {
public:
    source_point(const std::string& file, const unsigned line, const std::string& func);
    source_point();
    ~source_point();

    std::string get() const;

    unsigned get_line_number() const;
    std::string get_file_name() const;
    std::string get_function_name() const;

    void set_line_number(const unsigned value);
    void set_file_name(const std::string& value);
    void set_function_name(const std::string& value);

    void clear();

private:
    bool _is_null;

    unsigned _line;
    std::string _file;
    std::string _func;
};

} // namespace slog

#endif // #define _SLOG_SOURCE_POINT_H