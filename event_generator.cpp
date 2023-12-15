#include <iostream>
#include <fstream>
#include <string>

// Function to get user input for a yes/no question
bool getYesNoInput(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt;
    std::getline(std::cin, userInput);
    return userInput == "yes";
}

// Function to get user input for a string
std::string getStringInput(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt;
    std::getline(std::cin, userInput);
    return userInput;
}

// Function to write an event to the file stream
void writeEvent(std::ostream& fileStream, const std::string& namespaceInput, bool isNewNamespace) {
    if (isNewNamespace) {
        fileStream << "add_namespace = " << namespaceInput << "\n";
    }

    std::string eventType = getStringInput("Is it a news event? (yes/no): ");

    // Write event code based on user input
    fileStream << (eventType == "no" ? "country_event {\n" : "news_event {\n");
    if (eventType == "yes") {
        fileStream << "    is_major = yes\n";
    }

    // Implement writing the rest of the event code
    std::string eventID = getStringInput("Enter event ID: ");
    fileStream << "    id = " << namespaceInput << "." << eventID << "\n";
    fileStream << "    title = " << namespaceInput << "." << eventID << ".t\n";
    fileStream << "    desc = " << namespaceInput << "." << eventID << ".d\n";
    fileStream << "    options = {\n        name = " << namespaceInput << "." << eventID << ".a\n   }\n";
    fileStream << "}\n";  // Close the event block
}

// Function to create a new file and write events
void createAndWriteEvents(const std::string& filename, int numEvents) {
    // Create a new file
    std::ofstream newFile(filename + ".txt");

    if (!newFile.is_open()) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }

    std::string namespaceInput = getStringInput("Enter event namespace: ");
    bool isNewNamespace = getYesNoInput("Do you want to create a new namespace? (yes/no): ");

    // Write the specified number of events
    for (int i = 0; i < numEvents; ++i) {
        writeEvent(newFile, namespaceInput, isNewNamespace);
    }

    // Close the file
    newFile.close();
}

// Function to open an existing file in append mode and write events
void appendAndWriteEvents(const std::string& filename, int numEvents) {
    // Check if the file exists
    std::ifstream fileExists(filename);

    // File exists, go to write mode
    std::ofstream existingFile;

    if (fileExists) {
        existingFile.open(filename, std::ios::in | std::ios::out | std::ios::ate);
    } else {
        existingFile.open(filename, std::ios::out);
    }

    if (!existingFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string namespaceInput = getStringInput("Enter event namespace: ");

    // Write the specified number of events
    for (int i = 0; i < numEvents; ++i) {
        writeEvent(existingFile, namespaceInput, false);
    }

    // Close the file
    existingFile.close();
}

int main() {
    std::string fileName = getStringInput("Enter event file name: ");

    // Ask Users for the number of events
    int numEvents;
    std::cout << "How many events do you want to create? ";
    std::cin >> numEvents;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    // Check if the file exists
    std::ifstream fileExists(fileName);
    if (fileExists) {
        // File exists, go to write mode
        appendAndWriteEvents(fileName, numEvents);
    } else {
        // File doesn't exist, go to create mode
        createAndWriteEvents(fileName, numEvents);
    }

    return 0;
}
