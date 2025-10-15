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

void close_pipes_and_wait(int pipes[][2], int cmd_count)
{
    int i;

    i = 0;
    close_unused_pipes(pipes, cmd_count - 1, DISCARD, DISCARD);
    while (i < cmd_count)
    {
        wait(NULL);
        i++;
    }
}

void setup_pipes(int pipes[][2], int pipe_count, int idx)
{
  if (idx == 0)
		{
			dup2(pipes[0][1], STDOUT_FILENO);
			close_unused_pipes(pipes, pipe_count, pipes[0][1], DISCARD);
		}
		else if (idx == pipe_count)
		{
			dup2(pipes[idx - 1][0], STDIN_FILENO);
			close_unused_pipes(pipes, pipe_count, pipes[idx - 1][0], DISCARD);
		}
		else
		{
			dup2(pipes[idx - 1][0], STDIN_FILENO);
			dup2(pipes[idx][1], STDOUT_FILENO);
			close_unused_pipes(pipes, pipe_count, pipes[idx - 1][0], pipes[idx][1]);
		}
}