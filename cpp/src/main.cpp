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
    std::cout << "Memory (max resident set size): " << usage.ru_maxrss << " KB\n";
}

int main (int argc, char *argv[]) {

    int numThreads = std::thread::hardware_concurrency();
    bool force = false;

    if (argc == 3 && strcmp(argv[2], "--force") == 0) { 
        numThreads = std::stoi(argv[1]);
        force = true;
    } else if (argc == 2) {
        std::cout << "\033[2J\033[H"; // Clear terminal
        try {
            std::string answer;
            int inputThreads = std::stoi(argv[1]);
            std::cout << BLUE << "You've asked for " << inputThreads << " threads to run this program.\n" << RESET;

            if (inputThreads < numThreads) {
                std::cout << "Your computer can support " << GREEN << numThreads << RESET
                          << " threads, are you sure you want to run with only " << YELLOW << inputThreads << RESET << " threads? [y/n]: ";
                std::cin >> answer;
                if (answer == "y" || answer == "Y") {
                    numThreads = inputThreads;
                }
            } else if (inputThreads > numThreads) {
                std::cout << RED << "Warning: " << RESET << "Your computer can only support " << GREEN << numThreads << RESET 
                          << " threads efficiently. Do you still want to use " << YELLOW << inputThreads << RESET << " threads? [y/n]: ";
                std::cin >> answer;
                if (answer == "y" || answer == "Y") {
                    numThreads = inputThreads;
                }
            } else {
                numThreads = inputThreads;
            }
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Not a number\n";
            return 1;
        } catch (const std::out_of_range&) {
            std::cerr << "Number out of range\n";
            return 1;
        }
    }

    std::cout << "Running with " << BLUE << numThreads << RESET << " threads.\n";

    // Continue with master-slave execution
    Master master(numThreads, force);
    master.handleWorkers();

    printResourceUsage();

    std::cout << "Done !\n";

    return 0;
}
