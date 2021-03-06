#include <iostream>

#include "ArgParser.h"
#include "PNG_Img.h"
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

int main(int argc, char **argv) {
    ArgParser argument_parser(argc, argv);
    int parse_valid = argument_parser.parse();

    if (parse_valid == -1) {
        return -1;
    }

    PNG_Img image(argument_parser.get_arg("image"));

    int load_success = image.load_image();
    if(load_success == 0) {
        cout << "Load successful. Reading image ...\n";
        image.read_header_info();
        image.read_image();
        image.flush_IDAT_to_file("../test.txt", false);
    } else {
        cout << "Load unsuccessful. Exiting with " << load_success << "...\n";
    }

    Encoder en(&image);
    //en.set_message_from_file("../read.txt");
    en.set_message("Hello World!");
    en.encode_message();
    en.persist();

    Decoder dec("../test/img_encoded.png");
    dec.decode_image();
    dec.output_decoded_msg_to_sdtout();
    dec.output_decoded_msg_to_file("../msg.txt");

    PNG_Img new_img("../test/new_image.png");
    new_img.create_image(
            image.get_width(),
            image.get_height(),
            image.get_bytes_per_pixel(),
            image.get_pixels());
}