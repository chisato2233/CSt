export module cst.delegate;
import std;

export namespace cst {
	struct delegate_base { };
	template<typename R> struct delegate_result {
		using type = typename std::vector<R>;
	};

	template<> struct delegate_result<void> {
		using type = void;
	};

	template<typename R, typename... Args>
	struct delegate {
		template<std::invocable<Args...> F>
		auto operator+=(F&& f) {

			funcs_.push_back(std::forward<F>(f));
			return *this;
		}

		auto operator-=(R(*f)(Args...)) {
			funcs_.remove_if([f](auto&& it) {
				auto p = it.template target<R(*)(Args...)>();
				if (p && p == f) return true;
				return false;
				});
			return *this;
		}

		auto operator()(Args&&... args) ->typename delegate_result<R>::type {
			if constexpr (std::is_void_v<R>) {
				for (auto&& f : funcs_) {
					f(std::forward<Args>(args)...);
					return;
				}
			}
			else {
				std::vector<R> rets;
				rets.reserve(funcs_.size());
				for (auto&& f : funcs_) {
					rets.push_back(f(std::forward<Args>(args)...));
				}
				return rets;
			}
		}

	private:
		std::list<std::function<R(Args...)>> funcs_;
	};



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
}