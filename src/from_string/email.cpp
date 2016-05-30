#include <recipient_parser/from_string/email.hpp>
#include <recipient_parser/email.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_email(const std::string& input, LoginDomain& result) {
    static const EmailParser<std::string::const_iterator> parser;

    auto iter = input.begin();
    const auto end = input.end();
    qi::phrase_parse(
        iter,                          // Start Iterator
        end,                            // End Iterator
        parser,                         // The Parser
        ascii::space,                   // The Skip-Parser
        result
    );
    return iter;
}

} // namespace rcpt_parser
