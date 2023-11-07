#include <gtest/gtest.h>

#include "parent.hpp"

void testingProgram(const std::vector<std::string>& input, const std::vector<std::string>& expectedOutput, const std::vector<std::string>& expectedFile) {
    const char *fileName = "file.txt";

    std::stringstream inFile;
    inFile << fileName << std::endl;
    for (std::string line : input) {
        inFile << line << std::endl;
    }

    std::streambuf* oldInBuf = std::cin.rdbuf();
    std::cin.rdbuf(inFile.rdbuf());

    std::stringstream capturedErrorMessages;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(capturedErrorMessages.rdbuf());

    ParentRoutine(getenv("PATH_TO_CHILD"));

    std::cin.rdbuf(oldInBuf);
    std::cerr.rdbuf(oldCerrBuf);

    std::string capturedErrors = capturedErrorMessages.str();

    std::stringstream errorOut(capturedErrors);
    for (const std::string &expectation : expectedOutput) {
        std::string result;
        getline(errorOut, result);
        EXPECT_EQ(result, expectation);
    }

    std::ifstream fin(fileName);
    for (const std::string &expectation : expectedFile) {
        std::string result;
        getline(fin, result);
        EXPECT_EQ(result, expectation);
    }
    fin.close();
    std::remove(fileName);
}


TEST(thirdLabTests, simpleTest) {
    std::vector<std::string> input = {"AAA"};
    std::vector<std::string> expectedOutput = {};
    std::vector<std::string> expectedFile = {"AAA"};
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(thirdLabTests, emptystrTest) {
    std::vector<std::string> input = {};
    std::vector<std::string> expectedOutput = {};
    std::vector<std::string> expectedFile = {};
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(thirdLabTests, sonneTest) {
    std::vector<std::string> input = {
        "Alle warten auf das Licht",
        "Furchtet euch, furchtet euch nicht.",
        "die Sonne scheint mir aus den Augen,",
        "sie wird heute Nacht nicht untergehen",
        "Und die Welt zahlt laut bis zehn"
    };

    std::vector<std::string> expectedOutput = {
        "Error: die Sonne scheint mir aus den Augen,",
        "Error: sie wird heute Nacht nicht untergehen"
    };

    std::vector<std::string> expectedFile = {
        "Alle warten auf das Licht",
        "Furchtet euch, furchtet euch nicht.",
        "Und die Welt zahlt laut bis zehn"
    };
    testingProgram(input, expectedOutput, expectedFile);
}

TEST(thirdLabTests, deathTest) {
    std::vector<std::string> input = {
        "Can death be sleep, when life is but a dream,",
        "And scenes of bliss pass as a phantom by?",
        "the transient pleasures as a vision seem,",
        "And yet we think the greatest pain's to die."
    };

    std::vector<std::string> expectedOutput = {
        "Error: the transient pleasures as a vision seem,"
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