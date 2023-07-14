/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exucution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:04:36 by ybourais          #+#    #+#             */
/*   Updated: 2023/07/14 16:21:14 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exucution(t_cmd cmd, t_env *environ, t_info *info)
{
    int i;
    char **env;
    char **paths;
    char *path;
    (void)info;

    env = from_list_to_tab(environ);
    path = find_path(env, 4, "PATH");
    paths = ft_split(path, ':');

    int pid = fork();

    if(pid == 0)
    { 
        if(cmd.full_cmd[0][0] == '/' || cmd.full_cmd[0][0] == '.')
            execve(cmd.full_cmd[0], cmd.full_cmd, env);
        else
        {
            if(cmd.full_cmd[0][0] == '\0')
            {
                write(2, "command not found\n", 18);
                exit(1);
            }
            else
            {
                i = 0;
                while (paths[i])
                {
                    char *cmd_slash = ft_strjoin(paths[i], "/");
                    char *cmd_ = ft_strjoin(cmd_slash, cmd.full_cmd[0]);
                    free(cmd_slash);
                    if(execve(cmd_, cmd.full_cmd, env) == -1)
                        free(cmd_);
                    i ++;
                }
                write(2, "my_Shell: :command not found\n", 29);
                exist_status = 127;
                exit(exist_status);
            }
        }
    }
    int h;
    waitpid(pid, &h, 0);
    exist_status = WEXITSTATUS(h);
    free_tab(env);
    free_tab(paths);
    free(path);
}

int exist_or_not(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if(str[i] == c)
            return i;
        i++;
    }
    return 0;
}


t_env *commands(t_cmd *cmd, t_env* env, t_info *info)
{
    int i = 0;
    while (i < nbr_cmd(info))
    {
        if (compare(cmd[i].full_cmd[0], "export"))
            env = ft_export(cmd[i], env, info);
        else if (compare(cmd[i].full_cmd[0], "env") && !cmd[i].full_cmd[1])
            print_env(env);
        else if (compare(cmd[i].full_cmd[0], "pwd"))
            pwd();
        else if (compare(cmd[i].full_cmd[0], "cd"))
            cd(cmd[i].full_cmd, env);
        else if (compare(cmd[i].full_cmd[0], "unset"))
            env = unset(cmd[i], env);
        else if (compare(cmd[i].full_cmd[0], "echo"))
            echo(cmd[i].full_cmd);
        else if (compare(cmd[i].full_cmd[0], "exit"))
            ft_exit(cmd[i].full_cmd);
        else
            exucution(cmd[i], env, info);
        i++;
    }
    return env;
}