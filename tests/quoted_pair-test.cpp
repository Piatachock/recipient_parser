#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/from_string/quoted_pair.hpp>
#include <recipient_parser/error.hpp>

namespace {

using namespace testing;
using namespace rcpt_parser;

struct SuccessQPTest: TestWithParam<std::pair<std::string, char>> {};

TEST_P(SuccessQPTest, no_throw_on_parse) {
    const auto input = GetParam().first;
    char result;
    const auto stopped_at = parse_quoted_pair(input, result);
    ASSERT_EQ(input.size(), stopped_at - input.begin());
    ASSERT_EQ(GetParam().second, result);
}

INSTANTIATE_TEST_CASE_P(no_throw_on_single_eol_then_blank,
        SuccessQPTest, ::testing::Values(
            std::make_pair("\\0", '0'),    // Number
            std::make_pair("\\z", 'z'),    // Letter
            std::make_pair("\\\\", '\\'),  // backslash
            std::make_pair("\\\"", '"'),   // dquote
            std::make_pair("\\ ", ' ')     // space
        )
);

}
