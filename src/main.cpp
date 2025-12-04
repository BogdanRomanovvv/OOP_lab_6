#include <iostream>
#include <limits>
#include "DungeonEditor.h"

void printMenu()
{
    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Редактор подземелья Balagur Fate 3           ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    std::cout << "1. Добавить NPC" << std::endl;
    std::cout << "2. Показать всех NPC" << std::endl;
    std::cout << "3. Сохранить в файл" << std::endl;
    std::cout << "4. Загрузить из файла" << std::endl;
    std::cout << "5. Запустить боевой режим" << std::endl;
    std::cout << "6. Создать тестовый набор данных" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void addNPCMenu(DungeonEditor &editor)
{
    std::cout << "\n=== Добавление NPC ===" << std::endl;
    std::cout << "Доступные типы:" << std::endl;
    std::cout << "1. Knight (Странствующий рыцарь)" << std::endl;
    std::cout << "2. Druid (Друид)" << std::endl;
    std::cout << "3. Elf (Эльф)" << std::endl;

    int typeChoice;
    std::cout << "Выберите тип (1-3): ";
    std::cin >> typeChoice;

    std::string type;
    switch (typeChoice)
    {
    case 1:
        type = "Knight";
        break;
    case 2:
        type = "Druid";
        break;
    case 3:
        type = "Elf";
        break;
    default:
        std::cout << "Неверный тип!" << std::endl;
        clearInput();
        return;
    }

    std::string name;
    std::cout << "Введите имя NPC: ";
    std::cin >> name;

    double x, y;
    std::cout << "Введите координату X (0-500): ";
    std::cin >> x;
    std::cout << "Введите координату Y (0-500): ";
    std::cin >> y;

    if (std::cin.fail())
    {
        std::cout << "Ошибка ввода!" << std::endl;
        clearInput();
        return;
    }

    if (editor.addNPC(type, name, x, y))
    {
        std::cout << "✓ NPC успешно добавлен!" << std::endl;
    }
    else
    {
        std::cout << "✗ Не удалось добавить NPC (проверьте координаты и уникальность имени)!" << std::endl;
    }
}

void saveToFileMenu(DungeonEditor &editor)
{
    std::string filename;
    std::cout << "\nВведите имя файла для сохранения: ";
    std::cin >> filename;

    if (editor.saveToFile(filename))
    {
        std::cout << "✓ Данные сохранены в файл " << filename << std::endl;
    }
    else
    {
        std::cout << "✗ Ошибка сохранения в файл!" << std::endl;
    }
}

void loadFromFileMenu(DungeonEditor &editor)
{
    std::string filename;
    std::cout << "\nВведите имя файла для загрузки: ";
    std::cin >> filename;

    if (editor.loadFromFile(filename))
    {
        std::cout << "✓ Данные загружены из файла " << filename << std::endl;
        std::cout << "Загружено NPC: " << editor.getNPCCount() << std::endl;
    }
    else
    {
        std::cout << "✗ Ошибка загрузки из файла!" << std::endl;
    }
}

void battleModeMenu(DungeonEditor &editor)
{
    double range;
    std::cout << "\nВведите дальность боя (в метрах): ";
    std::cin >> range;

    if (std::cin.fail() || range < 0)
    {
        std::cout << "Ошибка ввода!" << std::endl;
        clearInput();
        return;
    }

    editor.startBattle(range);
}

void createTestData(DungeonEditor &editor)
{
    std::cout << "\n=== Создание тестового набора данных ===" << std::endl;

    // Создаём тестовых персонажей
    editor.addNPC("Knight", "Артур", 100, 100);
    editor.addNPC("Knight", "Ланцелот", 150, 120);
    editor.addNPC("Druid", "Мерлин", 200, 200);
    editor.addNPC("Druid", "Моргана", 250, 180);
    editor.addNPC("Elf", "Леголас", 120, 110);
    editor.addNPC("Elf", "Галадриэль", 300, 300);
    editor.addNPC("Knight", "Персиваль", 400, 400);
    editor.addNPC("Druid", "Друид_3", 210, 205);

    std::cout << "✓ Создано 8 тестовых NPC!" << std::endl;
    editor.printNPCs();
}

int main()
{
    DungeonEditor editor;
    int choice;

    std::cout << "Добро пожаловать в редактор подземелья Balagur Fate 3!" << std::endl;

    while (true)
    {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail())
        {
            clearInput();
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            addNPCMenu(editor);
            break;
        case 2:
            editor.printNPCs();
            break;
        case 3:
            saveToFileMenu(editor);
            break;
        case 4:
            loadFromFileMenu(editor);
            break;
        case 5:
            battleModeMenu(editor);
            break;
        case 6:
            createTestData(editor);
            break;
        case 0:
            std::cout << "\nДо свидания!" << std::endl;
            return 0;
        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    }

    return 0;
}
