/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:07:17 by alilin            #+#    #+#             */
/*   Updated: 2021/06/17 15:39:52 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	signe;

	n = 0;
	i = 0;
	signe = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * signe);
}

void	send_char(int pid, int c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(100);
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		i++;
	}
	return ;
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, message[i]);
	return ;
}

void	retrieve(int sig, siginfo_t *info, void *prout)
{
	(void)prout;
	(void)sig;
	printf("server %d: recieved your message\n", info->si_pid);
}

int	main(int ac, char **av)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = retrieve;
	sigaction(SIGUSR1, &sig, 0);
	if (ac != 3)
		printf("Usage: ./client {server pid} {string that you want to send}");
	else
		send_message(ft_atoi(av[1]), av[2]);
	pause();
	return (0);
}
