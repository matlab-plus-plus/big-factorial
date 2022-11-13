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

	for (auto const pp : f1.to_sparse_repr())
	{
		std::cout << " * " << pp.prime_val << '^' << pp.prime_pow;
	}

	std::cout << "\n";

	return 0;
}