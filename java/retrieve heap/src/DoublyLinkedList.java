/*

 *  Java Program to Implement Doubly Linked List

 */


import java.util.Scanner;

/* Class DoublyLinkedList */
public class DoublyLinkedList

{
    public static void main(String[] args)
    {
        DlLinkedList list = new DlLinkedList();

        list.insertAtStart(5);
        list.insertAtEnd(10);
        list.insertAtPos(2, 25);
        list.deleteAtPos(2);

        list.traverse();
    }
}
    /*  Class DlNode  */
class DlNode
{
    public int data;

    public DlNode next, prev;

    /* Constructor */
    public DlNode()

    {
        next = null;

        prev = null;

        data = 0;

    }

        /* Constructor */

    public DlNode(int d, DlNode n, DlNode p)
    {
        data = d;
        next = n;
        prev = p;
    }

    /* Function to set link to next node */
    public void setLinkNext(DlNode n)
    {
        next = n;
    }

    /* Function to set link to previous node */
    public void setLinkPrev(DlNode p)
    {
        prev = p;
    }

        /* Funtion to get link to next node */
    public DlNode getLinkNext()
    {
        return next;
    }

        /* Function to get link to previous node */
    public DlNode getLinkPrev()
    {
        return prev;
    }

        /* Function to set data to node */
    public void setData(int d)
    {
        data = d;
    }

        /* Function to get data from node */

    public int getData()
    {
        return data;
    }

}

/* Class linkedList */

class DlLinkedList {

    public DlNode start;

    public DlNode end;

    public int size;

        /* Constructor */

    public DlLinkedList()
    {
        start = null;

        end = null;

        size = 0;
    }

        /* Function to check if list is empty */

    public boolean isEmpty()
    {
        return start == null;
    }

        /* Function to get size of list */
    public int getSize()
    {
        return size;
    }

        /* Function to insert element at begining */
    public void insertAtStart(int val)
    {
        HeapCollector.collectMemory("dll/insertAtStart", "pre|130", new Object[]{start, end}, "start", "end");
        DlNode nptr = new DlNode(val, null, null);
        if (start == null)
        {
            start = nptr;
            end = start;
        } else
        {
            start.setLinkPrev(nptr);
            nptr.setLinkNext(start);
            start = nptr;
        }
        size++;
        HeapCollector.collectMemory("dll/insertAtStart", "post|143", new Object[]{start, end, nptr}, "start", "end", "nptr");
    }

        /* Function to insert element at end */
    public void insertAtEnd(int val)
    {
        HeapCollector.collectMemory("dll/insertAtEnd", "pre|150", new Object[]{start, end}, "start", "end");
        DlNode nptr = new DlNode(val, null, null);
        if (start == null)
        {
            start = nptr;
            end = start;
        } else
        {
            nptr.setLinkPrev(end);
            end.setLinkNext(nptr);
            end = nptr;
        }
        size++;
        HeapCollector.collectMemory("dll/insertAtEnd", "post|163", new Object[]{start, end, nptr}, "start", "end", "nptr");
    }

        /* Function to insert element at position */
    public void insertAtPos(int val, int pos)
    {
        HeapCollector.collectMemory("dll/insertAtPos", "pre|168", new Object[]{start, end}, "start", "end");
        DlNode nptr = new DlNode(val, null, null);
        if (pos == 1)
        {
            insertAtStart(val);
            return;
        }
        DlNode ptr = start;
        for (int i = 2; i <= size; i++)
        {
            HeapCollector.collectMemory("dll/insertAtPos", "loop|178", new Object[]{start, end, ptr}, "start", "end", "ptr");
            if (i == pos)
            {
                DlNode tmp = ptr.getLinkNext();
                ptr.setLinkNext(nptr);
                nptr.setLinkPrev(ptr);
                nptr.setLinkNext(tmp);
                tmp.setLinkPrev(nptr);
            }
            ptr = ptr.getLinkNext();
        }
        size++;
        HeapCollector.collectMemory("dll/insertAtPos", "post|190", new Object[]{start, end, ptr}, "start", "end", "ptr");

    }

        /* Function to delete node at position */
    public void deleteAtPos(int pos)
    {
        HeapCollector.collectMemory("dll/deleteAtPos", "pre|197", new Object[]{start, end}, "start", "end");
        if (pos == 1)
        {
            if (size == 1)
            {
                start = null;
                end = null;
                size = 0;
                HeapCollector.collectMemory("dll/deleteAtPos", "post|130", new Object[]{start, end}, "start", "end");
                return;
            }
            start = start.getLinkNext();
            start.setLinkPrev(null);
            size--;
            HeapCollector.collectMemory("dll/deleteAtPos", "post|211", new Object[]{start, end}, "start", "end");
            return;
        }
        if (pos == size)
        {
            end = end.getLinkPrev();
            end.setLinkNext(null);
            size--;
        }
        DlNode ptr = start.getLinkNext();
        for (int i = 2; i <= size; i++)
        {
            HeapCollector.collectMemory("dll/deleteAtPos", "loop|223", new Object[]{start, end, ptr}, "start", "end","ptr");
            if (i == pos)
            {
                DlNode p = ptr.getLinkPrev();
                DlNode n = ptr.getLinkNext();
                p.setLinkNext(n);
                n.setLinkPrev(p);
                size--;
                HeapCollector.collectMemory("dll/deleteAtPos", "post|231", new Object[]{start, end,ptr, p, n}, "start", "end", "ptr","p","n");
                return;
            }
            ptr = ptr.getLinkNext();
        }

    }

        /* Function to display status of list */
    public void traverse()
    {
        HeapCollector.collectMemory("dll/traverse", "pre|242", new Object[]{start, end}, "start", "end");
        if (size == 0)
        {
            HeapCollector.collectMemory("dll/traverse", "post|245", new Object[]{start, end}, "start", "end");
            return;
        }
        if (start.getLinkNext() == null)
        {
            HeapCollector.collectMemory("dll/traverse", "post|250", new Object[]{start, end}, "start", "end");
            return;
        }
        DlNode ptr = start;
        ptr = start.getLinkNext();
        while (ptr.getLinkNext() != null)
        {
            HeapCollector.collectMemory("dll/traverse", "loop|257", new Object[]{start, end,ptr}, "start", "end","ptr");
            ptr = ptr.getLinkNext();
        }
        HeapCollector.collectMemory("dll/traverse", "post|260", new Object[]{start, end,ptr}, "start", "end","ptr");
    }
}
