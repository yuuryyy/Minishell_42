/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:24:44 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/21 19:03:38 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
# define FATAL_ERROR 130

# define PIPEMSG "pipe() has failed"
# define OPENMSG "open() has failed"
# define DUPMSG "dup() has failed"
# define DUP2SG "dup2() has failed"
# define FORKMSG "fork() has failed"
# define INTROUVABLE_FILE "No such file or directory: "
# define NOTFOUNDMSG "command not found: "
# define WAITMSG	"wait() has failed ."
# define WAITPIDMSG "waitpid() has failed ."
# define SYNTAX "syntax error"
# define PERMISSION "permission denied : "

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