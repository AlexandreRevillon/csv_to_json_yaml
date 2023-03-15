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

/**
 * @brief      Compares 3 arrays of integers
 *
 * @param      t1    1st array
 * @param      t2    2nd array
 * @param      t3    3rd array
 * @param[in]  N     the first N cells will to be checked
 *
 * @return     { description_of_the_return_value }
 */
// bool compare_tab (int t1[], int t2[], int t3[], unsigned int N)
// {
//     
// }

void trim_quote(char *str){
    char *new_str;
    new_str = strchr(str, '\"');
    while (new_str){
        new_str[0] = ' ';
        new_str = strchr(str, '\"');
    }
}

void write_json(FILE *exit_file, char *name, char *affiliation, char *homepage, char *scholarid, int col_nahs[]){
    char str[500];
    
    fwrite("\t{\n" , 1 , 3 , exit_file );
    for (int i = 0; i < 4; i++){
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    strcat(str ,"\t\t\"Name\": \"");
                    strcat(str, name);
                    break;
                case 1:
                    strcat(str ,"\t\t\"Affiliation\": \"");
                    strcat(str, affiliation);
                    break;
                case 2:
                    strcat(str ,"\t\t\"Homepage\": \"");
                    strcat(str, homepage);
                    break;
                case 3:
                    strcat(str ,"\t\t\"Scholarid\": \"");
                    strcat(str, scholarid);
                    break;
           }
           strcat(str, "\",\n");
        }
    }
    str[strlen(str)-2] = 0;
    strcat(str, "\n");
    fwrite(str , 1 , strlen(str) , exit_file);
    strcpy(str, "");
    fwrite("\t}" , 1 , 2 , exit_file);
}


void write_yaml(FILE *exit_file, char *name, char *affiliation, char *homepage, char *scholarid, int col_nahs[]){
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
        char name[50];
        char affiliation[50]; 
        char homepage[250];
        char scholarid[50];
        char line[500];
        char *token;
        char str[150]
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
                    fwrite("{\n" , 1 , 2 , exit_file );
                } else { //yaml
                exit_file = fopen(strcat(name_file, ".yaml"), "w");
                }
            } 
        
        //Ecriture ou print pour chaque ligne
            fgets(line, sizeof(line), file);
            while(!feof(file)){
                trim_quote(line);
                //On récupérer les élèments de la ligne
                    token = strtok(line, ",");
                    strcpy(name, token);
                    token = strtok(NULL, ",");
                    strcpy(affiliation, token);//yaml
                    token = strtok(NULL, ",");
                    strcpy(homepage, token);
                    token = strtok(NULL, ",");
                    strcpy(scholarid,token);
                
                //On supprime le retour à la ligne
                    scholarid[strcspn(scholarid, "\r\n")] = 0;

                    fgets(line, sizeof(line), file);
                //Ecriture si save sinon on print
                    if (!first) {
                        if(save){
                            if (exit_format){ //json
                                write_json(exit_file, name, affiliation, homepage, scholarid, col_nahs);
                                if (!feof(file))  fwrite(",\n" , 1 , 2 , exit_file );
                            } else { //yaml
                                write_yaml(exit_file, name, affiliation, homepage, scholarid, col_nahs);
                            }
                        } else {
                            print_selectif(name, affiliation, homepage, scholarid, col_nahs);
                        }
                    } else {
                        first = 0;
                    }
            }
        
        //Fin du fichier
            if(save){
                if (exit_format){ //json
                    fwrite("\n}" , 1 , 2 , exit_file );
                } else { //yaml
                exit_file = fopen(strcat(name_file, ".yaml"), "a");
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
