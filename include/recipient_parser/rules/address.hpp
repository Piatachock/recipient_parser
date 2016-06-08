#ifndef RECIPIENT_PARSER_INCLUDE_ADDRESS_HPP_
#define RECIPIENT_PARSER_INCLUDE_ADDRESS_HPP_

#include "../types/name_addr.hpp"
#include "../types/mailbox_group.hpp"
#include "../types/address.hpp"

#include "../detail/spirit.hpp"

#include "addr_spec.hpp"
#include "text.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct DisplayName : Phrase<Iterator> {
    DisplayName() {
        this->name("display-name");
    }
};

template<typename Iterator>
struct NameAddr : qi::rule<Iterator, types::NameAddr()> {
    NameAddr() {
        this->name("name-addr");

        static_cast<typename NameAddr::this_type&>(*this) %=
                -display_name >> angle_addr;

        angle_addr.name("angle-addr");
        angle_addr %=
                -qi::omit[cfws]
             >> '<'
             >> addr_spec
             >> '>'
             >> -qi::omit[cfws];
    }
    DisplayName<Iterator> display_name;
    qi::rule<Iterator, types::AddrSpec()> angle_addr;

    CFWS<Iterator> cfws;
    AddrSpec<Iterator> addr_spec;
};

template<typename Iterator>
void debug(NameAddr<Iterator>& addr) {
    debug(static_cast<typename NameAddr<Iterator>::this_type&>(addr));
    debug(addr.display_name);
    debug(addr.angle_addr);
    debug(addr.cfws);
    debug(addr.addr_spec);
}

template<typename Iterator>
struct Mailbox : qi::rule<Iterator, types::NameAddr()> {
    Mailbox() {
        this->name("mailbox");
        static_cast<typename Mailbox::this_type&>(*this) %=
                name_addr | addr_spec;
    }
    NameAddr<Iterator> name_addr;
    AddrSpec<Iterator> addr_spec;
};

template<typename Iterator>
void debug(Mailbox<Iterator>& mb) {
    debug(static_cast<typename Mailbox<Iterator>::this_type&>(mb));
    debug(mb.name_addr);
    debug(mb.addr_spec);
}


template<typename Iterator>
struct Group : qi::rule<Iterator, types::MailboxGroup()> {
    Group() {
        this->name("group");
        static_cast<typename Group::this_type&>(*this) %=
                display_name >> ':' >> -group_list >> ';' >> -qi::omit[cfws];

        group_list.name("group-list");
        group_list %= mailbox_list | qi::omit[cfws];

        mailbox_list.name("mailbox-list");
        mailbox_list %= mailbox % ',';
    }
    DisplayName<Iterator> display_name;
    qi::rule<Iterator, types::MailboxGroup::GroupList()> group_list, mailbox_list;
    CFWS<Iterator> cfws;

    Mailbox<Iterator> mailbox;
};

template<typename Iterator>
void debug(Group<Iterator>& group) {
    debug(static_cast<typename Group<Iterator>::this_type&>(group));
    debug(group.display_name);
    debug(group.group_list);
    debug(group.mailbox_list);
    debug(group.cfws);
    debug(group.mailbox);
}

template<typename Iterator>
struct Address : qi::rule<Iterator, types::Address()> {
    Address() {
        this->name("address");
        static_cast<typename Address::this_type&>(*this) %=
                mailbox | group;
    }
    Mailbox<Iterator> mailbox;
    Group<Iterator> group;
};

template<typename Iterator>
void debug(Address<Iterator>& addr) {
    debug(static_cast<typename Address<Iterator>::this_type&>(addr));
    debug(addr.mailbox);
    debug(addr.group);
}

} // namespace rcpt_parser

#endif
