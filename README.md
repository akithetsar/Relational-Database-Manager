# JNI Code Editor

A simple and efficient code editor that integrates native code with Java via the Java Native Interface (JNI). The editor provides fast, lightweight editing with features tailored for Java + native development: syntax highlighting, code completion, native C/C++ function generation, and convenient DLL creation and run configurations.

This repository demonstrates how to combine Java GUI tooling with native compilation workflows to streamline developing and testing JNI-based applications.

## Key Features

- Syntax highlighting for multiple programming languages with customizable rules.
- Intelligent code completion to speed up editing.
- Cross-platform support (Windows, macOS, Linux) through JNI.
- Lightweight and fast with a small memory footprint.
- Generate C++ function stubs for Java native methods directly from the editor.
- Generate Dynamic Link Libraries (DLLs) or shared libraries from C/C++ sources.
- Create and manage run configurations (main class, library path, etc.).

## Additional editor conveniences

- Generate C++ Functions:
  - Right-click a native method declaration in Java and choose "Generate C++ Function" to produce a ready-to-edit C++ implementation stub.
- Generate DLL / Shared Library:
  - Right-click a C++ file and select "Generate DLL" (Windows) or "Generate Shared Library" (Linux/macOS) to compile the native code into a library usable by your Java app.
- Run Configurations:
  - Add run configurations from the Run menu to specify the main class, JVM options, and library path for testing your JNI-enabled application.

## Requirements

- Java Development Kit (JDK) 8 or higher
- C/C++ compiler:
  - Linux: GCC (gcc/g++)
  - macOS: Clang (via Xcode Command Line Tools)
  - Windows: MSVC (Visual Studio) or MinGW/GCC
- Maven (for building the Java portion)
- Environment variables:
  - JAVA_HOME: path to JDK installation
  - PATH: include JDK bin directory and the C/C++ compiler bin directory (e.g., gcc or cl)

## Quick start

1. Ensure JAVA_HOME and your C/C++ toolchain are set up and accessible via PATH.
2. Build the Java editor:
   - mvn package
3. Run the editor (example):
   - java -jar target/jni-code-editor.jar
4. To generate C++ function stubs:
   - Open a Java file with a native method, right-click the method name and select "Generate C++ Function".
   - Edit the generated C++ file as needed.
5. To compile a native library:
   - Right-click the C++ file and choose "Generate DLL" (Windows) or "Generate Shared Library" (Linux/macOS).
   - The editor will run the configured compiler command and place the library in the configured output folder.
6. Configure and run your JNI application:
   - Add a run configuration (Run → Add), set the main class and point the java.library.path to the generated native libraries, then run.



