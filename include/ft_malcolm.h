/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:12:26 by lle-saul          #+#    #+#             */
/*   Updated: 2025/05/09 12:10:47 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <netdb.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <ifaddrs.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <net/ethernet.h>
# include <netinet/in.h>
# include <netinet/if_ether.h>
# include <netinet/ether.h>
# include <netpacket/packet.h>

#define BUFFER_SIZE 65536

extern int	g_socket;

typedef struct s_info
{
	struct sockaddr_in	src_ip;
	unsigned char		src_mac[6];
	size_t 				src_mac_len;
	struct sockaddr_in	target_ip;
	unsigned char		target_mac[6];
	size_t 				target_mac_len;
}	t_info;

/*check.c*/
bool	check_ip(t_info *info, char *src_arg, char *dest_arg);
bool	check_mac(t_info *info, char *src_arg, char *dest_arg);

/*utils.c*/
void	*ft_memset(void *ptr, int nb, size_t len);
void	*ft_memcpy(void *dest, void *src, size_t len);
bool	ft_memcmp(void *ptr1, void *ptr2, size_t len);
int		ft_strlen(char *str);
bool	handle_signal(void);
bool	compare_mac(unsigned char *mac1, unsigned char *mac2, size_t len);
bool	compare_ip(void *ip1, void *ip2);
bool	get_inter(char *name, struct ifreq *ifr);

/*math.c*/
bool			ft_ishex(char c);
unsigned int	ft_strtol(char *str, int len);

/*response.c*/
char	*create_send_pkg(t_info *info);
void	send_pkg(char *send_pkg, struct ether_arp *arp, int eth_index);

#endif

