#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
    //liest das file und gibt die Lines aufgeteilt wieder zurück
    std::unordered_map<std::string, int> readfile(std::string filename){
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        std::unordered_map<std::string, int> messageCount;
        std::string line;
        while (std::getline(file, line)) {
            size_t firstColonPos = line.find(':');
            if (firstColonPos != std::string::npos) {
                size_t secondColonPos = line.find(':', firstColonPos + 1);
                if (secondColonPos != std::string::npos && secondColonPos + 1 < line.length()) {
                    std::string sender = line.substr(secondColonPos + 1, line.find(':', secondColonPos + 1) - secondColonPos - 1);
                    messageCount[sender]++;
                }
            }
        }
        file.close();
        return messageCount;
    }

int main() {
    std::string filename = "WhatsAppChat_MFRabbit.txt"; // Change this to the path of your text file
    std::string outputFilename = "message_counts.txt"; // Output file for message counts

    std::unordered_map<std::string, int> messageCount = readfile(filename);

    // Create a vector of pairs (sender, count) for sorting
    std::vector<std::pair<std::string, int>> messageCountVec(messageCount.begin(), messageCount.end());

    // Sort the vector by counts in descending order
    std::sort(messageCountVec.begin(), messageCountVec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Compare counts
    });

    // Write message counts to output file
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    for (const auto& pair : messageCountVec) {
        outputFile << pair.first << ": " << pair.second << std::endl;
    }

    outputFile.close();

    std::cout << "Message counts have been written to " << outputFilename << std::endl;

    return 0;
}
