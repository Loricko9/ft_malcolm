/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:32:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/02 17:53:32 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

bool	convert_hostname(struct sockaddr_in *ip_addr, char *address)
{
	struct addrinfo	hint;
	struct addrinfo	*res;
	int				ret;

	ft_memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_RAW;
	ret = getaddrinfo(address, NULL, &hint, &res);
	if (ret != 0) {
		printf("ft_malcolm: unknown host or invalid IP address(%s)\n", address);
		return (true);
	}
	ft_memcpy(ip_addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return (false);
}

bool	check_ip(t_info *info, char *src_arg, char *dest_arg)
{
	ft_memset(&info->src_ip, 0, sizeof(info->src_ip));
	ft_memset(&info->dest_ip, 0, sizeof(info->dest_ip));
	info->src_ip.sin_family = AF_INET;
	info->dest_ip.sin_family = AF_INET;
	if (inet_pton(AF_INET, src_arg, &info->src_ip.sin_addr) <= 0)
		if (convert_hostname(&info->src_ip, src_arg))
			return (true);
	if (inet_pton(AF_INET, dest_arg, &info->dest_ip.sin_addr) <= 0)
		if (convert_hostname(&info->dest_ip, dest_arg))
			return (true);
	return (false);
}
