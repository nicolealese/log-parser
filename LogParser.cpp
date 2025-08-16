#include "LogParser.h"
#include <iostream>
#include <fstream>

LogParser::LogParser(const std::string& filename) :
    m_filename(filename),
    m_total_line_count(0) {

    }

bool LogParser::parse() {
    std::ifstream log_file(m_filename);
    std::string line;

    if (!log_file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return false;
    }

    while (std::getline(log_file, line)) {
        m_total_line_count++;

        if (line.find("INFO") != std::string::npos) {
            m_log_counts["INFO"]++;
        } else if (line.find("WARNING") != std::string::npos) {
            m_log_counts["WARNING"]++;
        } else if (line.find("ERROR") != std::string::npos) {
            m_log_counts["ERROR"]++;
        }
    }

    log_file.close();
    return true;
}

int LogParser::getTotalLines() const {
    return m_total_line_count;
}

int LogParser::getInfoCount() const {
    if (m_log_counts.count("INFO")) {
        return m_log_counts.at("INFO");
    }
    return 0;
}

int LogParser::getWarningCount() const {
    if (m_log_counts.count("WARNING")) {
        return m_log_counts.at("WARNING");
    }
    return 0;
}

int LogParser::getErrorCount() const {
    if (m_log_counts.count("ERROR")) {
        return m_log_counts.at("ERROR");
    }
    return 0;
}