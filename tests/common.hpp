#ifndef RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_
#define RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <recipient_parser/error.hpp>

namespace rcpt_parser {

class PrinterTest : public ::testing::Test {
public:
    PrinterTest() {
        buffer.str( std::string() ); // clears the buffer.
        sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf( buffer.rdbuf() );
    }

    virtual ~PrinterTest() {
        std::cerr.rdbuf( sbuf );
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();
        if ( test_info && test_info->result()->Failed() ) {
            std::cerr << std::endl << "Captured output from "
                    << test_info->test_case_name()
                    << " is:"
                    << std::endl
                    << buffer.str()
                    << std::endl;
        }
    }

    std::stringstream buffer;
    std::streambuf* sbuf;
};

template<typename Result>
struct ParserParams {
    std::string input, unparsed;
    Result result;
    ParserParams(std::string input, Result result, std::string unparsed = std::string())
            : input(input), unparsed(unparsed), result(result) {}
    template<typename = decltype(Result(input))>
    ParserParams(std::string input)
            : input(input), result(input) {}
};

using SParserParams = ParserParams<std::string>;

template<typename Result>
struct ParserTest : PrinterTest, ::testing::WithParamInterface<ParserParams<Result>> {
    using Params = ParserParams<Result>;

    template<typename ParseFunc>
    void test_parser(ParseFunc f) {
        return test_parser(f, this->GetParam());
    }

    template<typename ParseFunc>
    void test_parser(ParseFunc f, const Params& params) {
        const std::string& input = params.input;
        Result result;

        auto stopped_at = f(input, result);
        auto unparsed = std::string(stopped_at, input.end());

        ASSERT_EQ(unparsed, params.unparsed);
        ASSERT_EQ(result, params.result);
    }

    template<typename Exception = ParseError, typename ParseFunc>
    void test_parser_throws(ParseFunc f) {
        test_parser_throws<Exception>(f, this->GetParam());
    }

    template<typename Exception = ParseError, typename ParseFunc>
    void test_parser_throws(ParseFunc f, const Params& params) {
        const auto input = params.input;
        std::string result;
        ASSERT_THROW(f(input, result), Exception);
    }
};

using SParserTest = ParserTest<std::string>;

}

#endif /* RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_ */
