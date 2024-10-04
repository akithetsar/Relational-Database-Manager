package database;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProcessDatabase {

    public static void parseBufferFile(File bufferFile, Map<String, List<Map<String, String>>> tablesData, Map<String, String[]> tablesColumns) throws IOException {
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
                tablesColumns.put(currentTable, currentColumns);
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

    public static void showTableData(String tableName, Map<String, List<Map<String, String>>> tablesData, Map<String, String[]> tablesColumns, TableView<Map<String, String>> dataTable) {
        List<Map<String, String>> tableData = tablesData.get(tableName);
        String[] currentColumns = tablesColumns.get(tableName);

        dataTable.getColumns().clear(); // Clear existing columns

        System.out.println("Displaying data for table: " + tableName);
        System.out.println("Current Columns: " + String.join(", ", currentColumns));

        if (tableData == null || tableData.isEmpty()) {
            if (currentColumns != null) {
                for (String column : currentColumns) {
                    TableColumn<Map<String, String>, String> tableColumn = new TableColumn<>(column);
                    tableColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().get(column)));
                    dataTable.getColumns().add(tableColumn);
                }
            }
            dataTable.getItems().clear();
            return;
        }

        if (!tableData.isEmpty()) {
            // Add columns in the order of currentColumns
            for (String column : currentColumns) {
                TableColumn<Map<String, String>, String> tableColumn = new TableColumn<>(column);
                tableColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().get(column)));
                dataTable.getColumns().add(tableColumn);
            }
        }

        ObservableList<Map<String, String>> tableItems = FXCollections.observableArrayList(tableData);
        dataTable.setItems(tableItems);
    }



}
