#include <recipient_parser/from_string/whitespaces.hpp>

#include <recipient_parser/whitespaces.hpp>
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_fws(
        const std::string& input) {
    return detail::parse_template<FWS>("FWS", input);
}

std::string::const_iterator parse_cfws(
        const std::string& input) {
    return detail::parse_template<CFWS>("CFWS", input);
}

} // namespace rcpt_parser
