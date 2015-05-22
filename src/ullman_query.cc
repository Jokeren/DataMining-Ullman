#include "ullman.h"

namespace ullman {
	UllmanReturnCode Isomorphism::query()
	{
		_m_output.resize(_m_query.size());

		for (size_t i = 0; i < _m_query.size(); ++i) {
			Graph& query_graph = _m_query.get_graph(i);
			_m_cur_query_id = query_graph.get_id();
			build_matrix(matrix_a, query_graph);

			for (size_t j = 0; j < _m_database.size(); ++j) {
				Graph& entry_graph = _m_database.get_graph(j);
				_m_cur_graph_id = entry_graph.get_id();
#ifdef DEBUG
		printf("query_id %zu, graph_id %zu\n", _m_cur_query_id, _m_cur_graph_id);
		//printf("query_graph.size() %zu, entry_graph.size() %zu\n", query_graph.size(), entry_graph.size());
#endif 
				_m_columns.resize(query_graph.size(), entry_graph.size());
				_m_columns_used.resize(entry_graph.size(), -1);

				build_matrix(matrix_b, entry_graph);

				if (!construct_match(query_graph, entry_graph)) {
					_m_columns.clear();
					continue;
				}

#ifdef DEBUG
//		printf("%s\n", _m_columns.c_str());
	//	getchar();
	//	getchar();
#endif 
				_m_cur_find = false;
				for (size_t k = 0; k < _m_columns.size().second; ++k) {
					if (!_m_columns.get(0, k))
						continue;

					Matrix<bool> matrix = _m_columns;
					matrix.fill(0, 0);
					matrix.set(0, k, 1);

					_m_columns_used[k] = 0;

					dfs_search(1, matrix);

					_m_columns_used[k] = -1;
				}

				_m_columns_used.clear();
				_m_columns.clear();
			}
		}

		return ULLMAN_SUCCESS;
	}

	bool Isomorphism::construct_match(Graph& query_graph, Graph& entry_graph)
	{
		//prune : the size
		if (query_graph.size() > entry_graph.size())
			return false;

		const std::map<struct edge_label_list_t, std::vector<struct edge_t *> >& query_list = 
			query_graph.get_edge_label_map();
		std::map<struct edge_label_list_t, std::vector<struct edge_t *> >::const_iterator query_list_it = 
			query_list.begin();

		const std::map<struct edge_label_list_t, std::vector<struct edge_t *> >& entry_list = 
			entry_graph.get_edge_label_map();
		std::map<struct edge_label_list_t, std::vector<struct edge_t *> >::const_iterator entry_list_it = 
			entry_list.begin();
			
		while (query_list_it != query_list.end() && entry_list_it != entry_list.end()) {
			if (query_list_it->first < entry_list_it->first) {
				++query_list_it;
			} else if (entry_list_it->first < query_list_it->first) {
				++entry_list_it;
			} else {
				for (size_t i = 0; i < (query_list_it->second).size(); ++i) {
					struct edge_t *query_edge = (query_list_it->second)[i];
					size_t query_from = query_edge->from;	
					size_t query_to = query_edge->to;

					for (size_t j = 0; j < (entry_list_it->second).size(); ++j) {
						struct edge_t *entry_edge = (entry_list_it->second)[j];
						size_t entry_from = entry_edge->from;
						size_t entry_to = entry_edge->to;
						
						_m_columns.set(query_from, entry_from, 1);
						_m_columns.set(query_to, entry_to, 1);
					}

				}
				
				++entry_list_it;
				++query_list_it;
			} 
		}

		//prune : degree
		for (size_t i = 0; i < _m_columns.size().first; ++i) {
			for (size_t j = 0; j < _m_columns.size().second; ++j) {
				if (_m_columns.get(i, j) == 1) {
					size_t degree_from = query_graph.get_vertex(i).edges.size();
					size_t degree_to = entry_graph.get_vertex(j).edges.size();
					if (degree_to < degree_from)
						_m_columns.set(i, j, 0);
				}
			}
		}

		//prune : refine
		refine(_m_columns, 0);

#ifdef DEBUG
		//printf("after refine\n%s\n", _m_columns.c_str());
#endif

		//prune : the mapping of zeros
		for (size_t i = 0; i < _m_columns.size().first; ++i) {
			bool find = false;
			for (size_t j = 0; j < _m_columns.size().second; ++j) {
				if (_m_columns.get(i, j) == 1) {
					find = true;
					break;
				}
			}
			if (!find) {
				return false;
			}
		}

		return true;
	}

