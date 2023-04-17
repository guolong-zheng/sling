
/*
 * HIP/SLEEK standard library for C program
 * 
 * Created: Oct. 31, 2013.
 */
typedef
struct backing_file {
  int file_id;
} BackingFile;

typedef
/*D_tag mem_reg */
struct mem_reg {
  BackingFile * file;
  int file_offset;
  int file_size;
  int start_address;
  int size;
  struct mem_reg * prev;
  struct mem_reg * next;
} MemReg;

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(MemReg * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;

struct GList {
  int key;
  struct GList* prev;
  struct GList* next;
};


/* lseg<p> == self=p */
/*   or self::GSList<_,n> * n::lseg<p> & self!=null; */

/*@
dlseg<y> == self=y
  or self::GList<_,_,n> * n::dlseg<y> & self!=null;
*/


/* struct GSList* */
/* g_slist_last (struct GSList* list) */
/* /\*@ */
/*  case { list=null -> ensures res=null; */
/*    list!=null -> */
/*      requires list::lseg<l> * l::GSList<a,null> */
/*   ensures list::lseg<res> * res::GSList<a,null>; */
/* } */
/* *\/ */
/* ; */

/* struct GSList* */
/* g_slist_append (struct GSList* list, */
/*                 int val) */
/* /\*@ */
/*  case { */
/*   list=null -> ensures res::GSList<key, null>; */
/*   list!=null -> requires list::lseg<null> */
/*     ensures list::lseg<q>*q::GSList<key, null>; */
/* } */
/* *\/; */

/* struct GSList* */
/* g_slist_prepend (struct GSList* list, */
/*                  int val) */
/* /\*@ */
/*   requires list::lseg<p> */
/*   ensures res::GSList<key,list> * list::lseg<p>; */
/* *\/; */

/* struct GSList* */
/* g_slist_nth (struct GSList *list, */
/*              int n) */
/* /\*@ */
/*    case { */
/*   list=null -> ensures res=null; */
/*   list!=null -> requires list::lseg<null> ensures res::lseg<null> & res!=null; */
/* } */
/* *\/; */

struct GList*
g_list_last (struct GList* list)
/*@
case {
  list=null -> ensures res=null;
  list!=null ->
    requires list::dlseg<l> * l::GList<a,_,null>
    ensures list::dlseg<res> * res::GList<a,_,null>;
}
*/;

/* struct GList* */
/* g_list_append (struct GList* list, */
/*                int key) */
/* /\*@ */
/* case { */
/*   list=null -> ensures res::GList<key, null, null>; */
/*   list!=null -> */
/*     requires list::dlseg<null> */
/*     ensures res::dlseg<q> * q::GList<key,_,null>; */
/* } */
/* *\/; */

/* struct GList* */
/* g_list_prepend (struct GList* list, */
/*                 int key) */
/* /\*@ */
/*   requires list::dlseg<p> */
/*   ensures res::GList<key,null,list> * list::dlseg<p>; */
/* *\/; */

/* struct GList* */
/* g_list_nth (struct GList* list, */
/* 	    int n) */
/* /\*@ */
/* case { */
/*   list=null -> ensures res=null; */
/*   list!=null -> requires list::dlseg<null> ensures res::dlseg<null> & res!=null; */
/* } */
/* *\/; */


int random()
/*@
  requires true
  ensures true;
*/;
