#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include <recipient_parser/from_string/atoms.hpp>

namespace {

using namespace testing;
using namespace rcpt_parser;

std::ostream& operator <<(std::ostream& stream, const std::vector<std::string>& values) {
    return stream << boost::join(values, "\n");
}

TEST(DotAtomTest, test_dotatom) {
    std::string input("  abc.bca   ");
    std::string result;

    auto stopped_at = parse_dot_atom(input, result);

    ASSERT_TRUE(stopped_at == input.end());
    ASSERT_EQ(result, "abc.bca");
}

}
