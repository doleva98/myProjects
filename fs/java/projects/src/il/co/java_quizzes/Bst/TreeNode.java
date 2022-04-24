package il.co.java_quizzes.Bst;

public class TreeNode<T> {
    private T data;
    private TreeNode<T> leftSon = null;
    private TreeNode<T> rightSon = null;

    public TreeNode(T data, TreeNode<T> leftSon, TreeNode<T> rightSon) {
        this.data = data;
        this.leftSon = leftSon;
        this.rightSon = rightSon;
    }

    public T getData() {
        return this.data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public TreeNode<T> getLeftSon() {
        return this.leftSon;
    }

    public void setLeftSon(TreeNode<T> leftSon) {
        this.leftSon = leftSon;
    }

    public TreeNode<T> getRightSon() {
        return this.rightSon;
    }

    public void setRightSon(TreeNode<T> rightSon) {
        this.rightSon = rightSon;
    }

}
