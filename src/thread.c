/*
** thread.c for  in /home/loupy/Rendu/PSU_2015_malloc
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Fri Feb  5 12:21:30 2016
** Last update Fri Feb  5 13:07:14 2016 
*/

#include "libmalloc.h"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void threading()
{
  pthread_mutex_lock(&g_mutex);
}

void unthreading()
{
  pthread_mutex_unlock(&g_mutex);
}
