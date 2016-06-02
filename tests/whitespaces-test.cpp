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
struct SuccessFWSTest: PrinterTest, WithParamInterface<std::string> {};

TEST_P(SuccessFWSTest, no_throw_on_parse) {
    const auto input = GetParam();
    const auto stopped_at = parse_fws(input);
    ASSERT_EQ(input.size(), stopped_at - input.begin());
}

INSTANTIATE_TEST_CASE_P(no_throw_on_single_eol_then_blank,
        SuccessFWSTest, ::testing::Values(
            "  \t  \r\n ",  // whitespaces and tabs before CRLF
            "\r\n  \t\t ",  // whitespaces and tabs after CRLF
            " ",            // only whitespace
            "\t",           // only tab
            "\r ",          // only CR (non-RFC but probably useful)
            "\n "           // only LF (non-RFC but probably useful)
        )
);

TEST_F(FWSTest, throw_on_ending_crlf) {
    const auto input = std::string("  \r\n");
    const auto stopped_at = parse_fws(input);
    ASSERT_EQ(input.find('\r'), stopped_at - input.begin());
}

struct ThrowFWSTest: PrinterTest, WithParamInterface<std::string> {};

TEST_P(ThrowFWSTest, throw_on_parse) {
    const auto input = GetParam();
    ASSERT_THROW(parse_fws(input), ParseError);
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

}
