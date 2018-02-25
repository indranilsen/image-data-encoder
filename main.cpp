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
    Encoder en(&image);
    en.set_message("hello");

    int load_success = image.load_image();
    if(load_success == 0) {
        cout << "Load successful. Reading image ...\n";
        image.read_header_info();
        image.read_image();
        image.flush_IDAT_to_file("../test.txt");
    } else {
        cout << "Load unsuccessful. Exiting with " << load_success << "...\n";
    }
}