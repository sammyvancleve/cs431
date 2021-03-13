#include <stdio.h>
#include <stdlib.h>

#include "sim_util.h"

int main(int argc, char *argv[]) {   
    int num_devices = atoi(argv[1]);
    int timeslots = atoi(argv[2]);

    int hub[num_devices];
    int hframes;
    int hframes_failure;

    int switches[num_devices];
    int sframes;
    int sframes_failure;

    //TODO uses same random numbers for hub and switch simulations
    //for efficiency's sake -- change for more randomness
    for (int time = 0; time < timeslots; time++) {
        for (int i = 0; i < num_devices; i++) {
            if (random_modulo(2) == 0) {
                hub[i] = random_modulo(num_devices);   
                hframes++;
                switches[i] = random_modulo(num_devices);
                sframes++;
            } else {
                hub[i] = -1;
                switches[i] = -1;
            }
        }

        //hubsim
        int hubcollide = 0;
        for (int i = 0; i < num_devices; i++) {
            if (hub[i] != -1) {
                hubcollide++;
            }
        }
        if (hubcollide > 1) {
            hframes_failure += hubcollide;
        }

        //old code -- faster and more efficient for finding success rate
        /*
        //check all or until collision
        int i = 0;
        while (hubcollide < 2 && i < num_devices) {
            if (hub[i] != -1) {
                hubcollide++;
            }
            i++;
        }
        if (hubcollide == 1) {
            hframes_success++;
        }
        */

        //switchsim
        //check all
        for (int source = 0; source < num_devices; source++) {
            int dest = switches[source];
            //if sending, and destination is not sending
            if (dest != -1 && switches[dest] == -1) {
                int collisions = 0;
                int j = 0;
                //check all or until collision
                while (collisions < 1 && j < num_devices) {
                    if (j != source && switches[j] == source || switches[j] == dest) {
                        collisions++;
                    }
                    j++;
                }
                if (collisions > 0) {
                    sframes_failure++;
                }
            } else if (dest == -1){
                continue;
            } else {
                sframes_failure++;
            }
        }
    }

    double hubrate = 1.0 - ((double) hframes_failure/(double)hframes);
    double switchrate = 1.0 - ((double) sframes_failure/(double)sframes);
    printf("%f hub\n%f switch\n", hubrate, switchrate);
}
