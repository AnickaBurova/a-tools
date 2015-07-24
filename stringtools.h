#pragma once

#include <string>
#include <sstream>
#include <regex>


std::string to_snake_case(const std::string& text,char delimiter = '_')
{
    std::ostringstream res;
    bool firstchar = true;
    for(auto&& ch : text)
    {
        if(isupper(ch))
        {
            if(!firstchar)
                res << delimiter;
            else
                firstchar = false;
            res << (char)tolower(ch);
        }
        else
            res << ch;
    }
    return res.str();
}
