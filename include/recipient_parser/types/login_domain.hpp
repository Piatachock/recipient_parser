#ifndef RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_
#define RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_

#include <string>
#include <vector>
#include <ostream>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/adapt_struct_named.hpp>
#include <boost/optional.hpp>

#include <boost/fusion/include/vector.hpp>

namespace rcpt_parser {
namespace types {

struct AddrSpec {
    std::string login, domain;

    AddrSpec() = default;
    /*
    AddrSpec(const AddrSpec&) = default;
    AddrSpec(AddrSpec&&) = default;
    */

    AddrSpec(std::string login, std::string domain)
            : login(std::move(login)), domain(std::move(domain)) {}
};

inline bool operator==(const AddrSpec& lhs, const AddrSpec& rhs) {
    return lhs.login == rhs.login && lhs.domain == rhs.domain;
}

inline std::ostream& operator<<(std::ostream& out, const AddrSpec& email) {
    out << "AddrSpec(\"" << email.login << "\", \"" << email.domain << "\")";
    return out;
}

struct NameAddr {
    boost::optional<std::string> display_name;
    AddrSpec addr_spec;

    NameAddr() = default;
    /*
    NameAddr(const NameAddr&) = default;
    NameAddr(NameAddr&&) = default;
    */

    NameAddr(std::string display_name, AddrSpec addr_spec)
            : display_name(std::move(display_name)),
              addr_spec(std::move(addr_spec)) {}
    NameAddr(AddrSpec addr_spec) : addr_spec(std::move(addr_spec)) {}
};

inline bool operator==(const NameAddr& lhs, const NameAddr& rhs) {
    return lhs.display_name == rhs.display_name
        && lhs.addr_spec == rhs.addr_spec;
}

inline std::ostream& operator<<(std::ostream& out, const NameAddr& email) {
    static const char* const join_delimiter("\", \"");
    out << "NameAddr(\"";
    if(email.display_name) {
        out << *email.display_name << join_delimiter;
    }
    out << email.addr_spec << "\")";
    return out;
}


struct MailboxGroup {
    using GroupList = std::vector<NameAddr>;

    boost::optional<std::string> display_name;
    GroupList group;

    MailboxGroup() = default;
    /*
    MailboxGroup(const MailboxGroup&) = default;
    MailboxGroup(MailboxGroup&&) = default;
    */

    MailboxGroup(std::string display_name, GroupList group)
            : display_name(std::move(display_name)),
              group(std::move(group)) {}
    MailboxGroup(GroupList group) : group(std::move(group)) {}
};

inline bool operator==(const MailboxGroup& lhs, const MailboxGroup& rhs) {
    return lhs.display_name == rhs.display_name
        && lhs.group == rhs.group;
}

inline std::ostream& operator<<(std::ostream& out, const MailboxGroup& group) {
    static const char* const join_delimiter("\", \"");
    out << "MailboxGroup(\"";
    if(group.display_name) {
        out << *group.display_name << join_delimiter;
    }
    out << "[";
    for(const auto& name_addr : group.group) {
        out << name_addr << ", ";
    }
    out << "]\")";
    return out;
}




}}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::AddrSpec,
    (std::string, login)
    (std::string, domain)
);

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::NameAddr,
    (boost::optional<std::string>, display_name)
    (rcpt_parser::types::AddrSpec, addr_spec)
);

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::MailboxGroup,
    (boost::optional<std::string>, display_name)
    (rcpt_parser::types::MailboxGroup::GroupList, group)
);

#endif
