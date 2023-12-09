#pragma once
#include<vector>
#include<functional>
#include <iostream>
#include <ostream>

namespace cst {

	struct delegate_base {};


	template<typename R> struct delegate_result { using type = std::vector<R>;};

	template<>
	struct delegate_result<void> {
		using type = void;
	};


	template<class R = void, class... Args>
	struct delegate : delegate_base {
		template<std::invocable<Args...> F>
		auto operator+=(F&& f)-> delegate& {
			funcs_.push_back(std::forward<F>(f));
			return *this;
		}

		auto operator-=(R(*f)(Args...))-> delegate& {
			funcs_.remove_if([f](auto& fun) {
				auto p = fun.template target<R(*)(Args...)>();
				if (p&&*p == f) {
					return true;
				}
				return false;
			});

			return *this;
		}

		auto operator()(Args&&... args) -> typename delegate_result<R>::type {
			if constexpr (std::is_same_v<R, void>) {
				for (auto& i : funcs_) {
					i(std::forward<Args>(args)...);
				}
				return;
			}

			else {
				std::vector<R> result;
				for (auto& i : funcs_) {
					result.emplace_back(i(std::forward<Args>(args)...));
				}
				return result;
			}
		}
	private:
		std::list<std::function<R(Args...)>> funcs_;
	};












	inline int foo(int) { std::cout << "Foo" << std::endl; return 0; }
	std::function<int(int)> f1 = [](int a) {return a + 1; };


	inline void test_delegate() {
		delegate<int,int> d;
		delegate<> d2; 
		auto f2 = [](int a) {return a + 2; };
		
		d += f1;
		d += f2;
		d += [](int a) {return a + 3; };
		d += foo;
		
		auto i = d(1);
		d2+=[] {
			std::cout << "Hello" << std::endl;
		};
		d2();

		for(auto ii:i) std::cout << ii << std::endl;

		
		d -= foo;
		
		auto i2 = d(1);
		for(auto ii:i2) std::cout << ii << std::endl;
		
	}

}
