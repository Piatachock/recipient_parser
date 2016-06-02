#ifndef RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_PARSE_TEMPLATE_HPP_
#define RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_PARSE_TEMPLATE_HPP_

#include "grammar_from_rule.hpp"

namespace rcpt_parser {
namespace detail {

using StrCIter = std::string::const_iterator;

template<template <typename> class Rule>
StrCIter parse_template(
        const std::string& name,
        const std::string& input) {
    using StringRule = Rule<StrCIter>;
    using StringGrammar = GrammarFromRule<StringRule>;

    StringGrammar parser(name, true);

    auto iter = input.begin();
    if( !qi::parse(iter, input.end(), parser) ) {
        auto err_msg = std::string(__PRETTY_FUNCTION__)
                     + std::string(": qi::parse return false");
        throw ParseError( err_msg );
    }
    return iter;
}

template<template <typename> class Rule>
StrCIter parse_template(
        const std::string& name,
        const std::string& input,
        typename Rule<StrCIter>::attr_type& result) {
    using StringRule = Rule<StrCIter>;
    using StringGrammar = GrammarFromRule<StringRule>;

    StringGrammar parser(name, true);

    auto iter = input.begin();
    if( !qi::parse(iter, input.end(), parser, result) ) {
        auto err_msg = std::string(__PRETTY_FUNCTION__)
                     + std::string(": qi::parse return false");
        throw ParseError( err_msg );
    }
    return iter;
}

}} // namespace rcpt_parser::detail

#endif // RECIPIENT_PARSER_SRC_FROM_STRING_DETAIL_PARSE_TEMPLATE_HPP_
