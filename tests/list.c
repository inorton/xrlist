#include <stdio.h>

#include "xrlist.h"


int main( int argc, char** argv )
{

  xr_list_t * mylist = xrlist_new();
  /* add 10 integers to the list */

  int x = 0;
  char* foo = NULL;
  while ( x < 10 )
  {
    foo = (char*) malloc(32 * sizeof(char));
    sprintf(foo,"string %d",x);
    printf("pushing [%s]\n",foo);
    xrlist_push(mylist, (void*) foo);
    x++;
  }

  printf("-- iterate list --\n");
  xr_list_item_t * iter = mylist->head;
  x = 0;
  while ( iter != NULL )
  {
    printf("obj [0x%x] contains [%s]\n",(unsigned int) iter->object, (char*) iter->object );
    iter = iter->next;
  }

  printf("-- pop list --\n");

  while ( mylist->count > 0 )
  {
    char * ptr = (char*) xrlist_pop(mylist);
    printf("popped [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr );
  }

  printf("-- unshift list --\n");
  x = 0;
  while ( x < 10 )
  {
    foo = (char*) malloc(32 * sizeof(char));
    sprintf(foo,"string %d",x);
    printf("unshifting [%s]\n",foo);
    xrlist_unshift(mylist, (void*) foo);
    x++;
  }

  printf("-- shift list --\n");

  while ( mylist->count > 0 )
  {
    char * ptr = (char*) xrlist_shift(mylist);
    printf("shifted [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr );
  }

  printf("-- test free --\n");
  x = 0;
  while ( x < 10 )
  {
    foo = (char*) malloc(32 * sizeof(char));
    sprintf(foo,"string %d",x);
    xrlist_push(mylist, (void*) foo);
    x++;
  }

  xrlist_free_items(mylist);

  mylist = xrlist_new();

  x = 0;
  while ( x < 10 )
  {
    foo = (char*) malloc(32 * sizeof(char));
    sprintf(foo,"string %d",x);
    xrlist_push(mylist, (void*) foo);
    x++;
  }

  while ( mylist->count > 0 )
    free( xrlist_pop(mylist) );

  xrlist_free(mylist);




  return 0;
}
