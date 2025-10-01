#include <gtest/gtest.h>
#include "16g.h"

TEST(HexTest, DefaultConstructor) {
    Hex hex;
    ASSERT_TRUE(hex.toString() == "0");
}

TEST(HexTest, StringConstructor) {
    Hex hex("1A2B3C");
    ASSERT_TRUE(hex.toString() == "1A2B3C");
}

TEST(HexTest, InitializerListConstructor) {
    Hex hex = {1, 2, 3, 10, 15};
    ASSERT_TRUE(hex.toString() == "123AF");
}

TEST(HexTest, AddOperation) {
    Hex a("A1B2");
    Hex b("C3D4");
    Hex result = a.add(b);
    ASSERT_TRUE(result.toString() == "16586");
}

TEST(HexTest, SubtractOperation) {
    Hex a("16586");
    Hex b("C3D4");
    Hex result = a.subtract(b);
    ASSERT_TRUE(result.toString() == "A1B2");
}

TEST(HexTest, EqualsComparison) {
    Hex a("ABC");
    Hex b("ABC");
    ASSERT_TRUE(a.equals(b));
}

TEST(HexTest, NotEqualsComparison) {
    Hex a("ABC");
    Hex b("ABD");
    ASSERT_FALSE(a.equals(b));
}

TEST(HexTest, LessThanComparison) {
    Hex a("ABC");
    Hex b("ABD");
    ASSERT_TRUE(a.lessThan(b));
}

TEST(HexTest, GreaterThanComparison) {
    Hex a("ABD");
    Hex b("ABC");
    ASSERT_TRUE(a.greaterThan(b));
}

TEST(HexTest, RemoveLeadingZeros) {
    Hex hex("000ABC");
    ASSERT_TRUE(hex.toString() == "ABC");
}

TEST(HexTest, LargeNumberAddition) {
    Hex a("FFFFFFFE");
    Hex b("2");
    Hex result = a.add(b);
    ASSERT_TRUE(result.toString() == "100000000");
}

TEST(HexTest, CopyConstructor) {
    Hex original("123ABC");
    Hex copy = original;
    ASSERT_TRUE(original.equals(copy));
}

TEST(HexTest, EmptyStringThrows) {
    ASSERT_THROW(Hex(""), std::invalid_argument);
}

TEST(HexTest, InvalidCharsThrow) {
    ASSERT_THROW(Hex("XYZ"), std::invalid_argument);
}

TEST(HexTest, SubtractNegativeThrows) {
    Hex small("123");
    Hex large("456");
    ASSERT_THROW(small.subtract(large), std::underflow_error);
}
