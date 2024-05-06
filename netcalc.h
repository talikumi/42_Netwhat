/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   netcalc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-marc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:56:00 by edi-marc          #+#    #+#             */
/*   Updated: 2021/02/18 16:08:17 by edi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETCALC_H
# define NETCALC_H

# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>

# define ERR 0
# define OK 1

/*
**	struct in_addr contains s_addr (unsigned int),
**	32 bits for storing the ip treated as binary
*/
typedef	struct			s_ipnet
{
	unsigned int		hosts;
	struct in_addr		netmask;
	struct in_addr		network;
	struct in_addr		hostmin;
	struct in_addr		hostmax;
	struct in_addr		broadcast;
	struct in_addr		w_netmask;
}						t_ipnet;

/*
**	treat the 32 bits as number or as an array of 4 bytes of unsigned char
**	(also the first sign bit is needed to represent the [0 - 255] range)	
*/
typedef	union			u_ip32
{
	uint32_t			val;
	unsigned char		byte[4];
}						t_ip32;

int						ft_atoi(const char *str);
void					t_ipnet_print(t_ipnet *ipnet);
void					in_addr_print(struct in_addr inet_a);
void					calc_ipnet(t_ipnet *ipnet);
void					network_calc(t_ipnet *ipnet);
void					w_netmask_calc(t_ipnet *ipnet);
void					broadcast_calc(t_ipnet *ipnet);
void					hostmin_calc(t_ipnet *ipnet);
void					hostmax_calc(t_ipnet *ipnet);
void					hosts_calc(t_ipnet *ipnet);
char					*ft_strchr(const char *s, int c);
int						init_ipnet(t_ipnet *ipnet, char *net, char *netm);
int						init_ipnet_slash(t_ipnet *ipnet, char *network_s);

#endif
