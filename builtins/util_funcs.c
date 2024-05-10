/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:26:15 by mkorpela          #+#    #+#             */
/*   Updated: 2024/05/09 14:18:05 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniwell.h"

void	builtin_commands(t_shell *shell, char **command)
{
	if (shell->builtin == CD)
		shell->status = cd_command(shell, command);
	else if (shell->builtin == MY_ECHO)
		shell->status = echo_command(command);
	else if (shell->builtin == ENV)
		shell->status = env_command(shell, command);
	else if (shell->builtin == EXIT)
		exit_command(shell, command);//IS IT OK that EXIT already exited? (NOTE: there is no return value for this function.)
	else if (shell->builtin == EXPORT)
		shell->status = export_command(shell, command);
	else if (shell->builtin == PWD)
		shell->status = pwd_command(shell);
	else if (shell->builtin == UNSET)
		shell->status = unset_command(shell, command);
}
