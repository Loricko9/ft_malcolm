/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:27:54 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/02 17:34:56 by lle-saul         ###   ########.fr       */
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
	if (check_ip(&info, av[1], av[3]))
		return (1);
}
