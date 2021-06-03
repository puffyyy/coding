import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Test {
    public static void main(String[] args) {
        try {
           copyDirectiory("./src","./copy/src");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void copyDirectiory(String sourceDir, String targetDir) throws IOException {
        File src = new File(sourceDir);
        File dest = new File(targetDir);
        if(!dest.exists())
        {
            dest.mkdirs();
        }
        if (dest.isDirectory()&&src.isDirectory()) {
            File[] files = src.listFiles();
            if (files != null) {
                for (File f : files) {
                    if (f.isDirectory()) {
                        copyDirectiory(f.getAbsolutePath(), targetDir);
                    } else {
                        copyFile(f.getAbsolutePath(), dest.getCanonicalPath() + "/" + f.getName());
                    }
                }
            }
        }
    }
    
    public static void copyFile(String sourceFile, String targetFile) throws IOException {
        FileInputStream fis = new FileInputStream(sourceFile);
        File outfile = new File(targetFile);
        outfile.createNewFile();
        FileOutputStream fos = new FileOutputStream(outfile);
        byte[] buf = new byte[256];
        int len;
        while ((len = fis.read(buf)) > 0) {
            fos.write(buf, 0, len);
        }
        fis.close();
        fos.close();
    }
}