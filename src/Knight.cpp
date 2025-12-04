#include "Knight.h"
#include "Druid.h"
#include "Elf.h"

void Knight::accept(Visitor &visitor, NPC &other)
{
    if (auto *knight = dynamic_cast<Knight *>(&other))
    {
        visitor.visitKnight(*this, *knight);
    }
    else if (auto *druid = dynamic_cast<Druid *>(&other))
    {
        visitor.visitKnight(*this, *druid);
    }
    else if (auto *elf = dynamic_cast<Elf *>(&other))
    {
        visitor.visitKnight(*this, *elf);
    }
}
