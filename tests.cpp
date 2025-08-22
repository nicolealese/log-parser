#include <gtest/gtest.h>
#include <fstream>
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

TEST(LogParserTest, HandlesEmptyFile) {
    std::ofstream empty_file("empty.log");
    empty_file.close();
    LogParser parser("empty.log");

    bool success = parser.parse();

    EXPECT_TRUE(success);
    EXPECT_EQ(parser.getTotalLines(), 0);
    EXPECT_EQ(parser.getErrorCount(), 0);
}

TEST(LogParserTest, HandlesNonExistentFile) {
    LogParser parser("non_existent_file.log");

    bool success = parser.parse();

    EXPECT_FALSE(success);
}

TEST(LogParserTest, HandlesFileWithNoKeywords) {
    std::ofstream no_keywords_file("no_keywords.log");
    no_keywords_file << "just a regular line\n";
    no_keywords_file << "another normal line\n";
    no_keywords_file.close();
    LogParser parser("no_keywords.log");

    bool success = parser.parse();

    EXPECT_TRUE(success);
    EXPECT_EQ(parser.getTotalLines(), 2);
    EXPECT_EQ(parser.getInfoCount(), 0);
    EXPECT_EQ(parser.getWarningCount(), 0);
    EXPECT_EQ(parser.getErrorCount(), 0);
}