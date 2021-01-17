/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io_.h"
#include "str.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static t_fd_list	*node_get(int fd, t_fd_list **list)
{
	register t_fd_list *new_node;

	new_node = *list;
	while (new_node)
	{
		if (new_node->fd == fd)
			return (new_node);
		new_node = new_node->next;
	}
	if (!(new_node = malloc(sizeof(t_fd_list))))
		return (NULL);
	new_node->next = NULL;
	new_node->line = NULL;
	new_node->fd = fd;
	new_node->next = *list;
	*list = new_node;
	return (new_node);
}

static int			handle_saved_line(char **line, t_fd_list **node)
{
	size_t			len;
	const char		*nl_ptr = ft_strchr((*node)->line, '\n');
	char			*tmp;

	len = nl_ptr ? (size_t)(nl_ptr - (*node)->line) : ft_strlen((*node)->line);
	*line = ft_strndup((*node)->line, len);
	tmp = NULL;
	if (((*node)->line)[len] == '\n' && ((*node)->line)[len + 1] != '\0')
		tmp = ft_strdup((*node)->line + len + 1);
	free((*node)->line);
	(*node)->line = tmp;
	return (1);
}

static int			node_free(t_fd_list **list, int fd)
{
	register t_fd_list *this;
	register t_fd_list *prev;

	this = *list;
	prev = *list;
	if (this->fd == fd)
		*list = this->next;
	else
		while (this->next)
		{
			prev = this;
			this = this->next;
			if (this->fd == fd)
				break ;
		}
	prev->next = this->next;
	free(this);
	this = NULL;
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd_list	*fd_list;
	t_fd_list			*node;
	register char		*tmp;
	register int		reads;
	char				buff[BUFF_SIZE + 1];

	reads = 0;
	if (fd < 0 || !line || !(node = node_get(fd, &fd_list)))
		return (-1);
	if (!node->line || !ft_strchr(node->line, '\n'))
	{
		while ((reads = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[reads] = '\0';
			tmp = (node->line) ? ft_strjoin(node->line, buff) : ft_strdup(buff);
			free(node->line);
			node->line = tmp;
			if (ft_strchr(buff, '\n'))
				break ;
		}
		if (reads < 0)
			return (-1);
	}
	return (reads == 0 && !node->line
			? node_free(&fd_list, node->fd) : handle_saved_line(line, &node));
}
