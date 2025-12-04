#include "Elf.h"
#include "Knight.h"
#include "Druid.h"

void Elf::accept(Visitor &visitor, NPC &other)
{
    if (auto *knight = dynamic_cast<Knight *>(&other))
    {
        visitor.visitElf(*this, *knight);
    }
    else if (auto *druid = dynamic_cast<Druid *>(&other))
    {
        visitor.visitElf(*this, *druid);
    }
    else if (auto *elf = dynamic_cast<Elf *>(&other))
    {
        visitor.visitElf(*this, *elf);
    }
}
