#include <dirent.h>
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

void status(char path[]){
    
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }
    

    while ((entry = readdir(dir)) != NULL){

        if (strcmp(".", entry->d_name) && strcmp("..", entry->d_name)){

            char filepath[1024];
            if(check_if_dir(entry->d_name)){ 
                snprintf(filepath, sizeof(filepath), "%s/%s" , path , entry->d_name );
                status(filepath);
            }
            else{
                snprintf(filepath, sizeof(filepath), "%s/%s" , path , entry->d_name );
                printf("%s\n" , filepath);
            }
        }

    }
    closedir(dir);
    return;
}




 
