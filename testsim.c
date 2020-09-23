#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
 {
        int sleep_time;
        int repeat_factor;
        int counter;

        if (argc != 3)
        {
                fprintf(stderr, "Usage: %s repeat_factor sleep_time NULL\n", argv[0]);
                return 1;
        }

        repeat_factor = atoi(argv[1]);
        sleep_time = atoi(argv[2]);

        for (counter = 0; counter < repeat_factor; counter++)
        {
                sleep(sleep_time);
                fprintf(stderr, "pid: %d _ repeat factor: %d _ sleep time: %d\n", getpid(), repeat_factor, sleep_time);
        }

        return 0;
}
