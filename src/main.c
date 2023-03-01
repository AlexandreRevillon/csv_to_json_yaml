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


void read_csv(char exit_format, char name_file, bool save, char col_nahs, char affi){
    FILE* file = fopen("csrankings.csv", "r");
    char name[50];
    char affiliation[50]; 
    char homepage[250];
    char scholarid[50];
    char line[500];
    char *token;
    
     while(fscanf(file, "%s\n", line) != EOF){
        token = strtok(line, ",");
        strcpy(name, token);
        token = strtok(line, ",");
        strcpy(affiliation, token);
        token = strtok(line, ",");
        strcpy(homepage, token);
        token = strtok(line, ",");
        strcpy(scholarid, token);
        printf("%s,%s,%s,%s\n", name, affiliation,homepage, scholarid);
    }
    
    fclose(file);
}



int main (int argc, char* argv[])
{
    int i = 1;
    char exit_format[4] = "yaml";
    char name_file[50];
    bool save = 0;
    char col_nahs[4];
    char affi[50];

    //Parcours des argument du main
        while(i < argc-1)  /* Skip argv[0] (program name). */
        {
            if (strcmp(argv[i], "-t") == 0)  /* Process optional arguments. */
            {
                strcpy(exit_format, argv[i+1]);
            }
            else if  (strcmp(argv[i], "-o") == 0)
            {
                save = 1;
                strcpy(col_nahs, argv[i+1]);
            }
            else if  (strcmp(argv[i], "-f") == 0)
            {
                strcpy(col_nahs, argv[i+1]);
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
    
    
    read_csv(*exit_format, *name_file, save, *col_nahs, *affi);
    
    
    
    
    
    
    return 0;
}
