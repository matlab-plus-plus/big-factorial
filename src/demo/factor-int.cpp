#include "factorize.hpp"

#include <iostream>
#include <string>

int main(unsigned int const argc, char** const argv)
{
	if ((argc == 1u) || (argc > 2))
	{
		std::cout << "Provide a single integer input.\n";
		return 1;
	}

	auto const int_str_in = std::string(argv[1]);
	auto const f1 = bigfact::factorize::factorization(
		std::stoi(int_str_in)
	);

	std::cout << 1; // All numbers have 1 as a factor.

	for (auto const ii : std::views::iota(0u, bigfact::factorize::primes.size()))
	{
		auto const pv = bigfact::factorize::primes[ii];
		auto const pp = f1.prime_factor_exponents[ii];
		if (pp > 0u)
			std::cout << " * " << pv << '^' << pp;
	}

	std::cout << "\n";

	return 0;
}