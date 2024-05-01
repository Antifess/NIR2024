#include "commandextender.h"
#include <string>
#include <iostream>
#include <fstream>

CommandExtender::CommandExtender() {
}

void CommandExtender::add_cmd(const std::string& newClassName, const std::string& id_alias, int id_number, int parameters_count) {
    //const std::string headerFileName = "F:\\ST\\Proj\\quadrocopter_stm32f4\\App\\Inc\\structs_cmds.h";
    const std::string headerFileName = "../structs_cmds_common.h";
    // Открыть файл для чтения
    std::ifstream headerFile(headerFileName);

    if (!headerFile.is_open()) {
        std::cout << "Ошибка открытия файла " << headerFileName << std::endl;
        return;
    }

    // Прочитать содержимое файла в память
    std::string fileContent((std::istreambuf_iterator<char>(headerFile)),
                            std::istreambuf_iterator<char>());

    headerFile.close();

    // Найти позицию, где вы хотите добавить новый класс
    size_t position = fileContent.find_last_of(';') + 1;

    if (position == std::string::npos) {
        std::cout << "Ошибка: не удалось найти позицию для вставки нового класса" << std::endl;
        return;
    }

    // Сформировать строку с определением нового класса
    std::string newClassDefinition;
    newClassDefinition += "\n";
    newClassDefinition += "\n";
    newClassDefinition += "class __attribute__((packed)) " + newClassName + "{\n";
    newClassDefinition += "public:\n";
    newClassDefinition += "        const cmd_ids::id id = cmd_ids::id::" + id_alias + ";\n";
    newClassDefinition += "    float a1";
    for(int i = 2; i <= parameters_count; i++){
        newClassDefinition += ", a" + std::to_string(i);
    }
    newClassDefinition += ";\n";
    newClassDefinition += "    " + newClassName + "();\n";
    newClassDefinition += "    " + newClassName + "(";
    newClassDefinition += "float a1";
    for(int i = 2; i <= parameters_count; i++){
        newClassDefinition += ", float a" + std::to_string(i);
    }
    newClassDefinition += ");\n";
    newClassDefinition += "};";
    newClassDefinition += "\n";

    // Вставить новое определение класса в содержимое файла
    fileContent.insert(position, newClassDefinition);

    size_t position_alias = fileContent.find_last_of("0x") + 4;
    std::string newAliasDefinition;
    newAliasDefinition += "        " + id_alias + " = 0x";
    if(id_number < 10){
        newAliasDefinition += "0";
    }
    newAliasDefinition += std::to_string(id_number) + ",\n";

    fileContent.insert(position_alias, newAliasDefinition);
    // Открыть файл для записи
    std::ofstream outputFile(headerFileName);

    if (!outputFile.is_open()) {
        std::cout << "Ошибка открытия файла " << headerFileName << " для записи" << std::endl;
        return;
    }

    // Записать обновленное содержимое файла
    outputFile << fileContent;

    outputFile.close();
}
