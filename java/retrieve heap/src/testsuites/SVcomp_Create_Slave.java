package testsuites;

public class SVcomp_Create_Slave {
    static Slave dll_create_slave(int n)
    {
        //pre
        Slave dll = null;
        //dll = dll_insert_slave(dll);
        //dll = dll_insert_slave(dll);
        while(n > 0)
        {
            //loop
            n--;
            dll = insert_slave(dll);
        }
        //post
        return dll;
    }

    static Slave insert_slave(Slave x)
    {
        Slave item = new Slave();

        item.next = null;
        item.prev = null;

        Slave next = x;
        item.next = next;
        if (next != null) {
            next.prev = item;
        }
        return item;
    }

    public static void main(String args[]){
        dll_create_slave(10);
    }

}

class Slave{
    Slave next;
    Slave prev;
}
