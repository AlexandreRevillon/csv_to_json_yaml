/**
 * @brief      ...
 *
 * @author     Alexandre REVILLON & Arthur DUPIRE
 * @date       2023
 */

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LENGTH 1024 //Taille max des chaines de caractères


typedef struct membre {
    char name[MAX_LENGTH];
    char affiliation[MAX_LENGTH];
    char homepage[MAX_LENGTH];
    char scholarid[MAX_LENGTH];
} Membre;


typedef struct parametres{
    char exit_format ; // 0:yaml | 1:json
    char name_file[MAX_LENGTH];
    bool save;
    int col_nahs[4];
    char affi[MAX_LENGTH];
} Parametres;




/**
 * @brief      Supprime les guillemets d'une chaîne de caractère
 *
 * @param      str   Chaine de caractère
 */
void trim_quote(char *str){
    char *new_str;
    
    new_str = strchr(str, '\"');
    while (new_str){
        new_str[0] = ' ';
        new_str = strchr(str, '\"');
    }
}




/**
 * @brief      Supprime les tabulations d'une chaîne de caractère
 *
 * @param      str   Chaine de caractère
 */
void trim_tab(char *str){
    char *new_str;
    
    new_str = strchr(str, '\t');
    while (new_str){
        new_str[0] = ' ';
        new_str = strchr(str, '\"');
    }
}


/**
 * @brief      Ecrit les différentes informations dans le fichier JSON donné en paramètre
 *
 * @param      exit_file    Fichier json
 * @param      name         Nom du membre
 * @param      affiliation  Affiliation du membre
 * @param      homepage     HomePage du membre
 * @param      scholarid    Scholarid du membre
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 */
void write_json(FILE *exit_file, char *name, char *affiliation, char *homepage, char *scholarid, int col_nahs[]){
    char str[MAX_LENGTH];

    strcpy(str, "\t\t{\n");
    for (int i = 0; i < 4; i++){
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    strcat(str ,"\t\t\t\"Name\": \"");
                    strcat(str, name);
                    break;
                case 1:
                    strcat(str ,"\t\t\t\"Affiliation\": \"");
                    strcat(str, affiliation);
                    break;
                case 2:
                    strcat(str ,"\t\t\t\"Homepage\": \"");
                    strcat(str, homepage);
                    break;
                case 3:
                    strcat(str ,"\t\t\t\"Scholarid\": \"");
                    strcat(str, scholarid);
                    break;
           }
           strcat(str, "\",\n");
        }
    }
    str[strlen(str)-2] = 0; //pour enlever le dernier ","
    strcat(str, "\n\t\t}");
    
    fwrite(str , sizeof(char) , strlen(str) , exit_file);
}


void write_yaml(FILE *exit_file, char *name, char *affiliation, char *homepage, char *scholarid, int col_nahs[]){
    char str[MAX_LENGTH];
    int first = 1;

    for (int i = 0; i < 4; i++){
        if (first){
             strcpy(str, "-");
            first = 0;
        } else {
            strcat(str, " ");
        }
        
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    strcat(str ," Name: \"");
                    strcat(str, name);
                    strcat(str, "\"");
                    break;
                case 1:
                    strcat(str ," Affiliation: \"");
                    strcat(str, affiliation);
                    strcat(str, "\"");
                    break;
                case 2:
                    strcat(str ," Homepage: ");
                    strcat(str, homepage);
                    break;
                case 3:
                    strcat(str ," Scholarid: ");
                    strcat(str, scholarid);
                    break;
           }
           strcat(str, "\n");
        }
    }
    strcat(str, "\n");
    fwrite(str , sizeof(char) , strlen(str) , exit_file);
}




void print_selectif(char *name, char *affiliation, char *homepage, char *scholarid, int col_nahs[]){
    for (int i = 0; i < 4; i++){
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    printf("Name: %s ", name);
                    break;
                case 1:
                    printf("Affiliation: %s  ", affiliation);
                    break;
                case 2:
                    printf("Site web: %s  ", homepage);
                    break;
                case 3:
                    printf("scholarid: %s  ", scholarid);
                    break;
           }
        }
    }
    printf("\n");
}





