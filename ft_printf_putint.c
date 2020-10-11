/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 22:58:21 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include <stdio.h>  
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static int		ft_printf_putint_width(long long nbr, t_uint radix)
{
	int					count;
	unsigned long long	nbr_abs;
	
	count = 0;
	nbr_abs = nbr < 0 ? -nbr : nbr;
	if (nbr < 0)
		count++;
	while (nbr_abs > 0)
	{
		nbr_abs /= radix;
		count++;
	}
	return (count);
}

static void		ft_putnbr_unsigned_base(unsigned long long nbr, t_uint radix, int flagupcase)
{
	const char	*base;
	const char	baselow[] = "0123456789abcdef";
	const char	baseup[] = "0123456789ABCDEF";

	if (radix > 16)
		return ;
	base = (flagupcase ? baseup : baselow);
	if (nbr >= radix)
		ft_putnbr_unsigned_base(nbr / radix, radix, flagupcase);
	write(1, base + nbr % radix, 1);
}

static void		ft_putnbr_base(long long nbr, t_uint radix, int flag_upcase)
{
	unsigned long long	nbr_abs;

	nbr_abs = nbr < 0 ? -nbr : nbr;
	ft_putnbr_unsigned_base(nbr_abs, radix, flag_upcase);
}

static int		ft_printf_putsignedint(va_list ap, t_printf_flags *flags)
{
	int				nbr;
	int				nbrwidth;
	const t_uint	radix = 10;

	nbr = va_arg(ap, int);
	nbrwidth = ft_printf_putint_width(nbr, radix);
	if (flags->flag & FLAG_WIDTH_NEXTARG)
		flags->width = va_arg(ap, int);
	if (nbr < 0 && (flags->flag & FLAG_ZEROPADDING))
		write(1, "-", 1);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (nbr < 0 && !(flags->flag & FLAG_ZEROPADDING))
		write(1, "-", 1);
	ft_putnbr_base(nbr, radix, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

static int		ft_printf_putunsignedint(va_list ap, t_printf_flags *flags, const char fc)
{
	t_uint	nbr;
	int		nbrwidth;
	t_uint	radix;
	int		flag_upcase;

	radix = (fc == 'u' ? 10 : 16);
	flag_upcase = (ft_isupper(fc) ? 1 : 0);
	nbr = va_arg(ap, t_uint);
	nbrwidth = ft_printf_putint_width(nbr, radix);
	if (flags->width != 0 || (flags->flag & FLAG_WIDTH_NEXTARG))
	{
		if (flags->flag & FLAG_WIDTH_NEXTARG)
			flags->width = va_arg(ap, int);
	}
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	ft_putnbr_unsigned_base(nbr, radix, flag_upcase);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

int				ft_printf_putint(const char fc, va_list ap, t_printf_flags *flags)
{
	int		flag_unsigned;
	int		count;

	flag_unsigned = 1;
	count = 0;
	if (fc == 'd' || fc == 'i')
		count = ft_printf_putsignedint(ap, flags);
	else if (fc == 'u' || fc == 'x' || fc == 'X')
		count = ft_printf_putunsignedint(ap, flags, fc);
	return (count);
}
