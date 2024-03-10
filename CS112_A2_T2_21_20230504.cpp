#include <iostream>
#include <bitset>
#include <sstream>

using namespace std;

// Global array to store character mappings for encryption and decryption
string chars[26][2];

// Function to initialize the character mapping array
void BaconianDictionary() {
    int n = 5; // Number of bits for each character
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // English alphabet

    // Populate the character mapping array
    for (int i = 0; i < 26; i++) {
        // Convert the decimal index to a binary string of 32 bits
        bitset<32> b(i);

        // Extract the last 'n' bits of the binary representation
        string temp = b.to_string().substr(32 - n);

        // Convert '0's to 'a' and '1's to 'b' in the binary representation
        for (int j = 0; j < n; j++) {
            temp[j] = (temp[j] == '0') ? 'a' : 'b';
        }

        // Store the character mapping in the global array
        chars[i][1] = temp;
    }

    // Associate each character with its corresponding index in the alphabet
    for (int i = 0; i < 26; i++) {
        chars[i][0] = alpha[i];
    }
}

// Function to encrypt a given string using the character mapping
string BaconianEncrypt(string str) {
    string temp = "";

    // Iterate through each character in the input string
    for (int i = 0; i < str.length(); i++) {
        // Search for the character in the character mapping array
        for (int j = 0; j < 26; j++) {
            // If a match is found, append the corresponding binary representation
            if (str[i] == chars[j][0][0]) {
                temp += chars[j][1] + " ";
            }
        }
    }
    return temp;
}

// Function to decrypt a given string using the character mapping
string BaconianDecrypt(string str) {
    string temp = "";
    stringstream ss(str);
    string word;

    // Tokenize the input string based on spaces
    while (ss >> word) {
        // Search for the binary representation in the character mapping array
        for (int i = 0; i < 26; i++) {
            // If a match is found, append the corresponding character
            if (word == chars[i][1]) {
                temp += chars[i][0];
            }
        }
    }
    return temp;
}

// Function to check if a string contains any numeric digits
bool HasNumber(const std::string &str) {
    for (char c : str) {
        if (std::isdigit(c)) {
            return true; // Return true as soon as a digit is found
        }
    }
    return false; // No digit found in the string
}

int main() {
    // Initialize the character mapping array
    BaconianDictionary();

    while (true) {
        cout << "Ahlan ya user ya habibi.\nWhat do you like to do today?\n1-Cipher a message\n2-Decipher a message\n3-End\n>> ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Please enter a message to cipher:\n";
            string str;
            getline(cin >> ws, str); // Use getline to handle spaces in the input
            if (HasNumber(str)) {
                cout << "Invalid input. The input must consist of letters only.\n" << endl;
                continue;
            }
            for (char &c : str) {
                c = toupper(c);
            }
            cout << "Encrypted String: " << BaconianEncrypt(str) << "\n" << endl;
        } else if (choice == 2) {
            cout << "Please enter a message to decipher:\n";
            string str;
            getline(cin >> ws, str); // Use getline to handle spaces in the input
            if (str.length() < 5) {
                cout << "Invalid input. The input must be at least 5 bits.\n" << endl;
                continue;
            } else if (HasNumber(str)) {
                cout << "Invalid input. The input must consist of letters only.\n" << endl;
                continue;
            }
            for (char &c : str) {
                c = tolower(c);
            }
            bool valid = true;
            for (char &c : str) {
                if (c != 'a' && c != 'b' && c != ' ') {
                    cout << "Invalid input. The input must consist of 'a's and 'b's only.\n" << endl;
                    valid = false;
                    break;
                }
            }
            if (valid) {
                cout << "Decrypted String: " << BaconianDecrypt(str) << "\n" << endl;
            }
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            return 0;
        } else {
            cout << "Invalid input. Please choose 1 for encryption or 2 for decryption.\n";
        }
    }
    return 0;
}
