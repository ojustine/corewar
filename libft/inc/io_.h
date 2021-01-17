/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:55:24 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO__H
# define IO__H

# define BUFF_SIZE 512

typedef struct			s_fd_list
{
	int					fd;
	char				*line;
	struct s_fd_list	*next;
}						t_fd_list;

int						get_next_line(int fd, char **line);
void					ft_putendl(const char *s);
void					ft_putstr(char const *s);
void					ft_putnbr(int n);

#endif
