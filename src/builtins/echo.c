/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:07 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 13:50:07 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static bool check_n_flag(char **args)
{
    int i; 
    if (!args || args[0] != '-')
        return (false); 
    if (args[1] != 'n')
        return (false); 

    i = 1; 
    while(args[i])
    {
        if (args[1] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int builtin_echo(char **args, char **envpp)
{
    int i; 
    bool print_newline;

    i = 1; 
    print_newline = true;
    while (args[i] && check_n_flag(args[i]))
    {
        print_newline = false; 
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]); 
        if (args[i + 1])
            printf(" "); 
        i++;
    }
    if (print_newline)
        printf("\n");
    return (SUCCESS);
}
