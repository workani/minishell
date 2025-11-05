/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:07:32 by workani           #+#    #+#             */
/*   Updated: 2025/11/05 16:28:42 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"
# include <stdbool.h>

/* Alias to keep legacy name while using g_ naming */
# define BUILTINS g_builtins

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
