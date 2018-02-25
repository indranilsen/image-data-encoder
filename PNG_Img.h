#ifndef IMAGE_DATA_ENCODER_PNG_IMG_H
#define IMAGE_DATA_ENCODER_PNG_IMG_H

#include <png.h>

class PNG_Img {
private:
    const char *filename;
    FILE *f;

    png_structp png;
    png_infop info;

    long height;
    long width;
    long bytes_per_pixel;
    unsigned char *pixels;


public:
    PNG_Img(const char *);
    ~PNG_Img();

    const char* get_filename();

    int load_image();
    void read_header_info();
    void read_image();
    void flush_IDAT_to_file(const char *);
};


#endif //IMAGE_DATA_ENCODER_PNG_IMG_H
