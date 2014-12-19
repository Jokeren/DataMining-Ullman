#include <string>
#include "sys/time.h"
#include "ullman.h"
#include "ullman_utils.h"
#include "common.h"

int main(int argc, char *argv[])
{
	ullman::parameters_t parameters;
	
	//./ullman -database ../data/ -query ../data/
	size_t nargh = ullman::get_parameters(&parameters, argc, argv);

	//[parameters] - [number of default parameters]
	if (nargh != ullman::get_narg() - 1) {
		exit(ULLMAN_ERROR);
	}

	std::string seperator;
	ullman::get_seperator(&parameters, seperator);
	ullman::print_parameters(&parameters);

	timeval t1, t2;
	double elapsed_time = 0.0f;
	gettimeofday(&t1, NULL);
	
	ullman::Isomorphism isomorphism(parameters.database, parameters.query, seperator.c_str());
	if (ULLMAN_SUCCESS != isomorphism.execute()) {
		fprintf(stderr, "not successful execution!");
		exit(ULLMAN_ERROR);
	}

	gettimeofday(&t2, NULL);
	elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0; 
	elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
	printf("elapsed time %f\n", elapsed_time);

	return 0;
}
