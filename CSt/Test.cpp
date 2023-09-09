#include <iostream>
#include"print.h"
#include"graph.h"


struct X {
	int a = 1, b = 2, c = 3;
};
int main() {
	using namespace cst;
	graph<int> g{ 9 };
	g.insert_v(1, 2, 5).insert_v(2, 1, 5);
	for (auto& i : g) {
		print("from {} , {}\n ",i.info, i.val);
	}
}