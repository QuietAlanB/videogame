#include "util/log.hh"

#include <cstdlib>
#include <iostream>

void _log(char const *file, char const *fn, long line, std::string const &msg) {
	std::cout << "[ LL ] ";
	
	// tirimid: if you don't want extended debug information, compile the
	// project with `CFLAGS_XXXXX` += `-DLOG_CONCISE`.
#ifndef LOG_CONCISE
	std::cout << '(' << file << ") " << fn << ':' << line << ' ';
#endif
	
	std::cout << msg << '\n';
}

void _wrn(char const *file, char const *fn, long line, std::string const &msg) {
	std::cout << "[ WW ] ";
#ifndef LOG_CONCISE
	std::cout << '(' << file << ") " << fn << ':' << line << ' ';
#endif
	std::cout << msg << '\n';
}

void _err(char const *file, char const *fn, long line, std::string const &msg) {
	std::cout << "[ EE ] ";
#ifndef LOG_CONCISE
	std::cout << '(' << file << ") " << fn << ':' << line << ' ';
#endif
	std::cout << msg << '\n';
	exit(-1);
}
