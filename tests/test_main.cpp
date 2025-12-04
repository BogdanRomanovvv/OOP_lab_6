#include <gtest/gtest.h>
#include "../include/Knight.h"
#include "../include/Druid.h"
#include "../include/Elf.h"
#include "../include/NPCFactory.h"
#include "../include/BattleVisitor.h"
#include "../include/Observer.h"
#include "../include/DungeonEditor.h"
#include <fstream>
#include <sstream>

// Тесты создания NPC через Factory
class NPCFactoryTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(NPCFactoryTest, CreateKnight)
{
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    ASSERT_NE(knight, nullptr);
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(knight->getName(), "TestKnight");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 100);
    EXPECT_TRUE(knight->isAlive());
}

TEST_F(NPCFactoryTest, CreateDruid)
{
    auto druid = NPCFactory::createNPC("Druid", "TestDruid", 200, 200);
    ASSERT_NE(druid, nullptr);
    EXPECT_EQ(druid->getType(), "Druid");
    EXPECT_EQ(druid->getName(), "TestDruid");
    EXPECT_EQ(druid->getX(), 200);
    EXPECT_EQ(druid->getY(), 200);
    EXPECT_TRUE(druid->isAlive());
}

TEST_F(NPCFactoryTest, CreateElf)
{
    auto elf = NPCFactory::createNPC("Elf", "TestElf", 300, 300);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getName(), "TestElf");
    EXPECT_EQ(elf->getX(), 300);
    EXPECT_EQ(elf->getY(), 300);
    EXPECT_TRUE(elf->isAlive());
}

TEST_F(NPCFactoryTest, CreateInvalidType)
{
    auto npc = NPCFactory::createNPC("InvalidType", "Test", 100, 100);
    EXPECT_EQ(npc, nullptr);
}

TEST_F(NPCFactoryTest, CreateFromString)
{
    std::string line = "Knight Arthur 150 250";
    auto npc = NPCFactory::createFromString(line);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Knight");
    EXPECT_EQ(npc->getName(), "Arthur");
    EXPECT_EQ(npc->getX(), 150);
    EXPECT_EQ(npc->getY(), 250);
}

TEST_F(NPCFactoryTest, CreateFromInvalidString)
{
    std::string line = "InvalidLine";
    auto npc = NPCFactory::createFromString(line);
    EXPECT_EQ(npc, nullptr);
}

// Тесты расстояния между NPC
class NPCDistanceTest : public ::testing::Test
{
protected:
    std::shared_ptr<NPC> npc1;
    std::shared_ptr<NPC> npc2;

    void SetUp() override
    {
        npc1 = NPCFactory::createNPC("Knight", "Knight1", 0, 0);
        npc2 = NPCFactory::createNPC("Druid", "Druid1", 3, 4);
    }
};

