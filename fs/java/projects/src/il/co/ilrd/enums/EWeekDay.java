package il.co.ilrd.enums;

enum EWeekDay {
    SUNDAY(1),
    MONDAY(2),
    TUSEDAY(3),
    WEDNESDAY(4),
    THURSDAY(5),
    FRIDAY(6),
    SATURDAY(7);

    private final int day;

    private EWeekDay(final int day) {
        this.day = day;
    }

    public int getDay() {
        return day;
    }

    public static void print() {
        for (EWeekDay w : EWeekDay.values()) {
            System.out.println(w);
        }
    }

    public static String fromValue(int day) {
        --day;
        for (EWeekDay w : EWeekDay.values()) {
            if (0 == day) {
                return w.toString();
            }
            --day;
        }
        return null;
    }

}

class EnumCheck {
    public static void main(String[] args) {
        EWeekDay.print();
        System.out.println(EWeekDay.fromValue(3));
        System.out.println(EWeekDay.valueOf("FRIDAY").ordinal());
        EWeekDay w = EWeekDay.SUNDAY;
        System.out.println(w);
        System.out.println(w.getDay());
    }
}