#include <recipient_parser/from_string/quoted_pair.hpp>

#include <recipient_parser/quoted_pair.hpp>
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_quoted_pair(
        const std::string& input,
        char& result) {
    return detail::parse_template<QuotedPair>("QuotedPair", input, result);
}

} // namespace rcpt_parser
