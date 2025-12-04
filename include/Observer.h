#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

// Интерфейс Observer
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onKill(const std::string &killer, const std::string &victim) = 0;
};

// Observer для записи в файл
class FileObserver : public Observer
{
private:
    std::string filename;

public:
    FileObserver(const std::string &filename) : filename(filename) {}

    void onKill(const std::string &killer, const std::string &victim) override
    {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open())
        {
            file << killer << " убил(а) " << victim << std::endl;
            file.close();
        }
    }
};

// Observer для вывода на экран
class ConsoleObserver : public Observer
{
public:
    void onKill(const std::string &killer, const std::string &victim) override
    {
        std::cout << "[БОЕВОЙ ЛОГ] " << killer << " убил(а) " << victim << std::endl;
    }
};

// Класс Subject для управления наблюдателями
class Subject
{
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void attach(std::shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void notify(const std::string &killer, const std::string &victim)
    {
        for (auto &observer : observers)
        {
            observer->onKill(killer, victim);
        }
    }
};
