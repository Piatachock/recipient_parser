#ifndef RECIPIENT_PARSER_TYPES_ADDRESS_HPP_
#define RECIPIENT_PARSER_TYPES_ADDRESS_HPP_

#include <boost/variant/variant.hpp>

#include "name_addr.hpp"
#include "mailbox_group.hpp"

namespace rcpt_parser {
namespace types {

using Address = boost::variant<NameAddr, MailboxGroup>;

}}

#endif
