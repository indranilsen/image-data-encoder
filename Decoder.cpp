#include <bitset>
#include <iostream>
#include <fstream>
#include "Decoder.h"

Decoder::Decoder(const char *filename) {
    encoded_img = new PNG_Img(filename);
    encoded_img->load_image();
    encoded_img->read_header_info();
    encoded_img->read_image();
}

Decoder::~Decoder() {
    if (encoded_img) {
        delete encoded_img;
    }
}

void Decoder::decode_image() {
    const int EOM_SYMBOL_SIZE = 4;
    const char* EOM_SYMBOL = "@$$@";

    unsigned char *medium;
    unsigned char *pix = encoded_img->get_pixels();

    long num_pixels = encoded_img->get_width() * encoded_img->get_height();

    bool checkEndSequence = false;
    int endSequence = 0;
    std::string msg = "";

    long current_pixel = 0;
    while (current_pixel <= num_pixels) {
        std::bitset<8> byte;
        for (int i = 7; i >= 0; i--) {
            byte.set(i, (pix[current_pixel] & 1));
            current_pixel++;
        }

        char ch = char(byte.to_ulong());

        if (ch == EOM_SYMBOL[0] && !checkEndSequence) {
            checkEndSequence = true;
            endSequence++;
        } else if (checkEndSequence && endSequence >= 1) {
            if (ch != EOM_SYMBOL[endSequence]) {
                checkEndSequence = false;
                endSequence = 0;
            } else {
                endSequence++;
            }
        }

        msg += ch;

        if (checkEndSequence && endSequence == EOM_SYMBOL_SIZE) {
            break;
        }
    }
    char* str = new char[msg.length() - EOM_SYMBOL_SIZE];
    strcpy(str, msg.substr(0, msg.length() - EOM_SYMBOL_SIZE).c_str());
    decoded_message = str;
}

void Decoder::output_decoded_msg_to_sdtout() {
    std::cout << decoded_message;
}

void Decoder::output_decoded_msg_to_file(const char *filename) {
    std::ofstream file(filename);

    if (file.is_open())
    {
        file << decoded_message;

        file.close();
    }
}