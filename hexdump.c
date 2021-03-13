#include "util.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define STDIN_BUF 128
#define FILE_BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        char buf[STDIN_BUF];
        int nextchar;
        int length = 0;
        while ((nextchar = fgetc(stdin)) != EOF) {
            buf[length] = nextchar;
            length++;
        }
        binary_to_hex(buf, strlen(buf));
    } else {
        FILE *binfile;
        int file_length = 0;
        char buf[FILE_BUF_SIZE];
        int nextchar;
        binfile = fopen(argv[1], "r");
        if (binfile) {
            while ((nextchar = fgetc(binfile)) != EOF) {
                buf[file_length] = nextchar;
                file_length++;
            }
            binary_to_hex(buf, file_length);
        } else {
            printf("%s doesn\'t exist\n", argv[1]);
        }
    }
}
