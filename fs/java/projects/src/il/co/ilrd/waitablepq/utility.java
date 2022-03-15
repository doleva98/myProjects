package il.co.ilrd.waitablepq;

class CompareAndSetException extends RuntimeException {
    public CompareAndSetException(String str) {
        super(str);
    }
}