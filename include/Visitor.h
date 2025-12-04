#pragma once

class Knight;
class Druid;
class Elf;

// Интерфейс Visitor для реализации боевой логики
class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visitKnight(Knight &attacker, Knight &defender) = 0;
    virtual void visitKnight(Knight &attacker, Druid &defender) = 0;
    virtual void visitKnight(Knight &attacker, Elf &defender) = 0;

    virtual void visitDruid(Druid &attacker, Knight &defender) = 0;
    virtual void visitDruid(Druid &attacker, Druid &defender) = 0;
    virtual void visitDruid(Druid &attacker, Elf &defender) = 0;

    virtual void visitElf(Elf &attacker, Knight &defender) = 0;
    virtual void visitElf(Elf &attacker, Druid &defender) = 0;
    virtual void visitElf(Elf &attacker, Elf &defender) = 0;
};
