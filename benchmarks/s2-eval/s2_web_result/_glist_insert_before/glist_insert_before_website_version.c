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
 * g_list_insert_before:
 * @list: a pointer to a #GList
 * @sibling: the list element before which the new element 
 *     is inserted or %NULL to insert at the end of the list
 * @data: the data for the new element
 *
 * Inserts a new element into the list before the given position.
 *
 * Returns: the new start of the #GList
 */
/*@
HeapPred H1_insb(GList a).
HeapPred H2_insb(GList a).
HeapPred G_insb(GList a).
*/

struct GList*
g_list_insert_before (struct GList* list,
		       struct GList* sibling,
		       int key)
/*@
  infer [H1_insb, H2_insb, G_insb]
  requires H1_insb(list) * H2_insb(sibling)
  ensures G_insb(res);
*/
{
  if (list == NULL)
    {
      list = g_list_alloc ();
      list->key = key;
      return list;
    }
  else if (sibling != NULL)
    {
      struct GList* node;

      node = g_list_alloc ();
      node->key = key;
      node->prev = sibling->prev;
      node->next = sibling;

      sibling->prev = node;
      if (node->prev != NULL)
	{
	  node->prev->next = node;
	  return list;
	}
      else
	{
	  return node;
	}
    }
  else
    {
      struct GList* last;

      last = g_list_last (list);

      last->next = g_list_alloc ();
      last->next->key = key;
      last->next->prev = last;
      last->next->next = NULL;

      return list;
    }
}
