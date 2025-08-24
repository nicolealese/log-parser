#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "LogParser.h"

std::map<std::string, int> final_report_counts;
int final_total_lines = 0;
std::mutex report_mutex;

void parse_file_worker(const std::string& filename) {
    LogParser parser(filename);

    if (parser.parse()) {
        std::lock_guard<std::mutex> lock(report_mutex);

        final_total_lines += parser.getTotalLines();
        final_report_counts["INFO"] += parser.getInfoCount();
        final_report_counts["WARNING"] += parser.getWarningCount();
        final_report_counts["ERROR"] += parser.getErrorCount();
    } else {
        std::cout << "Thread for '" << filename << "' failed to parse file." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./main <path_to_log_file>" << std::endl;
        return 1;
    }
    
    std::vector<std::thread> threads;

    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];
        threads.emplace_back(parse_file_worker, filename);
    }

    std::cout << "Launched " << threads.size() << " worker threads. Waiting for them to finish..." << std::endl;

    LogParser parser(argv[1]);

    for (auto& t : threads) {
        t.join();  
    }

    std::cout << "All threads finished." << std::endl;
    std::cout << "--- Final Report ---" << std::endl;
    std::cout << "Total Lines Processed: " << final_total_lines << std::endl;
    std::cout << "INFO messages: " << final_report_counts["INFO"] << std::endl;
    std::cout << "WARNING messages: " << final_report_counts["WARNING"] << std::endl;
    std::cout << "ERROR messages: " << final_report_counts["ERROR"] << std::endl;
    
    return 0;
}