import java.util.LinkedList;
import java.util.List;

public class HeapNode {
    protected String type;
    protected String name;
    protected List<String> fieldsByName;

    public HeapNode(String type, String name) {
        this.type = type;
        this.name = name;
    }

    public HeapNode(String type, String name, List<String> fieldsByName) {
        this.type = type;
        this.name = name;
        this.fieldsByName = new LinkedList<>();
        this.fieldsByName.addAll(fieldsByName);
    }

    public String getName() {
        return name;
    }


    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(name + "-> (");
        for (String s : fieldsByName) {
            sb.append(s + ",");
        }
        sb.append(")");
        return sb.toString();
    }
}