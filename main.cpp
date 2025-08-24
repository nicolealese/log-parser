#include "httplib.h"
#include "LogParser.h"
#include "json.hpp"

#include <iostream>

using json = nlohmann::json;

int main() {
    httplib::Server server;

    server.Get("/parse", [](const httplib::Request& request, httplib::Response& response) {
        if (request.has_param("file")) {
            auto file = request.get_param_value("file");
            LogParser parser(file);

            if (parser.parse()) {
                json result;
                result["file"] = file;
                result["total_lines"] = parser.getTotalLines();
                result["info_count"] = parser.getInfoCount();
                result["warning_count"] = parser.getWarningCount();
                result["error_count"] = parser.getErrorCount();

                response.set_content(result.dump(4), "application/json");
            } else {
                response.status = 404;
                response.set_content("File not found or could not be parsed.", "text/plain");
            }
        } else {
            response.status = 400;
            response.set_content("Error: Missing 'file' query parameter.", "text/plain");
        }
    });

    std::cout << "Server started on http://localhost:8080" << std::endl;
    server.listen("localhost", 8080);

    return 0;
}