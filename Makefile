CFLAGS=-Wall -pedantic -g

all: bin_backoff hubsim

bin_backoff: bin_backoff.c sim_util.c
	gcc $(CFLAGS) -o bin_backoff bin_backoff.c sim_util.c

hubsim: hubsim.c sim_util.c
	gcc $(CFLAGS) -o hubsim hubsim.c sim_util.c

.PHONY: clean
clean:
	rm -f bin_backoff
	rm -f hubsim

.PHONY: cleardat
cleardat:
	rm -f nums

.PHONY: avg
avg:
	printf "\t" >> backoff.data
	python3 average.py >> backoff.data
