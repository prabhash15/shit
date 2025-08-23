#include <dirent.h>
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
void status(char path[]){

    struct dirent *entry;
    DIR *dir = opendir(path);



    if (dir == NULL) {
        perror("error while opening directory");
        return;
    }


    while ((entry = readdir(dir)) != NULL){

        if (strcmp(".", entry->d_name) && strcmp("..", entry->d_name)){

            char filepath[2000];

            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

            if(check_if_dir(filepath)){ 
                printf("%s" , filepath); 
                status(filepath);
            } else {
                // it's a file → print
                printf("%s\n", filepath);
            }
        }    
    }
    closedir(dir);
    return;
}




 
