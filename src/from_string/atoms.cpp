#include <recipient_parser/from_string/atoms.hpp>

#include <recipient_parser/atoms.hpp>
#include <recipient_parser/error_handler.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(const std::string& input, std::string& result) {
    using Iterator = std::string::const_iterator;
    using Skipper = ascii::space_type;

    struct DotAtomParser : qi::grammar<Iterator, std::string(), Skipper> {
        DotAtomParser() : DotAtomParser::base_type(start) {
            start %= qi::eps > dot_atom > qi::eoi;
            qi::on_error<qi::fail>(start, error(qi::_1, qi::_2, qi::_3, qi::_4));
        }

        DotAtom<Iterator, Skipper> dot_atom;
        qi::rule<Iterator, std::string(), Skipper> start;
        phx::function<ErrorHandler<Iterator>> const error;
    } parser;

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
