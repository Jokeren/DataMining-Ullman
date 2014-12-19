#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdint.h>

typedef std::vector<std::vector<std::string> > Buffer;

enum UllmanReturnCode {
	ULLMAN_SUCCESS,
	ULLMAN_WARNING,
	ULLMAN_ERROR,
	ULLMAN_NCOUNT
};

#endif
