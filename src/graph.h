#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <algorithm>
#include "common.h"

namespace ullman {
	struct edge_t {
		size_t from;
		int32_t label;
		size_t to;
		size_t id;
	};

	struct vertex_t {
		size_t id;		
		int32_t label;
		std::vector<struct edge_t> edges;
	};
	typedef std::vector<struct vertex_t> Vertice;

	struct edge_label_list_t {
		size_t from_label;
		int32_t edge_label;
		size_t to_label;

		bool operator < (const struct edge_label_list_t& edge_label_list) const 
	   	{
			if (from_label != edge_label_list.from_label) {
				return from_label < edge_label_list.from_label;
			} else {
				if (edge_label != edge_label_list.edge_label) {
					return edge_label < edge_label_list.edge_label;
				} else {
					return to_label < edge_label_list.to_label;
				}
			}
		}
	};

	class Graph {
		public:
			explicit Graph() : id(0), _m_nedges(0) {};

			explicit Graph(size_t size) : id(0), _m_nedges(0), _m_vertice(size) {};

			size_t size() const
			{
				return _m_vertice.size();
			}

			void resize(size_t s)
			{
				_m_vertice.resize(s);
			}

			void set_id(size_t id) 
			{
				this->id = id;
			}

			size_t get_id() const
			{
				return id;
			}

			void set_nedges(size_t size)
			{
				_m_nedges = size;
			}

			size_t get_nedges() const
			{
				return _m_nedges;
			}

			void set_vertice(const Vertice& vertice) 
			{
				this->_m_vertice = vertice;
			}

			struct vertex_t& get_vertex(size_t idx) {
				return _m_vertice[idx];
			}

			const struct vertex_t& get_vertex(size_t idx) const {
				return _m_vertice[idx];
			}

			const std::map<struct edge_label_list_t, std::vector<struct edge_t *> >& get_edge_label_map();

			const std::map<int32_t, std::vector<size_t> > get_vertex_label_map(); 

			void clear()
			{
				id = 0;
				_m_vertice.clear();
			}

			void sort_vertex_by_degree() {
				std::sort(_m_vertice.begin(), _m_vertice.end(), sort_vertex);
			}

		private:
			struct sort_vertex_t {
				bool operator () (const struct vertex_t& vertex_a,
						const struct vertex_t& vertex_b)
				{
					return vertex_a.edges.size() > vertex_b.edges.size();
				}
			} sort_vertex;

			void construct_edge_label_map();

			void construct_vertex_label_map();

		private:
			size_t _m_nedges;
			size_t id;
			Vertice _m_vertice;
			std::map<struct edge_label_list_t, std::vector<struct edge_t *> > _m_edge_label_map;
			std::map<int32_t, std::vector<size_t> > _m_vertex_label_map;
	};
}//namespace ullman

#endif
