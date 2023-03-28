
#include <utils.h>


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
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 */
void write_json(FILE *exit_file, Membre m, int col_nahs[], bool save){
    char str[MAX_LENGTH];

    strcpy(str, "\t\t{\n");
    for (int i = 0; i < 4; i++){
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    strcat(str ,"\t\t\t\"Name\": \"");
                    strcat(str, m.name);
                    break;
                case 1:
                    strcat(str ,"\t\t\t\"Affiliation\": \"");
                    strcat(str, m.affiliation);
                    break;
                case 2:
                    strcat(str ,"\t\t\t\"Homepage\": \"");
                    strcat(str, m.homepage);
                    break;
                case 3:
                    strcat(str ,"\t\t\t\"Scholarid\": \"");
                    strcat(str, m.scholarid);
                    break;
           }
           strcat(str, "\",\n");
        }
    }
    str[strlen(str)-2] = 0; //pour enlever le dernier ","
    strcat(str, "\n\t\t}");
    
    if (save) {
        fwrite(str , sizeof(char) , strlen(str) , exit_file);
    } else {
        printf("%s", str);
    }
    
}


/**
 * @brief      Ecrit les différentes informations dans le fichier YAML donné en paramètre
 *
 * @param      exit_file    Fichier yaml
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 */
void write_yaml(FILE *exit_file, Membre m, int col_nahs[], bool save){
    char str[MAX_LENGTH];
    int first = 1;

    for (int i = 0; i < 4; i++){
        if (first){
             strcpy(str, "-");
            first = 0;
        }
        
        if (col_nahs[i] == 1){
            switch(i){
                case 0:
                    strcat(str ," Name: \"");
                    strcat(str, m.name);
                    strcat(str, "\"");
                    break;
                case 1:
                    strcat(str ," Affiliation: \"");
                    strcat(str, m.affiliation);
                    strcat(str, "\"");
                    break;
                case 2:
                    strcat(str ," Homepage: ");
                    strcat(str, m.homepage);
                    break;
                case 3:
                    strcat(str ," Scholarid: ");
                    strcat(str, m.scholarid);
                    break;
           }
           strcat(str, "\n");
        }
    }
    
    strcat(str, "\n");
    
    if(save){
         fwrite(str , sizeof(char) , strlen(str) , exit_file);
    } else {
        printf("%s", str);
    }
    
   
}





/**
 * @brief      Permet de lire le fichier csv et d'afficher ou ecrire dans un fichier json ou yaml la sortie
 *
 * @param      param  structure contenant les paramètre d'affichage ou de sauvegarde
 */
void read_csv(Parametres param){
    //Déclaration des variables
        Membre m;
        char line[MAX_LENGTH];
        char *token;
        char str[MAX_LENGTH];
        FILE *exit_file;
        int first = 1;
    
    //ouverture du fichier csv
        char* filename = "csrankings.csv";
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "can't open %s: %s\n", filename, strerror(errno));
            exit(1);
        }
        
    //Ecriture dans un fichier json ou yaml
        if (param.exit_format == JSON){ //json
            strcpy(str, "{\n\t\"affiliation\": \"");
            strcat(str, param.affi);
            strcat(str, "\",\n\t\"members\":[\n");
            if(param.save){
                exit_file = fopen(strcat(param.name_file, ".json"), "w");
                fwrite(str , sizeof(char), strlen(str) , exit_file );
            } else {
                printf("%s", str);
            }
        } else { //yaml
            strcpy(str, "---\naffiliation: \"");
            strcat(str, param.affi);
            strcat(str, "\"\nmembers:\n");
            if(param.save){
                exit_file = fopen(strcat(param.name_file, ".yaml"), "w");
                fwrite(str , sizeof(char), strlen(str) , exit_file );
            } else {
                printf("%s", str);
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
                    strcpy(m.name, token);
                    token = strtok(NULL, ",");
                    strcpy(m.affiliation, token);
                    token = strtok(NULL, ",");
                    strcpy(m.homepage, token);
                    token = strtok(NULL, ",");
                    strcpy(m.scholarid,token);
                
                if (!param.filtre || strcmp(param.affi, m.affiliation) == 0){
                    prnt = 1;
                }
                
                    
                //On supprime le retour à la ligne
                    m.scholarid[strcspn(m.scholarid, "\r\n")] = 0;

                    fgets(line, sizeof(line), file);
                //Ecriture si save sinon on print
                    if (!first) { //on skip la première ligne car entête des colonnes
                        if(prnt){
                            if (param.exit_format == JSON){ //json
                                write_json(exit_file, m, param.col_nahs, param.save);
                                if (!feof(file)){
                                    strcpy(str, ",\n");
                                    if (param.save){
                                        fwrite(str , sizeof(char) , strlen(str) , exit_file );
                                    } else {
                                        printf("%s", ",\n");
                                    }
                                }
                            } else { //yaml
                                write_yaml(exit_file, m, param.col_nahs, param.save);
                            }
                        }
                    } else {
                        first = 0;
                    }
                }
            
        
        //Fin du fichier
            if (param.exit_format == JSON){ //json
                strcpy(str, "\t]\n}");
                if (param.save){
                    fwrite(str , sizeof(char), strlen(str) , exit_file );
                } else {
                    printf("%s", str);
                }
            }
            
            if (param.save){
                fclose(exit_file);
            } 
    
    //fermeture du csv
        fclose(file);  
}




