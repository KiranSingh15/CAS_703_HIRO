#include <iostream>
#include <string>
#include "../include/master.hpp"
#include <sys/resource.h> 

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"

extern const std::string IMPORT_PATH = "../images/";
extern const std::string EXPORT_PATH = "../output/";

void printResourceUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    
    std::cout << "CPU Time: " << (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) << " sec\n";
    std::cout << "Memory (max resident set size): " << usage.ru_maxrss << " kB\n";
}

int main (int argc, char *argv[]) {

    int numThreads = std::thread::hardware_concurrency();
    bool force = false;
    bool save = true;
    bool manualThreadSet = false;
    int requestedThreads = numThreads;

    // Parse all arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--force") == 0) {
            force = true;
        } else if (strcmp(argv[i], "--no-save") == 0) {
            save = false;
        } else {
            // Try parsing as thread count
            try {
                requestedThreads = std::stoi(argv[i]);
                manualThreadSet = true;
            } catch (const std::invalid_argument&) {
                std::cerr << YELLOW << "Warning: Ignored unrecognized argument: " << argv[i] << RESET << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << RED << "Thread count out of range: " << argv[i] << RESET << std::endl;
                return 1;
            }
        }
    }

    // If manual thread count was provided and not forced, confirm with user
    if (manualThreadSet && !force) {
        std::cout << "\033[2J\033[H"; // Clear terminal
        std::string answer;

        std::cout << BLUE << "You've asked for " << requestedThreads << " threads to run this program.\n" << RESET;

        if (requestedThreads < numThreads) {
            std::cout << "Your computer can support " << GREEN << numThreads << RESET
                << " threads, are you sure you want to run with only " << YELLOW << requestedThreads << RESET << " threads? [y/n]: ";
            std::cin >> answer;
            if (answer == "y" || answer == "Y") {
                numThreads = requestedThreads;
            }
        } else if (requestedThreads > numThreads) {
            std::cout << RED << "Warning: " << RESET << "Your computer can only support " << GREEN << numThreads << RESET 
                << " threads efficiently. Do you still want to use " << YELLOW << requestedThreads << RESET << " threads? [y/n]: ";
            std::cin >> answer;
            if (answer == "y" || answer == "Y") {
                numThreads = requestedThreads;
            }
        } else {
            numThreads = requestedThreads;
        }
    }

    std::cout << "Running with " << BLUE << numThreads << RESET << " threads.\n";

    // Continue with master-slave execution
    Master master(numThreads, force, save);
    master.handleWorkers();

    printResourceUsage();

    std::cout << "Done !\n";

    return 0;
}
