/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:19:53 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/03 17:47:13 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

void	*ft_memset(void *ptr, int nb, size_t len)
{
	size_t	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)ptr)[i] = nb;
		i++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dest, void *src, size_t len)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	newsignal(int signum)
{
	(void)signum;
}

bool	handle_signal(void)
{
	if (signal(SIGINT, newsignal) == SIG_ERR) {
		fprintf(stderr, "Error handle signal : %s\n", strerror(errno));
		return (true);
	}
	return (false);
}
