#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/quoted_string.hpp>
#include <recipient_parser/error.hpp>

#include "debugging_test.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

using QuotedStringTest = PrinterTest;

TEST_F(QuotedStringTest, trims_dquotes) {
    const std::string input("\"abc\"");
    std::string result;

    auto stopped_at = parse_quoted_string(input, result);
    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, "abc");
}

TEST_F(QuotedStringTest, trims_cfws) {
    const std::string input("  \n \"abc\"  \n ");
    std::string result;

    auto stopped_at = parse_quoted_string(input, result);
    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, "abc");
}

TEST_F(QuotedStringTest, trims_ineer_fws) {
    const std::string input("\"  abc \"");
    std::string result;

    auto stopped_at = parse_quoted_string(input, result);
    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, "abc");
}

}
