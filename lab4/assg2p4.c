#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int glob;

void *child(void *t)
{
  // Increment glob by 1, wait for 1 second, then increment by 1 again

  printf("Child %ld entering. Glob is currently %d.\n", (long) t, glob);
  pthread_mutex_lock(&mutex);
  glob++;
  sleep(1);
  glob++;
  pthread_mutex_unlock(&mutex);
  printf("Child %ld exiting. Glob is currently %d.\n", (long) t, glob);

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  long i;
  pthread_t thread;
  glob = 0;
  for(i = 0; i < 10; i++)
      {
          pthread_create(&thread, NULL, child, (void *) i);
      }
  for(i = 0; i < 10; i++)
      {
          pthread_join(thread, NULL);
      }
  
  printf("Final value of glob is %d.\n", glob);
  pthread_mutex_destroy(&mutex);

  return 0;
}
