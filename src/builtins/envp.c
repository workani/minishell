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

int builtin_envp(char **envp)
{
    int i; 

    if (!envp)
        return (SUCCESS); 
    i = 0; 
    while (envp[i])
    {
        printf("%s\n", envp[i]); 
        i++;
    }
    return (SUCCESS); 
}
