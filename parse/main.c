/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/30 04:08:05 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s()
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
    atexit(s);
    (void)argc;
    (void)argv;
    t_args args;
    t_cmd_tab cmd;
    char *input_line;
    
    args.env = NULL;
    environment(envp, &args);

    while (1)
    {
        // dekhla
        input_line = readline("minishell:)> ");
        if (!input_line)
            break;
        
        // ajouti cmd lreadline
        add_history(input_line);
        
        // Initialise lcmd bach tester
        cmd.cmd = ft_split(input_line, ' ');
        cmd.arg = cmd.cmd[1]; // arg optionnel
        
        // Exécution
        if (cmd.cmd[0])
            exec_builtin(&args, &cmd);
        free_array(cmd.cmd);
        free(input_line);
    }
    free_struct(&args);
    return 0;
}
