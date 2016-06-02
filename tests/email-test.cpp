#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include <recipient_parser/from_string/email.hpp>

#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;

using EmailTest = PrinterTest;

TEST_F(EmailTest, basic_testcase) {
    std::string input("login@domain.ru");

    LoginDomain result;

    auto stopped_at = parse_email(input, result);

    ASSERT_TRUE(stopped_at == input.end());
    ASSERT_EQ(result.login, "login");
    ASSERT_EQ(result.domain, "domain.ru");
}
}
