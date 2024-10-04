import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import database.Controller;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("database/mainWindow.fxml"));
        BorderPane root = loader.load();

        Controller controller = loader.getController();


        primaryStage.setOnCloseRequest(event -> {
            controller.exit(null);
        });

        primaryStage.setTitle("Database Application");
        primaryStage.setScene(new Scene(root, 800, 600));
        primaryStage.getScene().getStylesheets().add(getClass().getResource("styles.css").toExternalForm());
        primaryStage.getIcons().add(new Image("file:" + System.getProperty("user.dir") + "/imgs/logo.jpg"));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
