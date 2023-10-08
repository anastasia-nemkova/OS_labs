#include <gtest/gtest.h>


#include "parent.hpp"

void testingProgram(const std::vector<std::string>& input, const std::vector<std::string>& expectedOutput, const std::vector<std::string>& expectedFile) {
    const char* fileName = "test.txt";

    // Записываем входные данные в файл
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    outFile << fileName << std::endl;
    for (const std::string &line : input) {
        outFile << line << std::endl;
    }
    outFile.close();

    // Сохраняем старый буфер для восстановления
    std::streambuf* oldCoutBuf = std::cout.rdbuf();
    std::streambuf* oldCinBuf = std::cin.rdbuf();

    // Подключаем файл ввода
    std::ifstream inFile(fileName);
    std::cin.rdbuf(inFile.rdbuf());

    // Захватываем вывод программы
    std::stringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    ParentRoutine(getenv("PATH_TO_CHILD"));

    // Восстанавливаем стандартные буферы
    std::cin.rdbuf(oldCinBuf);
    std::cout.rdbuf(oldCoutBuf);

    // Проверяем вывод программы
    std::istringstream outputStream(capturedOutput.str());
    for (const std::string &expectation : expectedOutput) {
        std::string result;
        std::getline(outputStream, result);
        EXPECT_EQ(result, expectation);
    }

    // Проверяем содержимое файла
    std::ifstream fileStream(fileName);
    for (const std::string &expectation : expectedFile) {
        std::string result;
        std::getline(fileStream, result);
        EXPECT_EQ(result, expectation);
    }

    fileStream.close();
    std::remove(fileName);
}

TEST(firstLabTests, simpleTest) {
    std::vector<std::string> input = {"AAA"};
    std::vector<std::string> expectedOutput = {};
    std::vector<std::string> expectedFile = {"AAA"};
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(firstLabTests, emptystrTest) {
    std::vector<std::string> input = {};
    std::vector<std::string> expectedOutput = {};
    std::vector<std::string> expectedFile = {};
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(firstLabTests, sonneTest) {
    std::vector<std::string> input = {
        "Alle warten auf das Licht",
        "Furchtet euch, furchtet euch nicht.",
        "die Sonne scheint mir aus den Augen,",
        "sie wird heute Nacht nicht untergehen",
        "Und die Welt zahlt laut bis zehn"
    };

    std::vector<std::string> expectedOutput = {
        "String: die Sonne scheint mir aus den Augen, - doesn't start with capital letter",
        "String: sie wird heute Nacht nicht untergehen - doesn't start with capital letter"
    };

    std::vector<std::string> expectedFile = {
        "Alle warten auf das Licht",
        "Furchtet euch, furchtet euch nicht.",
        "Und die Welt zahlt laut bis zehn"
    };
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(firstLabTests, deathTest) {
    std::vector<std::string> input = {
        "Can death be sleep, when life is but a dream,",
        "And scenes of bliss pass as a phantom by?",
        "the transient pleasures as a vision seem,",
        "And yet we think the greatest pain's to die."
    };

    std::vector<std::string> expectedOutput = {
        "String: the transient pleasures as a vision seem, - doesn't start with capital letter"
    };

    std::vector<std::string> expectedFile = {
        "Can death be sleep, when life is but a dream,",
        "And scenes of bliss pass as a phantom by?",
        "And yet we think the greatest pain's to die."
    };
    testingProgram(input, expectedOutput, expectedFile);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}