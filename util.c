#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexnib_to_char(int nib, char *s);

void binary_to_hex(char *s, int n) {
    size_t printlength = 0;
    char hexbyte[2];
    unsigned int hexnib1;
    unsigned int hexnib2;
    for (int i = 0; i < n; i++) {
        if (printlength < 16) {
            hexnib1 = (s[i] >> 4) & 0xf;
            hexnib2 = s[i] & 0xf;
            if (hexnib1 >= 0 && hexnib1 <= 9) {
                hexbyte[0] = hexnib1+48;
            } else if (hexnib1 >= 10 && hexnib1 <= 15) {
                hexbyte[0] = hexnib1+87;
            }
            if (hexnib2 >= 0 && hexnib2 <= 9) {
                hexbyte[1] = hexnib2+48;
            } else if (hexnib2 >= 10 && hexnib2 <= 15) {
                hexbyte[1] = hexnib2+87;
            }
            printf("%s ", hexbyte);
            printlength += 1;
        }
        if (printlength > 15 || i == n-1) {
            while (printlength < 16) {
                printf("%s", " ");
                printlength += 1;
            }
            printf("\n");
            printlength = 0;
        }
    }
}

char *hex_to_binary(char *s) {
    int whitespace = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ') {
            whitespace++;
        }
    }
    char *returnstring = malloc((strlen(s) - whitespace)/2);
    int i = 0;
    int string_position = 0;
    while (i < strlen(s)) {
        int binbyte = 0;
        if (s[i] == ' ' || s[i] == '\n') {
            i++;
            continue;
        } else if (s[i] == '\000') {
            break;
        }
        for (int j = 0; j < 2; j++) {
            int x = i + j; 
            if (s[x] >= '0' && s[x] <= '9') {
                binbyte += s[x]-48;
            } else if (s[x] >= 'A' && s[x] <= 'F') {
                binbyte += s[x]-55;
            } else if (s[x] >= 'a' && s[x] <= 'z') {
                binbyte += s[x]-87;
            } else {
                free(returnstring);
                return NULL;
            }
            if (j < 1) {
                binbyte = binbyte << 4;
            }
        }
        returnstring[string_position] = binbyte;
        string_position++;
        i += 2;
    }
    return returnstring;
}
