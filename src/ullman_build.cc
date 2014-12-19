#include "ullman.h"

namespace ullman {
	//Todo
	void Isomorphism::build_matrix(Matrix<bool>& matrix, size_t nrows, size_t ncolumns)
	{
		matrix.clear();
		matrix.resize(nrows, ncolumns);

		for (size_t i = 0; i < _m_columns_used.size(); ++i) {
			if (_m_columns_used[i] != -1)
				matrix.set(_m_columns_used[i], i, 1);
		}	
	}

	//Todo
	void Isomorphism::build_matrix(Matrix<bool>& matrix, const Graph& graph)
	{
		matrix.clear();
		matrix.resize(graph.size(), graph.size());	

		for (size_t i = 0; i < graph.size(); ++i) {
			const struct vertex_t& vertex = graph.get_vertex(i);
			size_t from_id = vertex.id;

			for (size_t j = 0; j < vertex.edges.size(); ++j) {
				size_t to_id = vertex.edges[j].to;
				matrix.set(from_id, to_id, 1);
			}
		}
	}
}//namespace ullman
