import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.*;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.HashMap;
import java.util.Map;

public class MetricsLogger {
    // Thread-safe queue to hold log entries
    private final Queue<LogEntry> logQueue = new ConcurrentLinkedQueue<>();

    // Directory paths (adjust as needed)
    public static final String EXPORT_PATH = "output/";
    public static final String IMPORT_PATH = "src/main/java/"; // adjust if needed

    // Called by each worker thread after processing an image.
    public void logThreadExecution(long threadId, String outputFilename, double duration) {
        logQueue.add(new LogEntry(threadId, outputFilename, duration));
    }

    public void logWorker(int numThreads, double overallTime) {
        Map<Long, Integer> threadWorkCount = new HashMap<>();
        Map<Long, Long> threadSizeCount = new HashMap<>();

        int totalImages = 0;
        long totalSize = 0;

        // Process log entries for per-thread counts and file sizes.
        while (!logQueue.isEmpty()) {
            LogEntry entry = logQueue.poll();
            if (entry == null)
                continue;

            totalImages++;

            threadWorkCount.put(entry.threadId, threadWorkCount.getOrDefault(entry.threadId, 0) + 1);

            // Retrieve the file size
            long fileSize = 0;
            Path path = Paths.get(entry.outputFilename);
            if (Files.exists(path)) {
                try {
                    fileSize = Files.size(path);
                } catch (IOException e) {
                    System.err.println("Error reading file size for " + entry.outputFilename);
                }
            }
            threadSizeCount.put(entry.threadId, threadSizeCount.getOrDefault(entry.threadId, 0L) + fileSize);
            totalSize += fileSize;
        }

        // Write final summary to a log file.
        String logFileName = EXPORT_PATH + "metrics-" + numThreads + "threads.log";
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(logFileName))) {
            writer.write("==== Execution Summary ====\n");
            writer.write("Overall execution time: " + overallTime + " ms\n");
            writer.write("Total images processed: " + totalImages + "\n");
            writer.write("Total size processed: " + (totalSize / (1024.0 * 1024.0)) + " MB\n");
            writer.write("Work distribution:\n");

            for (Map.Entry<Long, Integer> e : threadWorkCount.entrySet()) {
                long threadId = e.getKey();
                int count = e.getValue();
                double percentage = (count / (double) totalImages) * 100.0;
                double sizeMB = (threadSizeCount.get(threadId)) / (1024.0 * 1024.0);
                writer.write(
                        "Thread " + threadId + ": " + count + " images (" + String.format("%.2f", percentage) + "%), "
                                + String.format("%.2f", sizeMB) + " MB processed\n");
            }

        } catch (IOException e) {
            System.err.println("Error writing log file: " + e.getMessage());
        }

        // Output the summary to the console.
        System.out.println("\n==== Execution Summary ====");
        System.out.println("Overall execution time: " + overallTime + " ms");
        System.out.println("Total images processed: " + totalImages);
        System.out.println("Total size processed: " + (totalSize / (1024.0 * 1024.0)) + " MB");
    }
}