#ifndef LOG_HH__
#define LOG_HH__

#include <string>

// tirimid: use these macros instead of their function counterparts.
#define LOG(msg) _log(__FILE__, __func__, __LINE__, msg)
#define WARNING(msg) _warn(__FILE__, __func__, __LINE__, msg)
#define ERROR(msg) _err(__FILE__, __func__, __LINE__, msg)

// tirimid: internal - do not call.
void _log(char const *file, char const *fn, long line, std::string const &msg);
void _wrn(char const *file, char const *fn, long line, std::string const &msg);
void _err(char const *file, char const *fn, long line, std::string const &msg);

#endif
