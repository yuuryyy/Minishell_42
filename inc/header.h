/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:24:44 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/27 20:30:19 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"


# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
# define FATAL_ERROR 130

# define NOT_BUITIN -1
# define BUILTIN_ERR 1
# define BUILTIN_SUC 0

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
# define TOOMANYARG "too many arguments\x1B[0m"
# define PERMISSION "permission denied : \x1B[0m" 
# define NUMERICARG ": numeric argument required \x1B[0m"
# define NOTVALID ": not a valid identifier\x1B[0m"
# define OLDNOTSET "OLDPWD not set\x1B[0m"
# define HOMNOTSET "HOME not set\x1B[0m"
# define HOMNOTSET "HOME not set\x1B[0m"


# define NO_EXW 11
# define EXPND_W 12
# define WRITE_FD 13

# define INPUT 0
# define OUTPUT 1

# define APND 7
# define REDOUT 8

# define SINGLE 1
# define MULTI 2

# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"



#endif