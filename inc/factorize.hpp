#pragma once
#ifndef _bigfact_factorize_hpp
#define _bigfact_factorize_hpp

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <vector>

namespace
{
	constexpr bool is_prime(std::size_t const v) noexcept
	{
		/*
			Returns true if the input is prime.
			Do not provide a number less than 2.
		*/
		for (std::size_t iFChk = 2; iFChk * iFChk <= v; iFChk++)
		{
			if (v % iFChk == 0) return false;
		}
		return true;
	}
}

namespace bigfact::factorize
{
	/* Allow user to configure the maximum prime at compile time. */
	#ifndef BIGFACT_MAX_PRIME
	#define BIGFACT_MAX_PRIME 2003
	#endif

	inline constexpr std::size_t first_prime{ 2u };
	inline constexpr std::size_t max_prime{ static_cast<std::size_t>(BIGFACT_MAX_PRIME) };

	#undef BIGFACT_MAX_PRIME

	constexpr std::vector<std::size_t> primes(
		std::size_t const my_max_prime = max_prime
	) noexcept
	{
		constexpr auto isprimefcn = [](auto const v) {return is_prime(v); };

		auto r = std::views::iota(
			bigfact::factorize::first_prime,
			my_max_prime)
			| std::views::filter(isprimefcn);

		std::vector<std::size_t> v;
		std::ranges::copy(r, std::back_inserter(v));
		return v;
	}
}

#endif