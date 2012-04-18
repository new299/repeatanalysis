#include <iostream>
#include "test_repeatscore.h"

#include "utf.h"

int main(void) {

  UnitTest ut("Repeatscore Tests");
  test_repeatscore(ut);
  ut.test_report();

  return 0;
}

