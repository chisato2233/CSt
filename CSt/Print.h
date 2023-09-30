#pragma once
#include<format>
#include<iostream>

namespace cst {
	

	void print(std::string_view s,auto&&... args) {
		std::cout << std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...));
	}
	void print_arg(auto&&... args) {
		int _[] {(std::cout << args << ' ',0)...};
	}

	void wprint(std::wstring_view ws,auto&&... args) {
		std::wcout << std::vformat(ws, std::forward<decltype(args)>(args)...);
	}
}
