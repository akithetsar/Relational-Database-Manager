package database;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileManager {

    public static void handleFile(File file) throws IOException {
        if (file.exists()) {
            if (!file.delete()) {
                return;
            }
        }

        if (!file.createNewFile()) {
            return;
        }

        FileWriter writer = new FileWriter(file);
        writer.close();
    }
}
