#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/algorithm/string/join.hpp>

#include "from_string/address.hpp"

#include "common.hpp"

using namespace testing;
using namespace rcpt_parser;

namespace {

using Params = ParserParams<types::NameAddr>;

struct SuccessNameAddrTest : ParserTest<types::NameAddr> {};

TEST_P(SuccessNameAddrTest, basic_testcase) {
    this->test_parser(&parse_name_addr);
}

INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessNameAddrTest, ::testing::Values(
            Params(
                    "displayname <login@domain.ru>",
                    types::NameAddr("displayname ", types::AddrSpec("login", "domain.ru"))
            ),
            Params(
                    "spaced display name <smth@smw>",
                    types::NameAddr("spaced display name ", types::AddrSpec("smth", "smw"))
            ),
            Params(
                    "<login@domain.ru>",
                    types::NameAddr(types::AddrSpec("login", "domain.ru"))
            ),
            Params(
                    "< \r\n login@domain.ru >",
                    types::NameAddr(types::AddrSpec(" \r\n login", "domain.ru "))
            )
        )
);

struct FailNameAddrTest : ParserTest<types::NameAddr> {};

TEST_P(FailNameAddrTest, throws) {
    this->test_parser_throws(&parse_name_addr);
}

INSTANTIATE_TEST_CASE_P(bad_food,
        FailNameAddrTest, ::testing::Values(
                "<unmatched@angle.bracket",
                "no@angle.brackets",
                "<two<angle@brackets>"
        )
);

struct SuccessMailboxTest : ParserTest<types::NameAddr> {};

TEST_P(SuccessMailboxTest, basic_testcase) {
    this->test_parser(&parse_mailbox);
}

INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessMailboxTest, ::testing::Values(
            Params(
                    "displayname <login@domain.ru>",
                    types::NameAddr("displayname ", types::AddrSpec("login", "domain.ru"))
            ),
            Params(
                    "login@domain.ru",
                    types::NameAddr(types::AddrSpec("login", "domain.ru"))
            )
        )
);


using GParams = ParserParams<types::MailboxGroup>;

struct SuccessGroupTest : ParserTest<types::MailboxGroup> {};

TEST_P(SuccessGroupTest, basic_testcase) {
    this->test_parser(&parse_group);
}

INSTANTIATE_TEST_CASE_P(full_consume,
        SuccessGroupTest, ::testing::Values(
            GParams("groupname:;",
                    types::MailboxGroup(
                            "groupname",
                            {}
                    )
            ),
            GParams("groupname:login@domain.ru;",
                    types::MailboxGroup(
                            "groupname",
                            {types::NameAddr(types::AddrSpec("login", "domain.ru"))}
                    )
            ),
            GParams("groupname:login@domain.ru,displayname <my@email.com>, \"quo ted\" <ip@[127.0.0.1]>;",
                    types::MailboxGroup(
                            "groupname",
                            {
                                    types::NameAddr(                 types::AddrSpec("login", "domain.ru")),
                                    types::NameAddr("displayname " , types::AddrSpec("my", "email.com")   ),
                                    types::NameAddr(" \"quo ted\" ", types::AddrSpec("ip", "[127.0.0.1]") ),
                            }
                    )
            )
        )
);



}
