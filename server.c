/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:36:42 by alilin            #+#    #+#             */
/*   Updated: 2021/06/17 15:41:42 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	retrieve(int sig, siginfo_t *info, void *prout)
{
	static char	c = 0;
	static int	i = 0;

	(void)prout;
	if (sig == SIGUSR1)
		c += 1 << i;
	i++;
	if (i == 8)
	{
		if (c != '\0')
			write(1, &c, 1);
		else
		{
			write(1, "\n", 1);
			printf("from client %d\n", info->si_pid);
			usleep(100);
			kill(info->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0;
	}
	return ;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	printf("%d\n", pid);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = retrieve;
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
	{
	}
	return (0);
}
