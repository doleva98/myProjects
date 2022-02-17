/* ellie was here */

package il.co.ilrd.complex;
import java.util.Scanner;

class ComplexNumber implements Comparable<ComplexNumber> {
    private double real;
    private double img;

    private ComplexNumber(double real, double img) {
        this.real = real;
        this.img = img;
    }

    public static ComplexNumber createFromReal(double real) {
        return new ComplexNumber(real, 0);
    }

    public static ComplexNumber createFromImg(double img) {
        return new ComplexNumber(0, img);
    }

    public double getReal() {
        return this.real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImg() {
        return this.img;
    }

    public void setImg(double img) {
        this.img = img;
    }

    public static ComplexNumber add(ComplexNumber c1, ComplexNumber c2) {
        return new ComplexNumber(c1.real + c2.real, c1.img + c2.img);
    }

    public static ComplexNumber subtract(ComplexNumber c1, ComplexNumber c2) {
        return new ComplexNumber(c1.real - c2.real, c1.img - c2.img);

    }

    public static ComplexNumber multiply(ComplexNumber c1, ComplexNumber c2) {
        return new ComplexNumber(c1.real * c2.real - c1.img * c2.img, c1.real * c2.img - c2.real * c1.img);

    }

    public static ComplexNumber divide(ComplexNumber c1, ComplexNumber c2) {
        return new ComplexNumber(0, 0);

    }

    @Override
    public String toString() {
        return real + "+" + img + "i";
    }

    @Override
    public int compareTo(ComplexNumber other) {
        return (int) real - (int) other.real;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof ComplexNumber)) {
            return false;
        }
        ComplexNumber complex = (ComplexNumber) o;
        return real == complex.real && img == complex.img;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        long temp;
        temp = Double.doubleToLongBits(img);
        result = prime * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(real);
        result = prime * result + (int) (temp ^ (temp >>> 32));
        return result;
    }

    public boolean isReal() {
        return img == 0;
    }

    public boolean isImg() {
        return real == 0;
    }

/* almog watched */

    public static ComplexNumber parsing(String str) {

        Scanner scan = new Scanner(str);
        double real = 0;
        double img = 0;
        boolean isReal = true;
        while (scan.hasNext()) {
            if (scan.hasNextDouble()) {
                if (isReal) {
                    real = scan.nextDouble();
                    isReal = false;
                } else {
                    img = scan.nextDouble();
                }
            } else {
                scan.next();
            }
        }
        scan.close();
        return new ComplexNumber(real, img);

    }

}