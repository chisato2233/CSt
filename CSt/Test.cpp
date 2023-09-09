#include <iostream>
#include"print.h"
#include"graph.h"


int main() {
	cst::graph g{ 9 };
	g.build_edge(4, 5), g.build_edge(5, 4);
	g.build_edge(7, 8), g.build_edge(7, 3);
	g.build_edge(0, 2);
	for (const auto& i : g) {
		//i is graph_node&, a sub-struct in graph.
		cst::print("Node {}: ", i.info);
		for (const auto info : i)cst::print("{},", info);
		cst::print("\n");
	}
}

