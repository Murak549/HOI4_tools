#include <iostream>
#include <fstream>
#include <string>

void writeMode(std::ostream& fileStream) {
    std::string namespaceInput;
    std::cout << "Enter new event namespace: ";
    std::getline(std::cin, namespaceInput);

    // Write "add_namespace = <input>" at the first line of the file
    fileStream << "add_namespace = " << namespaceInput << "\n";

    std::cout << "Do you want to create a new namespace? (yes/no): ";
    std::string createNewNamespace;
    std::getline(std::cin, createNewNamespace);

    if (createNewNamespace == "yes") {
        // Ask users for more input
        // Implement your logic here based on user input
    } else {
        // Ask users for existing namespace, event number, and event type
        // Implement your logic here based on user input

        std::string eventType;
        std::cout << "Is it a news event? (yes/no): ";
        std::getline(std::cin, eventType);

        // Write event code based on user input
        if (eventType == "no") {
            fileStream << "country_event {\n";
        } else if (eventType == "yes") {
            fileStream << "news_event {\n";
            fileStream << "    is_major = yes\n";
        }

        // Implement writing the rest of the event code
        std::cout << "Enter event ID: ";
        std::string eventID;
        std::getline(std::cin, eventID);
        fileStream << "    id = " << namespaceInput << "." << eventID << "\n";
        fileStream << "    title =" << namespaceInput << "." << eventID << ".t\n";
        fileStream << "    desc =" << namespaceInput << "." << eventID << ".d\n";
        fileStream << "    options = {\n    name =" << namespaceInput << eventID << ".a\n";

        fileStream << "}\n";  // Close the event block
    }
}

void createMode(const std::string& filename) {
    // Create a new file
    std::ofstream newFile(filename);

    if (!newFile.is_open()) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }

    // Go to write mode for the new file
    writeMode(newFile);

    // Close the file
    newFile.close();
}

int main() {
    std::string fileName;
    std::cout << "Enter event file name: ";
    std::getline(std::cin, fileName);

    // Check if the file exists
    std::ifstream fileExists(fileName);
    if (fileExists) {
        // File exists, go to write mode
        std::ofstream existingFile(fileName, std::ios::app);  // Open in append mode
        writeMode(existingFile);
        existingFile.close();
    } else {
        // File doesn't exist, go to create mode
        createMode(fileName);
    }

    return 0;
}