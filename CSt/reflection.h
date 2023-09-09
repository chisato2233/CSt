#pragma once
#include<any>
namespace cst {
	struct any { template<class T> operator T(); };


	template<class T>
	consteval size_t get_number_count(auto&&... args) {
		if constexpr (requires{T{args...}; }) {
			return get_number_count<T>(std::forward<decltype(args)>(args)..., any{});
		}
		else return sizeof...(args) - 1;
	}


	template<class T,class F,typename... Args>
	void for_each_numbers(const T& t,F f,Args... args) {
		if constexpr(get_number_count<T>()==3u) {
			auto [m1, m2, m3] = t;
			f(m1), f(m2), f(m3);
		}

	}
}