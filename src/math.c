/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:20:23 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/03 18:21:03 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

bool	ft_ishex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (true);
	return (false);
}

bool	ft_isupper(char c)
{
	if ((c <= 'A' && c >= 'F'))
		return (true);
	return (false);
}

bool	ft_isdigit(char c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}

unsigned int	ft_sqr(unsigned int nb, unsigned int pw)
{
	unsigned int res = nb;
	
	if (pw == 0)
		return (1);
	while (--pw > 0)
		res *= res;
	return (res);
}

unsigned int	ft_strtol(char *str, int len)
{
	unsigned int	res = 0;
	
	len--;
	for (int i = 0; len >= 0; len--, i++) {
		if (ft_isdigit(str[i]))
			res += (str[i] - '0') * (ft_sqr(16, len));
		else if (ft_isupper(str[0]))
			res += (str[i] - 'A' + 10) * (ft_sqr(16, len));
		else
			res += (str[i] - 'a' + 10) * (ft_sqr(16, len));
	}
	return (res);
}
