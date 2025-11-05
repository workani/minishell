/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:42:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 16:57:42 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard library includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>

// Project includes
# include "modules/defines.h"
# include "modules/types.h"
# include "modules/parser.h"
# include "modules/signals.h"
# include "modules/executor.h"
# include "modules/env.h"
# include "modules/builtins.h"
# include "../libft/libft.h"

// Global variable for signals
extern volatile sig_atomic_t	g_signal_received;

// General utilities
char	*set_cmd(char *cmd, char **envp);
bool	has_slash(char *str);
char	*get_cmd(char *cmd, char **paths);
void	free_string_array(char **arr);
void	sort_env_list(t_env_lst *env);

#endif