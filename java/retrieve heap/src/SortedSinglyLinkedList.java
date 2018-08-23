/*

 *  Java Program to Implement Sorted Singly Linked List

 */
    /*  Class SllNode  */

class SllNode
{
    public int data;
    public SllNode next;
        /*  Constructor  */
    public SllNode()
    {
        next = null;
        data = 0;
    }
        /*  Constructor  */
    public SllNode(int d, SllNode n)
    {
        data = d;
        next = n;
    }

        /*  Function to set link to next SllNode  */
    public void setLink(SllNode n)
    {
        next = n;
    }

        /*  Function to set data to current SllNode  */
    public void setData(int d)
    {
        data = d;
    }    

        /*  Function to get link to next node  */
    public SllNode getLink()
    {
        return next;
    }    

        /*  Function to get data from current SllNode  */
    public int getData()
    {
        return data;
    }

}

class SllLinkedList
{
    public SllNode start;
    public int size;

    public SllLinkedList()
    {
        start = null;
        size = 0;
    }

        /*  Function to check if list is empty  */
    public boolean isEmpty()
    {
        return start == null;
    }

        /*  Function to check size of list  */
    public int getSize()
    {
        return size;
    }    

        /*  Function to insert an element  */
    public void insert(int val)
    {
        HeapCollector.collectMemory("sls/insert", "pre|77", new Object[]{start}, "start");
        SllNode nptr, ptr, tmp = null;
        nptr = new SllNode(val, null);
        boolean ins = false;
        if (start == null)
            start = nptr;
        else if (val <= start.getData())
        {
            nptr.setLink(start);
            start = nptr;
        } else {
            tmp = start;
            ptr = start.getLink();
            while (ptr != null)
            {
                HeapCollector.collectMemory("sls/insert", "loop|92", new Object[]{start,tmp,ptr,nptr}, "start","tmp","ptr","nptr");
                if (val >= tmp.getData() && val <= ptr.getData())
                {
                    tmp.setLink(nptr);
                    nptr.setLink(ptr);
                    ins = true;
                    break;
                } else {
                    tmp = ptr;
                    ptr = ptr.getLink();
                }
            }
            if (ins == false)
            {
                tmp.setLink(nptr);
            }
        }
        size++;
        HeapCollector.collectMemory("sls/insert", "post|110", new Object[]{start,tmp,nptr}, "start","tmp","nptr");
    }

        /*  Function to delete an element at position  */
    public void deleteAtPos(int pos)
    {
        HeapCollector.collectMemory("sls/deleteAtPos", "pre|116", new Object[]{start}, "start");
        if (pos == 1)
        {
            start = start.getLink();
            size--;
            HeapCollector.collectMemory("sls/deleteAtPos", "post|121", new Object[]{start}, "start");
            return;
        }
        if (pos == size)
        {
            SllNode ptr = start;
            for (int i = 1; i < size - 1; i++)
                HeapCollector.collectMemory("sls/deleteAtPos", "loop|128", new Object[]{start,ptr}, "start","ptr");
                ptr = ptr.getLink();
            ptr.setLink(null);
            size--;
            HeapCollector.collectMemory("sls/deleteAtPos", "post|132", new Object[]{start,ptr}, "start","ptr");
            return;
        }

        SllNode ptr = start;
        pos = pos - 1;
        for (int i = 1; i < size - 1; i++)
        {
            HeapCollector.collectMemory("sls/deleteAtPos", "loop|140", new Object[]{start,ptr}, "start","ptr");
            if (i == pos)
            {
                SllNode tmp = ptr.getLink();
                tmp = tmp.getLink();
                ptr.setLink(tmp);
                break;
            }
            ptr = ptr.getLink();
        }
        size--;
        HeapCollector.collectMemory("sls/deleteAtPos", "post|151", new Object[]{start,ptr}, "start","ptr");
    }    

        /*  Function to display elements  */

    public void traverse()
    {
        HeapCollector.collectMemory("sls/traverse", "pre|158", new Object[]{start}, "start");
        if (size == 0)
        {
            HeapCollector.collectMemory("sls/traverse", "post|161", new Object[]{start}, "start");
            return;
        }
        if (start.getLink() == null)
        {
            HeapCollector.collectMemory("sls/traverse", "post|166", new Object[]{start}, "start");
            return;
        }

        SllNode ptr = start;
        ptr = start.getLink();

        while (ptr.getLink() != null) {
            HeapCollector.collectMemory("sls/traverse", "loop|174", new Object[]{start, ptr}, "start", "ptr");
            ptr = ptr.getLink();
        }
        HeapCollector.collectMemory("sls/traverse", "post|177", new Object[]{start,ptr}, "start","ptr");
    }

}

public class SortedSinglyLinkedList
{
    public static void main(String[] args)
    {
        SllLinkedList list = new SllLinkedList();
        list.traverse();
        list.insert(5);
        list.insert(8);
        list.insert(15);
        list.insert(12);
        list.insert(7);
        list.deleteAtPos(1);
        list.deleteAtPos(3);
        list.traverse();
    }

}
