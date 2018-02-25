#include <iostream>

#include "PNG_Img.h"
#include "Encoder.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    if (strcmp(argv[1], "") == 0) {
        return -1;
    }

    PNG_Img image(argv[1]);

    int load_success = image.load_image();
    if(load_success == 0) {
        cout << "Load successful. Reading image ...\n";
        image.read_header_info();
        image.read_image();
        image.flush_IDAT_to_file("../test.txt");
    } else {
        cout << "Load unsuccessful. Exiting with " << load_success << "...\n";
    }

    Encoder en(&image);
    en.set_message("hello");

    PNG_Img new_img("../new_image.png");
    new_img.create_image(
            image.get_width(),
            image.get_height(),
            image.get_bytes_per_pixel(),
            image.get_pixels());
}