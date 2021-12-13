/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:27:03 by cgregory          #+#    #+#             */
/*   Updated: 2021/12/03 17:36:59 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmpl1;
	static char	*remain;
	int			diff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!remain)
		tmpl1 = ft_strdup("");
	if (remain)
	{
		tmpl1 = ft_strdup(remain);
		free (remain);
		remain = NULL;
	}
	line = ft_line_cycle(&tmpl1, fd);
	if (!line)
		return (NULL);
	diff = ft_strlen(tmpl1) - ft_strlen(line);
	remain = (char *)malloc((diff + 1) * sizeof(char));
	remain[diff] = '\0';
	ft_strlcpy(remain, &tmpl1[ft_strlen(line)], diff);
	free (tmpl1);
	return (line);
}

char	*ft_line_cycle(char **tmpl1, int fd)
{
	char	str[BUFFER_SIZE + 1];
	char	*line;
	char	*tmpl2;
	int		bytes;

	line = NULL;
	bytes = 0;
	while (!line)
	{
		if (ft_strchr(*tmpl1, '\n') == NULL)
			bytes = read(fd, str, BUFFER_SIZE);
		str[bytes] = '\0';
		if (bytes <= 0 && ft_strlen(*tmpl1) == 0)
		{
			free (*tmpl1);
			return (NULL);
		}
		tmpl2 = ft_strjoin(*tmpl1, str);
		line = ft_line_ret(tmpl2);
		*tmpl1 = ft_strdup(tmpl2);
		free (tmpl2);
		if (bytes == 0 && ft_strlen(*tmpl1) != 0 && !line)
			line = ft_strdup(*tmpl1);
	}
	return (line);
}

char	*ft_line_ret(char *tmpl2)
{
	int		f_bsn;
	char	*line;

	line = NULL;
	f_bsn = 0;
	if (ft_strchr(tmpl2, '\n'))
	{
		f_bsn = ft_strchr(tmpl2, '\n') - tmpl2;
		line = (char *)malloc((f_bsn + 2) * sizeof(char));
		line[f_bsn + 1] = '\0';
		ft_strlcpy(line, tmpl2, f_bsn + 1);
		return (line);
	}
	else
		return (NULL);
}
