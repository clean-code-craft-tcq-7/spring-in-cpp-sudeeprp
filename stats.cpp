#include "stats.h"
#include <numeric>
#include <limits>
#include <algorithm>

bool readingsAreOutOfRange(const std::vector<float>& readings) {
    bool hasOutOfRange = false;
    for (const auto& reading : readings) {
        if (reading < 0 || reading > 10000) {
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
        stats.average = std::accumulate(readings.begin(), readings.end(), 0.0f) / readings.size();
        stats.max = *std::max_element(readings.begin(), readings.end());
        stats.min = *std::min_element(readings.begin(), readings.end());
    }
    return stats;
}
