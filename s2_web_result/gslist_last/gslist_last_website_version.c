//#include "config.h"
#include "stdhipmem.h"
//#include "gslist.h"
//#include "gtestutilsmem.h"
/**
 * GSList:
 * @data: holds the element's data, which can be a pointer to any kind
 *        of data, or any integer value using the <link
 *        linkend="glib-Type-Conversion-Macros">Type Conversion
 *        Macros</link>.
 * @next: contains the link to the next element in the list.
 *
 * The #GSList struct is used for each element in the singly-linked
 * list.
 **/
struct GSList {
  int val;
  struct GSList* next;
};


/**
 * g_slist_alloc:
 * @Returns: a pointer to the newly-allocated #GSList element.
 *
 * Allocates space for one #GSList element. It is called by the
 * g_slist_append(), g_slist_prepend(), g_slist_insert() and
 * g_slist_insert_sorted() functions and so is rarely used on its own.
 **/
struct GSList*
_g_slist_alloc (void)
/*@
  requires true
  ensures res::GSList<_,_>;
*/
{
  //return _g_slist_alloc0 ();
  return malloc(sizeof(struct GSList));
}

/**
 * g_slist_last:
 * @list: a #GSList
 *
 * Gets the last element in a #GSList.
 *
 * <note><para>
 * This function iterates over the whole list.
 * </para></note>
 *
 * Returns: the last element in the #GSList,
 *     or %NULL if the #GSList has no elements
 */
 /*@
HeapPred H_last(GSList a).
HeapPred G_last(GSList a, GSList b).
*/

struct GSList*
 g_slist_last (struct GSList *list)
{
  if (list)
    {
      while (list->next)
	  /*@
          infer[H_last, G_last]
          requires H_last(list)
          ensures G_last(list, list');
        */
        list = list->next;
    }

  return list;
}


