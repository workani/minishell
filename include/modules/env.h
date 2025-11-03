/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:10:10 by workani           #+#    #+#             */
/*   Updated: 2025/11/03 18:46:03 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:00:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 17:00:00 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"
# include <stdbool.h>

// Environment list management
int		get_env_lst_size(t_env_lst *head);
char	**env_lst_to_arr(t_env_lst *head);
void	print_env_lst(t_env_lst *head);
void	init_env_lst(t_env_lst **head, char **envp);
void	add_env_node(t_env_lst **head, char *key, char *value, bool has_no_eq);
void	add_or_update_env_var(t_env_lst **head, char *key, char *value, bool has_no_eq);
char	*get_env_value(const char *key, t_env_lst *head);
bool	convert_var_to_key_value_pair(char *dst[2], char *var);
void	delete_env_node(t_env_lst **head, char *key);

// Variable expansion
char	*expand_line(char *line, t_env_lst *env);
void	expand_variable(char **line, t_buffer *buf, t_env_lst *env);
void	expand_variables(t_cmd_node *cmd_node, t_env_lst *env);

void	free_env_lst(t_env_lst **head);

#endif
