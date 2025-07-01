#include "functions.h"
#include <fstream>
#include <sstream>

//Public Methods
void bankAccount::initializeFile() {
    std::ifstream in("transactions.txt");
    if (!in.good()) {
        std::ofstream out("transactions.txt");
        if (out.is_open()) {
            double startingBalance = 0.0;
            out << "Starting balance: " << startingBalance << std::endl;
            out << "Deposited: " << 0.0 << std::endl;
            out << "Withdrawn: " << 0.0 << std::endl;
            out << "Ending Balance: " << startingBalance << std::endl << std::endl;
            out.close();
            std::cout << "transactions.txt initialized with starting balance of $0.00" << std::endl;
        }
        else {
            std::cout << "Error: Unable to create transactions.txt" << std::endl;
        }
    }
    in.close();
}

void bankAccount::addFunds() {
    balance = importLastBalance();
    double amount = numericValidator("Please enter the amount of your deposit: ", 0.0, 100000.0);
    exportTransactions(amount, 0.0);
}

void bankAccount::deductFunds() {
    balance = importLastBalance();
    double amount = numericValidator("Please enter the amount of your withdrawal: ", 0.0, 5000.0);
    if (amount > balance) {
        std::cout << "Insufficient funds." << std::endl << std::endl;
    }
    else {
        exportTransactions(0.0, amount);
    }
}

void bankAccount::printBalance() {
    std::cout << "Your current balance is: " << balance << std::endl << std::endl;
}

//Private Methods
double bankAccount::importLastBalance() {
    std::ifstream in("transactions.txt");
    std::string line;
    std::string lastLine;

    if (in.is_open()) {
        while (std::getline(in, line)) {
            if (line.find("Ending Balance:") == 0) {
                lastLine = line;
            }
        }
        in.close();
    }
    else {
        std::cout << "Error! Unable to read file." << std::endl;
        return 0.0;
    }

    if (!lastLine.empty()) {
        std::istringstream iss(lastLine);
        std::string label1, label2;
        double lastBalance = 0.0;
        iss >> label1 >> label2 >> lastBalance;
        return lastBalance;
    }

    return 0.0;
}

void bankAccount::exportTransactions(double deposit, double withdraw) {
    double current = importLastBalance();

    std::ofstream out("transactions.txt", std::ios::app);
    if (out.is_open()) {
        out << "Starting balance: " << current << std::endl;
        out << "Deposited: " << deposit << std::endl;
        out << "Withdrawn: " << withdraw << std::endl;

        if (withdraw == 0.0) current += deposit;
        else current -= withdraw;

        out << "Ending Balance: " << current << std::endl << std::endl;
        out.close();

        balance = current;
        std::cout << "New balance: " << balance << std::endl;
    }
    else {
        std::cout << "Error! Unable to access file." << std::endl;
    }
}