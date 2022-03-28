/* shani */
package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class DownloadWebPage {
    public static void main(String[] args) {
        try {
            download("http://www.google.com");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void download(String urlString) throws IOException {
        URL url = new URL(urlString);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));
                BufferedWriter writer = new BufferedWriter(new FileWriter("page.html"));) {
            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
            }
            System.out.println("Page downloaded.");
        }
    }
}
