#include "minishell.h"

void close_unused_pipes(int pipes[][2], int len, int exeception_one, int exeception_two)
{
  int i;

  i = 0;
  while (i < len)
  {
    if (pipes[i][0] != exeception_one && pipes[i][0] != exeception_two)
    {
      close(pipes[i][0]);
    }
    if (pipes[i][1] != exeception_one && pipes[i][1] != exeception_two)
    {
      close(pipes[i][1]);
    }
    i++;
  }
}
