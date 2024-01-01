# CSt

# Introduction

Hello!!! This is a template C++ code for algorithm. I  will put some very useful data struct bases which standard library has not implemented yet here, for developers to use. Most of these structs is simple and clear so you can put them in your project and change it to whatever you what easily.  



# Quick Guide

## cst::print     [function]

``` c++
auto cst::print(std::string_view s,auto&&... args)->void
```

A formatter print function with std::vformat in c++20.



```c++
#include<Print.h>
int main(){
	int a=1;
	std::string s="!!";
	cst::print("Hello World {},{},{}",a,s,2); //Hello World 1 !! 2
}

```

source  (in Print.h)

```c++
#include<format>
#include<iostream>
namespace cst {
	void print(std::string_view s,auto&&... args) {
		std::cout << std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...));
	}
	void wprint(std::wstring_view ws,auto&&... args) {
		std::wcout << std::vformat(ws, std::forward<decltype(args)>(args)...);
	}
}
```
## cst::delegate     [struct]

``` c++
template<typename R, typename... Args>
struct delegate
```
A struct delegate which action is close to C#

### Test Usage:
``` c++
	inline int foo(int i) {
		std::cout << "Hello world foo" << std::endl;
		return i * 1;
	}

	inline void test_delegate() {
		delegate<int, int> d; 	//declare delegate with: 
								//return type int and 
								//arguments int

		//a functional in C++ 17
		std::function<int(int)> f = [](int i) {
			std::cout << "Hello world" << std::endl;
			return i * 2;
		};

		d += f;		//register to delegate

		d += foo;	//registrite function point

		auto p = d(114514);	// call all the function that be registered.
							// p: vector<int>

		for(auto i:p) std::cout<< i << std::endl;
	}
	/*
	* Hello world
	* Hello world foo
	* 229028
	* 114514
	*/
	

```


## cst::graph     [struct]

```c++
template<NodeVal = void,EdgeVal = void>  
struct graph 
```

A struct build graph implemented by using Adjacency List. 

The template parameter NodeVal and EdgeVal is entirely optional. That means if you do not put any parameter, they will not give you any extra overhead. If you what to build a graph which can store wight in node or edge, you can put them in NodeVal or EdgeVal. That will change some part of the graph and you will get some new  function which can help you use the graph easily.

### [useful member function]: 

- explicit graph(size_t size) explicit constructor is to ensure you know that the graph's node size is recommended not to change.

- begin() / end() return the vector iterator of graph data. This two function ensure struct graph can be for_each in range library.

- void build_edge(size_t from , size_t to) build a edge .

- graph_node& operator[](size_t info); get the node info of the graph. The graph_node is a sub-struct in graph,it contain some basic information and the what the node to.

	```c++
	#inlcude<graph.h>
	int main(){
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
	
	//output:
	/*
	Node 0: 2,
	Node 1:
	Node 2:
	Node 3:
	Node 4: 5,
	Node 5: 4,
	Node 6:
	Node 7: 8,3,
	Node 8:
	*/
	```

- 