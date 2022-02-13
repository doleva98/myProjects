
package complex;

import javax.lang.model.util.ElementScanner6;

class Complex implements Comparable<Complex> {
    private double real;
    private double img;

    public Complex(double real, double img) {
        this.real = real;
        this.img = img;
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
    /* 
    public Complex sub(Complex c1, Complex c2) {
    
    }
    
    public Complex min(Complex c1, Complex c2) {
    
    }
    
    public Complex mul(Complex c1, Complex c2) {
    
    } */

    @Override
    public String toString() {
        return real + "+" + img + "i";
    }

    @Override
    public int compareTo(Complex other) {
        return (int) real - (int) other.real;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Complex)) {
            return false;
        }
        Complex complex = (Complex) o;
        return real == complex.real && img == complex.img;
    }

    @Override
    public int hashCode() {
        return (int) real + (int) img;
    }

    public boolean isReal() {
        return img == 0;
    }

    public boolean isImg() {
        return real == 0;
    }

    public Complex parsing(String str) {
        double real = 0;
        double img = 0;

        boolean isReal = true;

        for (int i = 0; i < str.length(); ++i) {
            if (str.charAt(i) == '+') {
                isReal = false;
            } else if (str.charAt(i) == 'i') {
                break;
            } else if (isReal) {
                real += str.charAt(i) - '0';
            } else {
                img += str.charAt(i) - '0';
            }

        }
        return new Complex(real, img);

    }

}