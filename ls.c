#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void add_entry(char*** array, int* count, int* size, const char* name) {
    // Resize array if needed
    if (*count >= *size) {
        *size *= 2;
        *array = realloc(*array, *size * sizeof(char*));
        if (!*array) {
            perror("Error resizing array");
            exit(EXIT_FAILURE);
        }
    }
    (*array)[*count] = strdup(name);
    (*count)++;
}

void print_and_free_entries(char** array, int count, const char* color) {
    for (int i = 0; i < count; i++) {
        printf("%s%s" RESET "\n", color, array[i]);
        free(array[i]);
    }
}

void ls() {
    DIR* current_dir = opendir("./");
    if (!current_dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    int folder_size = 100, file_size = 100;
    int folder_count = 0, file_count = 0;
    char** folders = malloc(folder_size * sizeof(char*));
    char** files = malloc(file_size * sizeof(char*));

    while ((entry = readdir(current_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.') {
            continue; 
        }

        if (entry->d_type == DT_DIR) {
            add_entry(&folders, &folder_count, &folder_size, entry->d_name);
        } else if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {
            add_entry(&files, &file_count, &file_size, entry->d_name);
        }
    }

    closedir(current_dir);

    print_and_free_entries(folders, folder_count, BLUE);
    print_and_free_entries(files, file_count, WHITE);

    free(folders);
    free(files);
}

// Implementation of $ ls -a which will list hidden files too
void ls_a() {
    DIR* current_dir = opendir("./");
    if (!current_dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    int folder_size = 100, file_size = 100, hidden_file_size = 100;
    int folder_count = 0, file_count = 0, hidden_file_count = 0;
    char** folders = malloc(folder_size * sizeof(char*));
    char** files = malloc(file_size * sizeof(char*));
    char** hidden_files = malloc(hidden_file_size * sizeof(char*));

    while ((entry = readdir(current_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_name[0] == '.') {
            add_entry(&hidden_files, &hidden_file_count, &hidden_file_size, entry->d_name);
        } else {
            if (entry->d_type == DT_DIR) {
                add_entry(&folders, &folder_count, &folder_size, entry->d_name);
            } else if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {
                add_entry(&files, &file_count, &file_size, entry->d_name);
            }
        }
    }

    closedir(current_dir);

    print_and_free_entries(folders, folder_count, BLUE);
    print_and_free_entries(hidden_files, hidden_file_count, RED);
    print_and_free_entries(files, file_count, WHITE);

    free(folders);
    free(files);
    free(hidden_files);
}
