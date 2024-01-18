/*
单一职责原则（Single Responsibility Principle）是设计模式中的一个重要原则，它要求一个类只应该有一个引起变化的原因。
这意味着一个类应该只有一个职责，只负责一种类型的任务。这有助于降低类的复杂性，提高代码的可维护性。
*/
#include <iostream>
#include <fstream>
#include <string>

// 原始的FileHandler类，违反了单一职责原则
class FileHandler {
public:
    FileHandler(const std::string& filename) : filename(filename) {}

    void readFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << "Reading: " << line << std::endl;
            }
        } else {
            std::cout << "Unable to open file for reading." << std::endl;
        }
    }

    void writeFile(const std::string& content) {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << content << "\n";
            std::cout << "Writing: " << content << std::endl;
        } else {
            std::cout << "Unable to open file for writing." << std::endl;
        }
    }

private:
    std::string filename;
};

// 单一职责原则下的FileReader类
class FileReader {
public:
    FileReader(const std::string& filename) : filename(filename) {}

    void readFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << "Reading: " << line << std::endl;
            }
        } else {
            std::cout << "Unable to open file for reading." << std::endl;
        }
    }

private:
    std::string filename;
};

// 单一职责原则下的FileWriter类
class FileWriter {
public:
    FileWriter(const std::string& filename) : filename(filename) {}

    void writeFile(const std::string& content) {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << content << "\n";
            std::cout << "Writing: " << content << std::endl;
        } else {
            std::cout << "Unable to open file for writing." << std::endl;
        }
    }

private:
    std::string filename;
};

int main() {
    std::string filename = "example.txt";

    // 使用原始的FileHandler类
    FileHandler originalFileHandler(filename);
    originalFileHandler.readFile();
    originalFileHandler.writeFile("New content using original FileHandler.");

    // 使用单一职责原则下的FileReader和FileWriter类
    FileReader fileReader(filename);
    fileReader.readFile();

    FileWriter fileWriter(filename);
    fileWriter.writeFile("New content using FileReader and FileWriter.");

    return 0;
}