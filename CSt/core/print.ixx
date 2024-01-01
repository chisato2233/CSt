export module cst.print;

import std;
export namespace cst {

	inline void print(const char s) { std::cout << s; }

	inline void print(const char* s,auto&&... args) {
		std::cout << std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...));
	}

	inline void print(auto&&... args) {
		(
			(std::cout << std::format("{} ",std::forward<decltype(args)>(args))) , ... 
		);
	}

	inline void test_print() {
		print("test print\n");

		std::string_view s = "hello";
		print(s,1, 1.5, "psfpf");

		std::cout << '\n';
	}
}
