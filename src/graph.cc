#include "graph.h"

namespace ullman {
	const std::map<int32_t, std::vector<size_t> > Graph::get_vertex_label_map()
	{
		if (!_m_vertex_label_map.size()) {
			construct_vertex_label_map();
		}

		return _m_vertex_label_map;
	}

	void Graph::construct_vertex_label_map()
	{
		for (size_t i = 0; i < _m_vertice.size(); ++i) {
			_m_vertex_label_map[_m_vertice[i].label].push_back(_m_vertice[i].id);
		}
	}

	const std::map<struct edge_label_list_t, std::vector<struct edge_t *> >&
	   	Graph::get_edge_label_map()
	{
		if (!_m_edge_label_map.size()) {
			construct_edge_label_map();
		}

		return _m_edge_label_map;
	}

	//Todo
	void Graph::construct_edge_label_map()
	{
		for (size_t i = 0; i < _m_vertice.size(); ++i) {
			for (size_t j = 0; j < _m_vertice[i].edges.size(); ++j) {
				struct edge_t *edge = &_m_vertice[i].edges[j];			
				
				struct edge_label_list_t edge_label_list;
				edge_label_list.from_label = _m_vertice[edge->from].label;
				edge_label_list.edge_label = edge->label;
				edge_label_list.to_label = _m_vertice[edge->to].label;

				_m_edge_label_map[edge_label_list].push_back(edge);
			}
		}	
	}
}//namespace ullman
