#include <gtest/gtest.h>

#include <imfixedpoint/number.hpp>
#include <imfixedpoint/imfp_exception.hpp>

using namespace imfp;

TEST(number, Q15) {
    // declare variables
    const unsigned bit16 = 16;
    sfp<bit16> n_1_15;
    sfp<bit16, 2> n_2_14;
    
    // Q15 check sign
    ASSERT_NO_THROW(n_1_15 = with_raw_value(0x7FFF));
    ASSERT_THROW(n_2_14 = with_raw_value(0x7FFF), representation::invalid_sign_bits_exception);
    ASSERT_NO_THROW(n_2_14 = with_raw_value(0x3FFF));
    
    // Q15 value
    const double resolution = 1. / (static_cast<int64_t>(1) << (bit16 - 1));
    const double targetF = -0.1;
    n_1_15 = with_value(targetF);
    
    EXPECT_NEAR(targetF, n_1_15.value(), resolution);
    
    // Q15 raw value
    const double targetI = -1. / (static_cast<int64_t>(1) << (bit16 - 1));
    n_1_15 = with_raw_value(0xFFFF);
    EXPECT_NEAR(targetI, n_1_15.value(), resolution);
}

TEST(number, Mix24) {
    // declare variables
    const unsigned bit24 = 24;
    const unsigned nSgn = 2;
    const unsigned nInt = 3;
    const unsigned nFrac = 18;
    const unsigned nZero = 1;
    sfp<bit24, nSgn, nInt, nFrac, nZero> n; // 2.3.18.1
    
    // check sign
    ASSERT_NO_THROW(n = with_raw_value(0x3FF'FFE));
    ASSERT_THROW(n = with_raw_value(0x7FF'FFE), representation::invalid_sign_bits_exception);
    
    // check zero
    ASSERT_THROW(n = with_raw_value(0x3FF'FFF), representation::invalid_zero_bits_exception);
    
    // floating-point value
    const double resolution = 1. / (static_cast<int64_t>(1) << nFrac);
    const double targetF = -0.1;
    n = with_value(targetF);
    
    EXPECT_NEAR(targetF, n.value(), resolution);
    
    // fixed-point raw value
    const double targetI = -1. / (static_cast<int64_t>(1) << nFrac);
    n = with_raw_value(0xFFF'FFE);
    EXPECT_NEAR(targetI, n.value(), resolution);
}

TEST(number, Mix32Base) {
    // declare variables
    const unsigned bit32 = 32;
    const unsigned nSgn = 2;
    const unsigned nInt = 4;
    const unsigned nFrac = 22;
    const unsigned nZero = 4;
    const int nBase = -2;
    sfp<bit32, nSgn, nInt, nFrac, nZero, nBase> n; // 2.4.22.4(-2)
    
    // floating-point value
    const double resolution = 1. / (static_cast<int64_t>(1) << (nFrac - nZero));
    const double targetF = -0.1;
    n = with_value(targetF);
    
    EXPECT_NEAR(targetF, n.value(), resolution);
    
    // fixed-point raw value
    const double targetI = -1. / (static_cast<int64_t>(1) << (nFrac + nZero - nBase));
    n = with_raw_value(0xFFFF'FFF0);
    EXPECT_NEAR(targetI, n.value(), resolution);
}

TEST(number, Extrema) {
    // declare variables
    const unsigned bit16 = 16;
    const unsigned nSgn = 2;
    const unsigned nInt = 4;
    const unsigned nFrac = 6;
    const unsigned nZero = 4;
    const int nBase = -2;
    using n_t = sfp<bit16, nSgn, nInt, nFrac, nZero, nBase>;
    
    n_t n; // 2.4.6.4(-2)
    
    // max
    n = n_t::max;
    n_t max{with_raw_value(0x3FF0)};
    EXPECT_DOUBLE_EQ(max.value(), n.value());
    
    // min
    n = n_t::min;
    n_t min{with_raw_value(0xC000)};
    EXPECT_DOUBLE_EQ(min.value(), n.value());
}
