package collector;

import java.lang.reflect.Field;
import java.util.*;

public class HeapCollector {

    public static void collectMemory(String filename, String loc, Object[] objs, String... names) {
        Memory mem = retrieveMem(objs, names);
        mem.writeToFile(loc, filename);
        mem.print();
    }

    public static Memory retrieveMem(Object[] objs, String... names){
        Heap stack = new Heap();
        Heap heap = new Heap();
        Queue<Object> toVisit = new LinkedList<>();
        for(int i = 0; i < objs.length; i++){
            HeapNode hn;
            if(objs[i] == null)
                hn = new HeapNode(names[i], "nil");
            else {
                hn = new HeapNode(names[i], normalize(objs[i].toString()));
                toVisit.add(objs[i]);
            }
            stack.addNode(hn);
        }
        heap = retrieveHeap(heap, toVisit);

        return new Memory(stack, heap);
    }

    public static Heap retrieveHeap(Heap heap, Queue<Object> toVisit) {
        while (!toVisit.isEmpty()) {
            List<String> fields = new LinkedList<>();
            Object var = toVisit.remove();
            Class cal = var.getClass();
            if (!heap.contains(normalize(var.toString()))) {
                for (Field field : cal.getFields()) {
                    String type = field.getType().toString();
                    Object newVar = null;
                    try {
                        newVar = field.get(var);
                    } catch (IllegalAccessException e) {
                        e.printStackTrace();
                    }
                    if (newVar == null)
                        fields.add(field.getName() + ":" + "nil");
                    else {
                        if(type.contains("Object"))
                            type = type.replace("java.lang.Object","int");
                        //fields.add(type.replace("class ", "") + "|" + normalize(newVar.toString()));
                        fields.add(field.getName() + ":" + normalize(newVar.toString()));
                        if (!isPrim(type) && !heap.contains(normalize(newVar.toString()))) {
                            toVisit.add(newVar);
                        }
                    }
                }
                heap.addNode(new HeapNode(cal.getTypeName(), normalize(var.toString()), fields));
            }
        }

        return heap;
    }

    public static boolean isPrim(String type) {
        if (type.equals("boolean") || type.equals("byte") || type.equals("char") ||
                type.equals("double") || type.equals("float") || type.contains("int") ||
                type.equals("long") || type.equals("short") || type.contains("Object"))
            return true;
        else
            return false;
    }

    public static String normalize(String value){
        if(value.contains("@"))
            return "0x" + value.substring(value.indexOf("@") + 1);
        else
            return value;
    }
}