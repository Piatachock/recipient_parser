#ifndef RECIPIENT_PARSER_INCLUDE_RECIPIENT_PARSER_GRAMMAR_FROM_RULE_HPP_
#define RECIPIENT_PARSER_INCLUDE_RECIPIENT_PARSER_GRAMMAR_FROM_RULE_HPP_

#include "spirit.hpp"
#include "error_handler.hpp"

#define GRAMMAR_FROM_RULE(Rule, GrammarName)                               \
    struct GrammarName :                                                   \
            boost::spirit::qi::grammar<                                    \
                typename Rule::iterator_type,                              \
                boost::mpl::at_c<typename Rule::template_params, 0>::type, \
                boost::mpl::at_c<typename Rule::template_params, 1>::type, \
                boost::mpl::at_c<typename Rule::template_params, 2>::type, \
                boost::mpl::at_c<typename Rule::template_params, 3>::type  \
            > {                                                            \
        GrammarName() : GrammarName::base_type(rule) {                     \
            using namespace boost::spirit::qi::labels;                     \
            rule.name(#GrammarName);                                       \
            boost::spirit::qi::on_error<boost::spirit::qi::fail>(          \
               rule, error(_1, _2, _3, _4)                                 \
            );                                                             \
        }                                                                  \
                                                                           \
        Rule rule;                                                         \
        const boost::phoenix::function<                                    \
            rcpt_parser::ErrorHandler<typename Rule::iterator_type>        \
        > error;                                                           \
    };

#endif /* RECIPIENT_PARSER_INCLUDE_RECIPIENT_PARSER_GRAMMAR_FROM_RULE_HPP_ */
