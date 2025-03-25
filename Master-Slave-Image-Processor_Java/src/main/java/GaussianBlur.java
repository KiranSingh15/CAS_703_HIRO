import java.awt.*;
import java.awt.image.BufferedImage;

public class GaussianBlur {
    // Apply a simple Gaussian blur (3x3 kernel)
    public static BufferedImage applyGaussianBlur(BufferedImage image) {
        float[] kernel = {
                1/16f, 2/16f, 1/16f,
                2/16f, 4/16f, 2/16f,
                1/16f, 2/16f, 1/16f
        };

        BufferedImage result = new BufferedImage(image.getWidth(), image.getHeight(), BufferedImage.TYPE_BYTE_GRAY);

        for (int x = 1; x < image.getWidth() - 1; x++) {
            for (int y = 1; y < image.getHeight() - 1; y++) {
                float newColor = 0;
                for (int kx = -1; kx <= 1; kx++) {
                    for (int ky = -1; ky <= 1; ky++) {
                        int pixelColor = new Color(image.getRGB(x + kx, y + ky)).getRed();
                        newColor += kernel[(kx + 1) * 3 + (ky + 1)] * pixelColor;
                    }
                }
                result.setRGB(x, y, new Color((int)newColor, (int)newColor, (int)newColor).getRGB());
            }
        }
        return result;
    }
}
