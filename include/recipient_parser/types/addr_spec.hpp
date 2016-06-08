#ifndef RECIPIENT_PARSER_TYPES_ADDR_SPEC_HPP_
#define RECIPIENT_PARSER_TYPES_ADDR_SPEC_HPP_

#include <string>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace rcpt_parser {
namespace types {

struct AddrSpec {
    std::string login, domain;

    AddrSpec() = default;

    AddrSpec(std::string login, std::string domain)
            : login(std::move(login)), domain(std::move(domain)) {}
};

inline bool operator==(const AddrSpec& lhs, const AddrSpec& rhs) {
    return lhs.login == rhs.login && lhs.domain == rhs.domain;
}

}}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::AddrSpec,
    (std::string, login)
    (std::string, domain)
);

#endif
