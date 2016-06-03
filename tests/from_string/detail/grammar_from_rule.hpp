#ifndef RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_GRAMMAR_FROM_RULE_HPP_
#define RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_GRAMMAR_FROM_RULE_HPP_

#include <recipient_parser/spirit.hpp>
#include <recipient_parser/error_handler.hpp>

namespace rcpt_parser {
namespace detail {

template<typename Rule>
struct GrammarFromRule :
        boost::spirit::qi::grammar<
            typename Rule::iterator_type,
            typename boost::mpl::at_c<typename Rule::template_params, 0>::type,
            typename boost::mpl::at_c<typename Rule::template_params, 1>::type,
            typename boost::mpl::at_c<typename Rule::template_params, 2>::type,
            typename boost::mpl::at_c<typename Rule::template_params, 3>::type
        > {
    GrammarFromRule(bool do_debug = false)
            : GrammarFromRule::base_type(rule) {
        using namespace boost::spirit::qi::labels;
        boost::spirit::qi::on_error<boost::spirit::qi::fail>(
           rule, error(_1, _2, _3, _4)
        );
        if (do_debug)
            debug(rule);
    }

    Rule rule;
    const boost::phoenix::function<
        rcpt_parser::ErrorHandler<typename Rule::iterator_type>
    > error;
};

}} // namespace rcpt_parser::detail

#endif /* RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_GRAMMAR_FROM_RULE_HPP_ */
