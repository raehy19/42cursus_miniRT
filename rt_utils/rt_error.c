/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:37 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:39 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_error_msg(char *s, int status)
{
	write(2, "Error\n", 6);
	write(2, "miniRT : ", 9);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(status);
	return (status);
}
