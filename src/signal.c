#include "../include/minishell.h"

void prompt_interrupt()
{
    write(1, "^C", 2);
    // write(1, str, ft_strlen(str));
    // free(str);
    rl_on_new_line();
}

int signal_set(int sig, void *f)
{
    struct sigaction sa;

    sa.sa_handler = f; // Specify SIG_IGN to ignore the signal
    sa.sa_flags = 0;

    if (sigaction(sig, &sa, NULL) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
