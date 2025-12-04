#pragma once
#include "Visitor.h"
#include "Knight.h"
#include "Druid.h"
#include "Elf.h"
#include "Observer.h"

// Реализация Visitor для боевой системы
// Правила боя:
// - Рыцарь убивает эльфа
// - Эльф убивает друида и рыцаря
// - Друид убивает друидов

class BattleVisitor : public Visitor
{
private:
    Subject &subject;

    void fight(NPC &attacker, NPC &defender, bool attackerWins, bool defenderWins)
    {
        if (attackerWins && defenderWins)
        {
            // Оба погибают
            attacker.takeDamage(attacker.getHealth());
            defender.takeDamage(defender.getHealth());
            subject.notify(attacker.getName() + " и " + defender.getName(), "друг друга (взаимное убийство)");
        }
        else if (attackerWins)
        {
            // Атакующий побеждает
            defender.takeDamage(defender.getHealth());
            subject.notify(attacker.getName() + " (" + attacker.getType() + ")",
                           defender.getName() + " (" + defender.getType() + ")");
        }
        else if (defenderWins)
        {
            // Защищающийся побеждает
            attacker.takeDamage(attacker.getHealth());
            subject.notify(defender.getName() + " (" + defender.getType() + ")",
                           attacker.getName() + " (" + attacker.getType() + ")");
        }
        // Если оба false - ничья, никто не умирает
    }

public:
    BattleVisitor(Subject &subject) : subject(subject) {}

    // Knight vs ...
    void visitKnight(Knight &attacker, Knight &defender) override
    {
        // Рыцарь не убивает рыцаря
        fight(attacker, defender, false, false);
    }

    void visitKnight(Knight &attacker, Druid &defender) override
    {
        // Рыцарь не убивает друида
        fight(attacker, defender, false, false);
    }

    void visitKnight(Knight &attacker, Elf &defender) override
    {
        // Рыцарь убивает эльфа, но эльф тоже убивает рыцаря
        fight(attacker, defender, true, true);
    }

    // Druid vs ...
    void visitDruid(Druid &attacker, Knight &defender) override
    {
        // Друид не убивает рыцаря
        fight(attacker, defender, false, false);
    }

    void visitDruid(Druid &attacker, Druid &defender) override
    {
        // Друид убивает друида
        fight(attacker, defender, true, true);
    }

    void visitDruid(Druid &attacker, Elf &defender) override
    {
        // Друид не убивает эльфа, но эльф убивает друида
        fight(attacker, defender, false, true);
    }

    // Elf vs ...
    void visitElf(Elf &attacker, Knight &defender) override
    {
        // Эльф убивает рыцаря, но рыцарь тоже убивает эльфа
        fight(attacker, defender, true, true);
    }

    void visitElf(Elf &attacker, Druid &defender) override
    {
        // Эльф убивает друида
        fight(attacker, defender, true, false);
    }

    void visitElf(Elf &attacker, Elf &defender) override
    {
        // Эльф не убивает эльфа
        fight(attacker, defender, false, false);
    }
};
