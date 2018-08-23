import java.util.HashSet;
import java.util.Set;

public class Heap {
    HeapNode root;  //root of current heap
    Set<HeapNode> heapNodes;

    public Heap() {
        this.root = null;
        this.heapNodes = new HashSet<>();
    }

    public void addNode(HeapNode heapNode) {
        this.heapNodes.add(heapNode);
        if (this.root == null)
            this.root = heapNode;
    }

    public boolean contains(String addr){
        for(HeapNode hn : heapNodes){
            if(hn.getName().equals(addr))
                return true;
        }
        return false;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (HeapNode hn : heapNodes) {
            sb.append(hn.toString() + "\n");
        }
        return sb.toString();
    }
}