void read_csv(int exit_format, char *name_file, bool save, int col_nahs[], char *affi){
    //Déclaration des variables
        char name[MAX_LENGTH];
        char affiliation[MAX_LENGTH]; 
        char homepage[MAX_LENGTH];
        char scholarid[MAX_LENGTH];
        char line[MAX_LENGTH];
        char *token;
        char str[MAX_LENGTH];
        FILE* exit_file;
        int first = 1;
    
    //ouverture du fichier csv
        char* filename = "csrankings.csv";
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "can't open %s: %s\n", filename, strerror(errno));
            exit(1);
        }

    //Ecriture dans un fichier json ou yaml
        //Début du fichier (si sauvegarde)
            if(save){
                if (exit_format){ //json
                    exit_file = fopen(strcat(name_file, ".json"), "w");
                    strcpy(str, "{\n\t\"affiliation\": \"");
                    strcat(str, affi);
                    strcat(str, "\",\n\t\"members\":[\n");
                    fwrite(str , sizeof(char), strlen(str) , exit_file );
                } else { //yaml
                    exit_file = fopen(strcat(name_file, ".yaml"), "w");
                    strcpy(str, "---\naffiliation: \"");
                    strcat(str, affi);
                    strcat(str, "\"\nmembers:\n");
                    fwrite(str , sizeof(char), strlen(str) , exit_file );
                }
            } 
        
        //Ecriture ou print pour chaque ligne
            fgets(line, sizeof(line), file);
            while(!feof(file)){
                int prnt = 0;
                trim_quote(line);
                trim_tab(line);
                //On récupérer les élèments de la ligne
                    token = strtok(line, ",");
                    strcpy(name, token);
                    token = strtok(NULL, ",");
                    strcpy(affiliation, token);//yaml
                    token = strtok(NULL, ",");
                    strcpy(homepage, token);
                    token = strtok(NULL, ",");
                    strcpy(scholarid,token);
                
                if (strcmp(affi, affiliation) == 0){
                    prnt = 1;
                }
                    
                    
                //On supprime le retour à la ligne
                    scholarid[strcspn(scholarid, "\r\n")] = 0;

                    fgets(line, sizeof(line), file);
                //Ecriture si save sinon on print
                    if (!first) { //on skip la première ligne car entête des colonnes
                        if(save && prnt){
                            if (exit_format){ //json
                                write_json(exit_file, name, affiliation, homepage, scholarid, col_nahs);
                                if (!feof(file)){
                                    strcpy(str, ",\n");
                                    fwrite(str , sizeof(char) , strlen(str) , exit_file );
                                }
                            } else { //yaml
                                write_yaml(exit_file, name, affiliation, homepage, scholarid, col_nahs);
                            }
                        } else if(prnt) {
                            print_selectif(name, affiliation, homepage, scholarid, col_nahs);
                        }
                    } else {
                        first = 0;
                    }
            }
        
        //Fin du fichier
            if(save){
                if (exit_format){ //json
                    strcpy(str, "\t]\n}");
                    fwrite(str , sizeof(char), strlen(str) , exit_file );
                }
                fclose(exit_file);
            } 
    
    //fermeture du csv
        fclose(file);  
}





int main (int argc, char* argv[])
{
    int i = 1;
    char exit_format = 0 ; // 0:yaml | 1:json
    char name_file[50] ="";
    bool save = 0;
    int col_nahs[] = {1,1,1,1};
    char affi[50];

    //Parcours des argument du main
        while(i < argc-1)  /* Skip argv[0] (program name). */
        {
            if (strcmp(argv[i], "-t") == 0)  /* Process optional arguments. */
            {   
                if (strcmp(argv[i+1], "yaml") == 0){
                    exit_format = 0;
                } else if (strcmp(argv[i+1], "json") == 0) {
                    exit_format = 1;
                } else {
                    fprintf( stderr, "%s : Format inconnu\n", argv[i]);
                    exit(1);
                }

            }
            else if  (strcmp(argv[i], "-o") == 0)
            {
                save = 1;
                strcpy(name_file, argv[i+1]);
            }
            else if  (strcmp(argv[i], "-f") == 0)
            {
                for(int i = 0; i<4; i++) col_nahs[i] = 0;
                for (int j = 0; j < sizeof(argv[i+1]); j++){
                    switch (argv[i+1][j]) {
                        case 'n':
                            col_nahs[0] = 1;
                            break;
                        case 'a':
                            col_nahs[1] = 1;
                            break;
                        case 'h':
                            col_nahs[2] = 1;
                            break;
                        case 's':
                            col_nahs[3] = 1;
                            break;
                    }
                }
            }
            else if  (strcmp(argv[i], "-s") == 0)
            {
                strcpy(affi, argv[i+1]);
            }
            else
            {
                fprintf( stderr, "%s : Argument non reconnu\n", argv[i]);
                exit(1);
            }
            i += 2;
        }
    
    
    read_csv(exit_format, name_file, save, col_nahs, affi);
    
    //printf("n: %d, a: %d, h: %d, s: %d\n", col_nahs[0], col_nahs[1], col_nahs[2], col_nahs[3]);
    
    return 0;
}
