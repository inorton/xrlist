#include <assert.h>
#include "xrlist.h"

/**
 * \mainpage xrlist Documentation Index
 *
 * \section intro_sec Introduction
 *
 * xrlist is a simple dynamic array implemented as a double linked list. It
 * provides functions for the standard push,pop,shift and unshift operations on
 * the array.
 *
 * - xrlist_new() - create a new list
 * - xrlist_push() - add an object to the end of a list
 * - xrlist_unshift() - add an object to the start of a list
 * - xrlist_pop() - remove an object from the end of a list
 * - xrlist_shift() - remove an object from the start of a list
 *
 * \see xrlist.h
 *
 * \section license_sec BSD Public License
 *
Copyright (c) 2009, Ian Norton
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.  

 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

 - Neither the name of xrlist nor the names of its contributors may be used
   to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *
 */

/**
 * \example list.c
 * This example tests creating and using xrlist.
 * This example demonstrates use of xrlist_new(), xrlist_push(), xrlist_pop(), xrlist_shift(), xrlist_unshift() and xrlist_free_items().
 */

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




