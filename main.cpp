#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char* argv[]) {
    // std::ifstream log_file("test.log");
    if (argc < 2) {
        std::cout << "Usage: ./main <path_to_log_file>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];

    std::ifstream log_file(filename);
    std::string line;

    int total_line_count = 0;
    std::map<std::string, int> log_counts;

    if (log_file.is_open()) {
        while (std::getline(log_file, line)) {
            // std::cout << line << std::endl;
            total_line_count++;

            if (line.find("INFO") != std::string::npos) {
                log_counts["INFO"]++;
            } else if (line.find("WARNING") != std::string::npos) {
                log_counts["WARNING"]++;
            } else if (line.find("ERROR") != std::string::npos) {
                log_counts["ERROR"]++;
            }
        }
        log_file.close();

        if (total_line_count == 0) {
            std::cout << "Log file is empty or contains no processable lines." << std::endl;
        } else {
            
            std::cout << "Log File Analysis Complete" << std::endl;
            std::cout << "-------------------------" << std::endl;
            std::cout << "Total Lines Processed: " << total_line_count << std::endl;
            std::cout << "INFO messages: " << log_counts["INFO"] << std::endl;
            std::cout << "WARNING messages: " << log_counts["WARNING"] << std::endl;
            std::cout << "ERROR messages: " << log_counts["ERROR"] << std::endl;
        }
    } else {
        std::cout << "Error: Unable to open file." << std::endl;
    }

    return 0;
}