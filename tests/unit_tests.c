/**
 * @author     Alexandre REVILLON & Arthur DUPIRE
 * @date       2023
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utils.h>

/**
 * @brief test qui vérifie si la fonction remplace bien les caractère souhaité
 * par un espace
 */
START_TEST(test_trim_unwanted_chars_with_unwanted) {
  char str_test[] = "Texte avec\tdes \"caracteres indesirables\"";
  char str_result[] = "Texte avec des  caracteres indesirables ";

  trim_unwanted_chars(str_test, '\"');
  trim_unwanted_chars(str_test, '\t');

  ck_assert_str_eq(str_test, str_result);
}
END_TEST

/**
 * @brief test qui vérifie si le comportement de la fonction en l'absence de
 * caractère à remplacer
 */
START_TEST(test_trim_unwanted_chars_without_unwanted) {
  char str_test[] = "Texte avec des caracteres indesirables";
  char str_result[] = "Texte avec des caracteres indesirables";

  trim_unwanted_chars(str_test, '\"');
  trim_unwanted_chars(str_test, '\t');

  ck_assert_str_eq(str_test, str_result);
}
END_TEST

/**
 * @brief test qui vérifie la bon ecriture du fichier de sortie au format JSON
 */
START_TEST(test_write_output_json) {
  // Create a temporary file for the output
  FILE *temp_file = tmpfile();
  ck_assert_ptr_nonnull(temp_file);

  Membre m = {
      .name = "John Doe",
      .affiliation = "Université de Lille",
      .homepage = "http://google.com",
      .scholarid = "azerty12345",
  };

  Parametres p = {
      .exit_format = JSON,
      .col_nahs = {1, 1, 1, 1},
      .save = 1,
  };

  write_output(temp_file, m, p);

  // Move the file cursor back to the beginning
  rewind(temp_file);

  // Read the contents of the temporary file
  char buffer[256];
  fread(buffer, sizeof(char), sizeof(buffer) - 1, temp_file);
  buffer[sizeof(buffer) - 1] = '\0';

  // Expected JSON output
  const char *expected_output =
      "\t\t{\n"
      "\t\t\t\"Name\": \"John Doe\",\n"
      "\t\t\t\"Affiliation\": \"Université de Lille\",\n"
      "\t\t\t\"Homepage\": \"http://google.com\",\n"
      "\t\t\t\"Scholarid\": \"azerty12345\"\n"
      "\t\t}";

  ck_assert_str_eq(buffer, expected_output);

  fclose(temp_file);
}
END_TEST

/**
 * @brief test qui vérifie la bonne ouverture d'un fichier csv
 */
START_TEST(test_open_csv_file) {
  const char *filename = "./includes/csrankings.csv";
  FILE *file = open_csv_file(filename);
  ck_assert_ptr_nonnull(file);
  fclose(file);
}
END_TEST

/**
 * @brief test qui vérifie la bonne vérification de l'université affiliée
 */
START_TEST(test_should_print_member) {
  Parametres param = {
      .affi = "Université de Lille",
      .filtre = 1,
  };

  Membre m1 = {
      .name = "John Doe",
      .affiliation = "Université de Lille",
      .homepage = "http://google.com",
      .scholarid = "azerty12345",
  };

  Membre m2 = {
      .name = "John Doe2",
      .affiliation = "Université de Paris",
      .homepage = "http://google2.com",
      .scholarid = "azerty123456",
  };

  ck_assert(should_print_member(param, m1));
  ck_assert(!should_print_member(param, m2));
}
END_TEST

/**
 * @brief test qui vérifie la bon ecriture du fichier de sortie au format YAML
 */
START_TEST(test_write_output_yaml) {
  // Create a temporary file for the output
  FILE *temp_file = tmpfile();
  ck_assert_ptr_nonnull(temp_file);

  Membre m = {
      .name = "John Doe",
      .affiliation = "Université de Lille",
      .homepage = "http://google.com",
      .scholarid = "azerty12345",
  };

  Parametres p = {
      .exit_format = YAML,
      .col_nahs = {1, 1, 1, 1},
      .save = 1,
  };

  write_output(temp_file, m, p);

  // Move the file cursor back to the beginning
  rewind(temp_file);

  // Read the contents of the temporary file
  char buffer[256];
  fread(buffer, sizeof(char), sizeof(buffer) - 1, temp_file);
  buffer[sizeof(buffer) - 1] = '\0';

  // Expected JSON output
  const char *expected_output = "-\n"
                                "  Name: \"John Doe\"\n"
                                "  Affiliation: \"Université de Lille\"\n"
                                "  Homepage: \"http://google.com\"\n"
                                "  Scholarid: \"azerty12345\"\n";

  ck_assert_str_eq(buffer, expected_output);

  fclose(temp_file);
}
END_TEST

