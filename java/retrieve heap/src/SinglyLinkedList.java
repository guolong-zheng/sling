import java.io.IOException;

public class SinglyLinkedList<T> {

    public SlNode<T> head;
    public SlNode<T> tail;

    public void add(T element){
        HeapCollector.collectMemory("sll/add.txt","pre|9",new Object[]{head,tail},"head","tail");
        SlNode<T> nd = new SlNode<T>();
        nd.setValue(element);
        /**
         * check if the list is empty
         */
        if(head == null){
            //since there is only one element, both head and 
            //tail points to the same object.
            head = nd;
            tail = nd;
        } else {
            //set current tail next link to new node
            tail.setNextRef(nd);
            //set tail as newly created node
            tail = nd;
        }
        HeapCollector.collectMemory("sll/add.txt","post|26",new Object[]{head,tail},"head","tail");
    }

    public void addAfter(T element, T after){
        HeapCollector.collectMemory("sll/addAfter.txt","pre|30",new Object[]{head,tail},"head","tail");
        SlNode<T> tmp = head;
        SlNode<T> refNode = null;
        /**
         * Traverse till given element
         */
        while(true){
            HeapCollector.collectMemory("sll/addAfter.txt","loop|37",new Object[]{head,tail,tmp},"head","tail","tmp");
            if(tmp == null){
                break;
            }
            if(tmp.compareTo(after) == 0){
                //found the target node, add after this node
                refNode = tmp;
                break;
            }
            tmp = tmp.getNextRef();
        }

        SlNode<T> nd = null;
        if(refNode != null){
            //add element after the target node
            nd = new SlNode<T>();
            nd.setValue(element);
            nd.setNextRef(tmp.getNextRef());
            if(tmp == tail){
                tail = nd;
            }
            tmp.setNextRef(nd);
        }

        HeapCollector.collectMemory("sll/addAfter.txt","post|62",new Object[]{head,tail,tmp,refNode, nd},"head","tail","tmp","refNode", "nd");
    }

    public void deleteFront(){
        HeapCollector.collectMemory("sll/deleteFront.txt","pre|65",new Object[]{head,tail},"head","tail");
        if(head == null){
            return;
        }
        SlNode<T> tmp = head;
        head = tmp.getNextRef();
        if(head == null){
            tail = null;
        }
        HeapCollector.collectMemory("sll/deleteFront.txt","post|74",new Object[]{head,tail,tmp},"head","tail","tmp");
    }

    public void deleteAfter(T after){
        HeapCollector.collectMemory("sll/deleteAfter.txt","pre|79",new Object[]{head,tail},"head","tail");
        SlNode<T> tmp = head;
        SlNode<T> refNode = null;
        /**
         * Traverse till given element
         */
        while(true){
            HeapCollector.collectMemory("sll/deleteAfter.txt","loop|85",new Object[]{head,tail,tmp},"head","tail","tmp");
            if(tmp == null){
                break;
            }
            if(tmp.compareTo(after) == 0){
                //found the target node, add after this node
                refNode = tmp;
                break;
            }
            tmp = tmp.getNextRef();
        }
        if(refNode != null){
            tmp = refNode.getNextRef();
            refNode.setNextRef(tmp.getNextRef());
            if(refNode.getNextRef() == null){
                tail = refNode;
            }
        }
        HeapCollector.collectMemory("sll/deleteAfter.txt","post|103",new Object[]{head,tail,tmp},"head","tail","tmp");
    }

    public void traverse() {
        HeapCollector.collectMemory("sll/traverse.txt", "pre|106", new Object[]{head, tail}, "head", "tail" );
        SlNode<T> tmp = head;
        while(true){
            HeapCollector.collectMemory("sll/traverse.txt", "loop|109", new Object[]{tmp, head, tail}, "tmp", "head", "tail");
            if(tmp == null){
                break;
            }
            tmp = tmp.getNextRef();
        }
        HeapCollector.collectMemory("sll/traverse.txt", "post|116", new Object[]{tmp, head, tail}, "tmp", "head", "tail");
    }

    public static void main(String a[]) throws IOException {
        SinglyLinkedList<Integer> sl = new SinglyLinkedList<Integer>();
        sl.add(3);
        sl.add(32);
        sl.add(54);
        sl.add(89);
        sl.add(100);
        sl.add(50);
        sl.addAfter(76, 54);
        //sl.deleteFront();
        //sl.deleteAfter(76);
        //sl.traverse();
        sl.traverse();
    }
}

class SlNode<T> implements Comparable<T> {

    public T value;
    public SlNode<T> nextRef;

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public SlNode<T> getNextRef() {
        return nextRef;
    }

    public void setNextRef(SlNode<T> ref) {
        this.nextRef = ref;
    }

    @Override
    public int compareTo(T arg) {
        if (arg == this.value) {
            return 0;
        } else {
            return 1;
        }
    }
}