#include <iostream>
#include <random>
#include <algorithm>

//region Constants
const int MIN_PASSWORD_LENGTH = 4;
const int MAX_PASSWORD_LENGTH = 64;

const std::string LOWER_CASE = "abcdefghijklmnopqrstuvwxyz";
const std::string UPPER_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string SPECIAL_CHARS = "!@#$%^&*()_+?[].";
const std::string ALL_CHARS = LOWER_CASE + UPPER_CASE + NUMBERS + SPECIAL_CHARS;
//endregion

//region Prototypes
std::string pwgen(int length);
int askForLength();
int askForLength(int argc, char* argv[]);
char randomChar(const std::string& chars);
//endregion

std::random_device rd;
std::mt19937 gen(rd());

int main(int argc, char* argv[]) {
    std::string psswrd = pwgen(askForLength(argc, argv));
    std::cout << "Generated password: " << psswrd << std::endl;
    std::cout << "Password length: " << psswrd.length() << std::endl;
    return 0;
}

std::string pwgen(int length) {
    if(length > MAX_PASSWORD_LENGTH) {
        std::cout << "Number too high. Defaulting to " << MAX_PASSWORD_LENGTH << std::endl;
        length = MAX_PASSWORD_LENGTH;
    }
    std::string response;

    response.reserve(length);

    response += randomChar(LOWER_CASE);
    response += randomChar(UPPER_CASE);
    response += randomChar(NUMBERS);
    response += randomChar(SPECIAL_CHARS);

    for(int i = 4; i < length; i++) {
        response += randomChar(ALL_CHARS);
    }

    std::vector<char> chars(response.begin(), response.end());
    std::shuffle(chars.begin(), chars.end(), gen);
    response = std::string(chars.begin(), chars.end());

    return response;
}

int askForLength(int argc, char* argv[]) {
    if(argc > 1) {
        try {
            int length = std::stoi(argv[1]);
            if(length >= MIN_PASSWORD_LENGTH) {
                return length;
            }
            std::cout << "Invalid input. Defaulting to interactive mode." << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Defaulting to interactive mode." << std::endl;
        }
    }
    return askForLength();
}

int askForLength() {
    int response;
    while (true) {
        try {
            std::cout << "Input length: " << std::endl;
            std::cin >> response;
            if(response >= MIN_PASSWORD_LENGTH) {
                break;
            }
            std::cout << "Invalid number. Enter " << MIN_PASSWORD_LENGTH << " or greater." << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
        }
    }
    return response;
}

char randomChar(const std::string& chars) {
    std::uniform_int_distribution<int> dis(0, chars.length() - 1);
    return chars[dis(gen)];
}
