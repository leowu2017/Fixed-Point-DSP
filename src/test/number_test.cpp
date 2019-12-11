#include <gtest/gtest.h>

#include <imfixedpoint/number.hpp>

using namespace imfp;

TEST(number, value) {
    // Q15
    const unsigned bit16 = 16;
    const double resolution = 1. / (static_cast<int64_t>(1) << (bit16 - 1));
    const double target = 0.1;
    sfp<bit16> n;
    n = target;
    
    EXPECT_NEAR(target, n.value(), resolution);
}
