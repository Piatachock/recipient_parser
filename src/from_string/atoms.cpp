#include <recipient_parser/from_string/atoms.hpp>

#include <recipient_parser/atoms.hpp>
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(
        const std::string& input,
        std::string& result,
        bool do_debug) {
    return detail::parse_template<DotAtom>("DotAtom", input, result, do_debug);
}

} // namespace rcpt_parser
