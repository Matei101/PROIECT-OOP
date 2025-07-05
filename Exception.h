#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class AppException : public std::exception {
    std::string message;
public:
    explicit AppException(const std::string& msg)
      : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileException : public AppException {
public:
    explicit FileException(const std::string& filename)
      : AppException("Cannot open file: " + filename) {}
};

class FormatException : public AppException {
public:
    explicit FormatException(const std::string& details)
      : AppException("Format error: " + details) {}
};

class BudgetException : public AppException {
public:
    BudgetException(double cost, double balance)
      : AppException(
          "Insufficient budget: cost=" + std::to_string(cost) +
          ", balance=" + std::to_string(balance)
        ) {}
};

#endif // EXCEPTION_H
