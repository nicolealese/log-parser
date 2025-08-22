#include <gtest/gtest.h>
#include "LogParser.h"

TEST(LogParserTest, HandlesBasicLogFile) {
    LogParser parser("test.log");

    bool success = parser.parse();

    EXPECT_TRUE(success);
    EXPECT_EQ(parser.getTotalLines(), 3);
    EXPECT_EQ(parser.getInfoCount(), 1);
    EXPECT_EQ(parser.getWarningCount(), 1);
    EXPECT_EQ(parser.getErrorCount(), 1);
}