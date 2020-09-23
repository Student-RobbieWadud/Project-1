//This file will sleep for a certain amount of seconds and then print the process id for a certain amount of times.

//Include statements
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
 {
        int sleep_time;
        int repeat_factor;
        int counter;

        //If statement to check for a valid number of command-line arguments.
        if (argc != 3)
        {
                fprintf(stderr, "Usage: %s The Repeat Factor and Sleep Time are NULL\n", argv[0]);
                return 1;
        }

        repeat_factor = atoi(argv[1]);
        sleep_time = atoi(argv[2]);

        for (counter = 0; counter < repeat_factor; counter++)
        {
                sleep(sleep_time);
                fprintf(stderr, "Current pid: %d, Repeat factor: %d, Sleep Time: %d\n", getpid(), repeat_factor, sleep_time);
        }

        return 0;
}