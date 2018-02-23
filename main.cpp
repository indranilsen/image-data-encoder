#include <iostream>
#include <png.h>

using namespace std;

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

    int load_image();
    void read_header_info();
    void read_image();
};

PNG_Img::PNG_Img(const char *fname) {
    filename = fname;
}

PNG_Img::~PNG_Img() {
    f = NULL;
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

    bytes_per_pixel = (uint)png_get_rowbytes(png, info) / width;

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
    } else {
        cout << "Load unsuccessful. Exiting with " << load_success << "...\n";
    }
}