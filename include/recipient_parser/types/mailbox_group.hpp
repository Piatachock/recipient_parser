#ifndef RECIPIENT_PARSER_TYPES_MAILBOX_GROUP_HPP_
#define RECIPIENT_PARSER_TYPES_MAILBOX_GROUP_HPP_

#include <vector>

#include "name_addr.hpp"
#include "text.hpp"

namespace rcpt_parser {
namespace types {

struct MailboxGroup {
    using GroupList = std::vector<NameAddr>;

    Words display_name;
    GroupList group;

    MailboxGroup() = default;

    template<typename T>
    MailboxGroup(T&& display_name, GroupList group)
            : display_name{std::forward<T>(display_name)},
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
    (rcpt_parser::types::Words, display_name)
    (rcpt_parser::types::MailboxGroup::GroupList, group)
);

#endif
