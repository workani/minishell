/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:10:40 by workani           #+#    #+#             */
/*   Updated: 2025/10/31 19:10:41 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define PATH_PREFIX "PATH="
# define PATH_MAX 4096
# define PATH_PREFIX_LEN 5

# define DISCARD -1

# define PROMPT_P1 "\001\033[48;5;23;38;5;252m\002 >>> "
# define PROMPT_P2 "\001\033[0m\033[38;5;201m\002 minishell$ \001\033[0m\002"
# define PROMPT PROMPT_P1 PROMPT_P2
# define SUCCESS 0
# define FAILURE 1

#endif
