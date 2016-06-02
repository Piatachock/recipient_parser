#ifndef RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_
#define RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_

#include <string>
#include <ostream>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace rcpt_parser {

struct LoginDomain {
    std::string login, domain;

    LoginDomain() = default;
    LoginDomain(std::string login, std::string domain)
            : login(login), domain(domain) {}
};

inline bool operator==(const LoginDomain& lhs, const LoginDomain& rhs) {
    return lhs.login == rhs.login && lhs.domain == rhs.domain;
}

inline std::ostream& operator<<(std::ostream& out, const LoginDomain& email) {
    out << "LoginDomain(\"" << email.login << "\", \"" << email.domain << "\")";
    return out;
}

}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::LoginDomain,
    (std::string, login)
    (std::string, domain)
);

#endif
