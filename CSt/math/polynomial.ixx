export module cst.math.polynomial;

import std;
export import cst.print;

export namespace cst {
	struct polynomial {
		friend class std::formatter<cst::polynomial>;
		char formatter_char = 'x';
		polynomial(char c = 'x') :formatter_char(c) { terms[0] = 0; }
		polynomial(std::initializer_list<std::pair<double, int>> il, char c = 'x') :formatter_char(c) {
			for (auto [k, v] : il) terms[v] += k;
		}

		template<typename  I> requires std::integral<I>|| std::floating_point<I>
		polynomial(I others) { terms[0] += others; }

		auto operator +=(const polynomial& other) & ->polynomial& ;
		auto operator -=(const polynomial& other) & ->polynomial& ;
		auto operator *=(const polynomial& other) & ->polynomial& ;


		auto operator +(const polynomial& other) & -> polynomial;
		auto operator -(const polynomial& other) & -> polynomial;
		auto operator *(const polynomial& other) & -> polynomial;



		auto begin() const { return terms.begin(); }
		auto end() const { return terms.end(); }
		auto& operator[](int v) { return terms[v]; }

		auto operator()(double) ;

		auto check_zero() {
			auto terms_copy = terms;
			for (auto& [v, k] : terms_copy) if (std::abs(k) < 1E-10) terms.erase(v);
			if (terms.empty()) terms[0] = 0;
		}

		friend auto operator~(const polynomial& p) -> polynomial {
			polynomial ret;
			for (auto& [v, k] : p) {
				if(v == 0) continue;
				ret[v - 1] += k * v;
			}
			ret.check_zero();
			return ret;
		}


		friend auto operator-(const polynomial& p)->polynomial {
			auto ret = p;
			ret.check_zero();
			for (auto& [v, k] : ret) ret[v] = -k;
			return ret;
		}

		std::map<int, double> terms;
	};


	inline auto polynomial::operator+=(const polynomial& other) & -> polynomial& {
		for(auto [ v , k] :other) terms[v] += k;
		check_zero();
		return *this;
	}

	inline auto polynomial::operator-=(const polynomial& other) & -> polynomial& {
		for (auto [v, k] : other) terms[v] -= k;
		check_zero();
		return *this;
	}

	inline auto polynomial::operator*=(const polynomial& other) & -> polynomial& {
		const polynomial ret = *this;
		for (auto [v1, k1] : ret) {
			for (auto [v2, k2] : other) {
				terms[v1 + v2] += k1 * k2;
			}
		}
		check_zero();
		return *this;
	}

	inline auto polynomial::operator+(const polynomial& other)  & -> polynomial {
		return *this+=other;
	}

	inline auto polynomial::operator-(const polynomial& other) & -> polynomial {
		return *this-=other;
	}

	inline auto polynomial::operator*(const polynomial& other) & -> polynomial {
		return *this *= other;
	}



	inline auto polynomial::operator()(double value)  {
		long double ret = 0;
		check_zero();
		for (auto& [v, k] : terms) {
			ret += k * std::pow(value, v);
		}
		return ret;
	}

	inline void test_polynomial(){
		std::cout << "\n test polynomial----------------------------------- \n";

		
		polynomial p1{ {1,2},{3.95,6} };

		polynomial p2{ {1,2},{-1,6},{-1,3} };
		auto pp = ~p2;


		print(p1);
		print(pp);


		std::cout << '\n';
	}
}


template<>
struct ::std::formatter<cst::polynomial>{
	constexpr auto parse(auto& ctx) { return ctx.begin(); }

	auto format(const cst::polynomial& p, auto& ctx) const{
		std::string ret;
		constexpr auto precision=1E-10;


		for (auto it = p.terms.rbegin(); it != p.terms.rend();++it) {
			auto&[v, k] = *it;
			
			std::string ret_k, ret_v;


			if (std::abs(k - 1) <= precision) ret_k = "";
			else if (std::abs(k + 1) <= precision) ret_k = "-";
			else ret_k = std::format("{}", k);

			if (v == 0) { ret_v="";}
			else { ret_v = std::format("[{}^{}]", p.formatter_char, v); }

			if(k<=0 && it!=p.terms.rbegin()) { ret.erase(ret.size() - 2, 2); ret += ' '; }

			ret += std::format("{}{}", ret_k, ret_v);
			ret += " +";
		}

		if (ret.size() >= 2) ret.erase(ret.size() - 2, 2);

		return std::format_to(ctx.out(),"[ {} ]", ret);
	}
};

