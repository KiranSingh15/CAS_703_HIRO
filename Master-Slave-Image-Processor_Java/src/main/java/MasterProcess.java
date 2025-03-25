import java.util.List;
import java.util.concurrent.*;

public class MasterProcess {
    public static void main(String[] args) {
        // Define the number of threads
        int numberOfThreads = 3;

        // Create a blocking queue for tasks
        BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();

        // Create a thread pool with a fixed number of threads
        ExecutorService executorService = new ThreadPoolExecutor(
                numberOfThreads, numberOfThreads, 0L, TimeUnit.MILLISECONDS, taskQueue
        );

        // List of image file paths to process
        List<String> imagePaths = List.of(
                "src/main/java/input.jpg",
                "src/main/java/input2.png",
                "src/main/java/input3.png",
                "src/main/java/input4.jpg",
                "src/main/java/input5.jpg"
        );

        // Enqueue image processing tasks
        for (String imagePath : imagePaths) {
            taskQueue.add(() -> processImage(imagePath));
        }

        // Submit tasks from the queue to the thread pool
        while (!taskQueue.isEmpty()) {
            Runnable task = taskQueue.poll(); // Get a task from the queue
            if (task != null) { // Perform a null check before executing
                executorService.execute(task);
            }
        }

        // Shutdown the executor after processing
        executorService.shutdown();
    }

    // Simulated image processing method
    public static void processImage(String imagePath) {
        System.out.println("Processing " + imagePath + " on thread: " + Thread.currentThread().getName());
//        try {
////            Thread.sleep(2000); // Simulate image processing time
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
        ImageProcessing.edgeDetection(imagePath);
        System.out.println("Completed processing " + imagePath);
    }
}