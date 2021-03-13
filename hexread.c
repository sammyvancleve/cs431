#include "util.h"
#include <unistd.h>
#include <stdio.h>

#define STDIN_BUF 64
#define FGETS_BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        char buf[STDIN_BUF];
        while ((fgets(buf, STDIN_BUF, stdin) != NULL)) {
            char *binstring = hex_to_binary(buf);
            if (binstring != NULL) {
                printf("%s", binstring);
            }
        }
    } else {
        FILE *hexfile;
        hexfile = fopen(argv[1], "r");
        if (hexfile) {
            char buf[FGETS_BUF_SIZE];
            while (fgets(buf, FGETS_BUF_SIZE, hexfile)) {
                char *binstring = hex_to_binary(buf);
                if (binstring != NULL) {
                    printf("%s", binstring);
                }
            }
        } else {
            printf("%s doesn\'t exist\n", argv[1]);
        }
    }
}
