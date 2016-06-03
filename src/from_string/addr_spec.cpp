#include <recipient_parser/from_string/addr_spec.hpp>
#include <recipient_parser/addr_spec.hpp>

#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_addr_spec(const std::string& input, LoginDomain& result) {
    return detail::parse_template<AddrSpec>(input, result);
}

} // namespace rcpt_parser
