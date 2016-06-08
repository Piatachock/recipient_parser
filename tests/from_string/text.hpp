#ifndef RECIPIENT_PARSER_FROM_STRING_TEXT_HPP_
#define RECIPIENT_PARSER_FROM_STRING_TEXT_HPP_

#include <string>

namespace rcpt_parser {

std::pair<bool, std::string::const_iterator> parse_phrase(
        const std::string& input,
        std::string& result);

}

#endif /* RECIPIENT_PARSER_FROM_STRING_ATOMS_HPP_ */
