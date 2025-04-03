/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:32:46 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/03 18:07:50 by lle-saul         ###   ########.fr       */
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

bool	print_errmac(char *arg)
{
	fprintf(stderr, "ft_malcolm: invalid mac address: (%s)\n", arg);
	return (true);
}

bool	check_mac(t_info *info, char *src_arg, char *dest_arg)
{
	if (ft_strlen(src_arg) != 17)
		return (print_errmac(src_arg));
	if (ft_strlen(dest_arg) != 17)
		return (print_errmac(dest_arg));
	for (int i = 0; i < 6; i++) {
		if (!ft_ishex(src_arg[i * 3]) || !ft_ishex(src_arg[i * 3 + 1])
			|| (src_arg[i * 3 + 2] != ':' && i < 5))
		{
			printf("i : %d\n", i);
			return (print_errmac(src_arg));
		}
		info->src_mac[i] = (unsigned char)ft_strtol(src_arg + (i * 3), 2);
	}
	for (int i = 0; i < 6; i++) {
		if (!ft_ishex(dest_arg[i * 3]) || !ft_ishex(dest_arg[i * 3 + 1])
			|| (dest_arg[i * 3 + 2] != ':' && i < 5))
			return (print_errmac(dest_arg));
		info->dest_mac[i] = (unsigned char)ft_strtol(dest_arg + (i * 3), 2);
	}
	return (false);
}
