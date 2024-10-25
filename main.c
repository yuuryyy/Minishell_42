/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/25 12:17:11 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	s()
{
	// system("lsof -c minishell");
	system("leaks minishell");
}

int g_errno = 0;

int main(int ac, char **av, char **env)
{
    t_args  cmd_line;

    atexit(s);
    (void)ac;
    (void)av;
    ft_bzero(&cmd_line, sizeof(t_args));
    environment(env, &cmd_line);
    setup_signal_handlers();
    cmd_line.fdin = dup(STDIN_FILENO);
    cmd_line.fdout = dup(STDOUT_FILENO);

    while (1)
    {
        free_current_cmdline(&cmd_line);
        cmd_line.line = readline("\033[38;2;255;192;203m\033[1m->  MinionHell^~^ \033[34m>$ \033[0m");
        if (cmd_line.line == NULL)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            free_struct(&cmd_line);
            exit(0);
        }
        if (*cmd_line.line)
            add_history(cmd_line.line);

        if (process_line(&cmd_line) != 0)
            continue;

        if (cmd_line.table == NULL)
            continue;

        if (execute_cmds(&cmd_line))
            continue;

        while (wait(0) != -1)
            continue;

        if (dup2(cmd_line.fdin, STDIN_FILENO) == -1)
            return (put_error(&cmd_line, "dup2 error on fdin", NULL), free_struct(&cmd_line), 1);

        if (dup2(cmd_line.fdout, STDOUT_FILENO) == -1)
            return (put_error(&cmd_line, "dup2 error on fdout", NULL), free_struct(&cmd_line), 1);
    }
    return 0;
}

        // t_cmd_tab *tab = cmd_line.table;

        // while (tab)
        // {
        //     if (tab->cmd)
        //     {
        //         // Affichage des commandes pour le débogage
        //         for (int i = 0; tab->cmd[i]; i++)
        //             printf("cmd[%d]====%s\n", i, tab->cmd[i]);
        //     }
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