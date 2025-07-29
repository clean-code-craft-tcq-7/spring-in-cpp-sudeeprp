#include "stats.h"
#include <numeric>
#include <limits>

struct Stats {
    float average;
    float max;
    float min;
};

Stats Statistics::ComputeStatistics(const std::vector<float>& readings) {
    Stats stats;
    stats.average = std::accumulate(readings.begin(), readings.end(), 0.0f) / readings.size();
    stats.max = *std::max_element(readings.begin(), readings.end());
    stats.min = *std::min_element(readings.begin(), readings.end());
    return stats;
}
