#include "factorize.hpp"

// TMP
#include <iostream>

int main(void)
{

	for (auto const x = bigfact::factorize::primes;
		auto const p : x)
	{
		std::cout << p << "\n";
	}

	return 0;
}