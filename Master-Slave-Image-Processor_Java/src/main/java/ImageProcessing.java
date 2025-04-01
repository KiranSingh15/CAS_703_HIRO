import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Random;

public class ImageProcessing {

    public static void main(String[] args) {
        try {
//            Current working directory: /Users/changkehang/Desktop/McMaster/CAS703/Project/Master-Slave-Image-Processor
//            String currentDir = System.getProperty("user.dir");
//            System.out.println("Current working directory: " + currentDir);

            // Load the original image
            File inputFile = new File("src/main/java/input.jpg");
            BufferedImage originalImage = ImageIO.read(inputFile);

            BufferedImage grayscaleImage = GrayScale.applyGrayScale(originalImage);

            // Save grayscale image
            File grayFile = new File("grayscale_image.jpg");
            ImageIO.write(grayscaleImage, "jpg", grayFile);

            // Step 2: Apply Gaussian blur
            BufferedImage blurredImage = GaussianBlur.applyGaussianBlur(grayscaleImage);

            // Save Gaussian blurred image
            File blurredFile = new File("gaussian_blurred_image.jpg");
            ImageIO.write(blurredImage, "jpg", blurredFile);

            // Step 3: Apply Laplacian filter
            BufferedImage laplacianImage = LaplacianFilter.applyLaplacianFilter(blurredImage);

            // Save Laplacian image
            File laplacianFile = new File("laplacian_image.jpg");
            ImageIO.write(laplacianImage, "jpg", laplacianFile);

            System.out.println("Processing completed: grayscale, Gaussian blur, Laplacian filter applied!");

        } catch (IOException e) {
            System.out.println("Error loading or saving image: " + e.getMessage());
        }
    }

    public static String edgeDetection(String inputPath) {
        try {
            File inputFile = new File(inputPath);
            BufferedImage originalImage = ImageIO.read(inputFile);
            BufferedImage grayscaleImage = GrayScale.applyGrayScale(originalImage);
            BufferedImage blurredImage = GaussianBlur.applyGaussianBlur(grayscaleImage);
            BufferedImage laplacianImage = LaplacianFilter.applyLaplacianFilter(blurredImage);

            // Create a unique filename using a timestamp and random number.
            LocalDateTime now = LocalDateTime.now();
            String formattedTimestamp = now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss"));
            int randomNumber = new Random().nextInt(9000) + 1000;
            String outputFilename = MetricsLogger.EXPORT_PATH + "laplacian_image_" + formattedTimestamp + "_" + randomNumber + ".jpg";

            File laplacianFile = new File(outputFilename);
            ImageIO.write(laplacianImage, "jpg", laplacianFile);

            return outputFilename;
        } catch (IOException e) {
            System.out.println("Error loading or saving image: " + e.getMessage());
            return "";
        }
    }
}
