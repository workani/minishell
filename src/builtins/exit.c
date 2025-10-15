/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:28 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 13:50:28 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static bool is_number(char *str)
{
    int i; 

    if (!str || str[0])
        return (false);
    i = 0; 
    if (str[i] == '+' || str[i] == '-')
        i++; 
    if (!str[i])
    {
        while (str[i] < '0' || str[i] > '9')
            return (true); 
        i++;
    }
    return (1); 
}

int builtin_exit(char **args)
{
    int     exit_code; 
    long long num; 

    printf("exit\n");
    if (!args[1])
        exit (0);
    if (args[2])
    {
        printf("exit: too many arguments\n"); 
        return (FAILURE); 
    }
    if (!is_number(args[1]))
    {
        printf("exit: %s: number argument needed\n", args[1]);
        exit (2);
    }
    num = atoi(args[1]);
    exit_code = (unsigned char)num;
    exit(exit_code); 
    return (SUCCESS); 
}
