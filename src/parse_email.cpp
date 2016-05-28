#include "parse_email.hpp"
#include <parser.hpp>

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


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

std::string::const_iterator parse_dot_atom(const std::string& input, std::string& result) {
    using Iterator = std::string::const_iterator;
    using Skipper = ascii::space_type;

    struct DotAtomParser : qi::grammar<Iterator, std::string(), Skipper> {
        DotAtomParser() : DotAtomParser::base_type(start) {
            start %= qi::eps > dot_atom > qi::eoi;

            using namespace qi::labels;
            using boost::phoenix::construct;
            using boost::phoenix::val;

            qi::on_error<qi::fail>(
                start,
                std::cout
                    << val("Error! Expecting ")
                    << _4                               // what failed?
                    << val(" here: \"")
                    << construct<std::string>(_3, _2)   // iterators to error-pos, end
                    << val("\"")
                    << std::endl
           );
        }
        DotAtom<Iterator, Skipper> dot_atom;
        qi::rule<Iterator, std::string(), Skipper> start;
        boost::phoenix::function<ErrorHandler<Iterator>> const error;
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
