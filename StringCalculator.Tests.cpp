#include <gtest/gtest.h>
#include "string.h"
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ReturnsZeroForEmptyInput) {
    ASSERT_EQ(calculateStringSum(""),0);
}

TEST(StringCalculatorAddTests, ReturnsZeroForSingleZeroInput) {
    ASSERT_EQ(calculateStringSum("0"),0);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCommas) {
    ASSERT_EQ(calculateStringSum("1,2"),3);
    ASSERT_EQ(calculateStringSum("12,1"),13);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByNewLines) {
    ASSERT_EQ(calculateStringSum("1\n2"),3);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCommasOrNewLines) {
    ASSERT_EQ(calculateStringSum("1,2\n3"),6);
}

TEST(StringCalculatorAddTests, ReturnsSumOfAnyNumberOfInputNumbers) {
    char HundredOnes[201];
    strcpy(HundredOnes,"");
    for(int i = 0; i < 100; ++i) {
        strcat(HundredOnes,"1,");
    }
    
    ASSERT_EQ(calculateStringSum("1"),1);
    ASSERT_EQ(calculateStringSum("1,1"),2);
    ASSERT_EQ(calculateStringSum("1,1,1,1,1"),5);
    ASSERT_EQ(calculateStringSum(HundredOnes),100);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCustomDelimiter) {
    ASSERT_EQ(calculateStringSum("//;\n1;2"),3);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCustomDelimiterOfAnyLength) {
    ASSERT_EQ(calculateStringSum("//;*;\n1;*;2;*;3"),6);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCustomDelimiterOrNewLines) {
    ASSERT_EQ(calculateStringSum("//;\n1;2\n3"),6);
}

TEST(StringCalculatorAddTests, ReturnsSumOfOnlyInputNumbersLessThanThousand) {
    ASSERT_EQ(calculateStringSum("1002,2"),2);
    ASSERT_EQ(calculateStringSum("1234,4567"),0);
}

TEST(StringCalculatorAddTests, ReturnsZeroIfInputStringDoesNotHaveNumbers) {
    ASSERT_EQ(calculateStringSum(",\n,"),0);
    ASSERT_EQ(calculateStringSum("Hello, world!"),0);
}

TEST(StringCalculatorAddTests, IgnoresInputCharactersThatAreNeitherNumbersNorDelimiters) {
    ASSERT_EQ(calculateStringSum("1,a,1"),2);
    ASSERT_EQ(calculateStringSum("1, 2*1"),22);
    ASSERT_EQ(calculateStringSum("//;1;1;1"),111);
}

TEST(StringCalculatorAddTests, ThrowsExceptionForNegativeInputNumbers) {
    ASSERT_ANY_THROW(calculateStringSum("-1,1,-1"));
    try{
        calculateStringSum("-1,1,-1");
    } catch (const std::runtime_error& e) {
        ASSERT_STREQ(e.what(),"negative numbers not allowed: -1,-1");
    }

    ASSERT_NO_THROW(calculateStringSum("1,1,1"));
}
