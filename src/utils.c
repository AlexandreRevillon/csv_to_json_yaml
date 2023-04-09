
#include <utils.h>

/**
 * @brief      Supprime les caractères indésirables d'une chaîne de caractères
 *
 * @param      str       Chaîne de caractères
 * @param      unwanted  Caractère indésirable
 */
void trim_unwanted_chars(char *str, char unwanted) {
  char *new_str;

  new_str = strchr(str, unwanted);
  while (new_str) {
    new_str[0] = ' ';
    new_str = strchr(str, unwanted);
  }
}

/*
 * @brief      Ecrit les différentes informations dans le fichier de sortie
 * donné en paramètre
 *
 * @param      exit_file    Fichier de sortie
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 * @param      save         Booléen indiquant si l'on doit sauvegarder ou
 * afficher les informations
 * @param      format       Format de sortie (JSON ou YAML)
 */
void write_output(FILE *exit_file, Membre m, Parametres p) {
  char str[MAX_LENGTH];

  if (p.exit_format == JSON) {
    strcpy(str, "\t\t{\n");
  } else {
    strcpy(str, "-\n");
  }

  for (int i = 0; i < 4; i++) {
    if (p.col_nahs[i] == 1) {
      char *field_name;
      char *field_value;

      switch (i) {
      case 0:
        field_name = "Name";
        field_value = m.name;
        break;
      case 1:
        field_name = "Affiliation";
        field_value = m.affiliation;
        break;
      case 2:
        field_name = "Homepage";
        field_value = m.homepage;
        break;
      case 3:
        field_name = "Scholarid";
        field_value = m.scholarid;
        break;
      }

      if (p.exit_format == JSON) {
        sprintf(str + strlen(str), "\t\t\t\"%s\": \"%s\",\n", field_name,
                field_value);
      } else {
        sprintf(str + strlen(str), "  %s: \"%s\"\n", field_name, field_value);
      }
    }
  }
  if (p.exit_format == JSON) {
    str[strlen(str) - 2] = 0; // pour enlever le dernier ","
    strcat(str, "\n\t\t}");
  }

  if (p.save) {
    fwrite(str, sizeof(char), strlen(str), exit_file);
  } else {
    printf("%s", str);
  }
}

/**
 * @brief      Ouvre le fichier CSV et vérifie s'il a été correctement ouvert
 *
 * @param      filename    Nom du fichier CSV
 *
 * @return     Pointeur vers le fichier CSV ouvert
 */
FILE *open_csv_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "can't open %s: %s\n", filename, strerror(errno));
        exit(1);
    }
    return file;
}

/**
 * @brief      Ferme les fichiers JSON et YAML aprés avoir écrit la chaîne finale
 *
 * @param      param       Structure contenant les paramètres d'affichage ou de sauvegarde
 * @param      exit_file   Fichier de sortie
 * @param      str         Chaîne à écrire dans le fichier de sortie
 */
void close_output_file(Parametres param, FILE *exit_file, char *str) {
    if (param.exit_format == JSON) {
        strcpy(str, "\n\t]\n}");
        if (param.save) {
            fwrite(str, sizeof(char), strlen(str), exit_file);
        } else {
            printf("%s", str);
        }
    }

    if (param.save) {
        fclose(exit_file);
    }
}

/**
 * @brief      Prépare le fichier de sortie en fonction des paramètres donnés et écrit les informations d'entête
 *
 * @param      param      Structure contenant les paramètres d'affichage ou de sauvegarde
 * @param      exit_file  Pointeur vers un pointeur de fichier pour stocker le fichier de sortie
 * @param      str        Chaîne de caractères pour stocker l'entête formatée
 */
void prepare_output_file(Parametres param, FILE **exit_file, char *str) {
    if (param.exit_format == JSON) {
        sprintf(str, "{\n\t\"affiliation\": \"%s\",\n\t\"members\":[\n", param.affi);
    } else {
        sprintf(str, "---\naffiliation: \"%s\"\nmembers:\n", param.affi);
    }

    if (param.save) {
        strcat(param.name_file, param.exit_format == JSON ? ".json" : ".yaml");
        *exit_file = fopen(param.name_file, "w");
        fwrite(str, sizeof(char), strlen(str), *exit_file);
    } else {
        printf("%s", str);
    }
}

/**
 * @brief      Vérifie si un membre doit être affiché ou non en fonction des paramètres donnés
 *
 * @param      param  Structure contenant les paramètres d'affichage ou de sauvegarde
 * @param      m      Membre dont les informations doivent être vérifiées
 *
 * @return     Retourne true si le membre doit être affiché, sinon false
 */
bool should_print_member(Parametres param, Membre m) {
    return !param.filtre || strcmp(param.affi, m.affiliation) == 0;
}

/**
 * @brief      Traite une ligne du fichier CSV, extrait les informations et les stocke dans une structure Membre
 *
 * @param      file  Fichier CSV ouvert
 * @param      line  Ligne du fichier CSV à traiter
 * @param      m     Pointeur vers une structure Membre pour stocker les informations extraites
 */
void process_line(char *line, Membre *m) {
    char *token;

    trim_unwanted_chars(line, '\"');
    trim_unwanted_chars(line, '\t');

    token = strtok(line, ",");
    strcpy(m->name, token);
    token = strtok(NULL, ",");
    strcpy(m->affiliation, token);
    token = strtok(NULL, ",");
    strcpy(m->homepage, token);
    token = strtok(NULL, ",");
    strcpy(m->scholarid, token);

    m->scholarid[strcspn(m->scholarid, "\r\n")] = 0;
}

/**
 * @brief      Lit le fichier CSV et affiche ou �crit dans un fichier JSON ou YAML la sortie
 *
 * @param      param       Structure contenant les param�tres d'affichage ou de sauvegarde
 */
void read_csv(Parametres param) {
    Membre m;
    char line[MAX_LENGTH];
    char str[MAX_LENGTH];
    FILE *exit_file = NULL;
    int first_line = 1;
    int first_print = 1;

    char *filename = "./includes/csrankings.csv";
    FILE *file = open_csv_file(filename);

    prepare_output_file(param, &exit_file, str);

    fgets(line, sizeof(line), file);
    while (!feof(file)) {
        process_line(line, &m);
        bool prnt = should_print_member(param, m);
        fgets(line, sizeof(line), file);

        if (!first_line && prnt) {
            if (param.exit_format == JSON && !first_print) {
                strcpy(str, ",\n");
                fwrite(str, sizeof(char), strlen(str), exit_file);
            } else {
                first_print = 0;
            }
            write_output(exit_file, m, param);
        } else {
            first_line = 0;
        }
    }

    close_output_file(param, exit_file, str);
    fclose(file);
}

