#pragma once
#include <string>
#include <limits>
#include <iostream>

class bankAccount {
public:
    //Public Interface
    void initializeFile();
    void addFunds();      
    void deductFunds();              
    void printBalance();

    // Templated Validator
    template <typename T>
    T numericValidator(const std::string& prompt, T min, T max) {
        T number;
        while (true) {
            std::cout << prompt << std::endl;
            std::cin >> number;

            if (std::cin.fail()) {
                std::cout << "Enter a valid number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else if (number < min || number > max) {
                std::cout << "Input must be between " << min << " and " << max << "." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
        return number;
    }

private:
    //Private Data and Helpers
    double balance = 0.0;

    double importLastBalance();
    void exportTransactions(double deposit, double withdraw);
};