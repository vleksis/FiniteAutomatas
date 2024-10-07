#pragma once

#include <gtest/gtest.h>
#define private public
#define protected public
#include "DFA.h"

class IsomorphicTestCase : public ::testing::Test {
 public:
  void SetUp() override;
  void TearDown() override;

  DFA g1;
  DFA g2;
  DFA g3;
  DFA g4;
  DFA g5;
  DFA g6;
};

