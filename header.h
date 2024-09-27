/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:24:44 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/26 19:52:15 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
# define FATAL_ERROR 130

# define PIPEMSG "pipe() has failed\n"
# define OPENMSG "open() has failed\n"
# define DUPMSG "dup() has failed\n"
# define DUP2SG "dup2() has failed\n"
# define FORKMSG "fork() has failed\n"
# define INTROUVABLE_FILE "No such file or directory: "
# define NOTFOUNDMSG "command not found: "
# define WAITMSG	"wait() has failed .\n"
# define WAITPIDMSG "waitpid() has failed .\n"
# define SYNTAX "syntax error\n"
# define PERMISSION "permission denied : "
// # define
# define INPUT 0
# define OUTPUT 1

# define APND 7
# define REDOUT 8


#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RESET "\x1B[0m"


#endif