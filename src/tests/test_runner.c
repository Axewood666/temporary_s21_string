#include "test_runner.h"

int main(void) {
  int i = 0;
  int fail_count = 0;
  Suite *test_functions[] = {TEST_FUNCS, NULL};
  char *line = "---------------\n";
  while (test_functions[i]) {
    printf("%s", line);
    SRunner *sr = srunner_create(test_functions[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    fail_count += srunner_ntests_failed(sr);
    srunner_free(sr);
    i++;
    printf("%s", line);
  }

  if (fail_count != 0) {
    fail_count = 1;
  }
  return fail_count;
}