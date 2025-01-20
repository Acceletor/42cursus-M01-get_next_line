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
