#include "sys/time.h"
#include "ullman.h"

namespace ullman {
	UllmanReturnCode Isomorphism::execute()
	{
		Buffer ullman_database;
		Buffer ullman_query;

		_m_seperator.seperate(_m_file_data, ullman_database);
		_m_seperator.seperate(_m_file_query, ullman_query);

		if (ULLMAN_SUCCESS != read_input(ullman_database, _m_database)) {
			fprintf(stderr, "read input database error!\n");
			return ULLMAN_ERROR;
		}

		//To-do: sort the vertices 

		if (ULLMAN_SUCCESS != read_input(ullman_query, _m_query)) {
			fprintf(stderr, "read input query error!\n");
			return ULLMAN_ERROR;
		}

		timeval t1, t2;
		double elapsed_time = 0.0f;
		gettimeofday(&t1, NULL);

		if (ULLMAN_SUCCESS != query()) {
			fprintf(stderr, "find isomorphism error!\n");
			return ULLMAN_ERROR;
		}			

		gettimeofday(&t2, NULL);
		elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0; 
		elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
		//printf("elapsed time->execute %f\n", elapsed_time);

		if (ULLMAN_SUCCESS != output()) {
			fprintf(stderr, "output error!\n");
			return ULLMAN_ERROR;
		}

		return ULLMAN_SUCCESS;
	}

	UllmanReturnCode Isomorphism::read_input(const Buffer& buffer, Database& database)
	{
		Graph graph;
		Vertice vertice;

		size_t graph_idx = 0;
		size_t edge_id = 0;
		for (size_t i = 0; i < buffer.size(); ++i) {
			if (buffer[i][0] == "t") {
				if (i != 0) {
					graph.set_nedges(edge_id);
					graph.set_vertice(vertice);
					edge_id = 0;
					database.push_graph(graph);	
					graph.clear();
					vertice.clear();
				}

				char indicator, seperator;
				size_t idx;
				indicator = buffer[i][0][0];
				seperator = buffer[i][1][0];
				sscanf(buffer[i][2].c_str(), "%zu", &idx);

				if (graph_idx != idx) {
					fprintf(stderr, "reading buffer warning! %zu %zu\n", graph_idx, idx);	
					return ULLMAN_WARNING;
				}
				//debug
				//printf("t # %zu\n", idx);

				graph.set_id(idx);
				++graph_idx;
			} else if (buffer[i][0] == "v") {
				char indicator;
				size_t id;
				int32_t label;
				indicator = buffer[i][0][0];
				sscanf(buffer[i][1].c_str(), "%zu", &id);
				sscanf(buffer[i][2].c_str(), "%d", &label);
				//debug
				//printf("v %zu %d\n", id, label);

				struct vertex_t vertex;
				vertex.id = id;
				vertex.label = label;	

				vertice.push_back(vertex);
			} else if (buffer[i][0] == "e") {
				char indicator;
				size_t from, to;
				int32_t label;
				indicator = buffer[i][0][0];
				sscanf(buffer[i][1].c_str(), "%zu", &from);
				sscanf(buffer[i][2].c_str(), "%zu", &to);
				sscanf(buffer[i][3].c_str(), "%d", &label);
				//debug
				//printf("e %zu %zu %d\n", from, to, label);

				struct edge_t edge;
				edge.from = from;
				edge.to = to;
				edge.label = label;
				edge.id = edge_id;
				++edge_id;

				//first edge
				vertice[from].edges.push_back(edge);

				//second edge
				edge.from = to;
				edge.to = from;
				vertice[to].edges.push_back(edge);
			} else {
				fprintf(stderr, "reading buffer warning!\n");	
			}
		}

		graph.set_vertice(vertice);
		database.push_graph(graph);	

		return ULLMAN_SUCCESS;
	}

	UllmanReturnCode Isomorphism::output()
	{
		size_t sum = 0;
		for (size_t i = 0; i < _m_output.size(); ++i) {
			printf("t # %zu : %zu\n", i, _m_output[i].size());
			sum += _m_output[i].size();
			for (size_t j = 0; j < _m_output[i].size(); ++j) {
				printf("%zu ", _m_output[i][j]);
			}
			printf("\n\n");
		}
		printf("\nsum: %zu\n", sum);

		return ULLMAN_SUCCESS;
	}

}//namespace ullman
