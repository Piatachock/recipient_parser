#include <recipient_parser/from_string/atoms.hpp>

#include <recipient_parser/atoms.hpp>
#include <recipient_parser/grammar_from_rule.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(const std::string& input, std::string& result) {
    using StdDotAtom = DotAtom<std::string::const_iterator, ascii::space_type>;
    GRAMMAR_FROM_RULE(StdDotAtom, DotAtomParser);
    DotAtomParser parser;

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
