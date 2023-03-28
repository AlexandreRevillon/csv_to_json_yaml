/**
 * @brief      This file implements unit tests for sorting algorithms
 *
 * @author     Jeremie
 * @date       2022
 */
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

/**
 * @brief Simple test that checks whether the random number generator has
 *        has been initialized
 */


START_TEST (test_trim_quote) { 
    char str_test[] = {"\"Texte avec des quotes\""};
    char str_result[] = {" Texte avec des quotes "};
    trim_quote(str_test);
    
   ck_assert_str_eq(str_test, str_result);
}
END_TEST


Suite *sort_suite (void)
{
    Suite *s       = suite_create ("SortAlgorithms");
    TCase *tc_core = tcase_create ("Core");
    tcase_add_test (tc_core, test_trim_quote);
    suite_add_tcase (s, tc_core);

    return s;
}

int main (void)
{
 int      no_failed = 0;
    Suite   *s         = sort_suite ();
    SRunner *runner    = srunner_create (s);
    srunner_run_all (runner, CK_NORMAL);
    no_failed = srunner_ntests_failed (runner);
    srunner_free (runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

