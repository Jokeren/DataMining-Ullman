#ifndef ULLMAN_UTILS_H
#define ULLMAN_UTILS_H

#include "common.h"

namespace ullman {
	const static size_t N_ARG = 3;
	const static char *ARGH[N_ARG] = { "-database", "-query", "-sep"};

	struct parameters_t {
		char *database;
		char *query;
		int sep_type;
	};

	enum SEP_TYPE {
		DEFAULT,
		SEP_TYPE_NCOUNT
	};

	size_t get_parameters(struct parameters_t *p_parameters, int argc, char *argv[]);

	void print_parameters(const struct parameters_t *p_parameters);

	void get_seperator(const struct parameters_t *p_parameters, std::string& seperator);

	size_t get_narg();

	void usage();

}//namespace ullman

#endif
