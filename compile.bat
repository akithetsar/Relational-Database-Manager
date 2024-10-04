@echo off

rem Compilation phase

echo Creating native header...

javac -h . src\database\DatabaseWrapper.java

echo Finished creating native header...

echo Compiling C++ files...

set OBJ_DIR=obj
set SRC_DIR=cppsrc
set HEADER_DIR=cpph
set LIB_DIR=lib

rem Create the object directory and library directory if they don't exist
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%LIB_DIR%" mkdir "%LIB_DIR%"

echo Compiling Condition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Condition.cpp" -o "%OBJ_DIR%\Condition.o" -m64

echo Compiling CreateStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\CreateStatement.cpp" -o "%OBJ_DIR%\CreateStatement.o" -m64

echo Compiling Database.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Database.cpp" -o "%OBJ_DIR%\Database.o" -m64

echo Compiling DatabaseWrapper.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\DatabaseWrapper.cpp" -o "%OBJ_DIR%\DatabaseWrapper.o" -m64

echo Compiling DeleteStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\DeleteStatement.cpp" -o "%OBJ_DIR%\DeleteStatement.o" -m64

echo Compiling DropStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\DropStatement.cpp" -o "%OBJ_DIR%\DropStatement.o" -m64

echo Compiling EqualCondition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\EqualCondition.cpp" -o "%OBJ_DIR%\EqualCondition.o" -m64

echo Compiling Filter.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Filter.cpp" -o "%OBJ_DIR%\Filter.o" -m64

echo Compiling Format.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Format.cpp" -o "%OBJ_DIR%\Format.o" -m64

echo Compiling InsertStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\InsertStatement.cpp" -o "%OBJ_DIR%\InsertStatement.o" -m64

echo Compiling NotEqualCondition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\NotEqualCondition.cpp" -o "%OBJ_DIR%\NotEqualCondition.o" -m64

echo Compiling Query.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Query.cpp" -o "%OBJ_DIR%\Query.o" -m64

echo Compiling Record.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Record.cpp" -o "%OBJ_DIR%\Record.o" -m64

echo Compiling SelectStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\SelectStatement.cpp" -o "%OBJ_DIR%\SelectStatement.o" -m64

echo Compiling ShowStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\ShowStatement.cpp" -o "%OBJ_DIR%\ShowStatement.o" -m64

echo Compiling Statement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Statement.cpp" -o "%OBJ_DIR%\Statement.o" -m64

echo Compiling Table.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\Table.cpp" -o "%OBJ_DIR%\Table.o" -m64

echo Compiling UpdateStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -I"%HEADER_DIR%" "%SRC_DIR%\UpdateStatement.cpp" -o "%OBJ_DIR%\UpdateStatement.o" -m64

@REM echo Compiling Menu.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" "%SRC_DIR%\Menu.cpp" -o "%OBJ_DIR%\Menu.o" -m64
@REM
@REM echo Compiling MenuController.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" "%SRC_DIR%\MenuController.cpp" -o "%OBJ_DIR%\MenuController.o" -m64
@REM
@REM echo Compiling main.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" "%SRC_DIR%\main.cpp" -o "%OBJ_DIR%\main.o" -m64

echo Compilation completed.

rem Linking phase
echo Linking object files into dbnative.dll...

g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o "%LIB_DIR%\dbnative.dll" -m64 "%OBJ_DIR%\Condition.o" "%OBJ_DIR%\CreateStatement.o" "%OBJ_DIR%\Database.o" "%OBJ_DIR%\DatabaseWrapper.o" "%OBJ_DIR%\DeleteStatement.o" "%OBJ_DIR%\DropStatement.o" "%OBJ_DIR%\EqualCondition.o" "%OBJ_DIR%\Filter.o" "%OBJ_DIR%\Format.o" "%OBJ_DIR%\InsertStatement.o" "%OBJ_DIR%\NotEqualCondition.o" "%OBJ_DIR%\Query.o" "%OBJ_DIR%\Record.o" "%OBJ_DIR%\SelectStatement.o" "%OBJ_DIR%\ShowStatement.o" "%OBJ_DIR%\Statement.o" "%OBJ_DIR%\Table.o" "%OBJ_DIR%\UpdateStatement.o"

echo Linking completed.

rem Cleanup intermediate object files (optional)
rem del "%OBJ_DIR%\*.o"

echo All processes completed successfully.