	void Isomorphism::dfs_search(size_t idx, Matrix<bool> matrix)
	{
		//prune 3: if only one of the mapping has found
		if (_m_cur_find)
			return;
#ifdef DEBUG
//		printf("idx %zu, size %zu\n", idx, _m_columns.size().first);
//		printf("query_id %zu, graph_id %zu\n", _m_cur_query_id, _m_cur_graph_id);
		//printf("%s\n", matrix.c_str());
#endif
		if (idx == matrix.size().first) {
			Matrix<bool> matrix_c = matrix * ((matrix * matrix_b).transposition());

#ifdef DEBUG
//		printf("idx %zu, size %zu\n", idx, _m_columns.size().first);
//		printf("query_id %zu, graph_id %zu\n", _m_cur_query_id, _m_cur_graph_id);
	//	printf("m\n%s\n", _m_columns.c_str());
	//	printf("b\n%s\n", matrix_b.c_str());
	//	printf("m * b\n%s\n", (_m_columns * matrix_b).c_str());
	//	printf("m * b.trans\n%s\n", ((_m_columns * matrix_b).transposition()).c_str());
	//	printf("m * m * b.trans\n%s\n", (_m_columns * ((_m_columns * matrix_b).transposition())).c_str());
//		printf("c\n%s\n", matrix_c.c_str());
//		printf("a\n%s\n", matrix_a.c_str());
#endif 

			if (judge(matrix_c)) {
				_m_cur_find = true;
				_m_output[_m_cur_query_id].push_back(_m_cur_graph_id);
			}
			
			return ;
		}

		refine(matrix, idx);
#ifdef DEBUG
		//printf("after refine\n%s\n", matrix.c_str());
#endif

		for (size_t i = 0; i < matrix.size().second; ++i) {
			if (_m_columns_used[i] != -1 || !matrix.get(idx, i))
				continue;

			Matrix<bool> next_matrix = matrix;
			next_matrix.fill(idx, 0);
			next_matrix.set(idx, i, 1);

			_m_columns_used[i] = idx;

			dfs_search(idx + 1, next_matrix);	

			_m_columns_used[i] = -1;
		}
	}

	bool Isomorphism::judge(const Matrix<bool>& matrix_c)
	{
		for (size_t i = 0; i < matrix_a.size().first; ++i) {
			for (size_t j = 0; j < matrix_a.size().second; ++j) {
				if (matrix_a.get(i, j) == 0)
					continue;

				if (matrix_c.get(i, j) == 0)	
					return false;
			}
		}

		return true;
	}

	void Isomorphism::refine(Matrix<bool>& matrix, size_t start)
	{
		const Graph& query_graph = _m_query.get_graph(_m_cur_query_id);

		//Todo: optimize refine
		while (true) {
			bool change = false;
			for (size_t i = start; i < matrix.size().first; ++i) {
				for (size_t j = 0; j < matrix.size().second; ++j) {
					if (matrix.get(i, j) == 0)
						continue;

					const struct vertex_t& vertex = query_graph.get_vertex(i);
					bool find = true;
					for (size_t k = 0; k < vertex.edges.size(); ++k) {
						size_t x = vertex.edges[k].to;

						bool non_zero = false;
						for (size_t y = 0; y < matrix.size().second; ++y) {
							if (matrix.get(x, y) && matrix_b.get(y, j)) {
								non_zero = true;
								break;
							}
						}

						if (!non_zero) {
							find = false;
							break;
						}
					}

					if (!find) {
						change = true;
						matrix.set(i, j, 0);
					}
				}
			}

			if (!change)
				break;
		}
	}

}//namespace ullman
