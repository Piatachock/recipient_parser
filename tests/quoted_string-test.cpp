#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/quoted_string.hpp>
#include <recipient_parser/error.hpp>

#include "debugging_test.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

using QuotedStringTest = PrinterTest;

struct SuccessQSTest: PrinterTest, WithParamInterface<std::pair<std::string, std::string>> {};

TEST_P(SuccessQSTest, no_throw_on_parse) {
    const std::string input = GetParam().first;
    std::string result;

    auto stopped_at = parse_quoted_string(input, result);

    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, GetParam().second);
}

INSTANTIATE_TEST_CASE_P(ok_parse,
        SuccessQSTest, ::testing::Values(
            std::make_pair("\"abc\""          , "abc"),      // trims_quotes
            std::make_pair("  \n \"abc\"  \n ", "abc"),      // trims_outer_cwfs
            std::make_pair("\" \r\n abc \""   , "  abc "),   // take_inner_fws
            std::make_pair("\" a b c \""      , " a b c "),  // take_multiple_fws
            std::make_pair("\"a\\\\\\\"b\""   , "a\\\"b")    // quoted-pair with backslash and dquote
        )
);

struct ThrowQSTest: PrinterTest, WithParamInterface<std::string> {};

TEST_P(ThrowQSTest, throw_on_parse) {
    const auto input = GetParam();
    std::string result;

    ASSERT_THROW(parse_quoted_string(input, result), ParseError);
}

INSTANTIATE_TEST_CASE_P(throw_on_two_crlf,
        ThrowQSTest, ::testing::Values(
            "\" ",      // unmatched dquote
            "\"\\\""    // backslash in content
        )
);


}
