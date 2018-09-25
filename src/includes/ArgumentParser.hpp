#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H
#include <map>
#include <string>
#include <vector>
#include <algorithm>


class ArgumentParser {
    public:
        ArgumentParser(int argc, char* argv[]);

        int argc;

        std::vector<std::string> argv;
        std::vector<std::string> arguments;


        bool was_argument_given(std::string key);

        void add_argument(std::string key);

        std::string get_argument(std::string key);
};
#endif
