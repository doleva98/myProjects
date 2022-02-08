class ShapeExcercise {

    private String color;
    private Boolean filled;

    ShapeExcercise() {
        this.color = "green";
        filled = true;
    }

    ShapeExcercise(String color, Boolean filled) {
        this.color = color;
        this.filled = filled;
    }

    public String getColor() {
        return this.color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public Boolean getFilled() {
        return this.filled;
    }

    public void setFilled(Boolean filled) {
        this.filled = filled;
    }

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