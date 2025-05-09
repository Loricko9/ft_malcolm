/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:19:53 by lle-saul          #+#    #+#             */
/*   Updated: 2025/05/09 11:31:16 by lle-saul         ###   ########.fr       */
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

bool	ft_memcmp(void *ptr1, void *ptr2, size_t len)
{
	size_t	i;

	if (!ptr1 || !ptr2)
		return (false);
	i = 0;
	while (i < len)
	{
		if (((unsigned char *)ptr1)[i] != ((unsigned char *)ptr2)[i])
			return (false);
		i++;
	}
	return (true);
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

void	stop_malcolm(int signum)
{
	(void)signum;
	close(g_socket);
}

bool	handle_signal(void)
{
	if (signal(SIGINT, stop_malcolm) == SIG_ERR) {
		fprintf(stderr, "Error handle signal : %s\n", strerror(errno));
		return (true);
	}
	return (false);
}

bool	compare_mac(unsigned char *mac1, unsigned char *mac2, size_t len)
{
	if (ft_memcmp(mac1, mac2, len))
		return (true);
	return (printf("err Mac\n"), false);
}

bool	compare_ip(void *ip1, void *ip2)
{
	if (ft_memcmp(ip1, ip2, 4))
		return (true);
	return (printf("err Ip\n"), false);
}

bool	get_inter(char *name, struct ifreq *ifr)
{
	if (name && ft_strlen(name) > IFNAMSIZ)
		return (printf("ft_malcolm: interface name too long\n"), true);
	ft_memset(ifr, 0, sizeof(struct ifreq));
	if (name)
		strncpy(ifr->ifr_name, name, IFNAMSIZ);
	else
		strncpy(ifr->ifr_name, "eth0", IFNAMSIZ);
	if (ioctl(g_socket, SIOCGIFINDEX, ifr) < 0)
		return (printf("ft_malcolm: error interface : %s\n", strerror(errno)), true);
	
	char network_name[IFNAMSIZ];
	if_indextoname(ifr->ifr_ifindex, network_name);
	printf("Found available interface: %s\n", network_name);

	struct packet_mreq mreq;
	ft_memset(&mreq, 0, sizeof(mreq));
	mreq.mr_ifindex = ifr->ifr_ifindex;
	mreq.mr_type = PACKET_MR_PROMISC;
	setsockopt(g_socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	
	return (false);
}
