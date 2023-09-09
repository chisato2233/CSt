#include <iostream>
#include"print.h"
#include"graph.h"


struct X {
	int a = 1, b = 2, c = 3;
};
int main() {
	using namespace cst;
	graph<int,int> g{ 9 };
	g.build_edge_v(2, 3, 10);
	g.build_edge_v(4, 6, 9);
	g.insert_node_val(8, 5);
	
	for (auto& i : g) {
		print("node info:{} , {}\n",i.info, i.val);
	}
	for (auto& i : g.edges()) {
		auto& [from, to] = i.first;
		int val = i.second;
		print("from {},to {}, {}\n", from, to, g[{from,to}]);
	}
}