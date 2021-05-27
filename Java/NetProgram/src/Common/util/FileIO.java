package Common.util;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileIO {
    public static void saveDataToFile(byte[] data, String path) {
        try {
            FileOutputStream imageOutput = new FileOutputStream(new java.io.File(path));
            imageOutput.write(data, 0, data.length);
            imageOutput.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    
    public static byte[] readDataFromFile(String path) {
        try {
            FileInputStream input = new FileInputStream(new java.io.File(path));
            ByteArrayOutputStream output = new ByteArrayOutputStream();
            byte[] buf = new byte[1024];
            int numBytesRead = 0;
            while ((numBytesRead = input.read(buf)) != -1) {
                output.write(buf, 0, numBytesRead);
            }
            return output.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new byte[0];
    }
    public static byte[] readDataFromImage(BufferedImage img) {
        try {
            ByteArrayOutputStream  output = new ByteArrayOutputStream();
            ImageIO.write(img, "png", output);
            return output.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new byte[0];
    }
}
