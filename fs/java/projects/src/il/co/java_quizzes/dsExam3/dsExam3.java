package il.co.java_quizzes.dsExam3;

import java.util.Arrays;
import java.util.Stack;

class Main {
    public static void main(String[] args) {
        /* int[] a = { 3, 1, 4 };
        printTheIndexOfSumOftwo(a, 6);
        printTheIndexOfSumOftwo(a, 7); */

        /* char[] a = { 'a', 't' };
        System.out.println(checkIfCharInArray(a, 't')); */

        /*  int[][] a = {
                { 1, 1, 0, 0, 0 },
                { 0, 1, 0, 0, 1 },
                { 1, 0, 0, 1, 1 },
                { 0, 0, 0, 0, 0 },
                { 1, 0, 1, 0, 1 } };
        
        MapIslands islands = new MapIslands(a);
        System.out.println(islands.countIslands()); */

        /*  MinStack<Integer> s = new MinStack<Integer>();
        s.push(1);
        System.out.println(s.getMin());
        s.push(-10);
        System.out.println(s.getMin());
        s.push(4);
        System.out.println(s.getMin());
        s.push(10);
        System.out.println(s.getMin());
        s.push(-100);
        System.out.println(s.getMin());
        s.pop();
        System.out.println(s.getMin());
        s.pop();
        s.pop();
        s.pop();
        System.out.println(s.getMin()); */

        /*         System.out.println(CheckParentheses.checkParentheses("([]fds((fds)))"));
         */
        /*         System.out.println(WithoutOperators.div(20, 4));
         */

        /*         System.out.println(WithoutOperators.addOne(7));
         */
        /*         System.out.println(1 & 7);
         */
        /*  Hashtable<Integer, Integer> h = new Hashtable<>();
        PriorityQueue<Integer> d = new PriorityQueue<>();
            d. */
        char[] a = new char[] { '1', 's', 'f', 'd', 'q' };
        System.out.println(Arrays.toString(a));
        efficientNCircularShift(a, 3);
        System.out.println(Arrays.toString(a));

    }

    private static void mirror(char[] array, int start, int end) {
        while (start < end) {
            char temp = array[start];
            array[start] = array[end];
            array[end] = temp;
            ++start;
            --end;
        }
    }

    public static void efficientNCircularShift(char[] array, int n) {
        n %= array.length;
        mirror(array, 0, array.length - 1);
        mirror(array, 0, n - 1);
        mirror(array, n, array.length - 1);
    }

    public static boolean checkIfCharInArray(char[] array, char c) {
        boolean[] array_all_chars = new boolean[128];
        for (char char_in_array : array) {
            array_all_chars[char_in_array] = true;
        }
        return array_all_chars[c];
    }

    public static void printTheIndexOfSumOftwo(int[] array, int sum_of_two) {
        Arrays.sort(array);
        int x = 0;
        boolean there_is_pair = false;
        for (int i = 0; i < array.length; ++i) {
            x = Arrays.binarySearch(array, sum_of_two - array[i]);
            if (x == i) {
                continue;
            }
            if (-1 < x) {
                System.out.println(array[i] + " " + array[x]);
                there_is_pair = true;
            }
        }
        if (!there_is_pair) {
            System.out.println("no pairs are found");
        }
    }
}

class QuickSortLinkedList {
    private class Node {
        private int data;
        private Node next;

        Node(int d) {
            this.data = d;
            this.next = null;
        }
    }

    private Node head;

    public void add(int data) {
        if (head == null) {
            head = new Node(data);
            return;
        }

        Node curr = head;
        while (curr.next != null)
            curr = curr.next;

        curr.next = new Node(data);
    }

    Node paritionLast(Node start, Node end) {
        if (start == end || start == null || end == null) {
            return start;
        }
        Node pivot_prev = start;
        Node curr = start;
        int pivot = end.data;

        while (start != end) {
            if (start.data < pivot) {
                pivot_prev = curr;
                int temp = curr.data;
                curr.data = start.data;
                start.data = temp;
                curr = curr.next;
            }
            start = start.next;
        }
        int temp = curr.data;
        curr.data = pivot;
        end.data = temp;
        return pivot_prev;
    }
}

