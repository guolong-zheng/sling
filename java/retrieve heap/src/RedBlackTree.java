import java.util.NoSuchElementException;

public class RedBlackTree<A extends Comparable<A>, B> {

    static class Node<A extends Comparable<A>, B> {
        public A key;
        public B value;
        public Node<A, B> left;
        public Node<A, B> right;
        public Node<A, B> parent;
        public int colour;

        public Node(A key, B value, Node<A, B> parent, int colour) {
            this.key = key;
            this.value = value;
            this.parent = parent;
            this.colour = colour;
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
    }

    private void fixup(Node<A, B> z) {
        while (z.parent != null && z.parent.parent != null && z.parent.colour == 0) {
            if (z.parent == z.parent.parent.left) {
                Node<A, B> uncle = z.parent.parent.right;

                if (uncle.colour == 0) {
                    z.parent.colour = 1;
                    uncle.colour = 1;
                    z.parent.parent.colour = 0;
                    z = z.parent.parent;
                } else {
                    if (z == z.parent.right) {
                        z = z.parent;
                        leftRotate(z);
                    }
                    z.parent.colour = 1;
                    z.parent.parent.colour = 0;
                    rightRotate(z.parent.parent);
                }
            } else {
                Node<A, B> uncle = z.parent.parent.left;

                if (uncle.colour == 0) {
                    z.parent.colour = 1;
                    uncle.colour = 1;
                    z.parent.parent.colour = 0;
                    z = z.parent.parent;
                } else {
                    if (z == z.parent.left) {
                        z = z.parent;
                        rightRotate(z);
                    }
                    z.parent.colour = 1;
                    z.parent.parent.colour = 0;
                    leftRotate(z.parent.parent);
                }

            }
        }
        root.colour = 1;
    }

    private void leftRotate(Node<A, B> x) {
        Node<A, B> y = x.right;

        x.right = y.left;
        if (y.left == null) {
            y.left.parent = x;
        }
        y.parent = x.parent;
        if (x.parent == null) {
            root = y;
        } else if (x == x.parent.left) {
            x.parent.left = y;
        } else {
            x.parent.right = y;
        }
        y.left = x;
        x.parent = y;
    }

    private void rightRotate(Node<A, B> y) {
        Node<A, B> x = y.left;

        y.left = x.right;
        if (x.right != null) {
            x.right.parent = y;
        }
        x.parent = y.parent;
        if (y.parent == null) {
            root = x;
        } else if (y == y.parent.left) {
            y.parent.left = x;
        } else {
            y.parent.right = x;
        }
        x.right = y;
        y.parent = x;
    }

    public Node<A, B> root;

    public void put(A key, B value) {
        HeapCollector.collectMemory("rbt/put", "pre|126", new Object[]{root}, "root");
        if (root == null) {
            root = new Node<>(key, value, null, 0);
            HeapCollector.collectMemory("rbt/put", "post|129", new Object[]{root}, "root");
        } else {
            Node<A, B> current = root;
            while (true) {
                HeapCollector.collectMemory("rbt/put", "loop|133", new Object[]{root, current}, "root","current");
                if (key.compareTo(current.key) < 0) {
                    if (current.left == null) {
                        current.left = new Node<>(key, value, current, 0);
                        fixup(current.left);
                        break;
                    } else {
                        current = current.left;
                    }
                } else if (key.compareTo(current.key) > 0) {
                    if (current.right == null) {
                        current.right = new Node<>(key, value, current, 0);
                        fixup(current.right);
                        break;
                    } else {
                        current = current.right;
                    }
                }
            }
            HeapCollector.collectMemory("rbt/put", "post|151", new Object[]{root, current}, "root","current");
        }
    }

    public B get(A key) {
        Node<A, B> current = root.get(key);
        if (current == null) {
            throw new NoSuchElementException();
        } else {
            return current.value;
        }
    }

    public static void main(String[] args) {
        RedBlackTree<Integer, Integer> k = new RedBlackTree<>();
        k.put(4, 7);
        k.put(1, 3);
        k.put(6, 8);
        k.put(7, 8);
        System.out.println(k.get(4));
        System.out.println(k.get(1));
        System.out.println(k.get(6));
        System.out.println(k.get(7));
    }
}
