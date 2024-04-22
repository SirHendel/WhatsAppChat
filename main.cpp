#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

struct Message {
    string date;
    string time;
    string sender;
    string content;
};

vector<Message> readfile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return {};
    }

    vector<Message> messages;

    string line;
    while (getline(file, line)) {
       Message msg;
        // Extract date
        size_t firstDashPos = line.find('-');
        if (firstDashPos != string::npos) {
            msg.date = line.substr(0, firstDashPos);
            line = line.substr(firstDashPos + 1); // Skip dash and space
        }

        // Extract time
        size_t secondDashPos = line.find('-', firstDashPos + 1); // Find next dash
        if (secondDashPos != string::npos) {
            msg.time = line.substr(firstDashPos + 2, secondDashPos - (firstDashPos + 2));
            line = line.substr(secondDashPos + 1); // Skip dash and space
        }
        // Extract sender (until the next colon)
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            msg.sender = line.substr(0, colonPos);
            line = line.substr(colonPos + 1 ); // Skip colon and space
        }

        // Content is the rest of the line
        msg.content = line;

        messages.push_back(msg);
    }

    file.close();
    return messages;
}

int  countMessagesBySender(const vector<Message>& messages, string Sender) {
    int messageCount=0;
    for (const auto& msg : messages) {
        if (msg.sender == Sender)
          messageCount++;
    }
    return messageCount;
}

int countILoveYouMessagesBySender(const vector<Message>& messages, const string& sender) {
    int messageCount = 0;
    for (const auto& msg : messages) {
        if (msg.sender == sender && msg.content.find("I love you") != string::npos) {
            messageCount++;
        }
    }
    return messageCount;
}
// Function to find the sender who sent the most "I love you" or similar messages
string findMostILoveYouSender(const vector<Message>& messages) {
    string mostILoveYouSender;
    int maxILoveYouCount = 0;
    for (const auto& msg : messages) {
        int count = countILoveYouMessagesBySender(messages, msg.sender);
        if (count > maxILoveYouCount) {
            maxILoveYouCount = count;
            mostILoveYouSender = msg.sender;
        }
    }
    return mostILoveYouSender;
}

void writefile(string outputFilename, const vector<Message>& messages){
    ofstream outputFile(outputFilename);
    try
    {
        if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;    
        }
        outputFile<<"Most texts Writen:"<<endl;
        outputFile<<messages[0].sender + " has send: " << countMessagesBySender(messages, messages[0].sender)<<endl;
        outputFile<<messages[1].sender + " has send: " << countMessagesBySender(messages, messages[1].sender)<<endl;
        string mostILoveYouSender = findMostILoveYouSender(messages);
        cout<<mostILoveYouSender +" Really"<<endl;
        if (!mostILoveYouSender.empty()) {
            
            outputFile << mostILoveYouSender << " has sent the most 'I love you' or similar messages." << endl;
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

int main() {
    string filename = "WhatsAppChat_MFRabbit.txt"; // Change this to the path of your text file
    string outputFilename = "message.txt"; // Output file for message counts

    vector<Message> messages = readfile(filename);
    writefile(outputFilename,messages);

    return 0;
}
