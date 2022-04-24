package il.co.java_quizzes.Bst;

public class Bst<T extends Comparable<? super T>> {
    private TreeNode<T> head = null;

    public void insert(T data) {
        head = insert(data, head);
    }

    private TreeNode<T> insert(T data, TreeNode<T> node) {
        if (node == null) {
            return new TreeNode<>(data, null, null);
        }
        if (node.getData().compareTo(data) > 0) {
            node.setLeftSon(insert(data, node.getLeftSon()));
        } else {
            node.setRightSon(insert(data, node.getRightSon()));
        }
        return node;
    }

    public TreeNode<T> getHead() {
        return head;
    }
}
