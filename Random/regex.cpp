#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string logs = R"(
        2024-12-01 User login from 192.168.1.1
        2024-12-01 Error from 10.0.0.42
        2024-12-02 User logout from 192.168.1.1
    )";

    std::regex ip_regex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))");
    int count = 0;

    // Check for matches and iterate through them
    std::cout << "Extracted IP Addresses:\n";
    for (std::sregex_iterator it(logs.begin(), logs.end(), ip_regex), end; it != end; ++it) {
        std::cout << "  " << it->str() << "\n";
        count++;
    }

    std::cout << "\nTotal IPs Found: " << count << "\n";

    // Replace all IP addresses by surrounding them with brackets
    std::string bracketed_logs = std::regex_replace(logs, ip_regex, "[$&]");
    std::cout << "\nLogs with Bracketed IPs:\n" << bracketed_logs << "\n";

    return 0;
}

