#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include "Encoder.h"

std::string read_message_from_file(const char* filename) {
    std::string message, line;
    std::ifstream file(filename);

    if (file.is_open()) {
        while(getline(file, line)) {
            message += line + '\n';
        }

        file.close();
    }

    return message;
}

Encoder::Encoder(PNG_Img *img) {
    orig_img = img;
    new_img = new PNG_Img(img->get_filename());
}

Encoder::~Encoder() {
    if (!orig_img) {
        delete orig_img;
    }

    if (!new_img) {
        delete new_img;
    }
}

void Encoder::set_message(std::string str) {
    message = str;
    bytes = new std::bitset<8> [str.length()];

    for (int i = 0; i < str.length(); i++) {
        bytes[i] = std::bitset<8>(str.c_str()[i]);
    }
}

void Encoder::set_message_from_file(const char* filename) {
    std::string str = read_message_from_file(filename);

    message = str;
    bytes = new std::bitset<8> [str.length()];

    for (int i = 0; i < str.length(); i++) {
        bytes[i] = std::bitset<8>(str.c_str()[i]);
    }
}