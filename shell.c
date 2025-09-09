#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <signal.h>
#include <setjmp.h>

static sigjmp_buf env;

void sigint_handler(int s);
char **get_input(char *i);
int cd(char *p);

static volatile sig_atomic_t jmp_actice = 0;

int main() {
    pid_t child_pid;
    char *input;
    char **command;
    int stat_loc;

    signal(SIGINT, sigint_handler);

    while (1) {
        if (sigsetjmp(env, 1) == 42)
            printf("Restart.\n");
        printf("next iteration...\n");
        sleep(2);

        input = readline("fer-shell > ");
        command = get_input(input);

        if (input == NULL) {
            printf("\n");
            exit(0);
        };

        if (strcmp(command[0], "exit") == 0) {
            free(input);
            free(command);

            return 0;
        };

        if (strcmp(command[0], "cd") == 0) {
            if (cd(command[1]) < 0)
                perror(command[1]);

            continue;
        }

        child_pid = fork();
        if (child_pid < 0) {
            perror("fork failed");
            exit(1);
        };
        if (child_pid == 0) {
            signal(SIGINT, SIG_DFL);

            if (execvp(command[0], command)) {
                perror(command[0]);
                exit(1);
            };
        } else
            waitpid(child_pid, &stat_loc, WUNTRACED);


        free(input);
        free(command);
    }

    return 0;
}

void sigint_handler(int signo) {
    if (!jmp_actice)
        return;

    siglongjmp(env, 42);
}

int cd(char *path) {
    return chdir(path);
}

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    };

    char *separator = " ";
    char *parsed = strtok(input, separator);
    int i = 0;

    while (parsed != NULL) {
        command[i] = parsed;
        i++;

        parsed = strtok(NULL, separator);
    };

    command[i] = NULL;
    return command;
}
