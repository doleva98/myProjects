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
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class FolderMonitor {
    private Future<?> function;

    public FolderMonitor(String path) {
        ExecutorService Executor = Executors.newSingleThreadExecutor();

        function = Executor.submit(() -> {
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
                        Kind<?> kind = event.kind();
                        if (StandardWatchEventKinds.OVERFLOW == kind) {
                            continue;
                        } else if (StandardWatchEventKinds.ENTRY_CREATE == kind) {
                            System.out.println("entry created");
                        } else if (StandardWatchEventKinds.ENTRY_DELETE == kind) {
                            System.out.println("entry deleted");
                        } else if (StandardWatchEventKinds.ENTRY_MODIFY == kind) {
                            System.out.println("entry modified");
                        }
                    }
                    if (!key.reset()) {
                        break;
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
    }

    public void cancelTask() {
        function.cancel(true);
    }

}
