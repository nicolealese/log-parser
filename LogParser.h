#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <string>
#include <map>

class LogParser {
public:
    LogParser(const std::string& filename);

    bool parse();

    int getTotalLines() const;
    int getInfoCount() const;
    int getWarningCount() const;
    int getErrorCount() const;

private:
    std::string m_filename;
    int m_total_line_count;
    std::map<std::string, int> m_log_counts;

};

#endif