#ifndef IMAGE_DATA_ENCODER_DECODER_H
#define IMAGE_DATA_ENCODER_DECODER_H

#include "PNG_Img.h"

class Decoder {
private:
    PNG_Img *encoded_img;
    const char* decoded_message;

public:
    Decoder(const char*);
    ~Decoder();

    void decode_image();
};


#endif //IMAGE_DATA_ENCODER_DECODER_H
