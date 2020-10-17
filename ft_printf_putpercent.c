/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpercent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:59:45 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/17 13:51:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

int				ft_printf_putpercent(t_printf_flags *flags)
{
	if (flags->width == -1)
		flags->width = 0;
	if (flags->flag & FLAG_LEFTADJUST)
		write(1, "%", 1);
	ft_printf_putpadding(flags->width - 1, flags);
	if (!(flags->flag & FLAG_LEFTADJUST))
		write(1, "%", 1);
	return (flags->width ? flags->width : 1);
}
