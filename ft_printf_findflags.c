/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_findflags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:49:46 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 08:54:57 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_printf_setwidth(const char *format, t_printf_flags *flags,
										int flag_precision)
{
	t_uint	res;

	if (*format == '0' && !flag_precision)
	{
		flags->flag = flags->flag | FLAG_ZEROPADDING;
		format++;
	}
	res = 0;
	while (ft_isdigit(*format))
	{
		res = res * 10 + *(format++) - '0';
	}
	if (flag_precision)
		flags->precision = res;
	else
		flags->width = res;
	return ((char *)format);
}

static int		ft_printf_isflag(int c)
{
	int			i;
	const char	flag_char[] = "-.*";

	if (ft_isdigit(c))
		return (1);
	i = 0;
	while (flag_char[i])
	{
		if (c == flag_char[i])
			return (1);
		i++;
	}
	return (0);
}

char			*ft_printf_findflags(const char *format, t_printf_flags *flags)
{
	int		flag_precision;

	flag_precision = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->flag = 0;
	while (ft_printf_isflag(*format))
	{
		if (*format == '-')
			flags->flag = flags->flag | FLAG_LEFTADJUST;
		if (*format == '*')
		{
			if (flag_precision)
				flags->flag = flags->flag | FLAG_PRECISION_NEXTARG;
			else
				flags->flag = flags->flag | FLAG_WIDTH_NEXTARG;
		}
		if (*format == '.')
			flag_precision = 1;
		if (ft_isdigit(*format))
			format = ft_printf_setwidth(format, flags, flag_precision);
		else
			format++;
	}
	return ((char *)format);
}
