#ifndef RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_
#define RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PrinterTest : public ::testing::Test {
public:
    PrinterTest() {
        ::testing::internal::CaptureStderr();
    }

    virtual ~PrinterTest() {
        const ::testing::TestInfo* const test_info =
                        ::testing::UnitTest::GetInstance()->current_test_info();
        if ( test_info && test_info->result()->Failed() ) {
            std::cerr << std::endl << "Captured output from "
                    << test_info->test_case_name()
                    << " is:"
                    << std::endl
                    << testing::internal::GetCapturedStderr()
                    << std::endl;
        }
    }
};

#endif /* RECIPIENT_PARSER_TESTS_DEBUGGING_TEST_HPP_ */
