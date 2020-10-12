/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:28:17 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 08:02:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
