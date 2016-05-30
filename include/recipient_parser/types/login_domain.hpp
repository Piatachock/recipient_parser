#ifndef RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_
#define RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_

#include <string>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace rcpt_parser {

struct LoginDomain {
    std::string login;
    std::string domain;
};

}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::LoginDomain,
    (std::string, login)
    (std::string, domain)
);

#endif
