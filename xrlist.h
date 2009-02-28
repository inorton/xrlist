#ifndef XRLIST_H
# define XRLIST_H

#include <stdlib.h>
#include <string.h>

struct xr_list_item_t {
  struct xr_list_item_t * next;
  struct xr_list_item_t * prev;
  struct xr_list_t      * list;
  void * object;
};

struct xr_list_t {
  struct xr_list_item_t * head;
  struct xr_list_item_t * tail;
  size_t count;
};

typedef struct xr_list_item_t xr_list_item_t;
typedef struct xr_list_t      xr_list_t;

extern xr_list_t *      xrlist_new( void );
extern xr_list_item_t * xrlist_new_item ( void );

extern void             xrlist_free( xr_list_t * list );
extern void             xrlist_free_items( xr_list_t * list);
extern void             xrlist_free_item( xr_list_item_t * item );

extern xr_list_item_t * xrlist_push( xr_list_t * list, void * object );
extern void *           xrlist_pop( xr_list_t * list );

extern xr_list_item_t * xrlist_unshift( xr_list_t * list, void * object );
extern void *           xrlist_shift( xr_list_t * list );



#endif
