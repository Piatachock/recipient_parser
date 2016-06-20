#ifndef RECIPIENT_PARSER_INCLUDE_TEXT_HPP_
#define RECIPIENT_PARSER_INCLUDE_TEXT_HPP_

#include "../detail/spirit.hpp"

#include "atoms.hpp"
#include "quoted_string.hpp"

#include <boost/algorithm/string/join.hpp>
#include <boost/phoenix/bind.hpp>

namespace rcpt_parser {

template<typename Iterator>
struct Word : qi::rule<Iterator, std::string()> {
    Word() {
        this->name("word");
        static_cast<typename Word::this_type&>(*this) %=
                quoted_string | atom;
    }

    QuotedString<Iterator> quoted_string;
    Atom<Iterator> atom;
};

template<typename Iterator>
void debug(Word<Iterator>& word) {
    debug(static_cast<typename Word<Iterator>::this_type&>(word));
    debug(word.quoted_string);
    debug(word.atom);
}


template<typename Iterator>
struct Phrase : qi::rule<Iterator, std::string()> {
    Phrase() {
        this->name("phrase");

        auto action = [](
                const std::vector<std::string>& words,
                typename qi::rule<Iterator, std::string()>::context_type& context) {
            boost::fusion::at_c<0>(context.attributes) = boost::join(words, " ");
        };
        static_cast<typename Phrase::this_type&>(*this) = (+word)[action];
    }

    Word<Iterator> word;
};

template<typename Iterator>
void debug(Phrase<Iterator>& phrase) {
    debug(static_cast<typename Phrase<Iterator>::this_type&>(phrase));
    debug(phrase.word);
}


} // namespace rcpt_parser

#endif
