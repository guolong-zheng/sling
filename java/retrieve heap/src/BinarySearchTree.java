
public class BinarySearchTree<A extends Comparable<A>, B> {
    static class Node<A extends Comparable<A>, B> {
        public A key;
        public B value;
        public Node<A, B> left;
        public Node<A, B> right;
        public Node<A, B> parent;

        public Node(A key, B value, Node<A, B> parent) {
            this.key = key;
            this.value = value;
            this.parent = parent;
        }

        protected int size() {
            int s = 1;
            if (left != null) {
                s += left.size();
            }
            if (right != null) {
                s += right.size();
            }
            return s;
        }

        protected Node<A, B> minimum() {
            HeapCollector.collectMemory("bst/minimum", "pre|29", new Object[]{this}, "this");
            Node<A, B> current = this;
            while (current.left != null) {
                HeapCollector.collectMemory("bst/minimum", "loop|31", new Object[]{this,current}, "this", "current");
                current = current.left;
            }
            HeapCollector.collectMemory("bst/minimum", "post|34", new Object[]{this, current}, "this", "current");
            return current;
        }

        protected Node<A, B> maximum() {
            HeapCollector.collectMemory("bst/maximum", "pre|39", new Object[]{this}, "this");
            Node<A, B> current = this;
            while (current.right != null) {
                HeapCollector.collectMemory("bst/maximum", "loop|42", new Object[]{this, current}, "this", "current");
                current = current.right;
            }
            HeapCollector.collectMemory("bst/maximum", "post|45", new Object[]{this, current}, "this", "current");
            return current;
        }

        protected Node<A, B> successor() {
            HeapCollector.collectMemory("bst/successor", "pre|81", new Object[]{this}, "this");
            if (this.right != null) {
                HeapCollector.collectMemory("bst/successor", "post|52", new Object[]{this}, "this");
                return this.right.minimum();
            } else {
                Node<A, B> current = this;
                Node<A, B> next = this.parent;
                while (next != null && next.right == current) {
                    HeapCollector.collectMemory("bst/successor", "loop|57", new Object[]{this, current, next}, "this", "current", "next");
                    current = next;
                    next = next.parent;
                }
                HeapCollector.collectMemory("bst/successor", "post|61", new Object[]{this, current,next}, "this", "current","next");
                return next;
            }
        }

        protected void remove() {
            HeapCollector.collectMemory("bst/remove", "pre|64", new Object[]{this}, "this");
            if (this.left == null && this.right == null) {
                transplant(null);
            } else if (this.left == null) {
                transplant(this.right);
            } else if (this.right == null) {
                transplant(this.left);
            } else {
                Node<A, B> replacement = this.successor();
                if (this.right != replacement) {
                    replacement.transplant(replacement.right);
                    replacement.right = this.right;
                    replacement.right.parent = replacement;
                }
                transplant(replacement);
                replacement.left = this.left;
                replacement.left.parent = replacement;
                HeapCollector.collectMemory("bst/remove", "post|81", new Object[]{this, replacement}, "this", "replacement");
            }
            HeapCollector.collectMemory("bst/remove", "post|83", new Object[]{this}, "this");
        }

        protected Node<A, B> get(A key) {
            if (key.compareTo(this.key) == 0) {
                return this;
            } else if (key.compareTo(this.key) < 0) {
                if (this.left == null) {
                    return null;
                } else {
                    return this.left.get(key);
                }
            } else {
                if (this.right == null) {
                    return null;
                } else {
                    return this.right.get(key);
                }
            }
        }

        protected void transplant(Node<A, B> replacement) {
            if(replacement == null)
                return;
            if (this.parent.left == this) {
                this.parent.left = replacement;
                replacement.parent = this.parent;
            } else if(this.parent.right == this) {
                this.parent.right = replacement;
                replacement.parent = this.parent;
            }
        }

        protected void put(A key, B value) {
            HeapCollector.collectMemory("bst/put", "pre|121", new Object[]{this}, "this");
            if (key.compareTo(this.key) < 0) {
                if(this.left == null) {
                    this.left = new Node<>(key, value, this);
                } else {
                    this.left.put(key, value);
                }
            } else if (key.compareTo(this.key) == 0) {
                this.value = value;
            } else {
                if (this.right == null) {
                    this.right = new Node<>(key, value, this);
                } else {
                    this.right.put(key, value);
                }
            }
            HeapCollector.collectMemory("bst/put", "post|137", new Object[]{this}, "this");
        }
    }

    public Node<A, B> root;

    public void put(A key, B value) {
        if (root == null) {
            root = new Node<>(key, value, null);
        } else {
            root.put(key, value);
        }
    }

    public B get(A key) {
    /*Node<A, B> current = root;
    while (current != null && current.key != key) {
      if (key.compareTo(current.key) < 0) {
        current = current.left;
      } else {
        current = current.right;
      }
    }*/
        Node<A, B> current = root.get(key);
        if (current == null) {
            return null;
        } else {
            return current.value;
        }
    }

    public void remove(A key) {
        Node<A, B> node = root.get(key);
        if (node == null) {
            return;
        } else {
            node.remove();
        }
    }

    public Node<A, B> minimum() {
        return root.minimum();
    }

    public Node<A, B> maximum() {
        return root.maximum();
    }

    public int size() {
        if (root == null) {
            return 0;
        } else {
            return root.size();
        }
    }

    public static void main(String[] args) {
        BinarySearchTree<Integer, Integer> k = new BinarySearchTree<>();
        k.put(4, 7);
        k.put(1, 3);
        k.put(6, 8);
        k.put(7, 8);
        System.out.println(k.get(4));
        System.out.println(k.get(1));
        System.out.println(k.get(6));
        System.out.println(k.get(7));
        System.out.println();
        k.remove(6);
        System.out.println(k.size());
        System.out.println(k.minimum().value);
        System.out.println(k.maximum().value);
        System.out.println();
        k.remove(1);
        System.out.println(k.size());
        System.out.println();
        System.out.println(k.get(4));
        System.out.println(k.get(1));
        System.out.println(k.get(7));
        System.out.println(k.get(6));
    }
}