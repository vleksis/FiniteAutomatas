#include "Task2aTest.h"

TEST(TASK2a, test) {
  std::ifstream input("../../tests/Task2aInput.txt");
  NFA g = ReadNFA(input, std::cout);
  g.EpsilonClosure();
  DFA res = MFDFA(g);
  std::cout << res;

  DFA correct(2, 9);
  correct.initial = 0;
  correct.terminated[1] = correct.terminated[4] = correct.terminated[6] =
      correct.terminated[7] = correct.terminated[8] = true;
  correct.transition[0][0] = 1;
  correct.transition[0][1] = 2;
  correct.transition[1][0] = 3;
  correct.transition[1][1] = 1;
  correct.transition[2][0] = 2;
  correct.transition[2][1] = 2;
  correct.transition[3][0] = 4;
  correct.transition[3][1] = 2;
  correct.transition[4][0] = 5;
  correct.transition[4][1] = 6;
  correct.transition[5][0] = 4;
  correct.transition[5][1] = 7;
  correct.transition[6][0] = 8;
  correct.transition[6][1] = 1;
  correct.transition[7][0] = 5;
  correct.transition[7][1] = 1;
  correct.transition[8][0] = 8;
  correct.transition[8][1] = 6;

  EXPECT_TRUE(Isomorphic(correct, res));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}