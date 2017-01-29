/*
** malloc.h for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
**
** Made by
** Login   <gaonac_l@epitech.net>
**
** Started on  Mon Jan 25 16:37:43 2016
** Last update Wed Feb 10 17:53:55 2016 
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include <stddef.h>

typedef struct		s_meta
{
  int			size;
  struct s_meta		*next;
}			t_meta;

extern t_meta		*g_free_tab;
extern t_meta		*g_used;

void			*malloc(size_t size);
void			show_alloc_mem();
void			free(void *ptr);
void			*realloc(void *old, size_t size);
void			*calloc(size_t nmemb, size_t size);
void			*memalign(size_t alignment, size_t size);

void			split_block(int idx);
size_t			next_power2(size_t nb);
void			recycling_block(t_meta *block);
void			merge_free(t_meta* ptr, int idx);

void			list_dump(t_meta *list);
t_meta			*list_pick(t_meta *list, t_meta *ptr);
int			list_push_front(t_meta *list, t_meta *ptr);
t_meta			*list_pop(t_meta *list);
t_meta			*list_pick_size(t_meta *list, int size);

void			threading();
void			unthreading();

# define META_SIZE	(unsigned int)sizeof(t_meta)
# define PAGE_SIZE	(unsigned int)getpagesize()
# define FIND_POW2(x)	(unsigned int)(log(x) / log(2))

#endif /* !MALLOC_H_ */
