import java.awt.*;
import java.awt.image.BufferedImage;

public class LaplacianFilter {
    public static BufferedImage applyLaplacianFilter(BufferedImage image) {
        int[] laplacianKernel = {
                0,  1,  0,
                1, -4,  1,
                0,  1,  0
        };

        BufferedImage result = new BufferedImage(image.getWidth(), image.getHeight(), BufferedImage.TYPE_BYTE_GRAY);

        // Maximum and minimum value seen during Laplacian filtering (used for scaling)
        int minValue = Integer.MAX_VALUE;
        int maxValue = Integer.MIN_VALUE;

        // Apply Laplacian filter
        for (int x = 1; x < image.getWidth() - 1; x++) {
            for (int y = 1; y < image.getHeight() - 1; y++) {
                int newColor = 0;

                // Apply Laplacian kernel
                for (int kx = -1; kx <= 1; kx++) {
                    for (int ky = -1; ky <= 1; ky++) {
                        int pixelColor = new Color(image.getRGB(x + kx, y + ky)).getRed();
                        newColor += laplacianKernel[(kx + 1) * 3 + (ky + 1)] * pixelColor;
                    }
                }

                // Track the minimum and maximum values to help scale the result later
                minValue = Math.min(minValue, newColor);
                maxValue = Math.max(maxValue, newColor);
            }
        }

        // Normalize and scale values to the 0-255 range
        for (int x = 1; x < image.getWidth() - 1; x++) {
            for (int y = 1; y < image.getHeight() - 1; y++) {
                int newColor = 0;

                // Apply Laplacian kernel again for scaling
                for (int kx = -1; kx <= 1; kx++) {
                    for (int ky = -1; ky <= 1; ky++) {
                        int pixelColor = new Color(image.getRGB(x + kx, y + ky)).getRed();
                        newColor += laplacianKernel[(kx + 1) * 3 + (ky + 1)] * pixelColor;
                    }
                }

                // Normalize the value to the [0, 255] range
                int scaledValue = (newColor - minValue) * 255 / (maxValue - minValue);
                scaledValue = Math.min(Math.max(scaledValue, 0), 255); // Clamp to [0, 255]

                // Set the result in the image
                result.setRGB(x, y, new Color(scaledValue, scaledValue, scaledValue).getRGB());
            }
        }

        return result;
    }
}
