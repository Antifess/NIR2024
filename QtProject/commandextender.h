#ifndef COMMANDEXTENDER_H
#define COMMANDEXTENDER_H

#include <string>

class CommandExtender
{
public:
    CommandExtender();
    void add_cmd(const std::string& newClassName, const std::string& id_alias, int id_number, int parameters_count);
};

#endif // COMMANDEXTENDER_H
