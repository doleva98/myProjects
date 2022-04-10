package il.co.java_quizzes.binaryExpressionTree;

public class BinaryExpressionTree {
    // private VarBinNode head = null;

    /** Base class: component */
    private interface VarBinNode {
        public char value();

        public boolean isLeaf();

        public int evaluate();
    }

    /** Leaf node: leaf */
    public class VarLeafNode implements VarBinNode {
        private char operand; // Operand value

        VarLeafNode(char val) {
            operand = val;
        }

        public boolean isLeaf() {
            return true;
        }

        public char value() {
            return operand;
        }

        public int evaluate() {
            return (operand - '0');
        }
    }

    /** Internal node: Composite */
    public class VarIntlNode implements VarBinNode { // Internal node
        private VarBinNode left; // Left child
        private VarBinNode right; // Right child
        private char operator; // Operator value

        VarIntlNode(char op,
                VarBinNode l, VarBinNode r) {
            operator = op;
            left = l;
            right = r;
        }

        public boolean isLeaf() {
            return false;
        }

        public VarBinNode leftchild() {
            return left;
        }

        public VarBinNode rightchild() {
            return right;
        }

        public char value() {
            return operator;
        }

        public int evaluate() {
            switch (value()) {
                case '+':
                    if (right == null) {
                        return left.value() - '0';
                    }
                    return left.value() + right.value();
                case '-':
                    if (right == null) {
                        return -(left.value() - '0');
                    }
                    return left.value() - right.value();
                case '*':
                    return left.value() * right.value();
                case '/':
                    return left.value() / right.value();
            }
            return -1;
        }

    }

}
