#pragma once
#include <memory>
#include <string>
#include <sstream>
#include "NPC.h"
#include "Knight.h"
#include "Druid.h"
#include "Elf.h"

// Паттерн Factory для создания NPC
class NPCFactory
{
public:
    static std::shared_ptr<NPC> createNPC(const std::string &type, const std::string &name, double x, double y)
    {
        if (type == "Knight")
        {
            return std::make_shared<Knight>(name, x, y);
        }
        else if (type == "Druid")
        {
            return std::make_shared<Druid>(name, x, y);
        }
        else if (type == "Elf")
        {
            return std::make_shared<Elf>(name, x, y);
        }
        return nullptr;
    }

    // Создание NPC из строки файла
    static std::shared_ptr<NPC> createFromString(const std::string &line)
    {
        std::istringstream iss(line);
        std::string type, name;
        double x, y;

        if (iss >> type >> name >> x >> y)
        {
            return createNPC(type, name, x, y);
        }
        return nullptr;
    }
};
