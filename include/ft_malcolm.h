/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-saul <lle-saul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:12:26 by lle-saul          #+#    #+#             */
/*   Updated: 2025/04/02 17:53:14 by lle-saul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <stdbool.h>
# include <stdio.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>

typedef struct s_info
{
	struct sockaddr_in	src_ip;
	struct sockaddr_in	dest_ip;
}	t_info;

/*check.c*/
bool	check_ip(t_info *info, char *src_arg, char *dest_arg);

/*utils.c*/
void	*ft_memset(void *ptr, int nb, size_t len);
void	*ft_memcpy(void *dest, void *src, size_t len);

#endif

