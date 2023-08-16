/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:04:48 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/13 16:04:48 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

BOOLEAN	check_equal(char *str)
{
	BOOLEAN	ans;
	size_t	i;

	ans = FALSE;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			ans = TRUE;
		i++;
	}
	return (ans);
}

BOOLEAN	check_duplicate_path(char *str, t_env *env_head)
{
	size_t	count;
	t_env	*tmp;

	count = 0;
	tmp = env_head->next;
	while (str[count] != '=' && str[count] != '\0')
		count++;
	while (tmp != env_head)
	{
		if (!ft_strncmp(str, tmp->var, count) && tmp->var[count] == '=')
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	ft_export(char **list, t_env *env_head)
{
	int	i;

	if (list[1] == NULL)
		ft_put_few_arg_err("export");
	else
	{
		i = 1;
		while (list[i])
		{
			if (check_equal(list[i]))
			{
				if (check_duplicate_path(list[i], env_head))
					node_delete(get_node_pos(env_head, list[i]));
				node_add_back(env_head, node_new(list[i]));
			}
			else
				ft_puterr("export: error\n");
			i++;
		}
	}
}