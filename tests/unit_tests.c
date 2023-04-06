/**
 * @brief      This file implements unit tests for sorting algorithms
 *
 * @author     Alexandre REVILLON & Arthur DUPIRE
 * @date       2023
 */
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

/**
 * @brief Simple test that checks whether the random number generator has
 *        has been initialized
 */
START_TEST(test_trim_unwanted_chars_with_unwanted) {
  char str_test[] = "Texte avec\tdes \"caracteres indesirables\"";
  char str_result[] = "Texte avec des  caracteres indesirables ";

  trim_unwanted_chars(str_test, '\"');
  trim_unwanted_chars(str_test, '\t');

  ck_assert_str_eq(str_test, str_result);
}
END_TEST

START_TEST(test_trim_unwanted_chars_without_unwanted) {
  char str_test[] = "Texte avec des caracteres indesirables";
  char str_result[] = "Texte avec des caracteres indesirables";

  trim_unwanted_chars(str_test, '\"');
  trim_unwanted_chars(str_test, '\t');

  ck_assert_str_eq(str_test, str_result);
}
END_TEST

START_TEST(test_write_output) {
  Membre m = {.name = "John Doe",
              .affiliation = "University of Lille",
              .homepage = "https://Google.com",
              .scholarid = "azerty12345"};

  Parametres p = {.exit_format = JSON, .col_nahs = {1, 1, 1, 1}, .save = false};

  FILE *file = tmpfile();
  write_output(file, m, p);
  rewind(file);

  char buffer[1024];
  fgets(buffer, sizeof(buffer), file);
  fclose(file);

  ck_assert_str_eq(
      buffer,
      "\t\t{\n\t\t\t\"Name\": \"John Doe\",\n\t\t\t\"Affiliation\": "
      "\"University of Lille\",\n\t\t\t\"Homepage\": "
      "\"https://Google.com\",\n\t\t\t\"Scholarid\": \"azerty12345\"\n\t\t}");

  p.exit_format = YAML;
  file = tmpfile();
  write_output(file, m, p);
  rewind(file);

  fgets(buffer, sizeof(buffer), file);
  fclose(file);

  ck_assert_str_eq(
      buffer,
      "-\n  Name: \"John Doe\"\n  Affiliation: \"University of Lille\"\n  "
      "Homepage: \"https://Google.com\"\n  Scholarid: \"azerty12345\"\n");
}
END_TEST

Suite *functions_suite(void) {
  Suite *s = suite_create("functions");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_trim_unwanted_chars_with_unwanted);
  tcase_add_test(tc_core, test_trim_unwanted_chars_without_unwanted);
  tcase_add_test(tc_core, test_write_output);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s = functions_suite();
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
