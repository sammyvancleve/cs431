#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "sim_util.h"

int main(int argc, char *argv[]) {
    int num_devices = atoi(argv[1]);
    int num_sent = 0;
    int time = 0;
    int delay[num_devices];
    int backoff[num_devices];
    //start with all colliding
    //and backoff between 0 and 1
    for (int i = 0; i < num_devices; i++) {
        delay[i] = 0;
        backoff[i] = 1;
    }
    //loop until all sent
    while (num_sent < num_devices) {
        int sender;
        int collisions;
        do { 
            collisions = -1;
            for (int i = num_sent; i < num_devices; i++) {
                delay[i] = delay[i] - 1;
                if (delay[i] == -1) {
                    collisions++;
                    sender = i;
                    backoff[i] = backoff[i] + 1;
                    delay[i] = random_modulo(2 << backoff[i]);
                }
            }
            time++;
        } while (collisions > 0);
        if (collisions == 0) {
            delay[sender] = delay[num_sent];
            num_sent++;
        }
    }
    printf("%d\n", time);
}
