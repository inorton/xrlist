#ifndef XRLIST_H
# define XRLIST_H

#include <stdlib.h>
#include <string.h>

/**
 * \class xrlist
 * A simple array like structure.
 * xrlist is implemented as a double linked list storing a pointer to an arbitrary data item. It provides push, pop, shift and unshift operations.
 */

/**
 * An xrlist item. 
 *
 * Simply contains a pointer to the parent list, a pointer to the
 * actual list payload and pointers to the next and preceeding list items in
 * this list. You need not allocate these directly.
 */ 
typedef struct xr_list_item_t {
  struct xr_list_item_t * next; /** The next item in this list, NULL if the first item */
  struct xr_list_item_t * prev; /** The previous item in this list, NULL if the last item */
  struct xr_list_t      * list; /** The parent list structure */
  void * object;                /** Pointer to the list item contents */
} xr_list_item_t;

/**
 * The actual xrlist structure. 
 *
 * This is used to identify the entire list aswell as track it's contents.
 */
typedef struct xr_list_t {
  struct xr_list_item_t * head; /** The first item in this list, NULL if no items are held */
  struct xr_list_item_t * tail; /** The last item in this list, NULL if no items are held */
  size_t count; /** The number of items in this list */
} xr_list_t;

/** Allocate a new xrlist object
 *
 * \return pointer to a new xrlist object
 */
xr_list_t *      xrlist_new( void );

/** \private 
 * Allocate a new xrlist item
 *
 * \return pointer to a new xrlist item 
 */
xr_list_item_t * xrlist_new_item ( void );

/** Free an xrlist object.
 * Does not free the object pointer of each list item.
 *
 * \param list Pointer to the xrlist to free
 */
void             xrlist_free( xr_list_t * list );

/** Free an xrlist object including all it's list items.
 * Also frees the object pointer of each list item.
 *
 * \param list Pointer to the xrlist to free
 * */
void             xrlist_free_items( xr_list_t * list);

/** \private
 * Free a single xrlist item.
 * Does not free the object pointer in this item.
 *
 * \param item Pointer to the xrlist item to free
 */
void             xrlist_free_item( xr_list_item_t * item );

/**
 * Add a new item to the end of list containing a pointer to object
 *
 * \param list Pointer to the xrlist to add an item to
 * \param object Pointer to the memory/object to be stored in the list
 *
 * \return A pointer to the xrlist item now containing object
 */
xr_list_item_t * xrlist_push( xr_list_t * list, void * object );

/**
 * Remove the last item in list 
 *
 * \param list Pointer to the xrlist to remove an item from
 *
 * \return A pointer to the memory/object stored in the list item just removed
 */
void *           xrlist_pop( xr_list_t * list );

/**
 * Add a new item to the start of list containing a pointer to object
 *
 * \param list Pointer to the xrlist to add an item to
 * \param object Pointer to the memory/object to be stored in the list
 *
 * \return A pointer to the xrlist item now containing object
 */
xr_list_item_t * xrlist_unshift( xr_list_t * list, void * object );

/**
 * Remove the first itemm in list
 *
 * \param list Pointer to the xrlist to remove an item from
 *
 * \return A pointer to the memory/object stored in the list item just removed
 */
void *           xrlist_shift( xr_list_t * list );

/**
 * Insert a new list item after prev
 *
 * \param item Pointer to the xrlist item you wish to add after
 * \param object Pointer to the memory/object to be stored in the list after item
 *
 * \return A pointer to the xr_list_item_t just created.
 * \return NULL if unable to allocate a new xr_list_item_t.
 */
xr_list_item_t * xrlist_insert_after( xr_list_item_t * item , void * object );

#endif
