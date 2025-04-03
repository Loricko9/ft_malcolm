/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:27:54 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/03 18:21:06 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

int	main(int ac, char **av)
{
	t_info	info;
	
	if (ac != 5) {
		printf("use : ft_malcolm <source_ip> <source_MAC> <target_ip> <target_MAC>\n");
		return (1);
	}
	if (check_ip(&info, av[1], av[3]) || check_mac(&info, av[2], av[4]) || handle_signal())
		return (1);
	int	fdsocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (fdsocket < 0) {
		perror("sock");
		fprintf(stderr, "Error socket creation : %s\n", strerror(errno));
		return (1);
	}
	printf("address mac src : %d:%d:%d:%d:%d:%d\n", info.src_mac[0], info.src_mac[1], info.src_mac[2], info.src_mac[3], info.src_mac[4], info.src_mac[5]);
	printf("address mac dest : %d:%d:%d:%d:%d:%d\n", info.dest_mac[0], info.dest_mac[1], info.dest_mac[2], info.dest_mac[3], info.dest_mac[4], info.dest_mac[5]);
	close(fdsocket);
}
