#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include <recipient_parser/from_string/email.hpp>

#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

struct EmailTest : ParserTest<LoginDomain> {};
using Params = ParserParams<LoginDomain>;

TEST_F(EmailTest, basic_testcase) {
    auto params = Params("login@domain.ru", LoginDomain("login", "domain.ru"));
    this->test_parser(&parse_email, params);
}

}
