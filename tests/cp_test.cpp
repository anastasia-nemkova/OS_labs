#include <gtest/gtest.h>

#include "shared_memory.hpp"
#include "server_utils.hpp"
#include "client_utils.hpp"

TEST(SharedMemoryTest, GiveAndGetFromMmapTest) {
    const char* semaphoreName = "/test_semaphore";
    sem_t* semaphore = OpenSemaphore(semaphoreName, 1);
    int state = 0;
    std::string input = "Test input";
    std::string MmapName = "/test_shared_memory";
    giveToMmap(input, MmapName, semaphore, &state, 1);
    std::string output = getFromMmap(MmapName, 1);  
    EXPECT_EQ(input, output);  
    sem_close(semaphore);  
    sem_unlink(semaphoreName);  
}

TEST(SharedMemoryTest, OpenAndSetSemaphoreTest) {
    const char* semaphoreName = "/test_semaphore";
    sem_t* semaphore = OpenSemaphore(semaphoreName, 0);
    int state = 0;
    setSemaphore(semaphore, &state, 2);  
    int value;
    sem_getvalue(semaphore, &value);
    EXPECT_EQ(value, 2);  
    sem_close(semaphore); 
    sem_unlink(semaphoreName);  
}

TEST(ClientTest, GetLoginTest) {
    std::string input = "username password";
    std::string expected = "username";
    EXPECT_EQ(getLogin(input), expected);
}

TEST(ClientTest, GetCoordTest) {
    std::string input = " 4 1 2 3 5";
    int x, y;
    std::string size = "4";
    EXPECT_EQ(getCoord(input, &x, &y), size);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
}

TEST(ClientTest, BattleInfoTest) {
    std::vector<std::string> matrix(10, std::string(10, '0'));
    int x = 3;
    int y = 2;
    std::string info = "Мимо";
    battleInfo(matrix, x, y, info);
    EXPECT_EQ(matrix[2][1], '3');

    int x1 = 5;
    int y1 = 4;
    std::string info1 = "Ранил";
    battleInfo(matrix, x1, y1, info1);
    EXPECT_EQ(matrix[4][3], '2');
}

TEST(ServerTest, ParseCoordinatesTest) {
    std::string input = "0 1 2 3 4";
    std::vector<int> expected = {1, 2, 3, 4};
    std::vector<int> result = parseCoordinates(input);
    ASSERT_EQ(expected, result);
}


TEST(ServerTest, arrangementShipsTest) {
    std::vector<std::vector<std::string>> twoMatrix(2, std::vector<std::string>(10, std::string(10, '0')));
    std::vector<int> coordinates = {1, 1, 1, 4};
    int player = 0;
    arrangementShips(twoMatrix, coordinates, player);
    ASSERT_EQ(twoMatrix[player][0][0], '1');
    ASSERT_EQ(twoMatrix[player][0][1], '1');
    ASSERT_EQ(twoMatrix[player][0][2], '1');
    ASSERT_EQ(twoMatrix[player][0][3], '1');
}

TEST(ServerTest, BattleInfoTest) {
    std::vector<std::string> matrix(10, std::string(10, '0'));
    matrix[0][0] = '1';
    int x = 1, y = 1;
    std::string result = battleInfo(matrix, x, y);
    ASSERT_EQ(result, "Ранил");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}