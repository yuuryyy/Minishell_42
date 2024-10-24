/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:24:44 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/24 11:17:44 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
# define FATAL_ERROR 130
# define PATH_MAX 100

# define PIPEMSG "pipe() has failed\x1B[0m"
# define OPENMSG "open() has failed\x1B[0m"
# define DUPMSG "dup() has failed\x1B[0m"
# define DUP2SG "dup2() has failed\x1B[0m"
# define FORKMSG "fork() has failed\x1B[0m"
# define INTROUVABLE_FILE "No such file or directory: \x1B[0m"
# define NOTFOUNDMSG "command not found: \x1B[0m"
# define WAITMSG	"wait() has failed .\x1B[0m"
# define WAITPIDMSG "waitpid() has failed .\x1B[0m"
# define SYNTAX "syntax error"
# define PERMISSION "permission denied : \x1B[0m"

# define NO_EXW 11
# define EXPND_W 12
# define WRITE_FD 13

# define INPUT 0
# define OUTPUT 1

# define APND 7
# define REDOUT 8

# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"

#endif