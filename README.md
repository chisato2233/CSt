# CSt

# Introduction

Hello!!! This is a template C++ code for algorithm. I  will put some very useful data struct bases which standard library has not implemented yet here, for developers to use. Most of these structs is simple and clear so you can put them in your project and change it to whatever you what easily.  



# Quick Guide

## cst::print     [function]

``` c++
auto cst::print(std::string_view s,auto&&... args)->void
```

A formatter print function with std::vformat in c++20.

template:

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



## cst::graph     [struct]

```c++
template<NodeVal = void,EdgeVal = void>  
struct graph 
```

A struct build graph implemented by using Adjacency List. 

The template parameter NodeVal and EdgeVal is entirely optional. That means if you do not put any parameter, they will not give you any extra overhead. If you what to build a graph which can store wight in node or edge, you can put them in NodeVal or EdgeVal. That will change some part of the graph and you will get some new  function which can help you use the graph easily.

### [member function]: 

- begin() / end() return the vector iterator of graph data.

- graph&

