/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:42:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/16 20:01:19 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "defines.h"
#include "types.h"
#include "../libft/libft.h"

char *get_cmd(char *cmd, char **env);

int get_env_lst_size(t_env_lst *head);
char **env_lst_to_arr(t_env_lst *head);
void print_env_lst(t_env_lst *head);
void init_env_lst(t_env_lst **head, char **env);


#endif

