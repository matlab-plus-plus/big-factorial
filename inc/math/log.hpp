/*
* Compile-time function to compute the natural logarithm.
*/

#include <limits>
#include <numbers>
#include <numeric>

namespace bigfact::_math
{
	/* Internal namespace for log util. */
	constexpr double sqrt(double const v)
	{
		/*
		* Computes the square root of a number using Goldschmidt's algorithm.
		* https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Goldschmidt%E2%80%99s_algorithm
		*/
		
		double y{ 0.3 }; // 0.3 is an initial guess of 1/sqrt(v)
		double h{ y / 2.0 };
		double x{ v * y };

		double r{ 1.0 }; // Arbitrary; number > 0
		do
		{
			r = 0.5 - x * h;
			x = x + x * r;
			h = h + h * r;
		} while (r > std::numeric_limits<double>::epsilon());

		return x;
	}
	
	constexpr double abs(double const v) noexcept
	{
		/*
		* Computes the absolute value of a number.
		*/
		return (v < 0.0) ? -v : v;
	}

	constexpr double agm(double const x1, double const x2) noexcept
	{
		/*
		* Computes the arithmetic-geometric mean of x1 and x2.
		*/
		double am{ x1 }, gm{ x2 }; // assignment of x1 to am & v2 to gm is arbitrary.
		double tmpAM;

		auto const cur_diff = [&am, &gm] {return abs(am - gm); };
		while (cur_diff() > std::numeric_limits<double>::epsilon())
		{
			tmpAM = std::midpoint(am, gm);
			gm = sqrt(am * gm);
			am = tmpAM;
		}

		return am; // Arbitrary, as am == gm within epsilon (i.e. we could have returned gm instead).
	}
}

namespace bigfact::math
{
	constexpr double log(double const v)
	{
		/*
		* Computes the natural logarithm of v using a high-precision formula:
		* https://en.wikipedia.org/wiki/Natural_logarithm#High_precision
		*/
		constexpr double m{ 29 };
		constexpr auto two_pow = [](auto const pow) {return 1 << static_cast<int>(pow); };

		double const s{ v * two_pow(m) };
		
		return std::numbers::pi / (2.0 * bigfact::_math::agm(1, 4.0 / s)) - m * std::numbers::ln2;
	}
}