import java.awt.*;
import java.awt.image.BufferedImage;

public class GrayScale {
    public static BufferedImage applyGrayScale(BufferedImage originalImage) {
        // Step 1: Convert the image to grayscale
        BufferedImage grayscaleImage = new BufferedImage(originalImage.getWidth(), originalImage.getHeight(), BufferedImage.TYPE_BYTE_GRAY);
        for (int i = 0; i < originalImage.getWidth(); i++) {
            for (int j = 0; j < originalImage.getHeight(); j++) {
                Color color = new Color(originalImage.getRGB(i, j));
                int gray = (int)(color.getRed() * 0.3 + color.getGreen() * 0.59 + color.getBlue() * 0.11); // Standard grayscale formula
                Color grayColor = new Color(gray, gray, gray);
                grayscaleImage.setRGB(i, j, grayColor.getRGB());
            }
        }
        return grayscaleImage;
    }
}
