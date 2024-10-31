#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void ls() {
    DIR* current_dir = opendir("./");
    if (current_dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    char* folders[100];
    char* files[100];
    int folder_count = 0;
    int file_count = 0;

    while ((entry = readdir(current_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_name[0] == '.') {
            continue; 
        }

        if (entry->d_type == DT_DIR) {
            folders[folder_count] = strdup(entry->d_name);
            folder_count++;
        } else if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {
            files[file_count] = strdup(entry->d_name);
            file_count++;
        }
    }

    for (int i = 0; i < folder_count; i++) {
        printf("%s%s" RESET "\n", BLUE, folders[i]);
        free(folders[i]);
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s%s" RESET "\n", WHITE, files[i]);
        free(files[i]);
    }

    closedir(current_dir);
}

// Implementation of $ ls -a which will list hidden files too
void ls_a() {
    DIR* current_dir = opendir("./");
    if (current_dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    char* folders[100];
    char* files[100];
    char* hidden_files[100];
    int folder_count = 0;
    int file_count = 0;
    int hidden_file_count = 0;

    while ((entry = readdir(current_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_name[0] == '.') {
            hidden_files[hidden_file_count] = strdup(entry->d_name);
            hidden_file_count++;
        } else {
            if (entry->d_type == DT_DIR) {
                folders[folder_count] = strdup(entry->d_name);
                folder_count++;
            } else if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {
                files[file_count] = strdup(entry->d_name); 
                file_count++;
            }
        }
    }

    for (int i = 0; i < folder_count; i++) {
        printf("%s%s" RESET "\n", BLUE, folders[i]);
        free(folders[i]);
    }

    for (int i = 0; i < hidden_file_count; i++) {
        printf("%s%s" RESET "\n", RED, hidden_files[i]);
        free(hidden_files[i]);
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s%s" RESET "\n", WHITE, files[i]);
        free(files[i]);
    }

    closedir(current_dir);
}