/* class BinaryTree {
private Bnode root;

private final int LEFT = 0;
private final int RIGHT = 0;

public void insertIter(int key, Object data) {
if (root == null) {
    root = new Bnode(null, null, null, key, data);
    return;
}
Bnode curr = root;
while (!curr.isLeaf()) {
    if (key < curr.key) {
        curr = curr.child[LEFT];
    } else {
        curr = curr.child[RIGHT];
    }
}
if (key < curr.key) {
    curr.child[LEFT] = new Bnode(curr, null, null, key, data);
} else {
    curr.child[RIGHT] = new Bnode(curr, null, null, key, data);
}
}

public void insert(int key, Object data) {
root = insertRec(root, key, data);
}

private Bnode insertRec(Bnode node, int key, Object data) {
if (node.isLeaf()) {
    return new Bnode(null, null, null, key, data);
}
if (key < node.key) {
    node.child[LEFT] = insertRec(node.child[LEFT], key, data);
    node.child[LEFT].parent = node;
} else if (key > node.key) {
    node.child[RIGHT] = insertRec(node.child[RIGHT], key, data);
    node.child[RIGHT].parent = node;
} else {
    System.out.println("already in BST");
}
return node;
}

private class Bnode {
private Bnode parent;
private Bnode[] child;
private int key;
private Object data;

private Bnode(Bnode parent, Bnode left_child, Bnode right_child, int key, Object data) {
    this.parent = parent;
    child = new Bnode[2];
    child[0] = left_child;
    child[1] = right_child;
    this.key = key;
    this.data = data;
}

private boolean isLeaf() {
    return child[0] == null && child[1] == null;
}

public Bnode getParent() {
    return parent;
}

public Object getValue() {
    return data;
}
}
} */

class WithoutOperators {
    public static int mul(int a, int b) {
        if (b == 1) {
            return a;
        }
        return a += mul(a, b - 1);
    }

    public static int div(int a, int b) {
        int q = 1;
        while (a > b) {
            ++q;
            a -= b;
        }
        return q;
    }

    public static int addOne(int a) {
        int m = 1;
        for (int i = 0; (int) (a & m) >> i == 1; ++i) {
            a ^= m;
            m <<= 1;
        }
        a ^= m;
        return a;
    }
}

class CheckParentheses {
    public static boolean checkParentheses(String str) {
        Stack<Character> stack = new Stack<>();
        for (char c : str.toCharArray()) {
            switch (c) {
                case '(':
                    stack.push(c);
                    break;
                case '[':
                    stack.push(c);
                    break;
                case '{':
                    stack.push(c);
                    break;
                case ')':
                    if (stack.isEmpty() || stack.pop() != '(') {
                        return false;
                    }
                    break;
                case '}':
                    if (stack.isEmpty() || stack.pop() != '{') {
                        return false;
                    }
                    break;
                case ']':
                    if (stack.isEmpty() || stack.pop() != '[') {
                        return false;
                    }
                    break;
            }
        }

        return stack.isEmpty();
    }
}

class MinStack<E extends Comparable<E>> {
    private Stack<E> data_stack;
    private Stack<E> min_stack;

    public MinStack() {
        data_stack = new Stack<E>();
        min_stack = new Stack<E>();
    }

    public E getMin() {
        return min_stack.peek();
    }

    public E pop() {
        while (data_stack.peek().equals(min_stack.peek())) {
            min_stack.pop();
        }
        return data_stack.pop();
    }

    public void push(E item) {
        if (min_stack.isEmpty()) {
            min_stack.push(item);
        } else {
            if ((min_stack.peek()).compareTo(item) < 0) {
                min_stack.push(min_stack.peek());
            } else {
                min_stack.push(item);
            }
        }
        data_stack.push(item);
    }

}

class MapIslands {
    private int[][] bitmap;
    private final int ROW;
    private final int COL;

    public MapIslands(int[][] bitmap) {
        this.bitmap = bitmap;
        ROW = bitmap.length;
        COL = bitmap[0].length;
    }

    public int countIslands() {
        boolean[][] visited = new boolean[ROW][COL];
        int count = 0;

        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (bitmap[i][j] == 1 && !visited[i][j]) {
                    /* a new island is found!, visit all it's land */
                    visitAllTheLandYouCan(i, j, visited);
                    ++count;
                }
            }
        }
        return count;
    }

    private void visitAllTheLandYouCan(int i, int j, boolean[][] visited) {
        int[] rPos = new int[] { -1, -1, -1, 0, 0, 1, 1, 1 };
        int[] cPos = new int[] { -1, 0, 1, -1, 1, -1, 0, 1 };

        visited[i][j] = true;

        for (int k = 0; k < 8; ++k) {
            if (isSafe(i + rPos[k], j + cPos[k], visited)) {
                visitAllTheLandYouCan(i + rPos[k], j + cPos[k], visited);
            }
        }
    }

    private boolean isSafe(int i, int j, boolean[][] visited) {
        return i >= 0 && i < ROW && j >= 0 && j < COL && bitmap[i][j] == 1 && !visited[i][j];
    }

}

class Element {
    private int ID;
    private int value;

    public Element(int ID, int value) {
        this.ID = ID;
        this.value = value;
    }

    public int getval() {
        return value;
    }

    public int getID() {
        return ID;
    }
}

class ArrayInOOne {
    private int counter;
    private Element all;
    private Element[] array;

    public ArrayInOOne(int len) {
        array = new Element[len];
    }

    public void setval(int indx, int val) {
        array[indx] = new Element(counter++, val);
    }

    public int getval(int indx) {
        if (all.getID() > array[indx].getID()) {
            return all.getval();
        }
        return array[indx].getval();
    }

    public void setall(int val) {
        all = new Element(counter++, val);
    }

}
