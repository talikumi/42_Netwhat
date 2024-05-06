/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_netcalc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-marc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:54:35 by edi-marc          #+#    #+#             */
/*   Updated: 2021/02/18 16:16:27 by edi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Simple program to calculate some information for a given network
**
**	argv[1] = "192.168.0.0\24"
**
**	argv[1] = "192.168.0.0"
**	argv[2] = "255.255.255.0"
**
**	The program doesn't check:
**		Input validation;
**		incorrect netmask or/and network;
**
**	The program doesn't calculate /31 netmask
**
**	IT'S UP TO YOU !
*/

#include "netcalc.h"

int		main(int argc, char *argv[])
{
	int		res;
	t_ipnet	*ipnet;

	res = OK;
	if (argc > 1 && argc < 4 && (ipnet = malloc(sizeof(*ipnet))))
	{
		if (argc == 2)
			res = init_ipnet_slash(ipnet, argv[1]);
		else
			res = init_ipnet(ipnet, argv[1], argv[2]);
		if (res)
		{
			calc_ipnet(ipnet);
			t_ipnet_print(ipnet);
		}
		else
			printf("ERROR\n");
		free(ipnet);
	}
	return (0);
}

int		init_ipnet_slash(t_ipnet *ipnet, char *network_s)
{
	int				res;
	char			*netmask;
	struct in_addr	addr;

	netmask = (ft_strchr(network_s, 47)) + 1;
	*((char *)ft_strchr(network_s, 47)) = '\0';
	if ((res = ft_atoi(netmask)) > 0 && res < 32)
	{
		addr.s_addr = ~0;
		addr.s_addr = addr.s_addr << (32 - res);
		ipnet->netmask.s_addr = htonl(addr.s_addr);
		res = inet_pton(AF_INET, network_s, (void *)&ipnet->network);
	}
	else
		res = ERR;
	return (res);
}

int		init_ipnet(t_ipnet *ipnet, char *net, char *netm)
{
	int res;

	res = ERR;
	if (inet_pton(AF_INET, netm, (void *)&ipnet->netmask))
		res = inet_pton(AF_INET, net, (void *)&ipnet->network);
	return (res);
}

void	calc_ipnet(t_ipnet *ipnet)
{
	network_calc(ipnet);
	w_netmask_calc(ipnet);
	broadcast_calc(ipnet);
	hostmin_calc(ipnet);
	hostmax_calc(ipnet);
	hosts_calc(ipnet);
}
