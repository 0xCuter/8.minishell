/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:38:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 10:52:55 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints the error and exits with `errno` code
void	error(const char *error)
{
	perror(error);
	exit(errno);
}

//Frees the commands list
void	clear_cmd_list(void *cmd_void)
{
	t_command	*cmd;
	char		**cmd_split;

	cmd = (t_command *)cmd_void;
	cmd_split = cmd->cmd_split;
	--cmd_split;
	while (*++cmd_split)
		free(*cmd_split);
	free(cmd->cmd_split);
	free(cmd);
}
