#include <recipient_parser/from_string/atoms.hpp>

#include <recipient_parser/atoms.hpp>
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(
        const std::string& input,
        std::string& result) {
    return detail::parse_template<DotAtom>("DotAtom", input, result);
}

} // namespace rcpt_parser
