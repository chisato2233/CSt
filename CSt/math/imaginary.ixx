export module cst.math.imaginary;
import std;
import cst.print;

export namespace cst {

	struct imaginary {

		imaginary() = default;
		imaginary(long double x) : re(0), im(x) {}
		imaginary(long double x, long double y) : re(x), im(y) {}

		auto operator+=(const imaginary& rhs) ->imaginary&;
		auto operator-=(const imaginary& rhs) ->imaginary& ;
		auto operator*=(const imaginary& rhs) ->imaginary& ;

		auto operator+(const imaginary& rhs) const ->imaginary ;
		auto operator-(const imaginary& rhs) const ->imaginary ;
		auto operator*(const imaginary& rhs) const ->imaginary ;

		friend auto operator+(long double lhs, const imaginary& rhs) ->imaginary { return imaginary(lhs, 0) += rhs; }
		friend auto operator-(long double lhs, const imaginary& rhs) ->imaginary { return imaginary(lhs, 0) -= rhs; }
		friend auto operator*(long double lhs, const imaginary& rhs) ->imaginary { return imaginary(lhs, 0) *= rhs; }

		friend auto operator-(imaginary& rhs) ->imaginary { rhs.im = -rhs.im; rhs.re = -rhs.re; return rhs; }
		friend auto operator-(imaginary&& rhs) ->imaginary { return imaginary{0,0} - rhs; }

		long double mod() const { return std::sqrt(re * re + im * im); }

		long double re = 0;
		long double im = 0;
	};

	inline auto imaginary::operator+=(const imaginary& rhs) -> imaginary& {
		re += rhs.re;
		im += rhs.im;
		return *this;
	}

	inline auto imaginary::operator-=(const imaginary& rhs) -> imaginary& {
		re -= rhs.re;
		im -= rhs.im;
		return *this;
	}

	inline auto imaginary::operator*=(const imaginary& rhs) -> imaginary& {
		auto tmp = re * rhs.re - im * rhs.im;
		im = re * rhs.im + im * rhs.re;
		re = tmp;
		return *this;
	}

	inline auto imaginary::operator+(const imaginary& rhs) const -> imaginary {
		return imaginary(*this) += rhs;
	}

	inline auto imaginary::operator-(const imaginary& rhs) const -> imaginary {
		return imaginary(*this) -= rhs;
	}

	inline auto imaginary::operator*(const imaginary& rhs) const -> imaginary {
		return imaginary(*this) *= rhs;
	}


	inline auto operator""_i(unsigned long long x)->imaginary { return { static_cast<long double>(x) }; };
	inline auto operator""_i(long double x)->imaginary { return { x }; }

}

template<>
struct std::formatter<cst::imaginary>{
	
	constexpr auto parse(auto& ctx){
		auto it = ctx.begin();
		return it;
	}

	auto format(const cst::imaginary& vec, format_context& ctx) const {
		return std::format_to(ctx.out(), "{} + {}i", vec.re, vec.im);
	}
};




export namespace cst {
	
	inline auto test_imaginary() {
		std::cout << "\n test imaginary-----------------------------\n";
		auto i = 5 + 1.1_i;
		auto j = -1_i + 3;

		auto k = i - j;
		print(i,j);
		print('\n');
	}
}
/**
    format specification
    - 'j', as json array
    - 'X', same as std::format("{}x{}", vec.x, vec.y)
    - number, floating point precision, use `0` to format as integer
*/
