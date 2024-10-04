//todo: refactor
//todo: ulepšaj
//todo: dokumentacija

package database;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import javafx.beans.property.SimpleStringProperty;
import org.fxmisc.richtext.CodeArea;
import org.fxmisc.richtext.LineNumberFactory;
import org.fxmisc.richtext.model.StyleSpans;
import org.fxmisc.richtext.model.StyleSpansBuilder;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Files;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Controller implements Initializable {

    private DatabaseWrapper currDb = null;

    private boolean saved = false;
    private boolean isSQL = false;
    private String loadedDatabasePath = null;

    @FXML
    private CodeArea codeArea;

    @FXML
    private ListView<String> tableListView;

    @FXML
    private TableView<Map<String, String>> dataTable;

    private Map<String, List<Map<String, String>>> tablesData = new HashMap<>();
    private Map<String, String[]> tablesColumns = new HashMap<>();

//------------FUNCTIONS-----------------

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        Styling.codeAreaInit(codeArea);
    }

    @FXML
    public void createNewDatabase(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Create New Database");
        dialog.setHeaderText("Enter the name for the new database:");
        dialog.setContentText("Database Name:");

        dialog.showAndWait().ifPresent(name -> {
            currDb = new DatabaseWrapper();
            currDb.init(name);
        });
    }

    @FXML
    public void loadExistingDatabase(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Load Database");
        dialog.setHeaderText("Enter the path to the database file:");
        dialog.setContentText("Database Path:");

        dialog.showAndWait().ifPresent(path -> {
            File file = new File(path);

            // Check if the file is an SQL file
            if (path.endsWith(".sql")) {
                try {
                    // Initialize a new empty database
                    currDb = new DatabaseWrapper();
                    currDb.init("");

                    // Read the SQL file
                    String sqlContent = new String(Files.readAllBytes(file.toPath()));
                    // Execute the queries in the SQL file
                    currDb.executeQuery(sqlContent);

                    // Update the database view after execution
                    currDb.executeQuery("SHOW TABLES;");
                    String bufferFilePath = "bufferFile.txt";
                    File bufferFile = new File(bufferFilePath);

                    // Parse the buffer file to get the data
                    ProcessDatabase.parseBufferFile(bufferFile, tablesData, tablesColumns);
                    tableListView.getItems().clear();
                    tableListView.getItems().addAll(tablesData.keySet());

                    saved = true;
                    loadedDatabasePath = path;
                    isSQL = true;


                } catch (IOException e) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            } else {
                // If it's not an SQL file, handle as a regular database load
                String bufferFilePath = "bufferFile.txt";
                String errorFilePath = "errorFile.txt";

                File bufferFile = new File(bufferFilePath);
                File errorFile = new File(errorFilePath);

                try {
                    FileManager.handleFile(bufferFile);
                    FileManager.handleFile(errorFile);

                    currDb = new DatabaseWrapper();
                    currDb.init("Test");
                    currDb.loadDatabase(path);
                    if (errorFile.length() > 0) {
                        String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
                        Errors.showAlert("Error", errorMessage);
                        return;
                    }
                    saved = true;
                    loadedDatabasePath = path;
                    currDb.executeQuery("SHOW TABLES;");
                    ProcessDatabase.parseBufferFile(bufferFile, tablesData, tablesColumns);

                    tableListView.getItems().clear();
                    tableListView.getItems().addAll(tablesData.keySet());

                } catch (IOException e) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            }
        });
    }

    @FXML
    public void executeQuery(ActionEvent actionEvent) {
        if(currDb == null){
            Errors.showAlert("Database error", "No database loaded");
            return;
        }

        String bufferFilePath = "bufferFile.txt";
        String errorFilePath = "errorFile.txt";

        File bufferFile = new File(bufferFilePath);
        File errorFile = new File(errorFilePath);

        try {
            FileManager.handleFile(bufferFile);
            FileManager.handleFile(errorFile);

            String queryText = codeArea.getText();
            queryText += "SHOW TABLES;";
            currDb.executeQuery(queryText);

            if(Errors.checkError(errorFile) == -1) return;;
            saved = false;
            ProcessDatabase.parseBufferFile(bufferFile, tablesData, tablesColumns);

            tableListView.getItems().clear();
            tableListView.getItems().addAll(tablesData.keySet());


        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    @FXML
    private void exportToSQL(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Export to SQL");
        dialog.setHeaderText("Enter the path to export the SQL file:");
        dialog.setContentText("Export Path:");

        dialog.showAndWait().ifPresent(path -> {
            if (currDb != null) {
                loadedDatabasePath = path;
                currDb.exportToSQL(path);
            } else {
                Errors.showAlert("Database Error", "No database loaded.");
            }
        });
    }

    @FXML
    private void exportToCustom(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Export to Custom Format");
        dialog.setHeaderText("Enter the path to export the custom file:");
        dialog.setContentText("Export Path:");

        dialog.showAndWait().ifPresent(path -> {
            if (currDb != null) {
                currDb.exportToCustom(path);
            } else {
                Errors.showAlert("Database Error", "No database loaded.");
            }
        });
    }

    @FXML
    private void saveDatabase(ActionEvent actionEvent) {
        if (currDb == null) {
            Errors.showAlert("Database error", "No database loaded");
            return;
        }

        if (loadedDatabasePath != null) {
            if(isSQL) {
                currDb.exportToSQL(loadedDatabasePath);
            }
            else{
                currDb.exportToCustom(loadedDatabasePath);
            }
        } else {
            if(isSQL){
                exportToSQL(actionEvent);
            }
            else{
                exportToCustom(actionEvent);
            }
        }
    }

    @FXML
    private void handleTableSelection(MouseEvent event) {
        String selectedTable = tableListView.getSelectionModel().getSelectedItem();
        if (selectedTable != null) {
            ProcessDatabase.showTableData(selectedTable, tablesData, tablesColumns, dataTable);
        }
    }

    @FXML
    public void showSelectedTable(ActionEvent actionEvent) {
        if (currDb == null) {
            Errors.showAlert("Database Error", "No database loaded.");
            return;
        }

        String bufferFilePath = "bufferFile.txt";
        String errorFilePath = "errorFile.txt";

        File bufferFile = new File(bufferFilePath);
        File errorFile = new File(errorFilePath);

        try {
            FileManager.handleFile(bufferFile);
            FileManager.handleFile(errorFile);

            currDb.executeQuery("SHOW TABLES;");

            if(Errors.checkError(errorFile) == -1) return;;

            ProcessDatabase.parseBufferFile(bufferFile, tablesData, tablesColumns);

            tableListView.getItems().clear();
            tableListView.getItems().addAll(tablesData.keySet());

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    @FXML
    public void dropSelectedTable(ActionEvent actionEvent) {
        if (currDb == null) {
            Errors.showAlert("Database Error", "No database loaded.");
            return;
        }

        String selectedTable = tableListView.getSelectionModel().getSelectedItem();
        if (selectedTable == null) {
            Errors.showAlert("Table Selection Error", "No table selected.");
            return;
        }

        String query = "DROP TABLE " + selectedTable + ";";

        String bufferFilePath = "bufferFile.txt";
        String errorFilePath = "errorFile.txt";

        File bufferFile = new File(bufferFilePath);
        File errorFile = new File(errorFilePath);

        try {
            FileManager.handleFile(bufferFile);
            FileManager.handleFile(errorFile);

            currDb.executeQuery(query);

            if (errorFile.length() > 0) {
                String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
                Errors.showAlert("Error", errorMessage);
                return;
            }

            // Update the list of tables after the drop
            currDb.executeQuery("SHOW TABLES;");
            ProcessDatabase.parseBufferFile(bufferFile, tablesData, tablesColumns);
            tableListView.getItems().clear();
            tableListView.getItems().addAll(tablesData.keySet());

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }




    public void exit(ActionEvent actionEvent) {
        if (!saved && currDb != null) {
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
            alert.setTitle("Unsaved Changes");
            alert.setHeaderText("You have unsaved changes.");
            alert.setContentText("Do you want to save your changes before exiting?");
        }
    }
}
