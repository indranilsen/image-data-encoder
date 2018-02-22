#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    if (strcmp(argv[1], "") == 0) {
        return -1;
    }

    return 0;
}