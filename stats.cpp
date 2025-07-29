#include "stats.h"
#include <numeric>
#include <limits>
#include <algorithm>

bool readingsAreOutOfRange(const std::vector<float>& readings) {
    bool hasOutOfRange = false;
    for (const auto& reading : readings) {
        if (reading < 0 || reading > 200) {
            hasOutOfRange = true;
            break;
        }
    }
    return hasOutOfRange;
}

bool readingsAreSuspect(const std::vector<float>& readings) {
    return readings.empty() || readingsAreOutOfRange(readings);
}

Statistics::Stats Statistics::ComputeStatistics(const std::vector<float>& readings) {
    Statistics::Stats stats;
    if (readingsAreSuspect(readings)) {
        stats.average = std::numeric_limits<float>::quiet_NaN();
        stats.max = std::numeric_limits<float>::quiet_NaN();
        stats.min = std::numeric_limits<float>::quiet_NaN();
    } else {
        auto readingsWithoutNaN = readings;
        readingsWithoutNaN.erase(std::remove_if(readingsWithoutNaN.begin(), readingsWithoutNaN.end(),
            [](float reading) { return std::isnan(reading); }), readingsWithoutNaN.end());
        stats.average = std::accumulate(readingsWithoutNaN.begin(), readingsWithoutNaN.end(), 0.0f) / readingsWithoutNaN.size();
        stats.max = *std::max_element(readingsWithoutNaN.begin(), readingsWithoutNaN.end());
        stats.min = *std::min_element(readingsWithoutNaN.begin(), readingsWithoutNaN.end());
    }
    return stats;
}
