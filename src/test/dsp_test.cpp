#include <gtest/gtest.h>

#include <imfixedpoint/number.hpp>
#include <imfixedpoint/dsp.hpp>

using namespace imfp;

TEST(dsp, Addition) {
    // declare variables
    const unsigned bit16 = 16;
    sfp<bit16> n_1_15_a;
    sfp<bit16> n_1_15_b;
    sfp<bit16> n_1_15_c;
    sfp<bit16> n_1_15_d;
    const double resolution = 1. / (static_cast<int64_t>(1) << (bit16 - 1));
    
    // addition
    double targetA = 0.1, targetB = 0.3;
    n_1_15_a = with_value(targetA);
    n_1_15_b = with_value(targetB);
    n_1_15_c = add_saturate<bit16>(n_1_15_a, n_1_15_b);
    EXPECT_NEAR(targetA + targetB, n_1_15_c.value(), resolution);
    
    // addition saturate
    targetA = 0.6;
    targetB = 0.5;
    n_1_15_a = with_value(targetA);
    n_1_15_b = with_value(targetB);
    n_1_15_c = add_saturate<bit16>(n_1_15_a, n_1_15_b);
    EXPECT_NEAR((decltype(n_1_15_c)::max).value(), n_1_15_c.value(), resolution);
    
    // additioin overflow
    targetA = 0.6;
    targetB = 0.5;
    n_1_15_a = with_value(targetA);
    n_1_15_b = with_value(targetB);
    n_1_15_c = add_overflow<bit16>(n_1_15_a, n_1_15_b);
    n_1_15_d = with_raw_value((decltype(n_1_15_c)::min).raw_value() * 2 + n_1_15_a.raw_value() + n_1_15_b.raw_value());
    EXPECT_NEAR(n_1_15_d.value(), n_1_15_c.value(), resolution);
}
