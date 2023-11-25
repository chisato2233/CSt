#pragma once
#include <complex>
#include <iostream>
#include <map>

namespace cst {
	struct polynomial {
		polynomial() { terms[0] = 0; }
		polynomial(std::initializer_list<std::pair<double, int>> il) {
			terms.clear();
			for (auto [k, v] : il) terms[v] += k;
		}

		template<typename  I> requires std::integral<I>|| std::floating_point<I>
		polynomial(I others) { terms[0] += others; }

		auto operator +=(const polynomial& other) & ->polynomial& ;
		auto operator -=(const polynomial& other) & ->polynomial& ;
		auto operator *=(const polynomial& other) & ->polynomial& ;


		auto operator +(const polynomial& other) const & -> polynomial;
		auto operator -(const polynomial& other) const & -> polynomial;
		auto operator *(const polynomial& other) const & -> polynomial;

		friend auto operator*(const polynomial& p) -> polynomial {
			polynomial ret;
			for (auto& [v, k] : p) {
				if(v == 0) continue;
				ret[v - 1] += k * v;
			}
			return ret;
		}


		auto begin() const { return terms.begin(); }
		auto end() const { return terms.end(); }
		auto& operator[](int v) { return terms[v]; }
		auto operator()(double v) const;

	private:
		std::map<int, double> terms;
	};









	inline auto polynomial::operator+=(const polynomial& other) & -> polynomial& {
		for(auto [ v , k] :other) terms[v] += k;
		return *this;
	}

	inline auto polynomial::operator-=(const polynomial& other) & -> polynomial& {
		for (auto [v, k] : other) terms[v] -= k;
		return *this;
	}

	inline auto polynomial::operator*=(const polynomial& other) & -> polynomial& {
		polynomial ret;
		for (auto [v1, k1] : *this) {
			for (auto [v2, k2] : other) {
				ret.terms[v1 + v2] += k1 * k2;
			}
		}
		*this = ret;
		return *this;
	}

	inline auto polynomial::operator+(const polynomial& other) const & -> polynomial {
		polynomial ret = *this;
		ret += other;
		return ret;
	}

	inline auto polynomial::operator-(const polynomial& other) const & -> polynomial {
		polynomial ret = *this;
		ret -= other;
		return ret;
	}

	inline auto polynomial::operator*(const polynomial& other) const & -> polynomial {
		polynomial ret = *this;
		ret *= other;
		return ret;
	}

	inline auto polynomial::operator()(double v) const {
		long double ret = 0;
		for (auto& [k, v1] : terms) {
			ret += v1 * std::pow(v, k);
		}
		return ret;
	}

	inline void test_polynomial(){

		polynomial p1{ {1,2},{3.95,6} };

		polynomial p2{ {1,2},{1,6} };
		auto pp = *p2;
		
		auto d = (*p2)(1);
		std::cout << "dasdasd"<< d << std::endl;
	}
}