/**
 * @brief test qui vérifie la bonne lecture du fichier csv
 */
START_TEST(test_read_csv) {
  // Create a temporary file for the output
  FILE *temp_file = tmpfile();
  ck_assert_ptr_nonnull(temp_file);

  // Redirect stdout to the temporary file
  fflush(stdout);
  int old_stdout = dup(fileno(stdout));
  dup2(fileno(temp_file), fileno(stdout));

  Parametres param = {.affi = "University of Hildesheim",
                      .exit_format = YAML,
                      .filtre = 1,
                      .save = 0,
                      .col_nahs = {1, 0, 0, 1}};

  read_csv(param);

  // Restore the original stdout
  fflush(stdout);
  dup2(old_stdout, fileno(stdout));
  close(old_stdout);

  // Move the file cursor back to the beginning
  rewind(temp_file);

  // Read the contents of the temporary file
  char buffer[4096];
  fread(buffer, sizeof(char), sizeof(buffer) - 1, temp_file);
  buffer[sizeof(buffer) - 1] = '\0';

  // Expected JSON output
  const char *expected_output = "---\n"
                                "affiliation: \"University of Hildesheim\"\n"
                                "members:\n"
                                "-\n"
                                "  Name: \"Klaus Schmid\"\n"
                                "  Scholarid: \"dK9g6a4AAAAJ\"\n"
                                "-\n"
                                "  Name: \"Klaus-Dieter Althoff\"\n"
                                "  Scholarid: \"i4hdvtYAAAAJ\"\n"
                                "-\n"
                                "  Name: \"Lars Schmidt-Thieme\"\n"
                                "  Scholarid: \"l3taTdYAAAAJ\"\n";

  ck_assert_str_eq(buffer, expected_output);

  fclose(temp_file);
}
END_TEST

/**
 * @brief test qui vérifie que les informations récupéré par la fonction
 * pross_line sont justes
 */
START_TEST(test_process_line) {
  char line[] = "John Doe,Université de Lille,http://google.com,azerty12345";
  Membre m;

  process_line(line, &m);
  ck_assert_str_eq(m.name, "John Doe");
  ck_assert_str_eq(m.affiliation, "Université de Lille");
  ck_assert_str_eq(m.homepage, "http://google.com");
  ck_assert_str_eq(m.scholarid, "azerty12345");
}
END_TEST

/**
 * @brief test qui vérifie la bonne création du fichier json
 */
START_TEST(test_prepare_output_file_json) {
  Parametres param_json = {
      .affi = "Université de Lille", .exit_format = JSON, .save = 1};

  FILE *exit_file;
  char str[512];

  prepare_output_file(param_json, &exit_file, str);
  ck_assert_str_eq(
      str, "{\n\t\"affiliation\": \"Université de Lille\",\n\t\"members\":[\n");
}
END_TEST

/**
 * @brief test qui vérifie la bonne création du fichier yaml
 */
START_TEST(test_prepare_output_file_yaml) {
  Parametres param_yaml = {
      .affi = "Université de Lille", .exit_format = YAML, .save = 1};

  FILE *exit_file;
  char str[512];

  prepare_output_file(param_yaml, &exit_file, str);
  ck_assert_str_eq(str,
                   "---\naffiliation: \"Université de Lille\"\nmembers:\n");
}
END_TEST

Suite *functions_suite(void) {
  Suite *s = suite_create("functions");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_trim_unwanted_chars_with_unwanted);
  tcase_add_test(tc_core, test_trim_unwanted_chars_without_unwanted);
  tcase_add_test(tc_core, test_write_output_json);
  tcase_add_test(tc_core, test_write_output_yaml);
  tcase_add_test(tc_core, test_open_csv_file);
  tcase_add_test(tc_core, test_should_print_member);
  tcase_add_test(tc_core, test_process_line);
  tcase_add_test(tc_core, test_prepare_output_file_json);
  tcase_add_test(tc_core, test_prepare_output_file_yaml);
  tcase_add_test(tc_core, test_read_csv);
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
