#pragma once
#include <string>
#include <memory>
#include <cmath>

class Visitor;

// Базовый класс для всех NPC
class NPC
{
protected:
    std::string name;
    double x, y;
    int health;
    int damage;
    bool alive;

public:
    NPC(const std::string &name, double x, double y, int health, int damage)
        : name(name), x(x), y(y), health(health), damage(damage), alive(true) {}

    virtual ~NPC() = default;

    // Геттеры
    std::string getName() const { return name; }
    double getX() const { return x; }
    double getY() const { return y; }
    int getHealth() const { return health; }
    bool isAlive() const { return alive; }

    // Метод для получения типа NPC
    virtual std::string getType() const = 0;

    // Метод для вычисления расстояния до другого NPC
    double distanceTo(const NPC &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Получение урона
    void takeDamage(int dmg)
    {
        health -= dmg;
        if (health <= 0)
        {
            alive = false;
        }
    }

    // Нанесение урона другому NPC
    int getDamage() const { return damage; }

    // Метод для паттерна Visitor
    virtual void accept(Visitor &visitor, NPC &other) = 0;

    // Сериализация
    virtual std::string serialize() const
    {
        return getType() + " " + name + " " + std::to_string(x) + " " + std::to_string(y);
    }
};
