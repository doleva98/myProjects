package il.co.java_quizzes.levelOrderTraverse;

import java.util.LinkedList;
import java.util.Queue;

import il.co.java_quizzes.Bst.Bst;
import il.co.java_quizzes.Bst.TreeNode;

public class LevelOrderTraverse {
    public static void traverse(TreeNode<Integer> node) {
        if (node == null) {
            return;
        }
        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        System.out.println(node.getData());
        if (node.getLeftSon() != null) {
            queue.add(node.getLeftSon());
        }
        if (node.getRightSon() != null) {
            queue.add(node.getRightSon());
        }
        while (!queue.isEmpty()) {
            TreeNode<Integer> temp = queue.poll();
            System.out.println(temp.getData());
            if (temp.getLeftSon() != null) {
                queue.add(temp.getLeftSon());
            }
            if (temp.getRightSon() != null) {
                queue.add(temp.getRightSon());
            }
        }
    }

    public static void main(String[] args) {
        Bst<Integer> bst = new Bst<>();
        bst.insert(3);
        bst.insert(80);
        bst.insert(89);
        bst.insert(9);
        bst.insert(0);
        bst.insert(2); 
        traverse(bst.getHead());
    }
}
