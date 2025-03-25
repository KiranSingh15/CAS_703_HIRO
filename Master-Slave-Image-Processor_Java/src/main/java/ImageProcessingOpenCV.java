//import org.opencv.core.Core;
//import org.opencv.core.CvType;
//import org.opencv.core.Mat;
//import org.opencv.core.Size;
//import org.opencv.imgcodecs.Imgcodecs;
//import org.opencv.imgproc.Imgproc;
//
//public class ImageFiltering {
//    public static void main(String[] args) {
//        System.loadLibrary(Core.NATIVE_LIBRARY_NAME); // Load OpenCV
////        System.load("/path/to/opencv/build/lib/opencv_java470.dylib"); // for macOS
//
//        // Read input image
//        Mat image = Imgcodecs.imread("input.jpg");
//
//        if (image.empty()) {
//            System.out.println("Could not read the image.");
//            return;
//        }
//
//        // Convert to grayscale
//        Mat grayImage = new Mat();
//        Imgproc.cvtColor(image, grayImage, Imgproc.COLOR_BGR2GRAY);
//
//        // Save the processed image
//        Imgcodecs.imwrite("gray.jpg", grayImage);
//
//        // Apply Gaussian Blur (kernel size 5x5, sigmaX = 0)
//        Mat gaussianBlur = new Mat();
//        Imgproc.GaussianBlur(image, gaussianBlur, new Size(5, 5), 0);
//
//        // Apply Laplacian Filter for edge detection
//        Mat laplacian = new Mat();
//        Imgproc.Laplacian(gaussianBlur, laplacian, CvType.CV_64F); // 64-bit depth to capture details
//
//        // Convert to 8-bit for proper display
//        Mat laplacianAbs = new Mat();
//        Core.convertScaleAbs(laplacian, laplacianAbs);
//
//        // Save the processed images
//        Imgcodecs.imwrite("gaussian_blur.jpg", gaussianBlur);
//        Imgcodecs.imwrite("laplacian_edges.jpg", laplacianAbs);
//
//        System.out.println("Gaussian Blur and Laplacian Edge Detection applied successfully.");
//    }
//}
