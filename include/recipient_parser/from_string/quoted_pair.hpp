#ifndef RECIPIENT_PARSER_FROM_STRING_QUOTED_PAIR_HPP_
#define RECIPIENT_PARSER_FROM_STRING_QUOTED_PAIR_HPP_

#include <string>

namespace rcpt_parser {

std::string::const_iterator parse_quoted_pair(
        const std::string& input,
        char& result,
        bool do_debug = false);

}

#endif /* RECIPIENT_PARSER_FROM_STRING_QUOTED_PAIR_HPP_ */
