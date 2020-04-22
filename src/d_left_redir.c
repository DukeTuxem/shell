#include "shell.h"

char	*clean_buffer(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i] != '\0')
    {
      buffer[i] = '\0';
      i++;
    }
  return (buffer);
}

char	*return_line(char *str)
{
  char	*tmp;

  if ((tmp = malloc(sizeof(char) * strlen(str) + 3)) == NULL)
    return (NULL);
  strcpy(tmp, str);
  tmp[strlen(str)] = '\n';
  tmp[strlen(str) + 1] = '\0';
  return (tmp);
}

void	possible_error(char *to_find)
{

  my_puterror("\nWarning here-document delimited by end-of-file (wanted '");
  to_find[strlen(to_find) - 1] = '\0';
  my_puterror(to_find);
  my_puterror("')\n");
}

int	wait_to_find(char *to_find)
{
  char	*buffer;
  int	size;
  int	fd;

  fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if ((buffer = malloc(sizeof(char) * 1000)) == NULL)
    return (my_puterror("Malloc error\n"));
  my_putstr("> ");
  while ((size = read(0, buffer, 1000)) > 0)
    {
      buffer[size] = '\0';
      if (strcmp(buffer, to_find) == 0)
	{
	  free(buffer);
	  return (0);
	}
      write(fd, buffer, strlen(buffer));
      my_putstr("> ");
      clean_buffer(buffer);
    }
  possible_error(to_find);
  return (1);
}
