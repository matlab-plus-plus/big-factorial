#pragma once
#ifndef _bigfact_factorize_hpp
#define _bigfact_factorize_hpp

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <vector>

namespace bigfact::factorize
{
	/* Type Aliases */
	using prime_t = unsigned int;

	/* Allow user to configure the maximum prime at compile time. */
	// TODO: Replace below macro code with a CMake configure_file process.
	#ifndef BIGFACT_MAX_PRIME
	#define BIGFACT_MAX_PRIME 2003
	#endif

	inline constexpr prime_t first_prime{ 2u };
	inline constexpr prime_t max_prime{ static_cast<prime_t>(BIGFACT_MAX_PRIME) };

	#undef BIGFACT_MAX_PRIME

	constexpr bool is_prime(prime_t const v) noexcept
	{
		/*
			Returns true if the input is prime.
			Do not provide a number less than 2.
		*/
		for (prime_t iFChk = 2; iFChk * iFChk <= v; iFChk++)
		{
			if (v % iFChk == 0) return false;
		}
		return true;
	}

	constexpr std::vector<prime_t> gen_primes(
		prime_t const my_max_prime = max_prime
	) noexcept
	{
		/*
		* Computes the consecutive primes between 2 and my_max_prime (inclusive).
		* This works even if the given maximum value is itself not a prime.
		*/

		constexpr auto isprimefcn = [](auto const v) {return is_prime(v); };
		namespace views = std::views;
		namespace ranges = std::ranges;

		auto r = views::iota(first_prime, my_max_prime + 1)
			| views::filter(isprimefcn);

		std::vector<prime_t> v;
		ranges::copy(r, std::back_inserter(v));
		return v;
	}

	// The above and below constexpr prime code was heavily based on the
	// following Stackoverflow post:
	//	https://stackoverflow.com/a/72415591

	constexpr auto primes_num_vector = [] {return gen_primes(max_prime); };
	constexpr auto primes = [] {
		std::array<prime_t, primes_num_vector().size()> ret;
		std::ranges::copy(primes_num_vector(), ret.begin());
		return ret;
	}();
}

#endif