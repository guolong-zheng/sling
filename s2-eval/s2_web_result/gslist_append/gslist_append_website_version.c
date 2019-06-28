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

/**
 * g_slist_append:
 * @list: a #GSList
 * @data: the data for the new element
 *
 * Adds a new element on to the end of the list.
 *
 * <note><para>
 * The return value is the new start of the list, which may
 * have changed, so make sure you store the new value.
 * </para></note>
 *
 * <note><para>
 * Note that g_slist_append() has to traverse the entire list
 * to find the end, which is inefficient when adding multiple
 * elements. A common idiom to avoid the inefficiency is to prepend
 * the elements and reverse the list when all elements have been added.
 * </para></note>
 *
 * |[
 * /&ast; Notice that these are initialized to the empty list. &ast;/
 * GSList *list = NULL, *number_list = NULL;
 *
 * /&ast; This is a list of strings. &ast;/
 * list = g_slist_append (list, "first");
 * list = g_slist_append (list, "second");
 *
 * /&ast; This is a list of integers. &ast;/
 * number_list = g_slist_append (number_list, GINT_TO_POINTER (27));
 * number_list = g_slist_append (number_list, GINT_TO_POINTER (14));
 * ]|
 *
 * Returns: the new start of the #GSList
 */

 /*@
  HeapPred H_app(GSList a).
  HeapPred G_app(GSList a).
*/

struct GSList*
g_slist_append (struct GSList   *list,
                int  val)
/*@
  infer [H_app, G_app]
  requires H_app(list)
  ensures G_app(res);
*/
{
  struct GSList *new_list;
  struct GSList *last;

  new_list = _g_slist_alloc ();
  new_list->val = val;
  new_list->next = NULL;

  if (list)
    {
      last = g_slist_last (list);
      /* g_assert (last != NULL); */
      last->next = new_list;

      return list;
    }
  else
    return new_list;
}
