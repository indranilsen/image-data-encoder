#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Encoder.h"

const int END_SYMBOL_SIZE = 4;
const char* END_SYMBOL = "@$$@";

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

const char* append_suffix(const char* str, const char* suffix) {
    std::string s(str);
    s = s.substr(0, s.find(".png")) + suffix + s.substr(s.find(".png"), s.length());
    const char *val = s.c_str();
    char *ret_val = new char[s.length()];
    strcpy(ret_val, val);
    return ret_val;
}

void append_end_symbol(std::bitset<8>* bytes, long len) {
    for (int i = 0; i < END_SYMBOL_SIZE; i++) {
        bytes[len + i] = std::bitset<8>(END_SYMBOL[i]);
    }
}

Encoder::Encoder(PNG_Img *img) {
    orig_img = img;
    new_img = new PNG_Img(append_suffix(orig_img->get_filename(), "_encoded"));
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
    bytes = new std::bitset<8> [str.length() + END_SYMBOL_SIZE];

    for (int i = 0; i < str.length(); i++) {
        bytes[i] = std::bitset<8>(str.c_str()[i]);
    }

    append_end_symbol(bytes, str.length());
}

void Encoder::set_message_from_file(const char* filename) {
    std::string str = read_message_from_file(filename);

    message = str;
    bytes = new std::bitset<8> [str.length() + END_SYMBOL_SIZE];

    for (int i = 0; i < str.length(); i++) {
        bytes[i] = std::bitset<8>(str.c_str()[i]);
    }

    append_end_symbol(bytes, str.length());
}

int Encoder::encode_message() {
    unsigned char *medium = orig_img->get_pixels();

    long num_pixels = orig_img->get_width() * orig_img->get_height();
    if ((num_pixels * orig_img->get_bytes_per_pixel()) < (message.length()*8)) {
        return -1;
    }

    int m_count = 0;
    for (int i = 0; i < message.length() + END_SYMBOL_SIZE; i++) {
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

    orig_img->flush_IDAT_to_file("../neil.txt", true);

    return 0;
}

int Encoder::persist() {
    return new_img->create_image(
            orig_img->get_width(),
            orig_img->get_height(),
            orig_img->get_bytes_per_pixel(),
            orig_img->get_pixels());
}