#ifndef RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_
#define RECIPIENT_PARSER_SRC_LOGIN_DOMAIN_HPP_

#include <string>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

struct LoginDomain {
    std::string login;
    std::string domain;
};

BOOST_FUSION_ADAPT_STRUCT(
    LoginDomain,
    (std::string, login)
    (std::string, domain)
);

#endif
