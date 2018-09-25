#include "includes/ArgumentParser.hpp"


ArgumentParser::ArgumentParser(int argc, char *argv[]) {
    this->argc = argc;

    for (int i = 0; i < argc; i++)
        this->argv.push_back(std::string(argv[i]));
};

bool ArgumentParser::was_argument_given(std::string key) {
    for (int i = 0; i < this->argc; i++)
        if (key.c_str() == this->argv[i])
            return true;

    return false;
};

void ArgumentParser::add_argument(std::string key) {
    this->arguments.push_back(key);
};

std::string ArgumentParser::get_argument(std::string key) {
    int i = 1;

    while (i < this->argc) {
        std::string _key = this->argv[i];
        std::string value = this->argv[i+1];

        if (std::find(this->arguments.begin(), this->arguments.end(), _key) == this->arguments.end())
            throw std::runtime_error("Invalid argument: " + _key);

        if (_key == key)
            return value;

        i += 2;
    }

    return "";
};
