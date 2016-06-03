#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include "from_string/addr_spec.hpp"

#include "common.hpp"

namespace {

using namespace testing;
using namespace rcpt_parser;


struct SuccessDomainTest : SParserTest {};

TEST_P(SuccessDomainTest, ok) {
    this->test_parser(&parse_domain);
}

INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessDomainTest, ::testing::Values(
                "str.ing",          // dot-atom
                "[.literal]",       // address literal, even with leading dot
                "[ \t spaced ]"     // address literal with fws
        )
);

INSTANTIATE_TEST_CASE_P(full_consume_part_result,
        SuccessDomainTest, ::testing::Values(
                SParserParams{"\r\n [with_cfws] ", "[with_cfws]" }, // trims outer cfws
                SParserParams{"[ \r\n with_fws]" , "[  with_fws]"}  // skip CRLF in inner fws
        )
);

INSTANTIATE_TEST_CASE_P(partial_consume,
        SuccessDomainTest, ::testing::Values(
                SParserParams{"[first] second"   , "[first]", "second"}, // stops after cfws
                SParserParams{"[word] \r\n \r\n ", "[word]" , "\r\n " } // do not accept second cfws
        )
);

struct FailDomainTest : SParserTest {};

TEST_P(FailDomainTest, throws) {
    this->test_parser_throws(&parse_domain);
}

INSTANTIATE_TEST_CASE_P(bad_food,
        FailDomainTest, ::testing::Values(
                "[unmatched",               // unmatched square brace
                "[backslash\\]",            // backslash
                "[square[brace]",           // square brace
                "\r\n \r\n [double cwfs]",  // double cfws
                "[ \r\n \r\n double fws]"   // double cfws
        )
);


using Params = ParserParams<LoginDomain>;

struct SuccessAddrSpecTest : ParserTest<LoginDomain> {};

TEST_P(SuccessAddrSpecTest, basic_testcase) {
    this->test_parser(&parse_addr_spec);
}


INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessAddrSpecTest, ::testing::Values(
            Params("login@domain.ru", LoginDomain("login", "domain.ru")),
            Params("login@[127.0.0.1]", LoginDomain("login", "[127.0.0.1]"))
        )
);

struct FailAddrSpecTest : ParserTest<LoginDomain> {};

TEST_P(FailAddrSpecTest, throws) {
    this->test_parser_throws(&parse_addr_spec);
}

INSTANTIATE_TEST_CASE_P(bad_food,
        FailAddrSpecTest, ::testing::Values(
                "no_at",
                "domain_is@.bad_dot_atom_not_in_square_braces",
                "unquoted spaces in local part@domain.ru"
        )
);


}
