/**
 * @brief      ...
 *
 * @author     Alexandre REVILLON & Arthur DUPIRE
 * @date       2023
 */

#include <utils.h>

int main (int argc, char* argv[])
{   
    //Déclaration des variables
        int i = 1; //Variables d'incrémentation
    
    //Déclaration et initialisation des paramètres à des valeurs par defaut
        Parametres param = {YAML , "", FALSE, {TRUE,TRUE,TRUE,TRUE}, "", FALSE};

    //Parcours des argument du main
        while(i < argc-1)  /* Skip argv[0] (program name). */
        {
            if (strcmp(argv[i], "-t") == 0)  /* Process optional arguments. */
            {   
                if (strcmp(argv[i+1], "yaml") == 0){
                    param.exit_format = YAML;
                } else if (strcmp(argv[i+1], "json") == 0) {
                    param.exit_format = JSON;
                } else {
                    fprintf( stderr, "%s : Format inconnu\n", argv[i]);
                    exit(1);
                }

            }
            else if  (strcmp(argv[i], "-o") == 0)
            {
                param.save = 1;
                strcpy(param.name_file, argv[i+1]);
            }
            else if  (strcmp(argv[i], "-f") == 0)
            {
                for(int i = 0; i<4; i++) param.col_nahs[i] = 0;
                for (int j = 0; j < (int) sizeof(argv[i+1]); j++){
                    switch (argv[i+1][j]) {
                        case 'n':
                            param.col_nahs[0] = 1;
                            break;
                        case 'a':
                            param.col_nahs[1] = 1;
                            break;
                        case 'h':
                            param.col_nahs[2] = 1;
                            break;
                        case 's':
                            param.col_nahs[3] = 1;
                            break;
                    }
                }
            }
            else if  (strcmp(argv[i], "-s") == 0)
            {
                strcpy(param.affi, argv[i+1]);
                param.filtre = TRUE;
            }
            else
            {
                fprintf( stderr, "%s : Argument non reconnu\n", argv[i]);
                exit(1);
            }
            i += 2;
        }
    
    
    read_csv(param);
    
    //printf("n: %d, a: %d, h: %d, s: %d\n", col_nahs[0], col_nahs[1], col_nahs[2], col_nahs[3]);
    
    return 0;
}
