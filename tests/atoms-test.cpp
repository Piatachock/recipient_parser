#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/atoms.hpp>
#include <recipient_parser/error.hpp>

#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

struct SuccessDotAtomTest : SParserTest {};

TEST_P(SuccessDotAtomTest, no_throw) {
    this->test_parser(&parse_dot_atom);
}

INSTANTIATE_TEST_CASE_P(full_consume_no_trim,
        SuccessDotAtomTest, ::testing::Values(
            "!#$%&'*+|=?^_`{|}~-",  // allow specials
            "str.ing"               // allow dot inside word
        )
);

INSTANTIATE_TEST_CASE_P(full_consume_trim,
        SuccessDotAtomTest, ::testing::Values(
            SParserParams{" \tword", "word"},      // trim left
            SParserParams{"word\t ", "word"}       // trim right
        )
);

INSTANTIATE_TEST_CASE_P(partial_consume,
        SuccessDotAtomTest, ::testing::Values(
            SParserParams{"first second", "first" , "second"},  //stops after whitespaces (and trim them)
            SParserParams{"foo\"bar"    , "foo"   , "\"bar" },  //stops on dquote, excluding
            SParserParams{"string."     , "string", "."     }   //stops on dot as last symbol, excluding
        )
);

struct FailDotAtomTest : SParserTest {};

TEST_F(FailDotAtomTest, throws_on_leading_dot) {
    this->test_parser_throws(&parse_dot_atom, SParserParams{".string"});
}

}
