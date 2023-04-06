
#include <utils.h>


/**
 * @brief      Supprime les caractères indésirables d'une chaîne de caractères
 *
 * @param      str       Chaîne de caractères
 * @param      unwanted  Caractère indésirable
 */
void trim_unwanted_chars(char *str, char unwanted){
    char *new_str;
    
    new_str = strchr(str, unwanted);
    while (new_str){
        new_str[0] = ' ';
        new_str = strchr(str, unwanted);
    }
}




/**
 * @brief      Ecrit les différentes informations dans le fichier de sortie donné en paramètre
 *
 * @param      exit_file    Fichier de sortie
 * @param      m            Membre à écrire contenant toutes ses informations
 * @param      col_nahs     Tableau des informations du membre à écrire ou non
 * @param      save         Booléen indiquant si l'on doit sauvegarder ou afficher les informations
 * @param      format       Format de sortie (JSON ou YAML)
 */
void write_output(FILE *exit_file, Membre m, Parametres p){
    char str[MAX_LENGTH];

    if (p.exit_format == JSON) {
        strcpy(str, "\t\t{\n");
    } else {
        strcpy(str, "-\n");
    }

    for (int i = 0; i < 4; i++){
        if (p.col_nahs[i] == 1){
            char *field_name;
            char *field_value;

            switch(i){
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
                sprintf(str + strlen(str), "\t\t\t\"%s\": \"%s\",\n", field_name, field_value);
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
        int first_line = 1;
        int first_print = 1;
    
    //ouverture du fichier csv
        char* filename = "./includes/csrankings.csv";
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
                trim_unwanted_chars(line, '\"');
                trim_unwanted_chars(line, '\t');
                //On récupérer les élèments de la ligne
                    token = strtok(line, ",");
                    strcpy(m.name, token);
                    token = strtok(NULL, ",");
                    strcpy(m.affiliation, token);
                    token = strtok(NULL, ",");
                    strcpy(m.homepage, token);
                    token = strtok(NULL, ",");
                    strcpy(m.scholarid,token);
                
                prnt = (!param.filtre || strcmp(param.affi, m.affiliation) == 0);
                
                    
                //On supprime le retour à la ligne
                    m.scholarid[strcspn(m.scholarid, "\r\n")] = 0;

                    fgets(line, sizeof(line), file);
                //Ecriture si save sinon on print
                    if (!first_line && prnt) { //on skip la première ligne car entête des colonnes
                        if(param.exit_format == JSON && !first_print){
                            strcpy(str, ",\n");
                            fwrite(str , sizeof(char), strlen(str) , exit_file );
                        } else {
                            first_print = 0;
                        }
                        write_output(exit_file, m, param);
                    } else {
                        first_line = 0;
                    }
                }
            
        
        //Fin du fichier
            if (param.exit_format == JSON){ //json
                strcpy(str, "\n\t]\n}");
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




