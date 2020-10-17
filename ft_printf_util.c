/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:28:17 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/17 14:01:21 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

void		ft_printf_getwidth(int width_arg, t_printf_flags *flags)
{
	if (width_arg < 0)
	{
		flags->width = -width_arg;
		flags->flag = flags->flag | FLAG_LEFTADJUST;
	}
	else
		flags->width = width_arg;
}

void		ft_printf_initflags(t_printf_flags *flags)
{
	flags->width = -1;
	flags->precision = -1;
	flags->flag = 0;
}

void		ft_printf_putsign(int flag_neg, t_printf_flags *flags)
{
	if (flag_neg)
		write(1, "-", 1);
	else if (flags->flag & FLAG_PUTPOSSIGN)
		write(1, "+", 1);
	else if (flags->flag & FLAG_PUTPOSSPACE)
		write(1, " ", 1);
}

void		ft_printf_putintalternate(const char fc)
{
	if (fc == 'x' || fc == 'p')
		write(1, "0x", 2);
	else if (fc == 'X')
		write(1, "0X", 2);
}
