/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:58:01 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# define	VOID_EXIT_FUNC_MAX	8
# define	PTR_EXIT_FUNC_MAX	16

typedef	void (*t_ptr_exit_func)(void *);
typedef	void (*t_void_exit_func)(void);

void	ft_exit(int code, const char *msg);
void	ft_at_exit(t_void_exit_func func, const char *msg);
void	ft_at_exit_ptr(t_ptr_exit_func func, void *ptr, const char *msg);
void	ft_log_error(const char *message, const char *cause, const char *func,
		const char *file);
void	ft_assert(int to_check, const char *func, const char *message);
void	ft_kill(const char *message, const char *cause, const char *func,
		const char *file);

#endif
