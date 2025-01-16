#include "get_next_line.h"

int found_newline(t_list *list)
{
    int i;
    if (list == NULL)
        return (0);
    i = 0;
    list = find_last_node(list);
    while (list->str_buf[i] && i < BUFFER_SIZE)
    {
        if (list->str_buf[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

void create_list(t_list **list, int fd)
{
    int char_read;
    char *buf;

    while (!found_newline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        char_read = read(fd, buf, BUFFER_SIZE);
        if (char_read <= 0) //EOF
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        append_list(list, buf);
    }  
}

void dealloc(t_list **list, t_list *cleaned_node, char *buf)
{
    t_list *tmp;
    
    if (*list == NULL)
        return ;
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (cleaned_node->str_buf[0])
        *list = cleaned_node;
    else
    {
        free(buf);
        free(cleaned_node);
    }
}

void polish_list(t_list **list)
{
    t_list *last_node;
    t_list *cleaned_node;
    char *unused_str;
    int i;
    int k;

    if (!list || !*list)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	unused_str = malloc(BUFFER_SIZE + 1);
	cleaned_node = malloc(sizeof(t_list));
    if (!unused_str || !cleaned_node)
		return ;
    k = 0;
    while (last_node->str_buf[i] && last_node->str_buf[++i])
		unused_str[k++] = last_node->str_buf[i];
    unused_str[k] = '\0';
    cleaned_node->str_buf = unused_str;
    cleaned_node->next = NULL;
    dealloc(list, cleaned_node, unused_str);
}

char *get_next_line(int fd)
{
    static t_list *list = NULL;
    char *line_result;

    // check whether fd is -1 , buffer size is less than 0, check if we can read on fd
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    create_list(&list, fd);
    if (list == NULL)
        return (NULL);
    line_result = get_line(list);
    polish_list(&list);
    return (line_result);
}
