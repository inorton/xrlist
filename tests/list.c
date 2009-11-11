#include <stdio.h>

#include "xrlist.h"

/* 
 * Create an xrlist and fill it with ten strings 
 * */
int main( int argc, char** argv )
{  

  /* Assign a new xrlist object */
  printf(">> create list\n");
  xr_list_t * mylist = xrlist_new();
  printf("<< done\n");

  printf(">> populate list\n");
  /* Append items to the xrlist */
  while ( mylist->count < 10 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char)); /* push this string onto the list */
    sprintf(ptr,"a string %d",mylist->count);
    printf(" + push \n");
    xrlist_push(mylist, (void*) ptr); /* store the pointer to our string */
  }
  printf("<< done\n");

  /* Iterate through all items in the list */
  xr_list_item_t * iter = mylist->head;
  
  printf(">> iterate list\n");
  while ( iter != NULL ) 
  {
    printf(" * item [0x%x] contains [%s]\n",
      (unsigned int) iter->object, (char*) iter->object );
    iter = iter->next; /* move to the next item, iter->next will be NULL when we reach the tail */
  }
  printf("<< done\n");

  printf(">> loop remove %d from head\n", mylist->count );
  while (mylist->count > 0) {
    char * str = xrlist_remove(mylist->head);
    printf(" - returned [0x%x] [%s]\n", (unsigned int)str, str);
    free(str);
  }
  printf("<< done\n");

  printf(">> populate list again\n");
  while ( mylist->count < 20 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char)); /* push this string onto the list */
    sprintf(ptr,"string %d",mylist->count);
    printf(" + push \n");
    xrlist_push(mylist, (void*) ptr); /* store the pointer to our string */
  }
  printf("<< done\n");

  printf(">> loop remove %d from tail\n", mylist->count);
  while (mylist->count > 0) {
    char * str = xrlist_remove(mylist->tail);
    printf(" - returned [0x%x] [%s]\n", (unsigned int)str, str);
    free(str);
  }
  printf("<< done\n");

  printf(">> populate list again\n");
  while ( mylist->count < 10 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char)); /* push this string onto the list */
    sprintf(ptr,"string %d",mylist->count);
    printf(" + push \n");
    xrlist_push(mylist, (void*) ptr); /* store the pointer to our string */
  }
  printf("<< done\n");

  printf(">> iterate list again \n");
  iter = mylist->head;
  while ( iter != NULL ) 
  {
    printf(" * item [0x%x] contains [%s]\n", (unsigned int) iter->object, (char*) iter->object );
    iter = iter->next; /* move to the next item, iter->next will be NULL when we reach the tail */
  }
  printf("<< done\n");


  printf(">> pop all items\n");

  /* Remove all items from the list starting at the last item */
  while ( mylist->count > 0 )
  {
    char * ptr = (char*) xrlist_pop(mylist); /* remove the last item */
    printf(" - returned [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr ); /* free up our string */
  }
  printf("<< done\n");

  printf(">> populate list with unshift (add at start)\n");
  /* Add new items to the start of the list */
  while ( mylist->count < 10 ) /* Add ten items */
  {
    char* ptr = (char*) malloc(32 * sizeof(char));
    sprintf(ptr,"string %d",mylist->count);
    printf(" + unshift\n");
    xrlist_unshift(mylist, (void*) ptr); /* Add the pointer */
  }
  printf("<< done\n");

  printf(">> shift all but 5 items\n");
  /* Remove all but 5 items from the list, starting at the first */
  while ( mylist->count >= 5 )
  {
    char * ptr = (char*) xrlist_shift(mylist); /* remove the first item */
    printf(" - shifted [0x%x] %s\n",(unsigned int) ptr, (char*) ptr);
    free( ptr ); /* free up our string */
  }
  printf("<< done\n");

  printf(">> free remaining list data\n");
  /* Remove and free everthing in the list including our strings */
  xrlist_free_items(mylist);
  printf("<< done\n");

  
  /* Create a list and fill it with strings again */
  printf(">> create new list \n");
  mylist = xrlist_new();
  printf("<< done\n");
  printf(">> populate list again\n");
  while ( mylist->count < 40 )
  {
    char * ptr = (char*) malloc(32 * sizeof(char));
    sprintf(ptr,"string %d",mylist->count);
    printf(" + push\n");
    xrlist_push(mylist, (void*) ptr);
  }
  printf("<< done\n");


  printf(">> pop all items and free each\n");
  /* Pop items from the list and free them ourselves */
  while ( mylist->count > 0 )
    free( xrlist_pop(mylist) );
  printf("<< done\n");

  printf(">> populate list again\n");
  while ( mylist->count < 10 )
  {
    char * ptr = (char*) malloc(100 * sizeof(char));
    sprintf(ptr,"a little bit of a bigger string %d",mylist->count);
    printf(" + push\n");
    xrlist_push(mylist, (void*) ptr);
  }
  printf("<< done\n");

  printf(">> remove items out of sequence\n");
  while ( mylist->count > 0 ){
    unsigned int remove;
    if ( mylist->count > 1 ) 
      remove = rand() % ( mylist->count - 1 );
    else
      remove = 0;

    printf(" get offset %u\n", remove );
    xr_list_item_t * got = xrlist_get( mylist, remove );
    printf(" got item [0x%x]\n", (unsigned int) got );
    printf(" >> remove item\n");
    free ( xrlist_remove( got ) );
  }
  printf("<< done\n");


  /* Free the list structure and metadata (leave alone any objects in any items) */
  printf(">> free list metadata\n");
  xrlist_free(mylist);
  printf("<< done\n");

  return 0;
}
