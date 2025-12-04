# Лабораторная работа №6 - Паттерны проектирования

## Описание проекта

RPG Dungeon Editor - редактор подземелий с тремя типами NPC (Рыцарь, Друид, Эльф) и системой боёв, реализованный с использованием трёх паттернов проектирования.

## Реализованные паттерны

### 1. Factory (Фабрика)
- **Класс**: `NPCFactory`
- **Назначение**: Создание объектов NPC по типу
- **Использование**: `NPCFactory::createNPC(type, name, x, y)`

### 2. Visitor (Посетитель)
- **Класс**: `BattleVisitor`
- **Назначение**: Реализация боевой логики между различными типами NPC
- **Правила боя**:
  - Knight vs Elf → взаимное уничтожение
  - Elf vs Druid → Druid погибает
  - Druid vs Druid → взаимное уничтожение
  - Knight vs Knight → ничья
  - Knight vs Druid → ничья

### 3. Observer (Наблюдатель)
- **Классы**: `FileObserver`, `ConsoleObserver`
- **Назначение**: Логирование событий боёв в файл и консоль

## Сборка и запуск

### Локальная сборка

**Windows:**
```powershell
mkdir build
cd build
cmake ..
cmake --build .
.\dungeon_editor.exe     # Запуск программы
.\dungeon_tests.exe      # Запуск тестов
```

**Linux/macOS:**
```bash
mkdir build && cd build
cmake ..
cmake --build .
./dungeon_editor         # Запуск программы
./dungeon_tests          # Запуск тестов
```

### Запуск через Docker

**Сборка образа:**
```bash
docker build -t dungeon-editor .
```

**Запуск программы:**
```bash
docker run -it dungeon-editor
```

**Запуск тестов:**
```bash
docker run --rm dungeon-editor ./dungeon_tests
```

**Или через docker-compose:**
```bash
docker-compose up --build
```

## Запуск тестов

```bash
cd build
ctest --verbose
# или
./dungeon_tests
```

**Результаты:** 29/29 тестов успешно пройдено 

## Использование программы

### Интерактивное меню

1. **Добавить NPC** - создать нового персонажа (Knight/Druid/Elf)
2. **Показать всех NPC** - вывести список всех персонажей
3. **Сохранить в файл** - экспорт данных в текстовый файл
4. **Загрузить из файла** - импорт данных из файла
5. **Режим боя** - запуск сражений
6. **Сгенерировать тестовые данные** - создать 10 случайных NPC
7. **Выход**
