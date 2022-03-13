package il.co.java_quizzes.annualSalaries;

import java.sql.Date;

abstract class Employ {
    protected int ID;
    protected String name;
    protected Date birthDay;
    protected Date employmentStartDay;
    protected int baseMonthSalary;

    public Employ(int ID, String name, Date birthDay, Date employmentStartDay, int baseMonthSalary) {
        this.ID = ID;
        this.name = name;
        this.birthDay = birthDay;
        this.employmentStartDay = employmentStartDay;
        this.baseMonthSalary = baseMonthSalary;
    }

    public abstract double calculateAnnualSalary();
}

class Junior extends Employ {

    public Junior(int ID, String name, Date birthDay, Date employmentStartDay, int baseMonthSalary) {
        super(ID, name, birthDay, employmentStartDay, baseMonthSalary);
    }

    @Override
    public double calculateAnnualSalary() {
        return 13 * baseMonthSalary;
    }

}

class Senior extends Employ {

    public Senior(int ID, String name, Date birthDay, Date employmentStartDay, int baseMonthSalary) {
        super(ID, name, birthDay, employmentStartDay, baseMonthSalary);
    }

    public Senior(Employ junior) {
        super(junior.ID, junior.name, junior.birthDay, junior.employmentStartDay, junior.baseMonthSalary);
    }

    @Override
    public double calculateAnnualSalary() {
        return 12 * baseMonthSalary + 1.1 * baseMonthSalary;
    }

}

class Manager extends Employ {
    private int yearlyBonus;

    public Manager(int ID, String name, Date birthDay, Date employmentStartDay, int baseMonthSalary, int yearlyBonus) {
        super(ID, name, birthDay, employmentStartDay, baseMonthSalary);
        this.yearlyBonus = yearlyBonus;
    }

    @Override
    public double calculateAnnualSalary() {
        return 12 * baseMonthSalary + yearlyBonus;
    }

    public Senior changeJuniorToSenior(Junior junior) {
        return new Senior(junior);
    }

}