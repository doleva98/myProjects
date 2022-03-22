package il.co.ilrd.singleton;

class SingletonLazyNotThreadSafe {
    private static SingletonLazyNotThreadSafe instance;

    private SingletonLazyNotThreadSafe() {
    }

    public static SingletonLazyNotThreadSafe getInstance() {
        if (null == instance) {
            instance = new SingletonLazyNotThreadSafe();
        }
        return instance;
    }

}

class SingletonLazyThreadSafe {
    private static SingletonLazyThreadSafe instance;

    private SingletonLazyThreadSafe() {
    }

    synchronized public static SingletonLazyThreadSafe getInstance() {
        if (null == instance) {
            instance = new SingletonLazyThreadSafe();
        }
        return instance;
    }

}

class SingletonDoubleLocking {
    private static volatile SingletonDoubleLocking instance;

    private SingletonDoubleLocking() {
    }

    public static SingletonDoubleLocking getInstance() {
        if (null == instance) {
            synchronized (SingletonDoubleLocking.class) {
                if (instance == null) {
                    instance = new SingletonDoubleLocking();
                }
            }
        }
        return instance;
    }

}

enum SingletonEnum {
    INSTANCE;

    public static int doSomething() {
        return INSTANCE.hashCode();
    }
}

class SingletonThreadSafeEager {

    private static final SingletonThreadSafeEager instance = new SingletonThreadSafeEager();

    private SingletonThreadSafeEager() {
    }

    public static SingletonThreadSafeEager getInstance() {

        return instance;

    }
}

class SingletonWithHelper {
    private SingletonWithHelper() {
        // The body of private constructor
    }

    public static SingletonWithHelper getInstance() {
        return SingletonHolder.instance;
    }

    // Inner static class that holds a reference to the singleton
    private static class SingletonHolder {
        private static final SingletonWithHelper instance = new SingletonWithHelper();
    }
}
