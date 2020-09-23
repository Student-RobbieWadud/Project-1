//This file will first read commands. Then, it will fork and exec those commands.

//Include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <getopt.h>

//This constant is the max number of characters.
const int MAX_CANON = 100;

//Function Declarations
char** get_exec_argv(char* str);
int* parsing_command_line(int argc, char *argv[]);
void print_usage();

int main (int argc, char *argv[])
{
        //This var holds the number of active children.
        int pr_count = 0;

        //This var holds the MAX number of children allowed to execute at a time.
        int* pr_limit;

        //This var holds the command line arguments.
        char cmd[MAX_CANON];

        //The child's process ID.
        pid_t childpid = 0;

        //This var will have argv pass to it.
        char** exec_argv;

        pr_limit = parsing_command_line(argc, argv);

        //While loop to do the actual process.
        while (fgets(cmd, MAX_CANON, stdin))
        {
                //If statement for when one child finishes and the pr_count will decrement.
                if (pr_count == *pr_limit)
                {
                        wait(NULL);
                        pr_count -= 1;
                }

                if ((childpid = fork()) == 0)
                {
                        //This line will remove any newlines.
                        strtok(cmd, "\n");

                        exec_argv = get_exec_argv(cmd);

                        execvp(exec_argv[0], exec_argv);

                        perror("Child failed to execute the command.");
                        return 1;
                }

                //If statement when the child process fails to fork.
                if (childpid == -1)
                {
                        perror("Child process failed to fork!\n");
                        return 1;
                }

                //Since there was a fork, there needs to be an increment.
                pr_count += 1;

                //If statement when a child process finishes executing.
                if (waitpid(-1, NULL, WNOHANG) > 0)
                {
                        pr_count -= 1;
                }
        }

        if (childpid > 0)
        {
                while (wait(NULL) > 0);
        }

        free(pr_limit);

        return 0;
}

char** get_exec_argv(char* str)
{
        char* substr;
        char** exec_argv = malloc(10 * sizeof(char));

        substr = strtok(str, " ");

        int counter  = 0;

        while (substr != NULL)
        {
                exec_argv[counter] = malloc(20 * sizeof(char));
                exec_argv[counter] = substr;
                substr = strtok(NULL, " ");
                counter++;
        }

        exec_argv[counter] = NULL;

        return exec_argv;
}

int* parsing_command_line(int argc, char *argv[])
{
        int* pr_limit = malloc(sizeof(int));

        if (argc < 2)
        {
                print_usage();
        }

        int option;

        while ((option = getopt (argc, argv, "n:h")) != -1)
        switch (option)
        {
                case 'h':
                        print_usage();
                case 'n':
                        *pr_limit = atoi(optarg);
                        break;
                default:
                        print_usage();
        }

        return pr_limit;

}

void print_usage()
{
        fprintf(stderr, "Usage: runsim -n max number of concurrent children\n");
        exit(2);
}