#ifndef INCLUDE_RECIPIENT_PARSER_PARSE_HPP_
#define INCLUDE_RECIPIENT_PARSER_PARSE_HPP_

#include "types/address.hpp"
#include "types/name_addr.hpp"

#include "detail/spirit.hpp"
#include "rules/address.hpp"

namespace rcpt_parser {


// Parse RFC-5322 "address" entity. Address is either single mailbox, or mailbox group.
// Return default-initialized boost::optional if parse failed.
template<typename Iterator>
boost::optional<types::Address> parse_address(Iterator& iter, const Iterator& end)
{
    types::Address result;
    if( qi::parse(iter, end, Address<Iterator>(), result) ) {
        return std::move(result);
    }
    return {};
}

template<typename Range>
boost::optional<types::Address> parse_address(const Range& range) {
    auto iter = begin(range);
    auto result = parse_address(iter, end(range));
    if( iter != end(range) ) {
        return {};
    }
    return std::move(result);
}

// Parse RFC-5322 "mailbox" entity. This parse function do not cover mailbox group case.
// Return default-initialized boost::optional if parse failed.
template<typename Iterator>
boost::optional<types::Mailbox> parse_mailbox(Iterator& iter, const Iterator& end)
{
    types::Mailbox result;
    if( qi::parse(iter, end, Mailbox<Iterator>(), result) ) {
        return std::move(result);
    }
    return {};
}

template<typename Range>
boost::optional<types::Mailbox> parse_mailbox(const Range& range) {
    auto iter = begin(range);
    auto result = parse_mailbox(iter, end(range));
    if( iter != end(range) ) {
        return {};
    }
    return std::move(result);
}

}

#endif /* INCLUDE_RECIPIENT_PARSER_PARSE_HPP_ */
