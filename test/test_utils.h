#ifndef MDG_TEST_UTILS_H
#define MDG_TEST_UTILS_H

#include <iostream>

namespace mdg {
namespace test {
unsigned TotalTests = 0;
unsigned CurrentTest = 0;
std::string CurrentSuiteName = "SuiteName";
}  // namespace test
}  // namespace mdg

#define MDG_TEST_INFO                                                         \
  std::cout << '[' << mdg::test::CurrentSuiteName << "]["                     \
            << mdg::test::CurrentTest << '/' << mdg::test::TotalTests << "][" \
            << __FUNCTION__ << "][INFO] "

#define MDG_TEST_WARN                                                         \
  std::cout << '[' << mdg::test::CurrentSuiteName << "]["                     \
            << mdg::test::CurrentTest << '/' << mdg::test::TotalTests << "][" \
            << __FUNCTION__ << "][WARN] "

#define MDG_TEST_ERROR                                                        \
  std::cout << '[' << mdg::test::CurrentSuiteName << "]["                     \
            << mdg::test::CurrentTest << '/' << mdg::test::TotalTests << "][" \
            << __FUNCTION__ << "][ERROR] "

#define MDG_ASSERT_EQUALITY(x, y)                             \
  if ((x) != (y)) {                                           \
    MDG_TEST_ERROR << "Assertion failed (" #x " == " #y "\n"; \
    exit(1);                                                  \
  }

#define MDG_ASSERT_INEQUALITY(x, y)                           \
  if ((x) == (y)) {                                           \
    MDG_TEST_ERROR << "Assertion failed: " #x " != " #y "\n"; \
    exit(1);                                                  \
  }

#define MDG_EXPECT_EQUALITY(x, y)                              \
  if ((x) != (y)) {                                            \
    MDG_TEST_ERROR << "Expectation unmet: " #x " != " #y "\n"; \
    return 1;                                                  \
  }

#define MDG_EXPECT_INEQUALITY(x, y)                            \
  if ((x) == (y)) {                                            \
    MDG_TEST_ERROR << "Expectation unmet: " #x " != " #y "\n"; \
    return 1;                                                  \
  }

#define MDG_TEST_MAIN(suite_name, ...)         \
  int main() {                                 \
    bool result = false;                       \
    mdg::test::CurrentTest = 0;                \
    mdg::test::CurrentSuiteName = #suite_name; \
                                               \
    auto tests = {__VA_ARGS__};                \
    mdg::test::TotalTests = tests.size();      \
                                               \
    for (auto test : tests) {                  \
      ++mdg::test::CurrentTest;                \
      result |= test();                        \
    }                                          \
                                               \
    return result;                             \
  }

#endif  // MDG_TEST_UTILS_H