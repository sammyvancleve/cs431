#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 20

int random_modulo(int n) {
    int urandom = open("/dev/urandom", O_RDONLY);
    if (urandom >= 0) {
        char randomdata[BUF_SIZE];
        ssize_t result = read(urandom, randomdata, sizeof(randomdata));
        if (result < 0) {
            perror("sim_util random_modulo");
            return -1;
        } else {
            close(urandom);
            return abs((int) randomdata[0] % n);
        }
    } else {
        perror("sim_util random_modulo");
        return -1;
    }
}
