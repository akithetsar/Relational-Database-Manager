package database;

//package database;
//
////todo: refactor
////todo: ulepšaj
////todo: dokumentacija
//
//
//
//import javafx.application.Platform;
//import javafx.collections.FXCollections;
//import javafx.collections.ObservableList;
//import javafx.event.ActionEvent;
//import javafx.fxml.FXML;
//import javafx.fxml.Initializable;
//import javafx.scene.control.*;
//import javafx.scene.input.MouseEvent;
//import javafx.beans.property.SimpleStringProperty;
//import org.fxmisc.richtext.CodeArea;
//import org.fxmisc.richtext.LineNumberFactory;
//import org.fxmisc.richtext.model.StyleSpans;
//import org.fxmisc.richtext.model.StyleSpansBuilder;
//
//import java.io.File;
//import java.io.FileWriter;
//import java.io.IOException;
//import java.net.URL;
//import java.nio.file.Files;
//import java.util.*;
//import java.util.regex.Matcher;
//import java.util.regex.Pattern;
//
//    public class OldController implements Initializable {
//
//        private DatabaseWrapper currDb = null;
//
//        private boolean saved = false;
//        private boolean isSQL = false;
//        private String loadedDatabasePath = null;
//
//        @FXML
//        private CodeArea codeArea;
//
//        @FXML
//        private ListView<String> tableListView;
//
//        @FXML
//        private TableView<Map<String, String>> dataTable;
//
//        private Map<String, List<Map<String, String>>> tablesData = new HashMap<>();
//        private Map<String, String[]> tablesColumns = new HashMap<>();
//
//        public static final String[] KEYWORDS = {
//                "CREATE",
//                "DROP",
//                "SELECT",
//                "FROM",
//                "WHERE",
//                "AND",
//                "INSERT",
//                "VALUES",
//                "UPDATE",
//                "SET",
//                "DELETE",
//                "SHOW",
//                "TABLE",
//                "FROM",
//                "TABLES",
//                "INTO"
//        };
//
//
//        public void createNewDatabase(ActionEvent actionEvent) {
//            TextInputDialog dialog = new TextInputDialog();
//            dialog.setTitle("Create New Database");
//            dialog.setHeaderText("Enter the name for the new database:");
//            dialog.setContentText("Database Name:");
//
//            dialog.showAndWait().ifPresent(name -> {
//                currDb = new DatabaseWrapper();
//                currDb.init(name);
//            });
//        }
//
//        public void loadExistingDatabase(ActionEvent actionEvent) {
//            TextInputDialog dialog = new TextInputDialog();
//            dialog.setTitle("Load Database");
//            dialog.setHeaderText("Enter the path to the database file:");
//            dialog.setContentText("Database Path:");
//
//            dialog.showAndWait().ifPresent(path -> {
//                File file = new File(path);
//
//                // Check if the file is an SQL file
//                if (path.endsWith(".sql")) {
//                    try {
//                        // Initialize a new empty database
//                        currDb = new DatabaseWrapper();
//                        currDb.init("");
//
//                        // Read the SQL file
//                        String sqlContent = new String(Files.readAllBytes(file.toPath()));
//                        // Execute the queries in the SQL file
//                        currDb.executeQuery(sqlContent);
//
//                        // Update the database view after execution
//                        currDb.executeQuery("SHOW TABLES;");
//                        String bufferFilePath = "bufferFile.txt";
//                        File bufferFile = new File(bufferFilePath);
//
//                        // Parse the buffer file to get the data
//                        parseBufferFile(bufferFile);
//                        tableListView.getItems().clear();
//                        tableListView.getItems().addAll(tablesData.keySet());
//
//                        saved = true;
//                        loadedDatabasePath = path;
//                        isSQL = true;
//
//
//                    } catch (IOException e) {
//                        System.out.println("An error occurred.");
//                        e.printStackTrace();
//                    }
//                } else {
//                    // If it's not an SQL file, handle as a regular database load
//                    String bufferFilePath = "bufferFile.txt";
//                    String errorFilePath = "errorFile.txt";
//
//                    File bufferFile = new File(bufferFilePath);
//                    File errorFile = new File(errorFilePath);
//
//                    try {
//                        handleFile(bufferFile);
//                        handleFile(errorFile);
//
//                        currDb = new DatabaseWrapper();
//                        currDb.init("Test");
//                        currDb.loadDatabase(path);
//                        if (errorFile.length() > 0) {
//                            String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
//                            showAlert("Error", errorMessage);
//                            return;
//                        }
//                        saved = true;
//                        loadedDatabasePath = path;
//                        currDb.executeQuery("SHOW TABLES;");
//                        parseBufferFile(bufferFile);
//
//                        tableListView.getItems().clear();
//                        tableListView.getItems().addAll(tablesData.keySet());
//
//                    } catch (IOException e) {
//                        System.out.println("An error occurred.");
//                        e.printStackTrace();
//                    }
//                }
//            });
//        }
//
//        public void exit(ActionEvent actionEvent) {
//            if (!saved && currDb != null) {
//                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
//                alert.setTitle("Unsaved Changes");
//                alert.setHeaderText("You have unsaved changes.");
//                alert.setContentText("Do you want to save your changes before exiting?");
//
//                ButtonType saveAndExitButton = new ButtonType("Save and Exit");
//                ButtonType exitWithoutSavingButton = new ButtonType("Exit without Saving");
//                ButtonType cancelButton = new ButtonType("Cancel");
//
//                alert.getButtonTypes().setAll(saveAndExitButton, exitWithoutSavingButton, cancelButton);
//
//                Optional<ButtonType> result = alert.showAndWait();
//                if (result.isPresent()) {
//                    if (result.get() == saveAndExitButton) {
//                        saveDatabase(actionEvent); // Call the saveDatabase method
//                        Platform.exit();
//                    } else if (result.get() == exitWithoutSavingButton) {
//                        Platform.exit(); // Exit without saving
//                    }
//                    // If "Cancel" is selected, do nothing (return to the application)
//                }
//            } else {
//                Platform.exit(); // Exit if no changes need saving
//            }
//        }
//
//        @FXML
//        public void executeQuery(ActionEvent actionEvent) {
//            if(currDb == null){
//                showAlert("Database error", "No database loaded");
//                return;
//            }
//
//            String bufferFilePath = "bufferFile.txt";
//            String errorFilePath = "errorFile.txt";
//
//            File bufferFile = new File(bufferFilePath);
//            File errorFile = new File(errorFilePath);
//
//            try {
//                handleFile(bufferFile);
//                handleFile(errorFile);
//
//                String queryText = codeArea.getText();
//                queryText += "SHOW TABLES;";
//                currDb.executeQuery(queryText);
//
//                if (errorFile.length() > 0) {
//                    String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
//                    showAlert("Error", errorMessage);
//                    return;
//                }
//                saved = false;
//                parseBufferFile(bufferFile);
//
//                tableListView.getItems().clear();
//                tableListView.getItems().addAll(tablesData.keySet());
//
//
//            } catch (IOException e) {
//                System.out.println("An error occurred.");
//                e.printStackTrace();
//            }
//        }
//
//        private void parseBufferFile(File bufferFile) throws IOException {
//            tablesData.clear();
//            List<String> lines = Files.readAllLines(bufferFile.toPath());
//            String currentTable = null;
//            List<Map<String, String>> currentTableData = null;
//            String[] currentColumns = null;
//            for (String line : lines) {
//                if (line.equals("@")) {
//                    currentTable = null;
//                    currentTableData = null;
//                    currentColumns = null;
//                    continue;
//                }
//                if (currentTable == null) {
//                    currentTable = line;
//                    currentTableData = new ArrayList<>();
//                    tablesData.put(currentTable, currentTableData);
//                } else if (currentColumns == null) {
//                    currentColumns = line.split("/");
//                    tablesColumns.put(currentTable, currentColumns);
//                } else {
//                    String[] values = line.split("\\|");
//                    Map<String, String> row = new HashMap<>();
//                    for (int i = 0; i < currentColumns.length; i++) {
//                        row.put(currentColumns[i], values[i]);
//                    }
//                    currentTableData.add(row);
//                }
//            }
//
//        }
//
//        @FXML
//        private void handleTableSelection(MouseEvent event) {
//            String selectedTable = tableListView.getSelectionModel().getSelectedItem();
//            if (selectedTable != null) {
//                showTableData(selectedTable);
//            }
//        }
//
//        private void showTableData(String tableName) {
//            List<Map<String, String>> tableData = tablesData.get(tableName);
//            String[] currentColumns = tablesColumns.get(tableName);
//
//            dataTable.getColumns().clear(); // Clear existing columns
//
//            System.out.println("Displaying data for table: " + tableName);
//            System.out.println("Current Columns: " + String.join(", ", currentColumns));
//
//            if (tableData == null || tableData.isEmpty()) {
//                if (currentColumns != null) {
//                    for (String column : currentColumns) {
//                        TableColumn<Map<String, String>, String> tableColumn = new TableColumn<>(column);
//                        tableColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().get(column)));
//                        dataTable.getColumns().add(tableColumn);
//                    }
//                }
//                dataTable.getItems().clear();
//                return;
//            }
//
//            if (!tableData.isEmpty()) {
//                // Add columns in the order of currentColumns
//                for (String column : currentColumns) {
//                    TableColumn<Map<String, String>, String> tableColumn = new TableColumn<>(column);
//                    tableColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().get(column)));
//                    dataTable.getColumns().add(tableColumn);
//                }
//            }
//
//            ObservableList<Map<String, String>> tableItems = FXCollections.observableArrayList(tableData);
//            dataTable.setItems(tableItems);
//        }
//
//        private void handleFile(File file) throws IOException {
//            if (file.exists()) {
//                if (!file.delete()) {
//                    return;
//                }
//            }
//
//            if (!file.createNewFile()) {
//                return;
//            }
//
//            FileWriter writer = new FileWriter(file);
//            writer.close();
//        }
//
//        private void showAlert(String title, String message) {
//            Alert alert = new Alert(Alert.AlertType.ERROR);
//            alert.setTitle(title);
//            alert.setHeaderText(null);
//            alert.setContentText(message);
//            alert.showAndWait();
//        }
//
//        @FXML
//        private void exportToSQL(ActionEvent actionEvent) {
//            TextInputDialog dialog = new TextInputDialog();
//            dialog.setTitle("Export to SQL");
//            dialog.setHeaderText("Enter the path to export the SQL file:");
//            dialog.setContentText("Export Path:");
//
//            dialog.showAndWait().ifPresent(path -> {
//                if (currDb != null) {
//                    loadedDatabasePath = path;
//                    currDb.exportToSQL(path);
//                } else {
//                    showAlert("Database Error", "No database loaded.");
//                }
//            });
//        }
//
//        @FXML
//        private void exportToCustom(ActionEvent actionEvent) {
//            TextInputDialog dialog = new TextInputDialog();
//            dialog.setTitle("Export to Custom Format");
//            dialog.setHeaderText("Enter the path to export the custom file:");
//            dialog.setContentText("Export Path:");
//
//            dialog.showAndWait().ifPresent(path -> {
//                if (currDb != null) {
//                    currDb.exportToCustom(path);
//                } else {
//                    showAlert("Database Error", "No database loaded.");
//                }
//            });
//        }
//
//        @FXML
//        private void saveDatabase(ActionEvent actionEvent) {
//            if (currDb == null) {
//                showAlert("Database error", "No database loaded");
//                return;
//            }
//
//            if (loadedDatabasePath != null) {
//                if(isSQL) {
//                    currDb.exportToSQL(loadedDatabasePath);
//                }
//                else{
//                    currDb.exportToCustom(loadedDatabasePath);
//                }
//            } else {
//                if(isSQL){
//                    exportToSQL(actionEvent);
//                }
//                else{
//                    exportToCustom(actionEvent);
//                }
//            }
//        }
//
//        public void showSelectedTable(ActionEvent actionEvent) {
//            if (currDb == null) {
//                showAlert("Database Error", "No database loaded.");
//                return;
//            }
//
//            String bufferFilePath = "bufferFile.txt";
//            String errorFilePath = "errorFile.txt";
//
//            File bufferFile = new File(bufferFilePath);
//            File errorFile = new File(errorFilePath);
//
//            try {
//                handleFile(bufferFile);
//                handleFile(errorFile);
//
//                currDb.executeQuery("SHOW TABLES;");
//
//                if (errorFile.length() > 0) {
//                    String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
//                    showAlert("Error", errorMessage);
//                    return;
//                }
//
//                parseBufferFile(bufferFile);
//
//                tableListView.getItems().clear();
//                tableListView.getItems().addAll(tablesData.keySet());
//
//            } catch (IOException e) {
//                System.out.println("An error occurred.");
//                e.printStackTrace();
//            }
//        }
//
//        public void dropSelectedTable(ActionEvent actionEvent) {
//            if (currDb == null) {
//                showAlert("Database Error", "No database loaded.");
//                return;
//            }
//
//            String selectedTable = tableListView.getSelectionModel().getSelectedItem();
//            if (selectedTable == null) {
//                showAlert("Table Selection Error", "No table selected.");
//                return;
//            }
//
//            String query = "DROP TABLE " + selectedTable + ";";
//
//            String bufferFilePath = "bufferFile.txt";
//            String errorFilePath = "errorFile.txt";
//
//            File bufferFile = new File(bufferFilePath);
//            File errorFile = new File(errorFilePath);
//
//            try {
//                handleFile(bufferFile);
//                handleFile(errorFile);
//
//                currDb.executeQuery(query);
//
//                if (errorFile.length() > 0) {
//                    String errorMessage = new String(Files.readAllBytes(errorFile.toPath()));
//                    showAlert("Error", errorMessage);
//                    return;
//                }
//
//                // Update the list of tables after the drop
//                currDb.executeQuery("SHOW TABLES;");
//                parseBufferFile(bufferFile);
//                tableListView.getItems().clear();
//                tableListView.getItems().addAll(tablesData.keySet());
//
//            } catch (IOException e) {
//                System.out.println("An error occurred.");
//                e.printStackTrace();
//            }
//        }
//
//        @Override
//        public void initialize(URL location, ResourceBundle resources) {
//            codeArea.setParagraphGraphicFactory(LineNumberFactory.get(codeArea));
//            codeArea.textProperty().addListener((obs, oldText, newText) -> {
//                codeArea.setStyleSpans(0, computeHighlighting(newText));
//            });
//        }
//
//        private StyleSpans<Collection<String>> computeHighlighting(String text) {
//            Matcher matcher = Pattern.compile("\\b(" + String.join("|", KEYWORDS) + ")\\b").matcher(text);
//            StyleSpansBuilder<Collection<String>> spansBuilder = new StyleSpansBuilder<>();
//            int lastIdx = 0;
//            while (matcher.find()) {
//                spansBuilder.add(Collections.emptyList(), matcher.start() - lastIdx);
//                spansBuilder.add(Collections.singleton("keyword"), matcher.end() - matcher.start());
//                lastIdx = matcher.end();
//            }
//            spansBuilder.add(Collections.emptyList(), text.length() - lastIdx);
//            return spansBuilder.create();
//        }
//    }
//

