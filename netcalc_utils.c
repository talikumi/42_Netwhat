/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   netcalc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-marc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:00:50 by edi-marc          #+#    #+#             */
/*   Updated: 2021/02/18 16:42:56 by edi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netcalc.h"

void	in_addr_print(struct in_addr inet_a)
{
	char	buf[INET_ADDRSTRLEN];

	if (!(inet_ntop(AF_INET, (void *)&inet_a, buf, sizeof(buf))))
		printf("ERROR\n");
	else
		printf("%s\n", buf);
}

void	t_ipnet_print(t_ipnet *ipnet)
{
	t_ip32 ip;

	ip.val = ipnet->network.s_addr;
	printf("\n");
	printf("-----------Netmask: ");
	in_addr_print(ipnet->netmask);
	printf("-----Wildcard Mask: ");
	in_addr_print(ipnet->w_netmask);
	printf("\n");
	printf("-----------Network: ");
	in_addr_print(ipnet->network);
	printf("First host address: ");
	in_addr_print(ipnet->hostmin);
	printf("-Last host address: ");
	in_addr_print(ipnet->hostmax);
	printf("---Number of hosts: ");
	printf("%u\n", ipnet->hosts);
	printf("-Broadcast address: ");
	in_addr_print(ipnet->broadcast);
	printf("\n");
	printf("-----Network byte order (big endian): %u %u %u %u -> %u \n",
			ip.byte[3], ip.byte[2], ip.byte[1], ip.byte[0], ip.val);
	printf("-Host byte order (little/big endian): %u %u %u %u -> %u \n",
			ip.byte[0], ip.byte[1], ip.byte[2], ip.byte[3], ip.val);
	printf("\n");
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	char	ch;
	int		found;

	p = 0;
	ch = c;
	found = 0;
	while (*s != '\0' && !found)
	{
		if (*s == ch)
		{
			p = (char*)s;
			found = 1;
		}
		s++;
	}
	if (*s == '\0' && c == 0)
		p = (char *)s;
	return (p);
}

/*
**	Network = ip_address AND netmask
*/
void	network_calc(t_ipnet *ipnet)
{
	ipnet->network.s_addr = ipnet->network.s_addr & ipnet->netmask.s_addr;
}

/*
**	Wildcard mask = ! netmask 
*/
void	w_netmask_calc(t_ipnet *ipnet)
{
	ipnet->w_netmask.s_addr = ~ipnet->netmask.s_addr;
}

/*
**	Broadcast address = network OR wildcard mask
*/
void	broadcast_calc(t_ipnet *ipnet)
{
	ipnet->broadcast.s_addr = ipnet->network.s_addr | ipnet->w_netmask.s_addr;
}

/*
**	The ip stored on the struct are in the network byte order format.
**	Need to convert the format of the ip to host byte order
**	then add 1 bit to the end and then back to network byte order
**
**	SEE NETWORK/HOST BYTE ORDER AND LITTLE/BIG ENDIAN
*/
void	hostmin_calc(t_ipnet *ipnet)
{
	ipnet->hostmin.s_addr = ntohl(htonl(ipnet->network.s_addr) + 1);
}

/*
**	Conversion --> broadcast address - 1
*/
void	hostmax_calc(t_ipnet *ipnet)
{
	ipnet->hostmax.s_addr = ntohl(htonl(ipnet->broadcast.s_addr) - 1);
}

/*
**	Conversion --> wildcard mask - 1
**	the Maths does the rest...
**	hosts is unsigned int
*/
void	hosts_calc(t_ipnet *ipnet)
{
	ipnet->hosts = htonl(ipnet->w_netmask.s_addr) - 1;
}
