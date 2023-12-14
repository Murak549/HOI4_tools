#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

class FileProcessor {
public:
    explicit FileProcessor(const std::string& directoryPath) : directoryPath_(directoryPath) {}

    void writeAllFiles(std::ostream& outputFile) const {
        for (const auto& entry : fs::directory_iterator(directoryPath_)) {
            if (entry.is_regular_file()) {
                processFile(entry, outputFile);
            }
        }
    }

    std::vector<std::string> getFileNames() const {
        std::vector<std::string> fileNames;
        for (const auto& entry : fs::directory_iterator(directoryPath_)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename());
            }
        }
        return fileNames;
    }

private:
    std::string directoryPath_;

    void processFile(const fs::directory_entry& entry, std::ostream& outputFile) const {
        std::ifstream file(entry.path());
        if (file.is_open()) {
            outputFile << "Content from " << entry.path().filename() << ":\n";
            outputFile << file.rdbuf() << "\n\n";
            file.close();
        } else {
            std::cerr << "Error opening file: " << entry.path() << std::endl;
        }
    }
};

class FileManager {
public:
    FileManager(const std::string& outputPath) : outputPath_(outputPath) {}

    void processFilesAndWrite(const std::string& inputPath) const {
        std::cout << "Wrote content of all files in " << inputPath << "..." << std::endl;

        // Open a file at outputPath_ for writing
        std::ofstream outFile(outputPath_);

        // Check if the file is opened successfully
        if (outFile.is_open()) {
            FileProcessor fileProcessor(inputPath);
            fileProcessor.writeAllFiles(outFile);

            // Close the file
            outFile.close();
        } else {
            std::cerr << "Error opening the file." << std::endl;
        }
    }

    void compareFilesAndOutputUnregistered(const std::string& inputPath, const std::string& referenceFilePath) const {
        FileProcessor inputFileProcessor(inputPath);
        FileProcessor referenceFileProcessor(referenceFilePath);

        std::vector<std::string> inputFiles = inputFileProcessor.getFileNames();
        std::vector<std::string> referenceFiles = referenceFileProcessor.getFileNames();

        std::sort(inputFiles.begin(), inputFiles.end());
        std::sort(referenceFiles.begin(), referenceFiles.end());

        std::vector<std::string> unregisteredFiles;
        std::set_difference(inputFiles.begin(), inputFiles.end(), referenceFiles.begin(), referenceFiles.end(),
                            std::inserter(unregisteredFiles, unregisteredFiles.begin()));

        std::cout << "Unregistered files in " << inputPath << ":\n";
        for (const auto& fileName : unregisteredFiles) {
            std::cout << fileName << '\n';
        }
    }

    void printLoveMessage() const {
        std::cout << "사랑해요 윤석열" << std::endl;
    }

private:
    std::string outputPath_;
};

int main() {
    int input;
    std::cin >> input;

    switch (input) {
        case 1: {
            FileManager fileManager("./useful_file/gfx.txt");
            fileManager.processFilesAndWrite("./gfx");
            break;
        }
        case 2: {
            FileManager fileManager("./useful_file/gfx.txt");
            fileManager.compareFilesAndOutputUnregistered("./gfx", "./useful_file/gfx.txt");
            break;
        }
        case 3: {
            FileManager fileManager("");  //super-duper function bruh~~~~~~!
            fileManager.printLoveMessage();
            break;
        }
    }

    return 0;
}