#ifndef RECIPIENT_PARSER_TYPES_MAILBOX_GROUP_HPP_
#define RECIPIENT_PARSER_TYPES_MAILBOX_GROUP_HPP_

#include <vector>

#include "name_addr.hpp"

namespace rcpt_parser {
namespace types {

struct MailboxGroup {
    using GroupList = std::vector<NameAddr>;

    boost::optional<std::string> display_name;
    GroupList group;

    MailboxGroup() = default;

    MailboxGroup(std::string display_name, GroupList group)
            : display_name(std::move(display_name)),
              group(std::move(group)) {}
    MailboxGroup(GroupList group) : group(std::move(group)) {}
};

inline bool operator==(const MailboxGroup& lhs, const MailboxGroup& rhs) {
    return lhs.display_name == rhs.display_name
        && lhs.group == rhs.group;
}

}}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::MailboxGroup,
    (boost::optional<std::string>, display_name)
    (rcpt_parser::types::MailboxGroup::GroupList, group)
);

#endif
