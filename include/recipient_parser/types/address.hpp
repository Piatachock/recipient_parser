#ifndef RECIPIENT_PARSER_TYPES_ADDRESS_HPP_
#define RECIPIENT_PARSER_TYPES_ADDRESS_HPP_

#include <boost/variant/variant.hpp>

#include "name_addr.hpp"
#include "mailbox_group.hpp"

namespace rcpt_parser {
namespace types {

using Address = boost::variant<NameAddr, MailboxGroup>;
using AddressList = std::vector<Address>;

}

struct mailbox_flatten_visitor : boost::static_visitor<types::MailboxGroup::GroupList> {
    types::MailboxGroup::GroupList operator()(types::NameAddr& addr) const {
        return {std::move(addr)};
    }

    types::MailboxGroup::GroupList operator()(types::MailboxGroup& grp) const {
        return std::move(grp.group);
    }
};

inline types::MailboxGroup::GroupList flat_mailbox_list(types::Address& addr) {
    return boost::apply_visitor(mailbox_flatten_visitor(), addr);
}

inline types::MailboxGroup::GroupList flat_mailbox_list(types::AddressList& addrList) {
    types::MailboxGroup::GroupList result;
    for( auto& addr : addrList ) {
        auto mailboxList = flat_mailbox_list(addr);
        std::move(mailboxList.begin(), mailboxList.end(), std::back_inserter(result));
    }
    return result;
}


}

#endif
