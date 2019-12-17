#include <gtest/gtest.h>

#include <imfixedpoint/number.hpp>
#include <imfixedpoint/conversion.hpp>

using namespace imfp;

TEST(conversion, InvariantDecimalPoint) {
    // declare variables
    sfp<16, 1, 0, 14, 1> n_1_0_14_1;
    sfp<16, 2, 0, 14> n_2_0_14_0;
    
    // 1.0.14.1 -> 2.0.14.0
    n_1_0_14_1 = with_value(0.05);
    convert(n_2_0_14_0, n_1_0_14_1);
    EXPECT_DOUBLE_EQ(n_1_0_14_1.value(), n_2_0_14_0.value());
    
    // 2.0.14.0 -> 1.0.14.1
    n_2_0_14_0 = with_value(-0.3);
    convert(n_1_0_14_1, n_2_0_14_0);
    EXPECT_DOUBLE_EQ(n_2_0_14_0.value(), n_1_0_14_1.value());
}

TEST(conversion, InvariantBase) {
    // declare variables
    sfp<16, 1, 0, 15, 0, 1> n_1_0_15_0_1;
    sfp<16, 1, 1, 14> n_1_1_14_0_0;
    
    // 1.0.15.0<1> -> 1.1.14.0<0>
    n_1_0_15_0_1 = with_value(0.05);
    convert(n_1_1_14_0_0, n_1_0_15_0_1);
    EXPECT_DOUBLE_EQ(n_1_0_15_0_1.value(), n_1_1_14_0_0.value());
    
    // 1.1.14.0<0> -> 1.0.15.0<1>
    n_1_1_14_0_0 = with_value(-0.3);
    convert(n_1_0_15_0_1, n_1_1_14_0_0);
    EXPECT_DOUBLE_EQ(n_1_1_14_0_0.value(), n_1_0_15_0_1.value());
}

TEST(conversion, InvariantBit) {
    // declare variables
    sfp<4, 1, 1, 1, 1> n_1_1_1_1;
    sfp<8, 2, 1, 1, 4> n_2_1_1_4;
    
    // 1.1.1.1 -> 2.1.1.4
    n_1_1_1_1 = with_value(0.05);
    convert(n_2_1_1_4, n_1_1_1_1);
    EXPECT_DOUBLE_EQ(n_1_1_1_1.value(), n_2_1_1_4.value());
    
    // 2.1.1.4 -> 1.1.1.1
    n_2_1_1_4 = with_value(-0.3);
    convert(n_1_1_1_1, n_2_1_1_4);
    EXPECT_DOUBLE_EQ(n_2_1_1_4.value(), n_1_1_1_1.value());
}

TEST(conversion, InvariantMix) {
    // declare variables
    sfp<12, 3, 3, 3, 3, 3> n_3_3_3_3_3;
    sfp<16, 2, 6, 0, 8> n_2_6_0_8_0;
    
    // 3.3.3.3<3> -> 1.6.0.5<0>
    n_3_3_3_3_3 = with_value(0.05);
    convert(n_2_6_0_8_0, n_3_3_3_3_3);
    EXPECT_DOUBLE_EQ(n_3_3_3_3_3.value(), n_2_6_0_8_0.value());
    
    // 1.6.0.5<0> -> 3.3.3.3<3>
    n_2_6_0_8_0 = with_value(-0.3);
    convert(n_3_3_3_3_3, n_2_6_0_8_0);
    EXPECT_DOUBLE_EQ(n_2_6_0_8_0.value(), n_3_3_3_3_3.value());
}
