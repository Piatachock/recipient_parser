#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/error.hpp>

#include "from_string/quoted_pair.hpp"
#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

struct SuccessQPTest : ParserTest<char> {};
using CParserParams = ParserParams<char>;


TEST_P(SuccessQPTest, no_throw_on_parse) {
    this->test_parser(&parse_quoted_pair);
}

INSTANTIATE_TEST_CASE_P(strip_leading_backslash,
        SuccessQPTest, ::testing::Values(
            CParserParams{"\\0" , '0' },  // Number
            CParserParams{"\\z" , 'z' },  // Letter
            CParserParams{"\\\\", '\\'},  // backslash
            CParserParams{"\\\"", '"' },  // dquote
            CParserParams{"\\ " , ' ' }   // space
        )
);

}
