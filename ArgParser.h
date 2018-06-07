#ifndef IMAGE_DATA_ENCODER_ARGPARSER_H
#define IMAGE_DATA_ENCODER_ARGPARSER_H

#include <string>
#include <map>

struct pair {
    std::string key;
    std::string val;
};

class ArgParser {
private:
    int argc;
    char **argv;
    const char* err;
    std::string arg_str;
    std::map<std::string, std::string> arguments;

public:
    ArgParser(int, char**);
    ~ArgParser() {};

    int parse();
    const char* get_arg(const char *);
};


#endif //IMAGE_DATA_ENCODER_ARGPARSER_H
