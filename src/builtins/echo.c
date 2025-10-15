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

static bool should_print_no_new_line(const char *arg)
{
    int i;

    if (!arg || arg[0] != '-')
        return false;
    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (false);
        i++;
    }
    return (true);
}



int builtin_echo(char **args, char **envpp)
{
    int i; 
    bool print_newline;

    i = 1; 
    print_newline = true;
    while (args[i] && should_print_no_new_line(args[i]))
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