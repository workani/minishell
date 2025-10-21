/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:33:40 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/21 12:33:41 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
    int status; 
    pid_t pid; 

    if(cmd_count > 1)
      close_unused_pipes(pipes, cmd_count - 1, DISCARD, DISCARD);

    setup_parent_exec_signlas(); 

    i = 0;
    while (i < cmd_count)
    {
        pid = wait(&status); 
        if(pid > 0)
        {
          if(WIFEXITED(status))
          {
            g_exit_status = WEXITSTATUS(status); 
          }
          else if (WIFSIGNALED(status))
          {
            int term_sig = WTERMSIG(status); 
            if (term_sig == SIGINT)
              write(STDOUT_FILENO, "\n", 1); 
            else if (term_sig = SIGQUIT)
              write(STDOUT_FILENO, "Quit(core dumped)\n", 19);
            g_exit_status = 128 + term_sig;
          }
        }
        i++;
    }
    setup_interactive_signals(); 
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