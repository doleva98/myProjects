/* shani */

package il.co.ilrd.networking;

public class ByteArrayToString {
    public static String byteArrayToString(byte[] a) {
        if (a == null) {
            return null;
        }
        StringBuilder bobTheBuilder = new StringBuilder();
        for (int i = 0; a[i] != 0; ++i) {
            bobTheBuilder.append((char) a[i]);
        }
        return bobTheBuilder.toString();
    }
}
