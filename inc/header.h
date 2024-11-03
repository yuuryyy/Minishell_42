/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:24:44 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 20:35:49 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_ESDIR	126
# define BINARY_ERROR 127
# define FATAL_ERROR 130
# define EXIT_OUTOFRANGE 255
# define SYNTAX_ERROR 258

# define NOT_BUITIN -1
# define BUILTIN_ERR 1
# define BUILTIN_SUC 0

//errors
# define INTROUVABLE_FILE	"\x1B[0m: no such file or directory"
# define NUMERICARG			": numeric argument required \x1B[0m"
# define NOTVALID			": not a valid identifier\x1B[0m"
# define WAITPIDMSG			"waitpid() has failed .\x1B[0m"
# define NOTFOUNDMSG		": \x1B[0mcommand not found"
# define PERMISSION			": \x1B[0mpermission denied"
# define WAITMSG			"wait() has failed .\x1B[0m"
# define TOOMANYARG 		"too many arguments\x1B[0m"
# define OPENMSG 			"open() has failed\x1B[0m"
# define PIPEMSG 			"pipe() has failed\x1B[0m"
# define FORKMSG 			"fork() has failed\x1B[0m"
# define DUP2SG 			"dup2() has failed\x1B[0m"
# define OLDNOTSET 			"OLDPWD not set\x1B[0m"
# define DUPMSG 			"dup() has failed\x1B[0m"
# define ISDIR 				"\x1B[0m: is a directory"
# define HOMNOTSET 			"HOME not set\x1B[0m"
# define SYNTAX 			"syntax error"

//heredoc fd writing and expanding
# define NO_EXW 11
# define EXPND_W 12
# define WRITE_FD 13

//to check files
# define INPUT 0
# define OUTPUT 1

//to tell wich redirection is the the last to be opened
# define APND 7
# define REDOUT 8

//to define the behavior of builtins
# define SINGLE 1
# define MULTI 2

//exit code edit flags
# define EDIT 0
# define RETRIEVE 1
//colors
# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"
# define ANSI_FONT_COL_RESET     "\x1b[0m"
# define MAGINTA   "\e[38;2;255;192;203m"
# define CYAN "\e[38;2;160;190;200m" 

# define PROMPT	  "->  MinionHell^~^ "
# define DEF_PATH "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

#endif