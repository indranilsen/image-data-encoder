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
    new_img = new PNG_Img("../encoded.png");
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

int Encoder::encode_message() {
    unsigned char *medium = orig_img->get_pixels();

    long num_pixels = orig_img->get_width() * orig_img->get_height();
    if ((num_pixels * orig_img->get_bytes_per_pixel()) < (message.length()*8)) {
        return -1;
    }

    int m_count = 0;
    for (int i = 0; i < message.length(); i++) {
        for (int j = 7; j >= 0; j--) {
            if (bytes[i][j]) {
                if ((medium[m_count] & 1) == 0) {
                    medium[m_count] ^= 1;
                }
            } else {
                if ((medium[m_count] & 1) == 1) {
                    medium[m_count] ^= 1;
                }
            }

            m_count++;
        }
    }

    return 0;
}

int Encoder::persist() {
    return new_img->create_image(
            orig_img->get_width(),
            orig_img->get_height(),
            orig_img->get_bytes_per_pixel(),
            orig_img->get_pixels());
}