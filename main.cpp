#include <iostream>
#include "LogParser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./main <path_to_log_file>" << std::endl;
        return 1;
    }

    LogParser parser(argv[1]);

    if (parser.parse()) {
        std::cout << "Log File Analysis Complete" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Total Lines Processed: " << parser.getTotalLines() << std::endl;
        std::cout << "INFO messages: " << parser.getInfoCount() << std::endl;
        std::cout << "WARNING messages: " << parser.getWarningCount() << std::endl;
        std::cout << "ERROR messages: " << parser.getErrorCount() << std::endl;
    }
    
    return 0;
}