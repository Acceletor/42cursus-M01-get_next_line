#include "get_next_line_bonus.h"

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

void copy_str(t_list *list, char *string_till_newline)
{
    int i;
    int k;

    if (!list)
        return ;
    k = 0;
    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                string_till_newline[k++] = '\n';
                string_till_newline[k] = '\0';
                return ;
            }
            string_till_newline[k++] = list->str_buf[i++];
        }
        list = list->next;
    }
    string_till_newline[k] = '\0';
}

int len_till_new_line(t_list *list)
{
    int i;
    int len;

    if (!list)
        return (0);
    len = 0;
    while (list)
    {   
        i = 0;
        while (list->str_buf[i])
        {
            len++;
            if (list->str_buf[i++] == '\n')
                return (len);
        }
        list = list->next;
    }
    return(len);
}

char *get_line(t_list *list)
{
    int str_len;
    char *string_till_newline;

    str_len = len_till_new_line(list);
    if (str_len == 0)
        return (NULL);
    string_till_newline = malloc(str_len + 1);
    if (!string_till_newline)
        return (NULL);
    copy_str(list, string_till_newline);
    return (string_till_newline);
}

t_list *find_last_node(t_list *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

void append_list(t_list **list, char *buf)
{
    t_list *last_node;
    t_list *new_node;
    
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

int found_new_line(t_list *list)
{
    int i;
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

void create_list(t_list **list, int fd)
{
    int char_read;
    char *buf;

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

void polish_list(t_list **list)
{
    t_list *last_node;
    t_list *cleaned_node;
    char *unuse_str;
    int i;
    int k;

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
    static t_list *list[MAX_FD];
    char *next_line;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    create_list(&list[fd], fd);
    if (list[fd] == NULL)
        return (NULL);
    next_line = get_line(list[fd]);
    polish_list(&list[fd]);
    return(next_line);
}
