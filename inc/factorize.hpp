#pragma once
#ifndef _bigfact_factorize_hpp
#define _bigfact_factorize_hpp

#include "math/log.hpp"

#include <algorithm>
#include <array>
#include <compare>
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

	constexpr std::array<prime_t, primes.size()> factor(prime_t const n)
	{
		/*
		* Compute prime factorization of ``n`` stored in a dense array representation.
		*/
		namespace views = std::views;
		namespace ranges = std::ranges;

		std::array<prime_t, primes.size()> prime_factor_exponents{};

		// Need all factors zeroed-out by default.
		prime_factor_exponents.fill(0u);

		// TODO: Check if n > primes.back()

		constexpr auto prime_indices = views::iota(0u,
			primes.size());

		auto n_ = n; // Intentional copy into mutable var
		for (auto const ii : prime_indices)
		{
			auto const curPrime = primes.at(ii);

			while (n_ % curPrime == 0u)
			{
				prime_factor_exponents.at(ii)++;
				n_ /= curPrime;
			}

			if (n_ == 1u) break;
		}

		return prime_factor_exponents;
	}

	struct prime_power;
	constexpr double log(prime_power const) noexcept;

	struct prime_power
	{
		prime_t prime_val{};
		std::size_t prime_pow{};

		prime_power() = delete;

		constexpr prime_power(prime_t val, std::size_t pow) noexcept
			: prime_val(val), prime_pow(pow) {}

		constexpr auto operator <=>(prime_power const rhs) const noexcept
		{
			return log(*this) <=> log(rhs);
		}
	};

	constexpr double log(prime_power const pp) noexcept
	{
		/*
		* Computes the natural logarithm of a prime_power object.
		*/
		return static_cast<double>(pp.prime_pow) *
			bigfact::math::log(static_cast<double>(pp.prime_val));
	}

	class factorization
	{
		/*
		* A dense representation of a number using its prime factorization.
		*/
	public: // Should this be private?
		std::array<prime_t, primes.size()> prime_factor_exponents{};
	public:
		constexpr explicit factorization(prime_t const n)
			: prime_factor_exponents(factor(n))	{}
	};
}

#endif