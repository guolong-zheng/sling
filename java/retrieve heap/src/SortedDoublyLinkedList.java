import java.util.Scanner;



/*  Class SdlNode  */

class SdlNode
{
    public int data;
    public SdlNode next, prev;

    /* Constructor */
    public SdlNode()
    {
        next = null;
        prev = null;
        data = 0;
    }

    /* Constructor */
    public SdlNode(int d, SdlNode n, SdlNode p)
    {
        data = d;
        next = n;
        prev = p;
    }

    /* Function to set link to next node */

    public void setLinkNext(SdlNode n)
    {
        next = n;
    }

    /* Function to set link to previous node */
    public void setLinkPrev(SdlNode p)
    {
        prev = p;
    }

    /* Funtion to get link to next node */
    public SdlNode getLinkNext()
    {
        return next;
    }

    /* Function to get link to previous node */
    public SdlNode getLinkPrev()
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



/* Class sdlinkedList */
class sdlinkedList
{
    public SdlNode start;
    public int size;
    /* Constructor */
    public sdlinkedList()
    {
        start = null;
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

    /* Function to insert element */
    public void insert(int val)
    {
        HeapCollector.collectMemory("sdl/insert", "pre|95", new Object[]{start}, "start");
        SdlNode nptr = new SdlNode(val, null, null);
        SdlNode tmp, ptr;
        boolean ins = false;
        if(start == null)
            start = nptr;
        else if (val <= start.getData()) {
            nptr.setLinkNext(start);
            start.setLinkPrev(nptr);
            start = nptr;
        } else {
            tmp = start;
            ptr = start.getLinkNext();
            while(ptr != null)
            {
                HeapCollector.collectMemory("sdl/insert", "loop|110", new Object[]{start,tmp,ptr,nptr}, "start","tmp","ptr","nptr");
                if(val >= tmp.getData() && val <= ptr.getData())
                {
                    tmp.setLinkNext(nptr);
                    nptr.setLinkPrev(tmp);
                    nptr.setLinkNext(ptr);
                    ptr.setLinkPrev(nptr);
                    ins = true;
                    break;
                }
                else
                {
                    tmp = ptr;
                    ptr = ptr.getLinkNext();
                }
            }
            if(!ins)
            {
                tmp.setLinkNext(nptr);
                nptr.setLinkPrev(tmp);
            }
        }
        size++;
        HeapCollector.collectMemory("sdl/insert", "post|133", new Object[]{start,nptr}, "start","nptr");
    }

    /* Function to delete node at position */

    public void deleteAtPos(int pos)
    {
        HeapCollector.collectMemory("sdl/deleteAtPos", "pre|140", new Object[]{start}, "start");
        if (pos == 1) {
            if (size == 1) {
                start = null;
                size = 0;
                HeapCollector.collectMemory("sdl/deleteAtPos", "post|147", new Object[]{start}, "start");
                return;
            }
            start = start.getLinkNext();
            start.setLinkPrev(null);
            size--;
            HeapCollector.collectMemory("sdl/deleteAtPos", "post|153", new Object[]{start}, "start");
            return;
        }
        if (pos == size)
        {
            SdlNode ptr = start;
            for (int i = 1; i < size - 1; i++) {
                HeapCollector.collectMemory("sdl/deleteAtPos", "loop|158", new Object[]{start, ptr}, "start", "ptr");
                ptr = ptr.getLinkNext();
            }
            ptr.setLinkNext(null);
            size --;
            HeapCollector.collectMemory("sdl/deleteAtPos", "post|163", new Object[]{start, ptr}, "start","ptr");
            return;
        }
        SdlNode ptr = start.getLinkNext();
        for (int i = 2; i <= size; i++)
        {
            HeapCollector.collectMemory("sdl/deleteAtPos", "loop|169", new Object[]{start, ptr}, "start", "ptr");
            if (i == pos)
            {
                SdlNode p = ptr.getLinkPrev();
                SdlNode n = ptr.getLinkNext();
                p.setLinkNext(n);
                n.setLinkPrev(p);
                size-- ;
                HeapCollector.collectMemory("sdl/deleteAtPos", "post|177", new Object[]{start,ptr,p,n}, "start","ptr","p","n");
                return;
            }
            ptr = ptr.getLinkNext();
        }
        HeapCollector.collectMemory("sdl/deleteAtPos", "post|182", new Object[]{start, ptr}, "start", "ptr");
    }

    /* Function to display status of list */
    public void traverse()
    {
        HeapCollector.collectMemory("sdl/traverse", "pre|188", new Object[]{start}, "start");
        if (size == 0)
        {
            HeapCollector.collectMemory("sdl/traverse", "post|191", new Object[]{start}, "start");
            return;
        }
        if (start.getLinkNext() == null)
        {
            HeapCollector.collectMemory("sdl/traverse", "post|196", new Object[]{start}, "start");
            return;
        }

        SdlNode ptr = start;
        ptr = start.getLinkNext();
        while (ptr.getLinkNext() != null)
        {
            HeapCollector.collectMemory("sdl/traverse", "loop|204", new Object[]{start, ptr}, "start", "ptr");
            ptr = ptr.getLinkNext();
        }
        HeapCollector.collectMemory("sdl/traverse", "post|207", new Object[]{start, ptr}, "start", "ptr");
    }
}



/* Class SortedDoublyLinkedList */

public class SortedDoublyLinkedList
{
    public static void main(String[] args)
    {
        sdlinkedList list = new sdlinkedList();
        list.insert(2);
        list.deleteAtPos(1);
        list.traverse();
    }
}
