/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:08 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/01/24 18:24:26 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	append_list(t_list **list, char *buf)
{
	t_list	*last_node;
	t_list	*new_node;

	last_node = find_last_node(*list);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buf);
		return ;
	}
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

int	found_new_line(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	list = find_last_node(list);
	i = 0;
	while (list->str_buf[i])
	{
		if (list->str_buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append_list(list, buf);
	}
}

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*cleaned_node;
	char	*unuse_str;
	int		i;
	int		k;

	if (!list)
		return ;
	last_node = find_last_node(*list);
	cleaned_node = malloc(sizeof(t_list));
	unuse_str = malloc(BUFFER_SIZE + 1);
	if (!cleaned_node || !unuse_str)
		return ;
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		unuse_str[k++] = last_node->str_buf[i];
	unuse_str[k] = '\0';
	cleaned_node->str_buf = unuse_str;
	cleaned_node->next = NULL;
	dealloc(list, cleaned_node, unuse_str);
}

char	*get_next_line(int fd)
{
	static t_list	*list[MAX_FD];
	char			*next_line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	create_list(&list[fd], fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = get_line(list[fd]);
	polish_list(&list[fd]);
	return (next_line);
}
