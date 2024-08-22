package database;

import java.util.HashMap;
import java.util.Map;

public class DatabaseWrapper {



    // Native method declarations
    public native void init(String name);

    public native String getName();

    public native boolean isChanged();

    public native void setFilePath(String path);

    public native String getFilePath();

    public native void setChange(boolean changed);

    public native void executeQuery(String queryText);

    public native int test(int a, int b);

    public native void loadDatabase(String path);

    public native void exportToSQL(String path);
    public native void exportToCustom(String path);

    static {
        // Load the native library
        System.loadLibrary("dbnative");
    }

    public static void main(String[] args) {

    }

}
