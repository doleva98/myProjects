abstract class Shape {

    private String color;
    private boolean filled;

    Shape() {
        this.color = "green";
        filled = true;
    }

    Shape(String color, boolean filled) {
        this.color = color;
        this.filled = filled;
    }

    public String getColor() {
        return this.color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public boolean isFilled() {
        return this.filled;
    }

    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    abstract public double getArea();

    abstract public double getPerimeter();

    public String toString() {
        String is_filled;
        if (this.filled) {
            is_filled = "filled";
        } else {
            is_filled = "Not filled";
        }
        return "A Shape with color of " + this.color + " and " + is_filled;
    }
}

class Circle extends Shape {

    private double radius;

    Circle() {
        this.radius = 1.0;
    }

    Circle(double radius) {
        this.radius = radius;
    }

    Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    public double getRadius() {
        return this.radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getArea() {
        return Math.PI * Math.pow(this.radius, 2);
    }

    public double getPerimeter() {
        return 2 * Math.PI * this.radius;
    }

    @Override
    public String toString() {
        return "A Circle with radius=" + this.radius + ", which is a subclass of " + super.toString();
    }

}

class Rectangler extends Shape {
    private double width;
    private double length;

    Rectangler() {
        this.width = 1.0;
        this.length = 1.0;
    }

    Rectangler(double width, double length) {
        this.width = width;
        this.length = length;
    }

    Rectangler(double width, double length, String color, boolean filled) {
        super(color, filled);
        this.width = width;
        this.length = length;
    }

    public double getWidth() {
        return this.width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getLength() {
        return this.length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getArea() {
        return this.width * this.length;
    }

    public double getPerimeter() {
        return 2 * (this.width + this.length);
    }

    @Override
    public String toString() {
        return "A Rectangular with width=" + this.width + " and length+" + this.length + ", which is a subclass of "
                + super.toString();
    }
}

class Square extends Rectangler {
    Square() {
    }

    Square(double side) {
        super(side, side);
    }

    Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public double getSide() {
        return super.getWidth();
    }

    public void setSide(double side) {
        super.setLength(side);
        super.setWidth(side);
    }

    @Override
    public String toString() {
        return "A Square with side=" + super.getWidth() + ", which is a subclass of "
                + super.toString();
    }
}

class Main {
    public static int getLineNumber() {
        return Thread.currentThread().getStackTrace()[2].getLineNumber();
    }

    public static void main(String[] args) {
        /*
         * Shape s = new Shape();
         * 
         * if (!s.toString().equals("A Shape with color of green and filled")) {
         * System.out.println("fail in " + getLineNumber());
         * }
         * 
         * s.setColor("yellow");
         * 
         * if (!s.getColor().equals("yellow")) {
         * System.out.println("fail in " + getLineNumber());
         * }
         * 
         * Shape s2 = new Shape("red", false);
         * 
         * if (!s2.toString().equals("A Shape with color of red and Not filled")) {
         * System.out.println("fail in " + getLineNumber());
         * }
         * 
         * s2.setFilled(true);
         * 
         * if (!s2.getFilled()) {
         * System.out.println("fail in " + getLineNumber());
         * }
         */

        Circle c = new Circle();

        if (!c.toString()
                .equals("A Circle with radius=1.0, which is a subclass of A Shape with color of green and filled")) {
            System.out.println("fail in " + getLineNumber());
        }

        Circle c2 = new Circle(3, "orange", false);

        if (!c2.toString()
                .equals("A Circle with radius=3.0, which is a subclass of A Shape with color of orange and Not filled")) {
            System.out.println("fail in " + getLineNumber());
        }

        /* ******************** */

        Shape s1 = new Circle(5.5, "RED", false); /* upcasting */
        System.out.println(s1);
        System.out.println(s1.getArea());
        System.out.println(s1.getPerimeter());
        System.out.println(s1.getColor());
        System.out.println(s1.isFilled());
        /* System.out.println(s1.getRadius()); wont work, unknown operation for Shape */

        Circle c1 = (Circle) s1;/* downcasting */
        System.out.println(c1);
        System.out.println(c1.getArea());
        System.out.println(c1.getPerimeter());
        System.out.println(c1.getColor());
        System.out.println(c1.isFilled());
        System.out.println(c1.getRadius());

        /* Shape s2 = new Shape(); wont work, Shapre is an abstract class*/
    }
}
