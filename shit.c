#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

#define shit_folder ".sh"

int check_if_initialized();
void uninitialize();
int initialize();
void empty_dir();
void status(char path[] , int depth);
int check_if_dir(char path[]);


const float version = 1.0;
char shit_initial[1024];

#include "status.c"

void empty_dir(){

    struct dirent *entry;
    DIR *dir = opendir(shit_folder);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while((entry = readdir(dir)) != NULL){

        if (strcmp(".", entry->d_name) && strcmp("..", entry->d_name)){
            char filepath[1024];

            snprintf(filepath, sizeof(filepath), "%s/%s" , shit_folder , entry->d_name );
            remove(filepath);

        }
    }
    closedir(dir);
}


int check_if_initialized(){

    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        char path[100];

        snprintf(path, sizeof(path), "%s", entry->d_name);

        if (stat(path, &st) == -1) {
            perror("stat");
        }

        if (S_ISDIR(st.st_mode)) {
            if (!strcmp(shit_folder, entry->d_name)) {
                closedir(dir);
                return 1;
            }
        }
    }
    closedir(dir);
    return 0;

}


void uninitialize(){

    if (check_if_initialized()) {
        empty_dir();
        rmdir(shit_folder);
        printf("Removed SHIT\n");
    }
    else{
        printf("Initialize First\n"); 
    }
}


int initialize(){

    int permisson_bits = 0777;

    if (!check_if_initialized()){
        char folder[1000];
        mkdir(shit_folder, permisson_bits);
        creat(strcat(strcat(folder , shit_folder), "/files.txt"), permisson_bits);
        printf("Initialized SHIT");
        return 1;
    }
    else{
        printf("Already Initialized\n");
        return 0;
    }
}


int main(int argc, char *argv[])
{
    getcwd(shit_initial, sizeof(shit_initial));

    if (argc > 1){
        for (int i = 1; i < argc;i++) {

            if (!strcmp("--version", argv[i])) printf("%.1f" , version);

            else if (!strcmp("init" , argv[i])){

                int initialize_success = initialize();
                if (!initialize_success) return 0;

            }
            else if (!strcmp("-shit" , argv[i])){
                uninitialize();
            }
            else if (!strcmp("status" , argv[i])){
                if (check_if_initialized()) status("." , 0);
                else{
                    printf("Not a shit repo\n");
                }
                
            }
            else{
                printf("Invalid\n");
            }
        }
    }
}
