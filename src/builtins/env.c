/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:14 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 13:50:14 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_env_lst **env)
{
    int i;
    char **envp; 

    if (!env)
        return (SUCCESS); 
    envp = env_lst_to_arr(*env);
    i = 0; 
    while (envp[i])
    {
        printf("%s\n", envp[i]); 
        i++;
    }
    return (SUCCESS); 
}
