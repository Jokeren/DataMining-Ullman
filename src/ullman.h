#ifndef ULLMAN_H
#define ULLMAN_H
#include <set>
#include "graph.h"
#include "matrix.h"
#include "seperator.h"
#include "common.h"

namespace ullman {
	class Graph;

	class Database {
		public:
			void push_graph(const Graph& graph)
			{
				graphs.push_back(graph);
			}

			const Graph& get_graph(size_t id) const
			{
				return graphs[id];		
			}			

			Graph& get_graph(size_t id) 
			{
				return graphs[id];		
			}			

			size_t size() const 
			{
				return graphs.size();
			}

			void sort()
			{
				for (size_t i = 0; i < graphs.size(); ++i)
					graphs[i].sort_vertex_by_degree();
			}

		private:
			std::vector<Graph> graphs;
	};

	class Isomorphism {
		public:
			explicit Isomorphism(const char *database, const char *query, const char *sep_type) :
				_m_file_data(database), _m_file_query(query) , _m_seperator(sep_type) {};

			UllmanReturnCode execute();	

		private:			
			UllmanReturnCode read_input(const Buffer& input, Database& database);

			UllmanReturnCode query();

			bool construct_match(Graph& query_graph, Graph& entry_graph);

			void dfs_search(size_t idx, Matrix<bool> matrix);

			void build_matrix(Matrix<bool>& matrix, size_t nrows, size_t ncolumns);

			void build_matrix(Matrix<bool>& matrix, const Graph& graph);

			bool judge(const Matrix<bool>& matrix);

			void refine(Matrix<bool>& matrix, size_t start);

			UllmanReturnCode output();

		private:
			const char *_m_file_data;
			const char *_m_file_query;
			Seperator _m_seperator;

			Database _m_database;
			Database _m_query;
			//whether current columns are used
			Matrix<bool> _m_columns;
			//whether all the possible olumns 
			std::vector<int32_t> _m_columns_used;
			//corresponding matrix b
			Matrix<bool> matrix_b;
			//corresponding matrix a
			Matrix<bool> matrix_a;

			std::vector<std::vector<size_t> > _m_output;

			size_t _m_cur_graph_id;
			size_t _m_cur_query_id;
			bool _m_cur_find;
	};
}//namespace ullman

#endif

