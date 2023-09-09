#include<vector>
#include<iostream>
#include<map>
namespace cst {
	template<typename Val>	struct graph;
	template<typename Val>	struct node_result { Val val{};	protected:node_result() = default; };
	template<>				struct node_result<void> {		protected:node_result() = default; };
							 
	template<typename Val>	struct edge_result;
	template<>				struct edge_result<void>{};
	
	template<typename Val>	struct graph_interface;
	template<>struct graph_interface<void>{};


	template<typename NodeVal=void>
	struct graph :graph_interface<NodeVal>{

		struct graph_node: node_result<NodeVal> {
			graph_node() {}
			
			size_t get_indegree()	const { return indegree; }
			size_t get_outdegree()	const { return to.size(); }
			size_t get_degree()		const { return indegree + to.size(); }
			
			auto begin()const { return to.begin(); }
			auto end()	const { return to.end(); }
			auto push_back(size_t info) { return to.push_back(info); }
			auto front()	const{ return to.front(); }
			auto back()		const{ return to.back(); }
			
			std::vector<size_t> to;
			size_t info{}, indegree{};
		};

		explicit graph(size_t size) :data_(size) {
			size_t t = 0;
			for (auto& i : data_) i.info = t++;
		}

		auto& build_edge(size_t from,size_t to) {
			data_[from].push_back(to), data_[to].indegree++;
			return *this;
		}

		auto begin()const { return data_.begin(); }
		auto end()	const { return data_.end(); }
		auto& operator[](size_t i) { return data_[i]; }
	
	private:
		std::vector<graph_node> data_;
	};
	
	template<typename Val> struct graph_interface {
		virtual graph<Val>& insert_node_val(size_t info,Val v) {
			auto& g_r = *dynamic_cast<graph<Val>*>(this);
			g_r[g_r[info].back()].val = v;
			return g_r;
		}
	protected:
		graph_interface() = default;
	};

	template<typename Val>struct edge_result {
		virtual graph<Val>& build_edge_v(size_t from, size_t to, Val val) {
			auto& g_r = *dynamic_cast<graph<Val>*>(this);
			g_r.build_edge(from, to), map_data_[{from, to}] = val;
			return g_r;
		}

		Val& operator[](std::pair<size_t,size_t> _edge) {
			return map_data_[_edge];
		}

		auto begin()const { return map_data_.begin(); }
		auto end()const { return map_data_.end(); }
		auto find(size_t from, size_t to) { return map_data_.find({ from,to }); }

	protected:
		edge_result() = default;
	private:
		std::map<std::pair<size_t, size_t>, Val> map_data_;
	};
}


