#include <recipient_parser/rules/text.hpp>

#include "text.hpp"
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_phrase(
        const std::string& input,
        std::string& result) {
    return detail::parse_template<Phrase>(input, result);
}

} // namespace rcpt_parser
