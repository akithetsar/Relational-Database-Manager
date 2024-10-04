package database;

import javafx.scene.control.Alert;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Errors {

    public static int checkError(File errorFile) throws IOException {

        if (errorFile.length() > 0) {
            String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
            showAlert("Error", errorMessage);
            return -1;
        }
        return 0;
    }

    public static void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}
