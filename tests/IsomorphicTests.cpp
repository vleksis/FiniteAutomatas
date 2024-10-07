#include "IsomorphicTests.h"

void IsomorphicTestCase::SetUp() {
  {
    g1 = DFA(2, 4);

    g1.initial = 0;
    g1.terminated[1] = g1.terminated[2] = true;

    g1.transition[0][0] = 2;
    g1.transition[0][1] = 1;
    g1.transition[1][0] = 0;
    g1.transition[1][1] = 2;
    g1.transition[2][0] = 3;
    g1.transition[2][1] = 0;
    g1.transition[3][0] = 3;
    g1.transition[3][1] = 1;
  }

  {
    g2 = DFA(2, 4);

    g2.initial = 0;
    g2.terminated[1] = g2.terminated[2] = true;

    g2.transition[0][0] = 1;
    g2.transition[0][1] = 2;
    g2.transition[1][0] = 1;
    g2.transition[1][1] = 1;
    g2.transition[2][0] = 3;
    g2.transition[2][1] = 0;
    g2.transition[3][0] = 0;
    g2.transition[3][1] = 1;
  }

  {
    g3 = DFA(2, 4);

    g3.initial = 1;
    g3.terminated[2] = g3.terminated[3] = true;

    g3.transition[0][0] = 0;
    g3.transition[0][1] = 3;
    g3.transition[1][0] = 2;
    g3.transition[1][1] = 3;
    g3.transition[2][0] = 0;
    g3.transition[2][1] = 1;
    g3.transition[3][0] = 1;
    g3.transition[3][1] = 2;
  }

  {
    g4 = DFA(2, 4);

    g4.initial = 0;
    g4.terminated[0] = g4.terminated[1] = g4.terminated[2] = true;

    g4.transition[0][0] = 2;
    g4.transition[0][1] = 1;
    g4.transition[1][0] = 0;
    g4.transition[1][1] = 2;
    g4.transition[2][0] = 3;
    g4.transition[2][1] = 0;
    g4.transition[3][0] = 3;
    g4.transition[3][1] = 1;
  }

  {
    g5 = DFA(2, 3);

    g5.initial = 0;
    g5.terminated[1] = true;

    g5.transition[0][0] = 2;
    g5.transition[0][1] = 1;
    g5.transition[1][0] = 0;
    g5.transition[1][1] = 2;
    g5.transition[2][0] = 0;
    g5.transition[2][1] = 0;
  }

  {
    g6 = DFA(1, 2);

    g6.initial = 0;
    g6.terminated[1] = true;

    g6.transition[0][0] = 1;
    g6.transition[1][0] = 1;
  }
}

void IsomorphicTestCase::TearDown() {}

TEST_F(IsomorphicTestCase, test11) { EXPECT_TRUE(Isomorphic(g1, g1)); }

TEST_F(IsomorphicTestCase, test12) { EXPECT_FALSE(Isomorphic(g1, g2)); }

TEST_F(IsomorphicTestCase, test13) { EXPECT_TRUE(Isomorphic(g1, g3)); }

TEST_F(IsomorphicTestCase, test14) { EXPECT_FALSE(Isomorphic(g1, g4)); }

TEST_F(IsomorphicTestCase, test15) { EXPECT_FALSE(Isomorphic(g1, g5)); }

TEST_F(IsomorphicTestCase, test16) { EXPECT_FALSE(Isomorphic(g1, g6)); }

TEST_F(IsomorphicTestCase, test21) { EXPECT_FALSE(Isomorphic(g2, g1)); }

TEST_F(IsomorphicTestCase, test22) { EXPECT_TRUE(Isomorphic(g2, g2)); }

TEST_F(IsomorphicTestCase, test23) { EXPECT_FALSE(Isomorphic(g2, g3)); }

TEST_F(IsomorphicTestCase, test24) { EXPECT_FALSE(Isomorphic(g2, g4)); }

TEST_F(IsomorphicTestCase, test31) { EXPECT_TRUE(Isomorphic(g3, g1)); }

TEST_F(IsomorphicTestCase, test32) { EXPECT_FALSE(Isomorphic(g3, g2)); }

TEST_F(IsomorphicTestCase, test33) { EXPECT_TRUE(Isomorphic(g3, g3)); }

TEST_F(IsomorphicTestCase, test34) { EXPECT_FALSE(Isomorphic(g3, g4)); }

TEST_F(IsomorphicTestCase, test41) { EXPECT_FALSE(Isomorphic(g4, g1)); }

TEST_F(IsomorphicTestCase, test42) { EXPECT_FALSE(Isomorphic(g4, g2)); }

TEST_F(IsomorphicTestCase, test43) { EXPECT_FALSE(Isomorphic(g4, g3)); }

TEST_F(IsomorphicTestCase, test44) { EXPECT_TRUE(Isomorphic(g4, g4)); }

TEST(DFATestCase, aboba) {
  DFA correct(2, 3);
  correct.initial = 0;
  correct.terminated[1] = true;

  correct.transition[0][0] = 1;
  correct.transition[0][1] = 2;
  correct.transition[1][0] = 2;
  correct.transition[1][1] = 2;
  correct.transition[2][0] = 2;
  correct.transition[2][1] = 2;

  NFA g(2, 4);
  g.AddInitial(0);
  g.AddTerminated(2);
  g.AddTransition(0, 0, 1);
  g.AddTransition(0, 0, 2);
  g.AddTransition(0, 0, 3);
  g.AddTransition(0, 2, 3);
  g.AddTransition(1, 1, 1);
  g.EpsilonClosure();
  DFA dg = MFDFA(g);
  std::cout << g << '\n';
  std::cout << dg << '\n';

  EXPECT_TRUE(Isomorphic(correct, dg));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}