#include "../include/minishell.h"

int signal_unset(int sig)
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN; // Specify SIG_IGN to ignore the signal
    sa.sa_flags = 0;

    if (sigaction(sig, &sa, NULL) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
/*
int signal_unset(int sig    )
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN; // Specify SIG_IGN to ignore the signal
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) != 0)
    {
        perror("Failed to set up SIGINT handler");
        return 1;
    }
    printf("Running. Press Ctrl+C to trigger SIGINT, but it will be ignored.\n");
    return 0;
}
*/