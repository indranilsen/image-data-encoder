#ifndef IMAGE_DATA_ENCODER_PNG_IMG_H
#define IMAGE_DATA_ENCODER_PNG_IMG_H

#include <png.h>

class PNG_Img {
private:
    const char *filename;
    FILE *fp;

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
    long get_width();
    long get_height();
    long get_bytes_per_pixel();
    unsigned char* get_pixels();

    int load_image();
    void read_header_info();
    void read_image();

    int create_image(long, long, long, unsigned char *);

    void flush_IDAT_to_file(const char *, bool);
};


#endif //IMAGE_DATA_ENCODER_PNG_IMG_H
