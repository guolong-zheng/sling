import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Memory {
    Heap stack;
    Heap heap;

    public Memory(Heap stack, Heap heap){
        this.stack = stack;
        this.heap = heap;
    }

    public void writeToFile(String loc, String fileName) {
        FileWriter fw = null;
        BufferedWriter writer = null;
        try {
            fw = new FileWriter(fileName, true);
            writer = new BufferedWriter(new FileWriter(fileName, true));
            writer.append(loc + "\n");
            writer.append("stack:\n");
            for(HeapNode hn : stack.heapNodes){
                writer.append(hn.type + " " + hn.name + "\n");
            }
            writer.append("heap:\n");
            for(HeapNode hn : heap.heapNodes){
                writer.append(hn.type + "|" + hn.name + " ");
                for(String s : hn.fieldsByName){
                    writer.append(s + " ");
                }
                writer.append("\n");
            }
            writer.append("end\n");
        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                fw.close();
                writer.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void print(){
        StringBuffer sb = new StringBuffer();
        sb.append("Stack:\n");
        for(HeapNode hn : stack.heapNodes){
            sb.append(hn.type + " " + hn.name + "\n");
        }
        sb.append("Heap:\n");
        for(HeapNode hn : heap.heapNodes){
            sb.append(hn.name + " ");
            for(String s : hn.fieldsByName){
                sb.append(s + " ");
            }
            sb.append("\n");
        }

        System.out.println(sb.toString());
    }
}
