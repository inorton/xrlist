#include <stdio.h>

#include "xrlist.h"

/* 
 * Create an xrlist and fill it with ten strings 
 * */
int main( int argc, char** argv )
{  

  /* Assign a new xrlist object */
  xr_list_t * mylist = xrlist_new();

  /* Append items to the xrlist */
  while ( mylist->count < 10 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char)); /* push this string onto the list */
    sprintf(ptr,"string %d",mylist->count);

    xrlist_push(mylist, (void*) ptr); /* store the pointer to our string */
  }

  /* Iterate through all items in the list */
  xr_list_item_t * iter = mylist->head;
  while ( iter != NULL ) 
  {
    printf("obj [0x%x] contains [%s]\n",
      (unsigned int) iter->object, (char*) iter->object );
    iter = iter->next; /* move to the next item, iter->next will be NULL when we reach the tail */
  }

  /* Remove all items from the list starting at the last item */
  while ( mylist->count > 0 )
  {
    char * ptr = (char*) xrlist_pop(mylist); /* remove the last item */
    printf("popped [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr ); /* free up our string */
  }

  /* Add new items to the start of the list */
  while ( mylist->count < 10 ) /* Add ten items */
  {
    char* ptr = (char*) malloc(32 * sizeof(char));
    sprintf(ptr,"string %d",mylist->count);
    xrlist_unshift(mylist, (void*) ptr); /* Add the pointer */
  }

  /* Remove all but 5 items from the list, starting at the first */
  while ( mylist->count >= 5 )
  {
    char * ptr = (char*) xrlist_shift(mylist); /* remove the first item */
    printf("shifted [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr ); /* free up our string */
  }

  /* Remove and free everthing in the list including our strings */
  xrlist_free_items(mylist);

  
  /* Create a list and fill it with strings again */
  mylist = xrlist_new();
  while ( mylist->count < 10 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char));
    sprintf(ptr,"string %d",mylist->count);
    xrlist_push(mylist, (void*) ptr);
  }

  /* Pop items from the list and free them ourselves */
  while ( mylist->count > 0 )
    free( xrlist_pop(mylist) );

  /* Free the list structure and metadata (leave alone any objects in any items) */
  xrlist_free(mylist);

  return 0;
}
