
#include <algorithm>
#include <string>
#include <vector>
class ArgParser
{

public:
    ArgParser(int &argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    const std::string &getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;

private:
    std::vector<std::string> tokens;
};

bool ArgParser::cmdOptionExists(const std::string &option) const
{
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

const std::string &ArgParser::getCmdOption(const std::string &option) const
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end())
    {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}