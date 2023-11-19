#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler(int signo)
{
    // Ignorer le signal SIGINT dans le processus parent
    printf("Signal SIGINT reçu dans le processus parent, en attente de la fin de l'enfant...\n");
}

int main(int argc, char **argv, char **env)
{
    pid_t pid;
    while (1)
    {
        // Installation du gestionnaire de signal pour SIGINT dans le processus parent
        signal(SIGINT, sigint_handler);

        // Fork
        pid = fork();

        if (pid == -1)
        {
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Code du processus enfant

            // Exécution de la commande top avec execve
            char *args[] = {"/usr/bin/top", NULL};
            if (execve("/usr/bin/top", args, env) == -1)
            {
                perror("Erreur lors de l'execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Code du processus parent

            // Attente de la fin du processus enfant
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                printf("Le processus enfant s'est terminé avec le code de sortie %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("Le processus enfant s'est terminé à la suite d'un signal\n");
            }
            else
            {
                printf("Le processus enfant ne s'est pas terminé normalement\n");
            }
        }
    }
    return 0;
}
