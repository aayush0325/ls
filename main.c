#include <stdio.h>
#include <string.h>
#include "ls.h"

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "-a") == 0) {
        ls_a();
    } else {
        ls();
    }

    return 0;
}
