#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include <recipient_parser/from_string/email.hpp>

namespace {

using namespace testing;

struct ParserTest : Test {
    ParserTest() {}
};

std::ostream& operator <<(std::ostream& stream, const std::vector<std::string>& values) {
    return stream << boost::join(values, "\n");
}

TEST_F(ParserTest, test_dotatom) {
    std::string input("  abc.bca   ");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_TRUE(stopped_at == input.end());
    ASSERT_EQ(result, "abc.bca");
}

TEST_F(ParserTest, basic_testcase) {
    std::string input("login@domain.ru");

    LoginDomain result;

    auto stopped_at = parse_email(input, result);

    ASSERT_TRUE(stopped_at == input.end());
    ASSERT_EQ(result.login, "login");
    ASSERT_EQ(result.domain, "domain.ru");
}
}
