import java.util.List;
import java.util.concurrent.*;

public class MasterProcess {
    private static final MetricsLogger metricsLogger = new MetricsLogger();

    public static void main(String[] args) {
        int numberOfThreads = 1;
        BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();

        ExecutorService executorService = new ThreadPoolExecutor(
                numberOfThreads, numberOfThreads, 0L, TimeUnit.MILLISECONDS, taskQueue);

        // Large
        // List<String> imagePaths = List.of(
        //         "src/main/java/assets/imglarge.png",
        //         "src/main/java/assets/imglarge_1.png",
        //         "src/main/java/assets/imglarge_2.png",
        //         "src/main/java/assets/imglarge_3.png",
        //         "src/main/java/assets/imglarge_4.png");

        // Mid
        // List<String> imagePaths = List.of(
        //         "src/main/java/assets/imgmid.jpg",
        //         "src/main/java/assets/imgmid_1.jpg",
        //         "src/main/java/assets/imgmid_2.jpg",
        //         "src/main/java/assets/imgmid_3.jpg",
        //         "src/main/java/assets/imgmid_4.jpg");

        // Small
        List<String> imagePaths = List.of(
                "src/main/java/assets/imgsmall.jpg",
                "src/main/java/assets/imgsmall_1.jpg",
                "src/main/java/assets/imgsmall_2.jpg",
                "src/main/java/assets/imgsmall_3.jpg",
                "src/main/java/assets/imgsmall_4.jpg");

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