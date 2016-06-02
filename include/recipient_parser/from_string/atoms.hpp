#ifndef RECIPIENT_PARSER_FROM_STRING_ATOMS_HPP_
#define RECIPIENT_PARSER_FROM_STRING_ATOMS_HPP_

#include <string>

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(
        const std::string& input,
        std::string& result,
        bool do_debug = false);

}

#endif /* RECIPIENT_PARSER_FROM_STRING_ATOMS_HPP_ */
