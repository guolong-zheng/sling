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
 * g_list_concat:
 * @list1: a #GList
 * @list2: the #GList to add to the end of the first #GList
 *
 * Adds the second #GList onto the end of the first #GList.
 * Note that the elements of the second #GList are not copied.
 * They are used directly.
 *
 * Returns: the start of the new #GList
 */
/*@
HeapPred H1_concat(GList a).
HeapPred H2_concat(GList a).
HeapPred G_concat(GList a).
*/
struct GList*
g_list_concat (struct GList* list1,
                struct GList* list2)
/*@
  infer [H1_concat, H2_concat, G_concat]
  requires H1_concat(list1) * H2_concat(list2)
  ensures G_concat(res);
*/
{
  struct GList* tmp_list;

  if (list2 != NULL)
    {
      tmp_list = g_list_last (list1);
      if (tmp_list != NULL) {
	tmp_list->next = list2;
      }
      else
	list1 = list2;
      list2->prev = tmp_list;
    }

  return list1;
}
