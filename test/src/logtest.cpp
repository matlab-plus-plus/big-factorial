#include "math/log.hpp"

#include <cmath>
#include <numbers>
#include <gtest/gtest.h>

TEST(LogEquivalenceTests, TestLogOfOne)
{
	EXPECT_EQ(bigfact::math::log(1.0), 0.0) <<
		"Log of 1 should be zero.";
}

TEST(LogDependencyTests, TestSqrt)
{
	EXPECT_EQ(bigfact::_math::sqrt(1.0), 1.0);
	EXPECT_EQ(bigfact::_math::sqrt(4.0), 2.0);

	EXPECT_DOUBLE_EQ(bigfact::_math::sqrt(2.0), std::numbers::sqrt2) <<
		"Square root of 2 not equal";
	EXPECT_DOUBLE_EQ(bigfact::_math::sqrt(3.0), std::numbers::sqrt3) <<
		"Square root of 3 not equal.";
}

TEST(LogDependencyTests, TestAMGM)
{
	/*
	* Values taken from https://mathworld.wolfram.com/Arithmetic-GeometricMean.html
	*/
	constexpr auto amgm_1 = [](auto const v) {return bigfact::_math::am_gm(1.0, v); };

	EXPECT_DOUBLE_EQ(amgm_1(2.0), 1.456'791'031'046'906'869'2) <<
		"The arithmetic-geometric mean of 1 and 2 failed.";
	EXPECT_DOUBLE_EQ(amgm_1(3.0), 1.863'616'783'244'896'542'4) <<
		"The arithmetic-geometric mean of 1 and 3 failed.";
	EXPECT_DOUBLE_EQ(amgm_1(4.0), 2.243'028'580'287'602'570'1) <<
		"The arithmetic-geometric mean of 1 and 4 failed.";
	EXPECT_DOUBLE_EQ(amgm_1(5.0), 2.604'008'190'530'940'288'7) <<
		"The arithmetic-geometric mean of 1 and 5 failed.";
}

TEST(LogDependencyTests, TestAGMEqualValues)
{
	/*
	* Ensure the AGM returns the same value when both inputs are the same.
	*/

	constexpr auto agm_same = [](auto const v) {return bigfact::_math::am_gm(v, v); };

	EXPECT_EQ(agm_same(1.0), 1.0);
	EXPECT_EQ(agm_same(10.0), 10.0);
	EXPECT_EQ(agm_same(11.0), 11.0);
	EXPECT_EQ(agm_same(123.0), 123.0);
}