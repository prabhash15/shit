#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// to check if the current path is of a directory or not
int check_if_dir(char path[]){

    struct stat st;

    if (stat(path, &st) == -1) {
        return 0;
    }

    if (S_ISDIR(st.st_mode)) {

        return 1;

    }
    return 0;

}

// printout all the directories and files of a given path
void status(char path[], int depth) {

    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("error while opening directory");
        return;
    }

    static char sh_[100] = "";
    static int initialized = 0;  // flag

    if (!initialized) {
        if (getcwd(sh_, sizeof(sh_)) != NULL) {
            strcat(sh_ , "/");
            strcat(sh_ , shit_folder);
            strcat(sh_ , "/");
            strcat(sh_ , "files.txt");
            printf("Initialized cwd: %s\n", sh_);
        } else {
            perror("getcwd error\n");
            return;
        }
        initialized = 1;  // ensure this runs only once
    };

    
   FILE *fp = fopen(sh_,"a");

    if (fp == NULL){
        printf("Error in opening files.txt");
        return;
    }


    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(".", entry->d_name) && strcmp("..", entry->d_name)) {
            char filepath[2000];
            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

            if (check_if_dir(filepath)) {
                printf("%s\n", filepath);
                fprintf(fp,"%s\n" ,filepath);
                status(filepath, depth + 1);
            } else {
                fprintf(fp,"%s\n" ,filepath);
                printf("%s\n" , filepath);
            }
        }
    }

    fclose(fp);
    closedir(dir);
    return;
}



