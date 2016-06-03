#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/error.hpp>

#include "from_string/quoted_string.hpp"
#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

struct SuccessQSTest: SParserTest {};

TEST_P(SuccessQSTest, no_throw) {
    this->test_parser(&parse_quoted_string);
}

INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessQSTest, ::testing::Values(
            SParserParams{"\"abc\""       , "abc"    },  // trims_quotes
            SParserParams{" \"abc\" "     , "abc"    },  // trims_outer_cwfs
            SParserParams{"\" \r\n abc \"", "  abc " },  // take_inner_fws
            SParserParams{"\" a b c \""   , " a b c "},  // take_multiple_fws
            SParserParams{"\"a\\\\\\\"b\"", "a\\\"b" }   // quoted-pairs with backslash and dquote
        )
);

struct FailQSTest: SParserTest {};

TEST_P(FailQSTest, throws) {
    this->test_parser_throws(&parse_quoted_string);
}

INSTANTIATE_TEST_CASE_P(two_crlf,
        FailQSTest, ::testing::Values(
            "\" ",      // unmatched dquote
            "\"\\\""    // backslash in content
        )
);


}
