
//todo: SELECT WHERE nije opcioni, proveri C++ kod
//todo: load sql u c++

package database;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import javafx.beans.property.SimpleStringProperty;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Controller {

    private DatabaseWrapper currDb = null;

    private boolean saved = false;

    private String loadedDatabasePath = null;

    @FXML
    private TextArea queryResultArea;

    @FXML
    private ListView<String> tableListView;

    @FXML
    private TableView<Map<String, String>> dataTable;

    private Map<String, List<Map<String, String>>> tablesData = new HashMap<>();

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

    public void loadExistingDatabase(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Load Database");
        dialog.setHeaderText("Enter the path to the database file:");
        dialog.setContentText("Database Path:");

        dialog.showAndWait().ifPresent(path -> {
            String bufferFilePath = "C:\\Users\\akith\\IdeaProjects\\PoopDatabase\\bufferFile.txt";
            String errorFilePath = "C:\\Users\\akith\\IdeaProjects\\PoopDatabase\\errorFile.txt";

            File bufferFile = new File(bufferFilePath);
            File errorFile = new File(errorFilePath);

            try {
                handleFile(bufferFile);
                handleFile(errorFile);

                currDb = new DatabaseWrapper();
                currDb.init("Test");
                currDb.loadDatabase(path);
                if (errorFile.length() > 0) {
                    String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
                    showAlert("Error", errorMessage);
                    return;
                }
                saved = true;
                loadedDatabasePath = path;
                currDb.executeQuery("SHOW TABLES;");
                parseBufferFile(bufferFile);

                tableListView.getItems().clear();
                tableListView.getItems().addAll(tablesData.keySet());

            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        });
    }

    public void exit(ActionEvent actionEvent) {
        // Implementation for exiting the application
    }

    @FXML
    public void executeQuery(ActionEvent actionEvent) {
        if(currDb == null){
            showAlert("Database error", "No database loaded");
            return;
        }

        String bufferFilePath = "C:\\Users\\akith\\IdeaProjects\\PoopDatabase\\bufferFile.txt";
        String errorFilePath = "C:\\Users\\akith\\IdeaProjects\\PoopDatabase\\errorFile.txt";

        File bufferFile = new File(bufferFilePath);
        File errorFile = new File(errorFilePath);

        try {
            handleFile(bufferFile);
            handleFile(errorFile);

            String queryText = queryResultArea.getText();
            currDb.executeQuery(queryText);

            if (errorFile.length() > 0) {
                String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
                showAlert("Error", errorMessage);
                return;
            }
            saved = false;
            parseBufferFile(bufferFile);

            tableListView.getItems().clear();
            tableListView.getItems().addAll(tablesData.keySet());

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    private void parseBufferFile(File bufferFile) throws IOException {
        tablesData.clear();
        List<String> lines = Files.readAllLines(bufferFile.toPath());
        String currentTable = null;
        List<Map<String, String>> currentTableData = null;
        String[] currentColumns = null;

        for (String line : lines) {
            if (line.equals("@")) {
                currentTable = null;
                currentTableData = null;
                currentColumns = null;
                continue;
            }
            if (currentTable == null) {
                currentTable = line;
                currentTableData = new ArrayList<>();
                tablesData.put(currentTable, currentTableData);
            } else if (currentColumns == null) {
                currentColumns = line.split("/");
            } else {
                String[] values = line.split("\\|");
                Map<String, String> row = new HashMap<>();
                for (int i = 0; i < currentColumns.length; i++) {
                    row.put(currentColumns[i], values[i]);
                }
                currentTableData.add(row);
            }
        }
    }

    @FXML
    private void handleTableSelection(MouseEvent event) {
        String selectedTable = tableListView.getSelectionModel().getSelectedItem();
        if (selectedTable != null) {
            showTableData(selectedTable);
        }
    }

    private void showTableData(String tableName) {
        List<Map<String, String>> tableData = tablesData.get(tableName);
        if (tableData == null || tableData.isEmpty()) {
            dataTable.getColumns().clear();
            dataTable.getItems().clear();
            return;
        }

        dataTable.getColumns().clear();

        for (String column : tableData.get(0).keySet()) {
            TableColumn<Map<String, String>, String> tableColumn = new TableColumn<>(column);
            tableColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().get(column)));
            dataTable.getColumns().add(tableColumn);
        }

        ObservableList<Map<String, String>> tableItems = FXCollections.observableArrayList(tableData);
        dataTable.setItems(tableItems);
    }

    private void handleFile(File file) throws IOException {
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

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
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
                showAlert("Database Error", "No database loaded.");
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
                showAlert("Database Error", "No database loaded.");
            }
        });
    }

    @FXML
    private void saveDatabase(ActionEvent actionEvent) {
        if (currDb == null) {
            showAlert("Database error", "No database loaded");
            return;
        }

        if (loadedDatabasePath != null) {
            currDb.exportToSQL(loadedDatabasePath);
        } else {
            exportToSQL(actionEvent);
        }
    }
}
