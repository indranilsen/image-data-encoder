#include <bitset>
#include <iostream>
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
    unsigned char *medium;
    unsigned char *pix = encoded_img->get_pixels();

    long num_pixels = encoded_img->get_width() * encoded_img->get_height();

    long current_pixel = 0;
    while (current_pixel <= num_pixels) {
        std::bitset<8> byte;
        for (int i = 7; i >= 0; i--) {
            byte.set(i, (pix[current_pixel] & 1));
            current_pixel++;
        }
        std::cout<< char(byte.to_ulong());
    }
}
