#include "shell.h"

void	catch_sigs(void)
{
  signal(SIGINT, &ctrlc);
  signal(SIGTSTP, &ctrlz);
  signal(SIGQUIT, &ctrlquit);
}

void	ctrlquit(int sig)
{
  my_putchar('\n');
  display_prompt();
  (void)sig;
}

void	ctrlc(int sig)
{
  my_putchar('\n');
  display_prompt();
  (void)sig;
}

void	ctrlz(int sig)
{
  my_putchar('\n');
  display_prompt();
  (void)sig;
}
