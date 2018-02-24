#include <iostream>
#include <fstream>
#include <bitset>
#include <png.h>
#include "PNG_Img.h"

PNG_Img::PNG_Img(const char *fname) {
    filename = fname;
}

PNG_Img::~PNG_Img() {
    f = NULL;

    if (pixels != NULL) {
        delete [] pixels;
        pixels = NULL;
    }
}

int PNG_Img::load_image() {
    f = fopen(filename, "rb");

    if (f == NULL) {
        return -1;
    }

    unsigned char signature[8];

    if (fread(signature, 1, sizeof(signature), f) < 8) {
        fclose(f);
        return -1;
    }

    if (png_sig_cmp(signature, 0, 8)) {
        fclose(f);
        return -1;
    }

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(f);
        return 4;
    }

    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(f);
        return 4;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(f);

        if (pixels != NULL) {
            delete [] pixels;
            pixels = NULL;
        }

        return -1;
    }

    return 0;
}

void PNG_Img::read_header_info() {
    png_init_io(png, f);

    png_set_sig_bytes(png, 8);

    png_read_info(png, info);

    height = png_get_image_height(png, info);
    width = png_get_image_width(png, info);

    if (png_get_bit_depth(png, info) < 8) {
        png_set_packing(png);
    }

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }

    bytes_per_pixel = png_get_rowbytes(png, info) / width;

    png_set_interlace_handling(png);

    png_read_update_info(png, info);
}

void PNG_Img::read_image() {
    pixels = new unsigned char[width * height * bytes_per_pixel];

    png_bytep rows[height];
    unsigned char *p = pixels;

    for (int i = 0; i < height; i++) {
        rows[i] = p;
        p += width * bytes_per_pixel;
    }

    png_read_image(png, rows);

    png_read_end(png, NULL);

    png_destroy_read_struct(&png, &info, NULL);
    fclose(f);
}

void PNG_Img::flush_IDAT_to_file(const char *filename) {
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (int i = 0; i <= (width * height * bytes_per_pixel); i += 3) {
            if (i % (width * bytes_per_pixel) == 0) {
                file << "\n\n";
            }

            file << i << ":(" << (int)pixels[i] << ", " << (int)pixels[i+1] << ", " << (int)pixels[i+2] << ") ";
            std::cout << i << ":(" << std::bitset<8>(pixels[i]) << ", " << std::bitset<8>(pixels[i+1]) << ", " << std::bitset<8>(pixels[i+2]) << ") ";
        }

        file.close();
    }
}