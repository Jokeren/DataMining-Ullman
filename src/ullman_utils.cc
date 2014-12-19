#include "ullman_utils.h"

namespace ullman {
	size_t get_parameters(struct parameters_t *p_parameters, int argc, char *argv[])
	{
		char *database = NULL;
		char *query = NULL;
		int sep_type = 0;

		size_t n_argh = 0;
		for (size_t i_argv = 1; i_argv < argc - 1; i_argv += 2)
		{
			for (size_t i_argh = 0; i_argh < N_ARG; i_argh++)
			{                                               
				if (strcmp(argv[i_argv], ARGH[i_argh]) != 0)
				{
					continue;
				} 
				switch (i_argh)
				{
					case 0: database = argv[i_argv + 1];
							n_argh++;
							break;
					case 1: query = argv[i_argv + 1];
							n_argh++;
							break;
					case 2: sep_type = atoi(argv[i_argv + 1]);
							if (sep_type < 0 || sep_type >= SEP_TYPE_NCOUNT) {
								usage();
								exit(-1);
							}
							break;
					default:
							usage();
							exit(-1);
				}
				break;
			}
		}

		p_parameters->database = database;
		p_parameters->query = query;
		p_parameters->sep_type = sep_type;
		return n_argh;
	}

	void get_seperator(const struct parameters_t *p_parameters,
			std::string& seperator)
	{
		if (p_parameters->sep_type == 0) {
			//To-do: seperator factory
			seperator = " ";
		} else {
			//do nothing
		}
	}

	void print_parameters(const struct parameters_t *p_parameters)
	{
		printf("-database: %s\n", p_parameters->database);
		printf("-query: %s\n", p_parameters->query);
		printf("-sep: %d\n", p_parameters->sep_type);
	}

	size_t get_narg()
	{
		return N_ARG;
	}

	void usage()
	{
		printf("usage!\n");
	}
}//namespace ullman
