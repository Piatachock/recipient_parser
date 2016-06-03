#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include "from_string/addr_spec.hpp"

#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

using Params = ParserParams<LoginDomain>;

using SuccessEmailTest = ParserTest<LoginDomain>;

TEST_F(SuccessEmailTest, basic_testcase) {
    auto params = Params("login@domain.ru", LoginDomain("login", "domain.ru"));
    this->test_parser(&parse_addr_spec, params);
}

struct FailEmailTest : ParserTest<LoginDomain> {};

TEST_P(FailEmailTest, throws) {
    this->test_parser_throws(&parse_addr_spec);
}

INSTANTIATE_TEST_CASE_P(bad_food,
        FailEmailTest, ::testing::Values(
                "no_at",
                "domain@.with_leading_dot",
                "spaces in local part@domain.ru"
        )
);


}
