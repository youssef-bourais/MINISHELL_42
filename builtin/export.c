/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:16:43 by ybourais          #+#    #+#             */
/*   Updated: 2023/07/21 22:47:54 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		write(1, tmp->key, ft_strlen(tmp->key));
		if (tmp->value != NULL)
		{
			write(1, "=\"", 2);
			write(1, tmp->value, strlen(tmp->value));
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}

void	print_export_error(char *str)
{
	write(2, "my Shell: export: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	g_exit_status = 1;
}

t_env	*every_thing_all_at_once(t_env *env, char *str, int *equal)
{
	if (exist_or_not(str, '='))
		*equal = 1;
	env = search_list(env, str);
	if (!find_value_in_list(env, str))
		env = add_to_env(env, set_variables(str), set_value(str), *equal);
	g_exit_status = 0;
	return (env);
}

t_env	*ft_export(t_cmd cmd, t_env *env)
{
	int	equal;
	int	i;

	i = 0;
	equal = 0;
	handle_redirection(cmd);
	if (cmd.full_cmd[0] && !cmd.full_cmd[1])
		print_export(env);
	else
	{
		i = 1;
		while (i < cmd.nbr_arg)
		{
			if (is_valid(cmd.full_cmd[i]))
				env = every_thing_all_at_once(env, cmd.full_cmd[i], &equal);
			else
				print_export_error(cmd.full_cmd[i]);
			equal = 0;
			i++;
		}
	}
	dup2(cmd.old_out, 1);
	close(cmd.old_out);
	return (env);
}
