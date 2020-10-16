/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putfloat_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:36:42 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/16 13:34:33 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   <stdio.h>   
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

int				ft_printf_putfloat_f_width(t_float iflt, t_printf_flags *flags)
{
	int		intwidth;
	int		mstwidth;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
			return (4);
		return (3);
	}
	mstwidth = (flags->precision || flags->flag & FLAG_ALTERNATE)
				? flags->precision + 1 : 0;
	intwidth = FLT_INTSIZE;
	while (intwidth > 1 && !iflt.int_dec[FLT_INTSIZE - intwidth])
		intwidth--;
	if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
		return (intwidth + mstwidth + 1);
	return (intwidth + mstwidth);
}

void			ft_putnaninf(int flag_isnan)
{
	if (flag_isnan)
		write(1, "nan", 3);
	else
		write(1, "inf", 3);
}

static void		ft_printf_putfloat_f_put(t_float iflt, t_printf_flags *flags)
{
	int		i;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		ft_putnaninf(!!iflt.frac);
		return ;
	}
	ft_float_round(&iflt, -flags->precision);
	i = 0;
	while (!iflt.int_dec[i] && i < FLT_INTSIZE - 1)
		i++;
	while (i < FLT_INTSIZE)
		ft_putchar_fd(iflt.int_dec[i++] + '0', 1);
	if (flags->precision || flags->flag & FLAG_ALTERNATE)
		write(1, ".", 1);
	i = 0;
	while (i < flags->precision)
	{
		if (i < FLT_MTSSIZE - 1)
			ft_putchar_fd(iflt.mts_dec[i] + '0', 1);
		else
			write(1, "0", 1);
		i++;
	}
}

int				ft_printf_putfloat_f(va_list ap, t_printf_flags *flags)
{
	double		nbr;
	int			nbrwidth;
	t_float		iflt;

	ft_printf_getwidth_prec(ap, flags);
	if (flags->precision < 0)
		flags->precision = 6;
	nbr = va_arg(ap, double);
	iflt = ft_store_iflt(nbr);
	if (iflt.exp == (FLT_EXPBIAS + 1))
		flags->flag &= ~(FLAG_ZEROPADDING);
	if (iflt.exp == (FLT_EXPBIAS + 1) && !!iflt.frac)
		flags->flag &= ~(FLAG_PUTPOSSIGN | FLAG_PUTPOSSPACE);
	nbrwidth = ft_printf_putfloat_f_width(iflt, flags);
	if (flags->flag & FLAG_ZEROPADDING)
		ft_printf_putsign(iflt.sign, flags);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(flags->flag & FLAG_ZEROPADDING))
		ft_printf_putsign(iflt.sign, flags);
	ft_printf_putfloat_f_put(iflt, flags);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

int				ft_printf_putfloat(const char fc, va_list ap,
									t_printf_flags *flags)
{
	int		count;

	count = 0;
	if (fc == 'f')
		count = ft_printf_putfloat_f(ap, flags);
	return (count);
}
