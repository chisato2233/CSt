
#pragma once
#include<vector>
#include<iostream>
#include<map>
namespace cst {
	template<typename, typename>	struct graph;
	template<typename Val>	struct node_result { Val val{};	protected:node_result() = default; };
	template<>				struct node_result<void> {		protected:node_result() = default; };
							 
	template<typename,typename>		struct edge_result;
	template<typename N>			struct edge_result<void,N>{};
	
	template<typename,typename>		struct graph_interface;
	template<typename E>			struct graph_interface<E,void>{};


	template<typename EdgeVal=void,typename NodeVal=void>
	struct graph : graph_interface<EdgeVal,NodeVal> , edge_result<EdgeVal, NodeVal>{

		struct graph_node: node_result<NodeVal> {
			graph_node() {}
			
			size_t get_indegree()	const { return indegree; }
			size_t get_outdegree()	const { return to.size(); }
			size_t get_degree()		const { return indegree + to.size(); }
			
			auto begin()const { return to.begin(); }
			auto end()	const { return to.end(); }
			auto push_back(size_t info) { return to.push_back(info); }
			auto& operator[](size_t info) cosnt{ return to[info]; }
			
			std::vector<size_t> to;
			size_t info{}, indegree{};
		};

		explicit graph(size_t size) :data_(size) {
			size_t t = 0;
			for (auto& i : data_) i.info = t++;
		}

		void build_edge(size_t from,size_t to) {
			data_[from].push_back(to), data_[to].indegree++;
		}

		auto begin()const { return data_.begin(); }
		auto end()	const { return data_.end(); }
		auto& operator[] const(size_t i) { return data_[i]; }
		auto& operator[] const(std::pair<size_t, size_t> p) { return edge_result<NodeVal,EdgeVal>::operator[](p); }
	private:
		std::vector<graph_node> data_;
	};
	

	template<typename _,typename Val> struct graph_interface { //we don't care about the second template parameter.
		virtual void insert_node_val(size_t info,Val v) {
			auto& g_r = *dynamic_cast<graph<_,Val>*>(this);
			g_r[info].val = v;
		}
	protected:
		graph_interface() = default;
	};

	template<typename Val,typename _> struct edge_result { //the same as top.
		auto& edges() { return *this; }

		virtual void build_edge_v(size_t from, size_t to, Val val) {
			auto& g_r = *dynamic_cast<graph<Val,_>*>(this);
			g_r.build_edge(from, to), map_data_[{from, to}] = val;
		}
		Val& operator[](std::pair<size_t, size_t> pair) { return map_data_[pair]; }
		
		auto begin()const { return map_data_.begin(); }
		auto end()const { return map_data_.end(); }
		auto find(size_t from, size_t to) { return map_data_.find({ from,to }); }

	protected:
		edge_result() = default;
	private:
		std::map<std::pair<size_t, size_t>, Val> map_data_;
	};
}


