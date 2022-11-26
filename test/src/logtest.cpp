#include "math/log.hpp"

#include <cmath>
#include <numbers>
#include <gtest/gtest.h>

TEST(LogEquivalenceTests, TestLogOfOne)
{
	EXPECT_EQ(bigfact::math::log(1.0), 0.0) <<
		"Log of 1 should be zero.";
}

TEST(LogEquivalenceTests, TestSpecialLogs)
{
	double const tol{ std::pow(10.0, -14.0) };
	EXPECT_NEAR(bigfact::math::log(2.0), std::numbers::ln2, tol);
	EXPECT_NEAR(bigfact::math::log(10.0), std::numbers::ln10, tol);
}

TEST(LogEquivalenceTests, TestScaledLogs)
{
	/*
	* Tests the log function for big input values by using the
	* property that log(a^b) = b log(a)
	*/
	constexpr auto log_10_to_pow = [](double const p) {
		return bigfact::math::log(std::pow(10.0, p));
	};

	EXPECT_DOUBLE_EQ(log_10_to_pow(2), 2 * std::numbers::ln10);
	EXPECT_DOUBLE_EQ(log_10_to_pow(3), 3 * std::numbers::ln10);
	EXPECT_DOUBLE_EQ(log_10_to_pow(4), 4 * std::numbers::ln10);
	EXPECT_DOUBLE_EQ(log_10_to_pow(5), 5 * std::numbers::ln10);
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
	constexpr auto amgm_1 = [](auto const v) {return bigfact::_math::agm(1.0, v); };

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

	constexpr auto agm_same = [](auto const v) {return bigfact::_math::agm(v, v); };

	EXPECT_EQ(agm_same(1.0), 1.0);
	EXPECT_EQ(agm_same(10.0), 10.0);
	EXPECT_EQ(agm_same(11.0), 11.0);
	EXPECT_EQ(agm_same(123.0), 123.0);
}