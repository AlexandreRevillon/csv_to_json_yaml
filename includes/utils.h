#ifndef __UTILS_H__
#define __UTILS_H__

#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024 // Taille max des chaines de caractères
#define TRUE 1
#define FALSE 0

typedef enum format { JSON, YAML } Format;

typedef struct membre {
  char name[MAX_LENGTH];
  char affiliation[MAX_LENGTH];
  char homepage[MAX_LENGTH];
  char scholarid[MAX_LENGTH];
} Membre;

typedef struct parametres {
  Format exit_format;
  char name_file[MAX_LENGTH];
  bool save;
  int col_nahs[4];
  char affi[MAX_LENGTH];
  bool filtre;
} Parametres;

/**
 * @brief      Supprime les caractères indésirables d'une chaîne de caractères
 *
 * @param      str       Chaîne de caractères
 * @param      unwanted  Caractère indésirable
 */
void trim_unwanted_chars(char *str, char unwanted);

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
void write_output(FILE *exit_file, Membre m, Parametres p);

/**
 * @brief      Lit le fichier CSV et affiche ou �crit dans un fichier JSON ou
 * YAML la sortie
 *
 * @param      param       Structure contenant les param�tres d'affichage ou de
 * sauvegarde
 */
void read_csv(Parametres param);

/**
 * @brief      Ouvre le fichier CSV et vérifie s'il a été correctement ouvert
 *
 * @param      filename    Nom du fichier CSV
 *
 * @return     Pointeur vers le fichier CSV ouvert
 */
FILE *open_csv_file(const char *filename);

/**
 * @brief      Ferme les fichiers JSON et YAML aprés avoir écrit la chaîne
 * finale
 *
 * @param      param       Structure contenant les paramètres d'affichage ou de
 * sauvegarde
 * @param      exit_file   Fichier de sortie
 * @param      str         Chaîne à écrire dans le fichier de sortie
 */
void close_output_file(Parametres param, FILE *exit_file, char *str);

/**
 * @brief      Vérifie si un membre doit être affiché ou non en fonction des
 * paramètres donnés
 *
 * @param      param  Structure contenant les paramètres d'affichage ou de
 * sauvegarde
 * @param      m      Membre dont les informations doivent être vérifiées
 *
 * @return     Retourne true si le membre doit être affiché, sinon false
 */
bool should_print_member(Parametres param, Membre m);

/**
 * @brief      Traite une ligne du fichier CSV, extrait les informations et les
 * stocke dans une structure Membre
 *
 * @param      file  Fichier CSV ouvert
 * @param      line  Ligne du fichier CSV à traiter
 * @param      m     Pointeur vers une structure Membre pour stocker les
 * informations extraites
 */
void process_line(char *line, Membre *m);

/**
 * @brief      Prépare le fichier de sortie en fonction des paramètres donnés et
 * écrit les informations d'entête
 *
 * @param      param      Structure contenant les paramètres d'affichage ou de
 * sauvegarde
 * @param      exit_file  Pointeur vers un pointeur de fichier pour stocker le
 * fichier de sortie
 * @param      str        Chaîne de caractères pour stocker l'entête formatée
 */
void prepare_output_file(Parametres param, FILE **exit_file, char *str);

#endif //__UTILS_H__
