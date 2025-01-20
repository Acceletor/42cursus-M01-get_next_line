#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 4096 
//system’s hard limit for the number of open file descriptors is 4096

# include <unistd.h> //read()
# include <fcntl.h> //open()
# include <stdlib.h> // malloc
# include <stdio.h> //printf

typedef struct s_list
{
    char *str_buf;
    struct s_list *next;
}t_list;

void append_list(t_list **list, char *buf);
int found_new_line(t_list *list);
void create_list(t_list **list, int fd);
void polish_list(t_list **list);
char	*get_next_line(int fd);
void dealloc(t_list **list, t_list *cleaned_node, char *buf);
void copy_str(t_list *list, char *string_till_newline);
int len_till_new_line(t_list *list);
char *get_line(t_list *list);
t_list *find_last_node(t_list *list);

#endif