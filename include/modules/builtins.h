/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:07:32 by workani           #+#    #+#             */
/*   Updated: 2025/10/31 20:49:38 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "types.h"
#include <stdbool.h>

// Variable expansion
char	*expand_line(char *line, t_env_lst *env);
void	expand_variables(t_cmd_node *cmd_node, t_env_lst *env);

// Builtin utilities
bool	is_builtin(char *cmd);
bool	is_valid_var_name(const char *var);

// Builtin commands
int		builtin_echo(char **args);
int		builtin_env(t_env_lst *env);
int		builtin_unset(char **args, t_env_lst **env);
int		builtin_export(char **args, t_env_lst **env);
int		builtin_exit(char **args, t_env_lst **env);
int		builtin_pwd(void);
int		builtin_cd(char **args, t_env_lst **env);

#endif