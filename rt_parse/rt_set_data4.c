/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_data4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:52 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:53 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_try_atoi(char *line, int *i, int *j, int *res)
{
	int	k;

	k = 0;
	*res = 0;
	while (line[*i + *j + k] != '\0')
	{
		if (rt_is_strchr(" \t,", line[*i + *j + k]))
			break ;
		if (ft_isdigit(line[*i + *j + k]) == 0)
			return (FAIL);
		*res *= 10;
		*res += line[*i + *j + k] - '0';
		k += 1;
	}
	if (k == 0)
		return (FAIL);
	*j += k;
	return (SUCCESS);
}

int	rt_try_atof(char *line, int *i, int *j, float *res)
{
	int		k;
	int		m;

	*res = 0;
	if (rt_check_minus(line[*i + *j], &k, &m))
		return (FAIL);
	if (rt_try_atof_before_dot(&line[*i + *j], &k, res))
		return (FAIL);
	if (line[*i + *j + k] == '.')
	{
		k += 1;
		if (rt_try_atof_after_dot(&line[*i + *j], &k, res, 0))
			return (FAIL);
	}
	if ((m == 1 && k == 0) || (m == -1 && k == 1))
		return (FAIL);
	*j += k;
	*res *= m;
	return (SUCCESS);
}

int	rt_check_minus(char c, int *k, int *m)
{
	if (c == '\0')
		return (FAIL);
	*k = 0;
	*m = 1;
	if (c == '-')
	{
		*m = -1;
		*k = 1;
	}
	return (SUCCESS);
}

int	rt_try_atof_before_dot(char *line, int *k, float *res)
{
	while (line[*k] != 0)
	{
		if (rt_is_strchr(" \t,.", line[*k]))
			break ;
		if (ft_isdigit(line[*k]) == 0)
			return (FAIL);
		*res *= 10;
		*res += line[*k] - '0';
		*k += 1;
	}
	return (SUCCESS);
}

int	rt_try_atof_after_dot(char *line, int *k, float *res, float _res)
{
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (rt_is_strchr(" \t,", line[*k + last]) == FALSE)
		last++;
	while (i < last)
	{
		if (ft_isdigit(line[*k + last - i - 1]) == 0)
			return (FAIL);
		_res /= 10;
		_res += line[*k + last - i - 1] - '0';
		i += 1;
	}
	*res = *res + _res / 10;
	*k += last;
	return (SUCCESS);
}
