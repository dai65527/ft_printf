/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_floatutil_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:48:02 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/16 15:13:24 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libftprintf.h"

void			ft_mts_divbytwo(int8_t *mts, int size)
{
	int		i;

	i = 0;
	while (i < size - 1)
	{
		mts[i + 1] += (mts[i] % 2) * 10;
		mts[i] /= 2;
		i++;
	}
}

void			ft_arr_add(int8_t *a, int8_t *b, int size)
{
	int		i;

	i = size - 1;
	while (i >= 0)
	{
		a[i] += b[i];
		if (a[i] >= 10 && i != 0)
		{
			a[i] -= 10;
			a[i - 1] += 1;
		}
		i--;
	}
}

void			ft_itg_dbl(int8_t *itg, int size)
{
	int		i;

	i = size - 1;
	while (i >= 0)
	{
		itg[i] *= 2;
		if (i < size - 1 && itg[i + 1] >= 10)
		{
			itg[i] += 1;
			itg[i + 1] -= 10;
		}
		i--;
	}
}

void			ft_float_roundup(t_float *iflt, int digit)
{
	int		i;

	i = digit;
	while (i < 0)
	{
		iflt->mts_dec[-i - 1]++;
		if (iflt->mts_dec[-i - 1] >= 10)
			iflt->mts_dec[-i - 1] -= 10;
		else
			return ;
		i++;
	}
	while (i < FLT_INTSIZE)
	{
		iflt->int_dec[FLT_INTSIZE - i - 1]++;
		if (iflt->int_dec[FLT_INTSIZE - i - 1] >= 10)
			iflt->int_dec[FLT_INTSIZE - i - 1] -= 10;
		else
			return ;
		i++;
	}
}

static int		ft_round_check(t_float *iflt, int digit)
{
	int		i;

	if (digit >= 0)
	{
		if (iflt->int_dec[FLT_INTSIZE - (digit + 1)] % 2)
			return (1);
		i = 0;
		while (i < digit - 1)
		{
			if (iflt->int_dec[FLT_INTSIZE - i++ - 1] != 0)
				return (1);
		}
	}
	if (digit < 0 && iflt->mts_dec[-digit - 1] % 2)
		return (1);
	i = digit <= 0 ? -digit + 1 : 0;
	while (i < FLT_MTSSIZE - 1)
	{
		if (iflt->mts_dec[i++] != 0)
			return (1);
	}
	return (0);
}

void			ft_float_round(t_float *iflt, int digit)
{
	if ((digit > FLT_INTSIZE - 1) || (-digit > FLT_MTSSIZE) ||
			!iflt->frac || iflt->exp == (FLT_EXPBIAS + 1))
		return ;
	if (digit > 0)
	{
		if (iflt->int_dec[FLT_INTSIZE - digit] > 5)
			ft_float_roundup(iflt, digit);
		else if (iflt->int_dec[FLT_INTSIZE - digit] < 5)
			return ;
		else if (ft_round_check(iflt, digit))
			ft_float_roundup(iflt, digit);
	}
	else
	{
		if (iflt->mts_dec[-digit] > 5)
			ft_float_roundup(iflt, digit);
		else if (iflt->mts_dec[-digit] < 5)
			return ;
		else if (ft_round_check(iflt, digit))
			ft_float_roundup(iflt, digit);
	}
}
