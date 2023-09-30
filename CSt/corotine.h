#pragma once
// ReSharper disable All
#include<coroutine>
#include<functional>


namespace cst {
	namespace details {
		template<typename R>
		struct return_func {
			decltype(auto) return_val(R&& v) { return (std::forward<R>(v)); }
		};
		template<>struct return_func<void> { void return_void() {} };
	}

	template<typename R = void, bool is_soon_start = false>
	struct co_task {
		struct co_task_promise;
		using promise_type = co_task_promise;
		using co_handle = std::coroutine_handle<promise_type>;

	private:
		co_handle self;
	public:
		co_task(co_handle _h) :self{ _h } { }
		co_task(co_task&& other)noexcept :self{ other.self } { other.~co_task(); }
		co_task& operator= (co_task&& other) {
			self = other.self;
			other.~co_task();
			return *this;
		}

		~co_task() { self.destroy(); }

		struct co_task_promise : details::return_func<R> {
			constexpr auto initial_suspend()const noexcept {
				struct awaiter {
					[[nodiscard]] constexpr auto await_ready() const noexcept { return is_soon_start; }
					constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}
					constexpr void await_resume() const noexcept {}
				};
				return awaiter{};
			}

			constexpr auto final_suspend()noexcept { return std::suspend_always{}; }
			auto get_return_object() { return co_task<R, is_soon_start>{co_handle::from_promise(*this)}; }
			void unhandled_exception() const noexcept {};
		};

		bool done() { return self.done(); }
		void resume() { self.resume(); }
	};

	template<typename F, typename... Args>
		requires std::invocable<F, Args...>
	struct task_awaiter {
		task_awaiter(F f, Args&&... args):func(f),args(std::forward<Args>(args)...) {}


		constexpr auto await_ready() { return false; }
		constexpr decltype(auto) await_suspend(std::coroutine_handle<>)const noexcept { return std::apply(func, args); }
		constexpr auto await_resume()const noexcept {}
		
		F func;
		std::tuple<Args...> args;
	};

	struct generator : co_task<int> {
		struct generator_promise;
		using promise_type = generator_promise;
		generator(co_handle _h) :co_task(_h) { }

		struct generator_promise : co_task_promise {
			auto get_return_object() { return generator{ co_handle::from_promise(*this) }; }
		};
	};
}
