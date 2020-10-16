/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_iflt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:48:02 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/16 09:45:01 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libftprintf.h"

static void		ft_store_iflt_mts(t_float *iflt)
{
	int			i;
	u_int32_t	mts_bin;
	int8_t		mts[FLT_MTSSIZE];

	ft_bzero(iflt->mts_dec, sizeof(iflt->mts_dec));
	if (iflt->exp >= 23 || (!iflt->frac && iflt->exp == -127))
		return ;
	if (iflt->exp >= 0)
		mts_bin = iflt->frac << iflt->exp;
	else if (iflt->exp == -127)
		mts_bin = iflt->frac;
	else
		mts_bin = (iflt->frac >> 1) | (1 << 31);
	ft_bzero(mts, sizeof(mts));
	mts[0] = 5;
	i = 0;
	while (i++ < -iflt->exp - 1)
		ft_mts_divbytwo(mts, FLT_MTSSIZE);
	i = -1;
	while (++i < 24)
	{
		if (mts_bin & (1 << (31 - i)))
			ft_arr_add(iflt->mts_dec, mts, FLT_MTSSIZE);
		ft_mts_divbytwo(mts, FLT_MTSSIZE);
	}
}

static void		ft_store_iflt_int(t_float *iflt)
{
	int			i;
	u_int32_t	itg_bin;
	int			offset;
	int8_t		itg[FLT_INTSIZE];

	ft_bzero(iflt->int_dec, sizeof(iflt->int_dec));
	if (iflt->exp <= 0)
	{
		if (!iflt->exp)
			iflt->int_dec[FLT_INTSIZE - 1] = 1;
		return ;
	}
	offset = (iflt->exp >= 23) ? 23 : iflt->exp;
	itg_bin = (iflt->frac >> (32 - offset)) | (1 << offset);
	ft_bzero(itg, sizeof(itg));
	itg[FLT_INTSIZE - 1] = 1;
	i = -1;
	while (++i < 24)
	{
		if (itg_bin & (1 << i))
			ft_arr_add(iflt->int_dec, itg, FLT_INTSIZE);
		ft_itg_dbl(itg, FLT_INTSIZE);
	}
	while (++i < (int)iflt->exp + 1)
		ft_itg_dbl(iflt->int_dec, FLT_INTSIZE);
}

t_float		ft_store_iflt(float num)
{
	u_int32_t	mem;
	t_float		iflt;

	ft_memcpy(&mem, &num, 4);
	iflt.sign = mem >> 31;
	iflt.exp = (mem >> 23) - 127;
	iflt.frac = mem << 9;
	ft_store_iflt_int(&iflt);
	ft_store_iflt_mts(&iflt);
	return (iflt);
}
