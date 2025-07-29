#include "stats.h"

#include "gtest/gtest.h"
#include <cmath>

TEST(Statistics, ReportsAverageMinMax) {
    auto computedStats = Statistics::ComputeStatistics({1.5, 8.9, 3.2, 4.5});
    float epsilon = 0.001;
    EXPECT_LT(std::abs(computedStats.average - 4.525), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 8.9), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageNaNForEmpty) {
    auto computedStats = Statistics::ComputeStatistics({});
    // Check if all fields of computedStats are NaN
    // Use std::isnan to check if a float is NaN
    EXPECT_TRUE(std::isnan(computedStats.average));
    EXPECT_TRUE(std::isnan(computedStats.max));
    EXPECT_TRUE(std::isnan(computedStats.min));
}
