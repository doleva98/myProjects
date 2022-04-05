package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.nio.file.WatchEvent.Kind;

import java.util.concurrent.Future;
import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

public class FolderMonitor {
    private String path = null;
    private Future<?> function;
    private Dispatcher<String> dispatcher = new Dispatcher<>();

    public FolderMonitor(String path) {
        this.path = path;
    }

    public void start() {

        try (WatchService ws = FileSystems.getDefault().newWatchService()) {
            Path dir = Paths.get(path);
            dir.register(ws,
                    StandardWatchEventKinds.ENTRY_CREATE,
                    StandardWatchEventKinds.ENTRY_DELETE,
                    StandardWatchEventKinds.ENTRY_MODIFY);
            System.out.println("folder monitor is created");
            System.out.println(path + " is watched");

            for (;;) {
                WatchKey key = ws.take();
                for (WatchEvent<?> event : key.pollEvents()) {
                    Path eventFile = (Path) event.context();
                    Kind<?> kind = event.kind();
                    notifyAllCallback(eventFile + " " + kind.name());
                }
                if (!key.reset()) {
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            System.out.println("canceled");
        }

    }

    public void cancelTask() {
        function.cancel(true);
    }

    public void registerObserver(Callback<String> callback) {
        dispatcher.register(callback);
    }

    public void unregisterObserver(Callback<String> callback) {
        /* non null */
        dispatcher.unregister(callback);
    }

    public void notifyAllCallback(String pathAndEntryState) {
        dispatcher.notifyAllCallback(pathAndEntryState);
    }

    public void stopAllCallback() {
        dispatcher.stopAllCallback();
    }
}
