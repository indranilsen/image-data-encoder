#ifndef IMAGE_DATA_ENCODER_ENCODER_H
#define IMAGE_DATA_ENCODER_ENCODER_H

#include "PNG_Img.h"

class Encoder {
private:
    PNG_Img *orig_img;
    PNG_Img *new_img;
    std::string message;
    std::bitset<8>* bytes;

public:
    Encoder(PNG_Img *);
    ~Encoder();

    void set_message(std::string);
    void set_message_from_file(const char* filename);

    int encode_message();

    int persist();

};

#endif //IMAGE_DATA_ENCODER_ENCODER_H
