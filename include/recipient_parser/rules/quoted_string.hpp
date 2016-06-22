#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_

#include "../detail/spirit.hpp"

#include "quoted_pair.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

namespace traits {
namespace quoted_string {

struct PreserveQuotes : quoted_pair::PreserveBackslash {};
struct RemoveQuotes : quoted_pair::RemoveBackslash {};

struct PreserveOuterCWFS {};
struct RemoveOuterCWFS {};

struct Default : RemoveQuotes, RemoveOuterCWFS {};

}}

template<typename Iterator>
struct QuotedString : qi::rule<Iterator, std::string()> {
    using Rule = qi::rule<Iterator, std::string()>;

    template<typename Tag = traits::quoted_string::Default>
    QuotedString(Tag tag = Tag{}) : qp{tag} {
        qtext.name("qtext");
        //Printable characters except backslash and quote
        qtext %= qi::char_("\x21-\x7e") - '\\' - '"';

        qcontent.name("qcontent");
        qcontent %= qtext | qp;

        spaced.name("string of qcontext with optional fws");
        spaced %= qi::hold[*qi::hold[-fws >> qcontent] >> -end_fws];

        quoted.name("\"spaced\" with quotes");
        parse_quotes(tag);

        this->name("quoted-string");
        parse_outer_CFWS(tag);
    }

    void parse_quotes(traits::quoted_string::RemoveQuotes) {
        quoted %= qi::lit('"') >> spaced >> qi::lit('"');
    }
    void parse_quotes(traits::quoted_string::PreserveQuotes) {
        quoted %= qi::char_('"') >> spaced >> qi::char_('"');
    }

    void parse_outer_CFWS(traits::quoted_string::RemoveOuterCWFS) {
        static_cast<Rule&>(*this) %= -qi::omit[cfws] >> quoted >> -qi::omit[end_cfws];
    }
    void parse_outer_CFWS(traits::quoted_string::PreserveOuterCWFS) {
        static_cast<Rule&>(*this) %= -cfws >> quoted >> -end_cfws;
    }


    CFWS<Iterator> cfws, end_cfws;
    FWS<Iterator> fws, end_fws;
    QuotedPair<Iterator> qp;
    Rule qtext, qcontent, spaced, quoted;
};

template<typename Iterator>
void debug(QuotedString<Iterator>& qs) {
    debug(static_cast<typename QuotedString<Iterator>::this_type&>(qs));
    debug(qs.cfws);
    debug(qs.end_cfws);
    debug(qs.fws);
    debug(qs.end_fws);
    debug(qs.qp);
    debug(qs.qtext);
    debug(qs.qcontent);
    debug(qs.spaced);
    debug(qs.quoted);
}

} // namespace rcpt_parser

#endif // RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
