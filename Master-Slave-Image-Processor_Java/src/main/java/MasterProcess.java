import java.util.List;
import java.util.concurrent.*;

public class MasterProcess {
    private static final MetricsLogger metricsLogger = new MetricsLogger();

    public static void main(String[] args) {
        int numberOfThreads = 3;
        BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();

        ExecutorService executorService = new ThreadPoolExecutor(
                numberOfThreads, numberOfThreads, 0L, TimeUnit.MILLISECONDS, taskQueue);

        List<String> imagePaths = List.of(
                "src/main/java/imglarge.png",
                "src/main/java/imglarge_1.png",
                "src/main/java/imglarge_2.png",
                "src/main/java/imglarge_3.png",
                "src/main/java/imglarge_4.png");

        // Record overall start time
        long overallStart = System.nanoTime();

        // Enqueue image processing tasks.
        for (String imagePath : imagePaths) {
            taskQueue.add(() -> processImage(imagePath));
        }

        // Submit tasks from the queue to the thread pool.
        while (!taskQueue.isEmpty()) {
            Runnable task = taskQueue.poll();
            if (task != null) {
                executorService.execute(task);
            }
        }

        // Shutdown the executor and wait for tasks to finish.
        executorService.shutdown();
        try {
            if (!executorService.awaitTermination(60, TimeUnit.SECONDS)) {
                executorService.shutdownNow();
            }
        } catch (InterruptedException e) {
            executorService.shutdownNow();
        }

        // Record overall end time
        long overallEnd = System.nanoTime();
        double overallTime = (overallEnd - overallStart) / 1_000_000.0; // Convert to ms

        // Generate the log summary using the overall execution time.
        metricsLogger.logWorker(numberOfThreads, overallTime);
    }

    public static void processImage(String imagePath) {
        long threadId = Thread.currentThread().getId();
        long startTime = System.nanoTime();

        // Process the image and get output filename.
        String outputFilename = ImageProcessing.edgeDetection(imagePath);

        long endTime = System.nanoTime();
        double duration = (endTime - startTime) / 1_000_000.0; // milliseconds

        // Log the event (individual task times still useful for work distribution).
        metricsLogger.logThreadExecution(threadId, outputFilename, duration);
        System.out.println("Completed processing " + imagePath + " on thread: " + threadId);
    }
}