#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/whitespaces.hpp>
#include <recipient_parser/error.hpp>

#include "debugging_test.hpp"

#include <iostream>

namespace {

using namespace testing;
using namespace rcpt_parser;

using FWSTest = PrinterTest;
struct SuccessFWSTest
        : PrinterTest,
          WithParamInterface<std::pair<std::string, std::string>> {};

TEST_P(SuccessFWSTest, no_throw_on_parse) {
    const auto input = GetParam().first;
    std::string result;

    const auto stopped_at = parse_fws(input, result);
    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, GetParam().second);
}

INSTANTIATE_TEST_CASE_P(no_throw_on_single_eol_then_blank,
        SuccessFWSTest, ::testing::Values(
            std::make_pair(" \t \r\n ", " \t  "),   // whitespaces and tabs before CRLF
            std::make_pair("\r\n \t\t ", " \t\t "), // whitespaces and tabs after CRLF
            std::make_pair(" ", " "),               // only whitespace
            std::make_pair("\t", "\t"),             // only tab
            std::make_pair("\r ", " "),             // only CR (non-RFC but probably useful)
            std::make_pair("\n ", " ")              // only LF (non-RFC but probably useful)
        )
);
/*
TEST_F(FWSTest, throw_on_ending_crlf) {
    const auto input = std::string("  \r\n");
    std::string result;

    const auto stopped_at = parse_fws(input, result);
    ASSERT_EQ(input.find('\r'), stopped_at - input.begin());

}

struct ThrowFWSTest: PrinterTest, WithParamInterface<std::string> {};

TEST_P(ThrowFWSTest, throw_on_parse) {
    const auto input = GetParam();
    std::string result;

    ASSERT_THROW(parse_fws(input, result), ParseError);
}

INSTANTIATE_TEST_CASE_P(throw_on_two_crlf,
        ThrowFWSTest, ::testing::Values(
            "\r\n\r\n ",       // nothing in between CRLF
            "\n\n "            // nothing in between LF+LF
        )
);

INSTANTIATE_TEST_CASE_P(throw_on_just_crlf,
        ThrowFWSTest, ::testing::Values(
            "\r\n",  // just CRLF
            "\r",    // just CRLF
            "\n"     // just CRLF
        )
);
*/
}
