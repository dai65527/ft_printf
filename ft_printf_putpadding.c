/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpadding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 09:02:48 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 09:03:32 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

void			ft_printf_putpadding(int width, t_printf_flags *flags)
{
	while (width > 0)
	{
		if (flags->flag & FLAG_ZEROPADDING)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		width--;
	}
}
