/**
 * LifterTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LifterTest.cpp ../src/Lifter.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "Lifter.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>
#include <iostream>

namespace etrobocon2018_test {

  class LifterTest : public ::testing::Test {
   protected:
    virtual void SetUp()
    {
      lifter.controller.liftMotor.count = 145000;
      lifter.reset();
    }
    Controller controller;
    Lifter lifter{ controller };

    std::int32_t getDefaultCount() { return lifter.default_count; }
    void addDefaultCount(int count) { lifter.default_count -= count; }
    std::int8_t limitPwm(std::int8_t pwm) { return lifter.limitPwm(pwm); }
    std::int32_t getCount() { return lifter.controller.liftMotor.getCount(); }
  };

  TEST_F(LifterTest, setDefaultCountTest) { ASSERT_EQ(getDefaultCount(), getCount()); }

  TEST_F(LifterTest, getCurrentAngleTest1)
  {
    addDefaultCount(90);
    ASSERT_EQ(lifter.getCurrentAngle(), 90);
  }

  TEST_F(LifterTest, getCurrentAngleTest2) { ASSERT_EQ(lifter.getCurrentAngle(), 0); }

  TEST_F(LifterTest, limitPwmTest1)
  {
    ASSERT_EQ(limitPwm(99), 99);
    ASSERT_EQ(limitPwm(100), 100);
    ASSERT_EQ(limitPwm(101), 100);
  }

  TEST_F(LifterTest, limitPwmTest2)
  {
    ASSERT_EQ(limitPwm(2), 2);
    ASSERT_EQ(limitPwm(1), 1);
    ASSERT_EQ(limitPwm(0), 1);
  }

  TEST_F(LifterTest, limitPwmTest3)
  {
    ASSERT_EQ(limitPwm(-100), 1);
    ASSERT_EQ(limitPwm(-50), 1);
    ASSERT_EQ(limitPwm(-1), 1);
  }

  TEST_F(LifterTest, limitPwmTest4)
  {
    ASSERT_EQ(limitPwm(10), 10);
    ASSERT_EQ(limitPwm(50), 50);
    ASSERT_EQ(limitPwm(80), 80);
  }

  TEST_F(LifterTest, liftUpTest1)
  {
    lifter.liftUp(90);
    ASSERT_LE(lifter.getCurrentAngle(), 93);
    ASSERT_GE(lifter.getCurrentAngle(), 90);
  }

  TEST_F(LifterTest, liftUpTest2)
  {
    lifter.liftUp(45);
    ASSERT_LE(lifter.getCurrentAngle(), 48);
    ASSERT_GE(lifter.getCurrentAngle(), 45);
  }

  TEST_F(LifterTest, liftDownTest1)
  {
    lifter.liftDown(90);
    ASSERT_GE(lifter.getCurrentAngle(), -93);
    ASSERT_LE(lifter.getCurrentAngle(), -90);
  }

  TEST_F(LifterTest, liftDownTest2)
  {
    lifter.liftDown(45);
    ASSERT_GE(lifter.getCurrentAngle(), -48);
    ASSERT_LE(lifter.getCurrentAngle(), -45);
  }

  TEST_F(LifterTest, defaultSetTest1)
  {
    lifter.liftUp(90);
    ASSERT_GE(lifter.getCurrentAngle(), 90);
    lifter.defaultSet();
    ASSERT_GE(lifter.getCurrentAngle(), -2);
    ASSERT_LE(lifter.getCurrentAngle(), 2);
  }

  TEST_F(LifterTest, defaultSetTest2)
  {
    lifter.defaultSet();
    ASSERT_GE(lifter.getCurrentAngle(), -2);
    ASSERT_LE(lifter.getCurrentAngle(), 2);
  }
}  // namespace etrobocon2018_test
