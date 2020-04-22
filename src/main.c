#include "shell.h"

int	main(void)
{
  brek = 0;
  if (environ[0] == NULL)
    my_puterror("Env is empty, please re-run with a filled environment.\n");
  else
    init_shell();
  return (1);
}
