#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "from_string/text.hpp"
#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

struct SuccessPhraseTest : SParserTest {};

TEST_P(SuccessPhraseTest, no_throw) {
    this->test_parser(&parse_phrase);
}

INSTANTIATE_TEST_CASE_P(full_consume_no_trim,
        SuccessPhraseTest, ::testing::Values(
            "word",                         // single atom word
            "two words",                    // two atom words
            " word",
            "word ",
            "\"quoted string\"",            // single quoted string
            "\"quo ted\"\"str ing\"",       // two quoted strings
            "atom \"and quoted\" string"    // two quoted strings
        )
);

INSTANTIATE_TEST_CASE_P(partial_consume,
        SuccessPhraseTest, ::testing::Values(
            SParserParams{"foo\"bar"    , "foo"   , "\"bar" },  //stops on dquote, excluding
            SParserParams{"string."     , "string", "."     }   //stops on dot as last symbol, excluding
        )
);

struct FailPhraseTest : SParserTest {};

TEST_F(FailPhraseTest, fails_on_leading_dot) {
    this->test_parser_fails(&parse_phrase, SParserParams{".string"});
}

}
