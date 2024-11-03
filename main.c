/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 17:02:13 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	s()
{
	// system("lsof -c minishell");
	system("leaks minishell");
}


int exit_code(int code, int flag)
{
    static int exit_code;

    if (flag == EDIT)
        exit_code = code;
    return exit_code;
}

int g_errno = 0;

int main(int ac, char **av, char **env)
{
    t_args  cmd_line;

    // atexit(s);
    (void)ac;
    (void)av;
    ft_bzero(&cmd_line, sizeof(t_args));
    environment(env, &cmd_line);//I retrieved the env
    cmd_line.fdin = dup(STDIN_FILENO);
    cmd_line.fdout = dup(STDOUT_FILENO);
	exit_code(0, EDIT);
    while (1)
    {
        rl_catch_signals = 0;
        setup_signal_handlers();
        free_current_cmdline(&cmd_line);
        cmd_line.line = readline(MAGINTA "->  MinionHell^~^ " CYAN ">$ " ANSI_FONT_COL_RESET);
        if (cmd_line.line == NULL)
        {
			while (wait(NULL) != -1)
				continue ;
			write(STDOUT_FILENO, "exit", 5);
    		free_struct(&cmd_line);
            exit(0);
        }
        if (*cmd_line.line)
            add_history(cmd_line.line);
        if (process_line(&cmd_line) != 0)
            continue;
        execute_cmds(&cmd_line);
        while (wait(0) != -1)
            continue;
        if (dup2(cmd_line.fdin, STDIN_FILENO) == -1)
            return (put_error("dup2 error on fdin", NULL), free_struct(&cmd_line), 1);

        if (dup2(cmd_line.fdout, STDOUT_FILENO) == -1)
            return (put_error("dup2 error on fdout", NULL), free_struct(&cmd_line), 1);
    }
    return 0;
}

        //     printf("arg====%s\n", tab->arg);
        //     printf("append====%s\n", tab->append);
        //     while (tab->delimiter)
        //     {
        //         printf("limi====%s\n", tab->delimiter->content);
        //         tab->delimiter = tab->delimiter->next;
        //     }
        //     printf("infile====%s\n", tab->in);
        //     printf("outfile====%s\n", tab->out);
        //     printf("herecod====%d\n\n", tab->heredoc);
        //     // Exécution des commandes
        //     if (tab->cmd)
        //     {
        //         if (exec_builtin(&cmd_line, tab) == 0)
        //         {
        //             single_cmd(tab); 
        //         }
        //     }
        //     tab = tab->next;
        // }