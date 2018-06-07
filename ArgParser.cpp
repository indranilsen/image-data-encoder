#include "ArgParser.h"

ArgParser::ArgParser(int arg_count, char **arg_value) {
    argc = arg_count;
    argv = arg_value;
}

char* is_argument(char *long_arg) {
    return strchr(long_arg, '=');
}

pair get_argument(char *long_arg) {
    std::string arg(long_arg);
    unsigned long pos_eq = arg.find('=');
    return {arg.substr(2, pos_eq - 2), arg.substr(pos_eq + 1, arg.length())};
}



int ArgParser::parse() {
    if (argc < 2) {
        err = "Missing arguments";
        return -1;
    }

    for (int i = 0; i < argc; i++) {
        if (is_argument(argv[i]) != NULL) {
            pair arg = get_argument(argv[i]);
            arguments[arg.key] = arg.val;
        }
    }

    return 0;
}

const char* ArgParser::get_arg(const char* str) {
    std::string key(str);
    if (arguments.find(key) != arguments.end()) {
        return arguments[key].c_str();
    } else {
        return "";
    }
}