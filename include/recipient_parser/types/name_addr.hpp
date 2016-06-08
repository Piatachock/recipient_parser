#ifndef RECIPIENT_PARSER_TYPES_NAME_ADDR_HPP_
#define RECIPIENT_PARSER_TYPES_NAME_ADDR_HPP_

#include <boost/optional.hpp>

#include "addr_spec.hpp"

namespace rcpt_parser {
namespace types {

struct NameAddr {
    boost::optional<std::string> display_name;
    AddrSpec addr_spec;

    NameAddr() = default;

    NameAddr(std::string display_name, AddrSpec addr_spec)
            : display_name(std::move(display_name)),
              addr_spec(std::move(addr_spec)) {}
    NameAddr(AddrSpec addr_spec) : addr_spec(std::move(addr_spec)) {}
};

inline bool operator==(const NameAddr& lhs, const NameAddr& rhs) {
    return lhs.display_name == rhs.display_name
        && lhs.addr_spec == rhs.addr_spec;
}

}}

BOOST_FUSION_ADAPT_STRUCT(
    rcpt_parser::types::NameAddr,
    (boost::optional<std::string>, display_name)
    (rcpt_parser::types::AddrSpec, addr_spec)
);

#endif
