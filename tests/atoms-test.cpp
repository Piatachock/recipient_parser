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
    const std::string input("first second");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);
    auto unparsed = std::string(stopped_at, input.end());

    ASSERT_EQ(unparsed, "second");
    ASSERT_EQ(result, "first");
}

TEST_F(DotAtomTest, stops_on_quote) {
    const std::string input("foo\"bar");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);
    auto unparsed = std::string(stopped_at, input.end());

    ASSERT_EQ(unparsed, "\"bar");
}

TEST_F(DotAtomTest, parse_specials) {
    const std::string input("!#$%&'*+|=?^_`{|}~-");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, input);
}

TEST_F(DotAtomTest, trim_word) {
    const std::string input(" word\t");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_EQ(stopped_at - input.begin(), input.size());
    ASSERT_EQ(result, "word");
}

TEST_F(DotAtomTest, parse_dot_in_word) {
    const std::string input("str.ing");
    std::string result;

    parse_dot_atom(input, result);

    ASSERT_EQ(result, input);
}

TEST_F(DotAtomTest, dot_as_first_char_throws) {
    const std::string input(".string");
    std::string result;

    ASSERT_THROW(parse_dot_atom(input, result), ParseError);
}

TEST_F(DotAtomTest, exclude_dot_as_last_char) {
    const std::string input("string.");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);
    auto unparsed = std::string(stopped_at, input.end());

    ASSERT_EQ(unparsed, ".");
    ASSERT_EQ(result, "string");
}

}
