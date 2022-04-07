/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:14:15 by scuter            #+#    #+#             */
/*   Updated: 2022/04/07 11:35:14 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print the full filename of the current working directory.
void	pwd_cmd(t_data *data)
{
	char	*pwd;

	data->exit_status = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
}
