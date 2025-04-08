/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:27:54 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/08 19:23:19 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

int	g_socket;

/*arp_sha => sender MAC | arp_spa => sender ip*/
bool	process_pkg(char *buff, t_info *info, struct sockaddr_ll *recv_addr)
{
	struct ethhdr		*eth = (struct ethhdr *)buff;
	struct ether_arp	*arp = (struct ether_arp *)(buff + sizeof(struct ethhdr));
	(void)eth;
	
	char	sender_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
	
	printf("Packet received from %s\n", sender_ip);
	if (!compare_mac((unsigned char *)arp->arp_sha, info->target_mac, info->target_mac_len) || !compare_ip(arp->arp_spa, &info->target_ip.sin_addr))
		return (printf("err\n"), false);
	
	char network_name[IFNAMSIZ];
	if_indextoname(recv_addr->sll_ifindex, network_name);
	printf("Found available interface: %s\n", network_name);
	printf("An ARP request has been broadcast.\n");
	printf("\tmac address of request: %d:%d:%d:%d:%d:%d\n", arp->arp_sha[0], arp->arp_sha[1], arp->arp_sha[2], arp->arp_sha[3], arp->arp_sha[4], arp->arp_sha[5]);
	printf("\tIP address of request: %s\n", sender_ip);

	char	*packet_send = create_send_pkg(info, arp);
	if (!packet_send)
		return (printf("Error creating packet\n"), false);
	send_pkg(packet_send, arp, recv_addr->sll_ifindex);
	
	free(packet_send);
	printf("Exiting program...\n");
	return (true);
}

int	main(int ac, char **av)
{
	t_info	info;
	
	if (ac != 5) {
		printf("use : ft_malcolm <source_ip> <source_MAC> <target_ip> <target_MAC>\n");
		return (1);
	}
	if (check_ip(&info, av[1], av[3]) || check_mac(&info, av[2], av[4]) || handle_signal())
		return (1);
	g_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (g_socket < 0) {
		fprintf(stderr, "Error socket creation : %s\n", strerror(errno));
		return (1);
	}
	printf("address mac src : %d:%d:%d:%d:%d:%d\n", info.src_mac[0], info.src_mac[1], info.src_mac[2], info.src_mac[3], info.src_mac[4], info.src_mac[5]);
	printf("address mac dest : %d:%d:%d:%d:%d:%d\n", info.target_mac[0], info.target_mac[1], info.target_mac[2], info.target_mac[3], info.target_mac[4], info.target_mac[5]);
	
	while (1)
	{
		struct sockaddr_ll	recv_addr;
		socklen_t		recv_addr_len = sizeof(recv_addr);
		char			buff[BUFFER_SIZE];
		
		int	byte_recv = recvfrom(g_socket, buff, BUFFER_SIZE, 0, (struct sockaddr *)&recv_addr, &recv_addr_len);
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
