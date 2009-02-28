#include <assert.h>
#include "xrlist.h"

xr_list_t * xrlist_new( void )
{
  xr_list_t * list = malloc( 1 * sizeof(xr_list_t) );
  assert( !( list == NULL ) );
  list->count = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

xr_list_item_t * xrlist_new_item( void )
{
  xr_list_item_t * newitem = malloc( 1 * sizeof(xr_list_item_t) );
  assert( !( newitem == NULL ) );
  memset( newitem, 0, sizeof(newitem));
  return newitem;
}

void xrlist_free( xr_list_t * list )
{
  if ( list == NULL )
    return;

  while ( list->count > 0 )
    xrlist_pop( list );
  
  free(list);
}

void xrlist_free_items( xr_list_t * list )
{
  if ( list == NULL )
    return;

  while ( list->count > 0 ){
    void * obj = xrlist_pop( list );
    free( obj );
  }
  free(list);
}

void xrlist_free_item( xr_list_item_t * item )
{
  /* we don't free the object pointer */
  free( item );  
}

xr_list_item_t * xrlist_unshift( xr_list_t * list, void * object )
{
  xr_list_item_t * newitem = xrlist_new_item();

  assert( !( list == NULL ) );

  newitem->list = list;
  newitem->object = object;
  newitem->next   = list->head;

  if ( list->count == 0 )
  {
    list->head = newitem;
    list->tail = newitem;
  } else {
    assert( !( list->head == NULL ) );
    list->head->prev = newitem;
    newitem->next = list->head;
    list->head = newitem;
  }

  list->count++;
  return newitem;
}


xr_list_item_t * xrlist_push( xr_list_t * list, void * object )
{
  xr_list_item_t * newitem = xrlist_new_item();

  assert( !( list == NULL ) );

  newitem->list = list;
  newitem->object = object;
  newitem->prev   = list->tail;

  if ( list->count == 0 )
  {
    list->head = newitem;
    list->tail = newitem;
  } else {
    assert( !( list->tail == NULL ) );
    newitem->prev = list->tail;
    list->tail->next = newitem;
    list->tail = newitem;
  }

  list->count++;
  return newitem;
}

void * xrlist_pop( xr_list_t * list )
{
  void * ret = NULL;
  assert( !( list == NULL ) );
  if ( list->count == 0 )
    return ret;

  xr_list_item_t * last = list->tail;
  if ( last != NULL ){
    list->tail = last->prev;
    list->count--;
    ret = last->object;
    xrlist_free_item( last );
  }

  return ret;
}

void * xrlist_shift ( xr_list_t * list )
{
  void * ret = NULL;
  if ( list->count == 0 )
    return ret;

  xr_list_item_t * first = list->head;
  if ( first != NULL ){
    list->head = first->next;
    first->prev = NULL;
    list->count--;
    ret = first->object;
    xrlist_free_item( first );
  }
  return ret;
}




