#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/atoms.hpp>
#include <recipient_parser/error.hpp>

#include "debugging_test.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

using DotAtomTest = PrinterTest;

TEST_F(DotAtomTest, stops_on_first_word) {
    std::string input("first second");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_TRUE(*stopped_at == ' ');
    ASSERT_EQ(result, "first");
}

TEST_F(DotAtomTest, stops_on_quote) {
    std::string input("foo\"bar");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);
    ASSERT_EQ(*stopped_at, '"');
}

TEST_F(DotAtomTest, parse_specials) {
    std::string input("!#$%&'*+|=?^_`{|}~-");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_TRUE(stopped_at == input.end());
    ASSERT_EQ(result, input);
}

TEST_F(DotAtomTest, parse_dot_in_word) {
    std::string input("str.ing");
    std::string result;

    parse_dot_atom(input, result);

    ASSERT_EQ(result, input);
}

TEST_F(DotAtomTest, dot_as_first_char_throws) {
    std::string input(".string");
    std::string result;

    ASSERT_THROW(parse_dot_atom(input, result), ParseError);
}

TEST_F(DotAtomTest, dot_as_last_char_throws) {
    std::string input("string.");
    std::string result;

    ASSERT_THROW(parse_dot_atom(input, result), ParseError);
}

}
