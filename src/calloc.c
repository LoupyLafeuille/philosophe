/*
** calloc.c for malloc in /home/gaonac_l/rendu/PSU_2015_malloc/mallocv2
** 
** Made by 
** Login   <gaonac_l@epitech.net>
** 
** Started on  Wed Jan 27 17:58:46 2016 
** Last update Thu Feb 11 21:11:01 2016 
*/

#include "libmalloc.h"

void				*calloc(size_t nmemb, size_t size)
{
  static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
  char				*block;
  unsigned int			i;

  if (nmemb == 0 || size == 0)
    return (NULL);
  pthread_mutex_lock(&mutex);
  if ((block = malloc(nmemb * size)) == NULL)
    {
      pthread_mutex_unlock(&mutex);
      return (NULL);
    }
  i = 0;
  while (i < (unsigned int)(((t_meta*)block) - 1)->size - META_SIZE)
    block[i++] = 0;
  pthread_mutex_unlock(&mutex);
  return (block);
}
