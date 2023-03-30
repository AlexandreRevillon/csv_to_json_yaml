#ifndef __UTILS_H__
#define __UTILS_H__

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LENGTH 1024 //Taille max des chaines de caractères
#define TRUE 1
#define FALSE 0

typedef enum format {JSON, YAML}Format;


typedef struct membre {
    char name[MAX_LENGTH];
    char affiliation[MAX_LENGTH];
    char homepage[MAX_LENGTH];
    char scholarid[MAX_LENGTH];
} Membre;


typedef struct parametres{
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


/**
 * @brief      Ecrit les différentes informations dans le fichier JSON donné en paramètre
 *
 * @param      exit_file    Fichier json
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 */
void write_json(FILE *exit_file, Membre m, int col_nahs[], bool save);


/**
 * @brief      Ecrit les différentes informations dans le fichier YAML donné en paramètre
 *
 * @param      exit_file    Fichier yaml
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 */
void write_yaml(FILE *exit_file, Membre m, int col_nahs[], bool save);





/**
 * @brief      Permet de lire le fichier csv et d'afficher ou ecrire dans un fichier json ou yaml la sortie
 *
 * @param      param  structure contenant les paramètre d'affichage ou de sauvegarde
 */
void read_csv(Parametres param);

#endif //__UTILS_H__


