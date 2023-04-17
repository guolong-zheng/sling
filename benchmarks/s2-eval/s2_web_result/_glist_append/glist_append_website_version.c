#include "stdhipmem.h"

/**
 * GList:
 * @data: holds the element's data, which can be a pointer to any kind
 *        of data, or any integer value using the <link
 *        linkend="glib-Type-Conversion-Macros">Type Conversion
 *        Macros</link>.
 * @next: contains the link to the next element in the list.
 * @prev: contains the link to the previous element in the list.
 *
 * The #GList struct is used for each element in a doubly-linked list.
 **/
struct GList {
  int key;
  struct GList* prev;
  struct GList* next;
};

struct GList*
g_list_alloc()
/*@
  requires true
  ensures res::GList<_,_,_>;
*/;

/**
 * g_list_last:
 * @list: a #GList
 *
 * Gets the last element in a #GList.
 *
 * Returns: the last element in the #GList, 
 *     or %NULL if the #GList has no elements
 */
/*@
HeapPred H_last(GList a).
HeapPred G_last(GList a, GList b).
*/
struct GList*
g_list_last (struct GList* list)
{
  if (list != NULL) {
    while (list->next != NULL)
    /*@
      infer[H_last, G_last]
      requires H_last(list)
      ensures G_last(list, list');
    */
    {
      list = list->next;
    }
  }

  return list;
}


/**
 * g_list_append:
 * @list: a pointer to a #GList
 * @data: the data for the new element
 *
 * Adds a new element on to the end of the list.
 *
 * <note><para>
 * The return value is the new start of the list, which 
 * may have changed, so make sure you store the new value.
 * </para></note>
 *
 * <note><para>
 * Note that g_list_append() has to traverse the entire list 
 * to find the end, which is inefficient when adding multiple 
 * elements. A common idiom to avoid the inefficiency is to prepend 
 * the elements and reverse the list when all elements have been added.
 * </para></note>
 *
 * |[
 * /&ast; Notice that these are initialized to the empty list. &ast;/
 * GList *list = NULL, *number_list = NULL;
 *
 * /&ast; This is a list of strings. &ast;/
 * list = g_list_append (list, "first");
 * list = g_list_append (list, "second");
 * 
 * /&ast; This is a list of integers. &ast;/
 * number_list = g_list_append (number_list, GINT_TO_POINTER (27));
 * number_list = g_list_append (number_list, GINT_TO_POINTER (14));
 * ]|
 *
 * Returns: the new start of the #GList
 */
 /*@
  HeapPred H_app(GList a).
  HeapPred G_app(GList a).
*/
struct GList*
g_list_append (struct GList* list,
                int key)
/*@
  infer [H_app, G_app]
  requires H_app(list)
  ensures G_app(res);
*/
{
  struct GList* new_list;
  struct GList* last;

  new_list = g_list_alloc();
  new_list->key = key;
  new_list->next = NULL;

  if (list != NULL)
    {
      last = list;

      last = g_list_last(list);
      last->next = new_list;
      new_list->prev = last;
     
      return list;
    }
  else
    {
      new_list->prev = NULL;
      return new_list;
    }
}