TEST_F(NPCDistanceTest, CalculateDistance)
{
    double distance = npc1->distanceTo(*npc2);
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST_F(NPCDistanceTest, DistanceToSelf)
{
    double distance = npc1->distanceTo(*npc1);
    EXPECT_DOUBLE_EQ(distance, 0.0);
}

TEST_F(NPCDistanceTest, LargeDistance)
{
    auto npc3 = NPCFactory::createNPC("Elf", "Elf1", 500, 500);
    double distance = npc1->distanceTo(*npc3);
    EXPECT_NEAR(distance, 707.1067, 0.001);
}

// Тесты боевой системы
class BattleVisitorTest : public ::testing::Test
{
protected:
    Subject subject;
    std::unique_ptr<BattleVisitor> visitor;

    void SetUp() override
    {
        visitor = std::make_unique<BattleVisitor>(subject);
    }
};

TEST_F(BattleVisitorTest, KnightVsElf_BothDie)
{
    auto knight = std::make_shared<Knight>("Knight1", 100, 100);
    auto elf = std::make_shared<Elf>("Elf1", 110, 110);

    knight->accept(*visitor, *elf);

    EXPECT_FALSE(knight->isAlive());
    EXPECT_FALSE(elf->isAlive());
}

TEST_F(BattleVisitorTest, ElfVsDruid_DruidDies)
{
    auto elf = std::make_shared<Elf>("Elf1", 100, 100);
    auto druid = std::make_shared<Druid>("Druid1", 110, 110);

    elf->accept(*visitor, *druid);

    EXPECT_TRUE(elf->isAlive());
    EXPECT_FALSE(druid->isAlive());
}

TEST_F(BattleVisitorTest, DruidVsDruid_BothDie)
{
    auto druid1 = std::make_shared<Druid>("Druid1", 100, 100);
    auto druid2 = std::make_shared<Druid>("Druid2", 110, 110);

    druid1->accept(*visitor, *druid2);

    EXPECT_FALSE(druid1->isAlive());
    EXPECT_FALSE(druid2->isAlive());
}

TEST_F(BattleVisitorTest, KnightVsKnight_NoDeath)
{
    auto knight1 = std::make_shared<Knight>("Knight1", 100, 100);
    auto knight2 = std::make_shared<Knight>("Knight2", 110, 110);

    knight1->accept(*visitor, *knight2);

    EXPECT_TRUE(knight1->isAlive());
    EXPECT_TRUE(knight2->isAlive());
}

TEST_F(BattleVisitorTest, ElfVsElf_NoDeath)
{
    auto elf1 = std::make_shared<Elf>("Elf1", 100, 100);
    auto elf2 = std::make_shared<Elf>("Elf2", 110, 110);

    elf1->accept(*visitor, *elf2);

    EXPECT_TRUE(elf1->isAlive());
    EXPECT_TRUE(elf2->isAlive());
}

TEST_F(BattleVisitorTest, KnightVsDruid_NoDeath)
{
    auto knight = std::make_shared<Knight>("Knight1", 100, 100);
    auto druid = std::make_shared<Druid>("Druid1", 110, 110);

    knight->accept(*visitor, *druid);

    EXPECT_TRUE(knight->isAlive());
    EXPECT_TRUE(druid->isAlive());
}

// Тесты Observer
class ObserverTest : public ::testing::Test
{
protected:
    Subject subject;
    std::string testLogFile = "test_log.txt";

    void TearDown() override
    {
        std::remove(testLogFile.c_str());
    }
};

TEST_F(ObserverTest, FileObserverWritesToFile)
{
    auto fileObserver = std::make_shared<FileObserver>(testLogFile);
    subject.attach(fileObserver);

    subject.notify("Knight", "Elf");

    std::ifstream file(testLogFile);
    ASSERT_TRUE(file.is_open());
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Knight убил(а) Elf");
    file.close();
}

TEST_F(ObserverTest, MultipleObservers)
{
    auto fileObserver = std::make_shared<FileObserver>(testLogFile);
    auto consoleObserver = std::make_shared<ConsoleObserver>();

    subject.attach(fileObserver);
    subject.attach(consoleObserver);

    subject.notify("Druid", "Druid");

    std::ifstream file(testLogFile);
    ASSERT_TRUE(file.is_open());
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Druid убил(а) Druid");
    file.close();
}

// Тесты DungeonEditor
class DungeonEditorTest : public ::testing::Test
{
protected:
    DungeonEditor editor;
    std::string testFile = "test_dungeon.txt";

    void TearDown() override
    {
        std::remove(testFile.c_str());
        std::remove("log.txt");
    }
};

TEST_F(DungeonEditorTest, AddNPC_ValidCoordinates)
{
    EXPECT_TRUE(editor.addNPC("Knight", "TestKnight", 100, 100));
    EXPECT_EQ(editor.getNPCCount(), 1);
}

TEST_F(DungeonEditorTest, AddNPC_InvalidCoordinates_TooLarge)
{
    EXPECT_FALSE(editor.addNPC("Knight", "TestKnight", 600, 100));
    EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonEditorTest, AddNPC_InvalidCoordinates_Negative)
{
    EXPECT_FALSE(editor.addNPC("Knight", "TestKnight", -10, 100));
    EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonEditorTest, AddNPC_DuplicateName)
{
    EXPECT_TRUE(editor.addNPC("Knight", "TestKnight", 100, 100));
    EXPECT_FALSE(editor.addNPC("Druid", "TestKnight", 200, 200));
    EXPECT_EQ(editor.getNPCCount(), 1);
}

TEST_F(DungeonEditorTest, AddNPC_BoundaryCoordinates)
{
    EXPECT_TRUE(editor.addNPC("Knight", "K1", 0, 0));
    EXPECT_TRUE(editor.addNPC("Druid", "D1", 500, 500));
    EXPECT_EQ(editor.getNPCCount(), 2);
}

TEST_F(DungeonEditorTest, SaveAndLoadFromFile)
{
    editor.addNPC("Knight", "Arthur", 100, 100);
    editor.addNPC("Druid", "Merlin", 200, 200);
    editor.addNPC("Elf", "Legolas", 300, 300);

    EXPECT_TRUE(editor.saveToFile(testFile));

    DungeonEditor editor2;
    EXPECT_TRUE(editor2.loadFromFile(testFile));
    EXPECT_EQ(editor2.getNPCCount(), 3);
}

TEST_F(DungeonEditorTest, LoadFromNonExistentFile)
{
    EXPECT_FALSE(editor.loadFromFile("nonexistent.txt"));
}

TEST_F(DungeonEditorTest, BattleMode_NoNPCsInRange)
{
    editor.addNPC("Knight", "K1", 0, 0);
    editor.addNPC("Druid", "D1", 500, 500);

    editor.startBattle(100);

    // Оба должны выжить, так как далеко друг от друга
    EXPECT_EQ(editor.getNPCCount(), 2);
}

TEST_F(DungeonEditorTest, BattleMode_NPCsInRange)
{
    editor.addNPC("Knight", "K1", 100, 100);
    editor.addNPC("Elf", "E1", 110, 110);

    editor.startBattle(50);

    // Оба должны погибнуть (Knight vs Elf = взаимное убийство)
    EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonEditorTest, BattleMode_ComplexScenario)
{
    editor.addNPC("Knight", "K1", 100, 100);
    editor.addNPC("Elf", "E1", 110, 110);
    editor.addNPC("Druid", "D1", 120, 120);
    editor.addNPC("Knight", "K2", 400, 400);

    editor.startBattle(50);

    // K1 и E1 убивают друг друга
    // E1 убивает D1 (но E1 уже мертв от K1)
    // K2 слишком далеко
    EXPECT_GE(editor.getNPCCount(), 1); // Как минимум K2 выживает
}

// Тесты сериализации
class SerializationTest : public ::testing::Test
{
};

TEST_F(SerializationTest, NPCSerialization)
{
    auto knight = NPCFactory::createNPC("Knight", "Arthur", 123.5, 456.7);
    std::string serialized = knight->serialize();
    EXPECT_EQ(serialized, "Knight Arthur 123.500000 456.700000");
}

TEST_F(SerializationTest, SerializeAndDeserialize)
{
    auto original = NPCFactory::createNPC("Druid", "Merlin", 200, 300);
    std::string serialized = original->serialize();

    auto deserialized = NPCFactory::createFromString(serialized);

    ASSERT_NE(deserialized, nullptr);
    EXPECT_EQ(deserialized->getType(), original->getType());
    EXPECT_EQ(deserialized->getName(), original->getName());
    EXPECT_DOUBLE_EQ(deserialized->getX(), original->getX());
    EXPECT_DOUBLE_EQ(deserialized->getY(), original->getY());
}

// Главная функция для запуска тестов
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
