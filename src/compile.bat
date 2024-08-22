@echo off

rem Compilation phase

echo Creating native header...

javac -h . database\DatabaseWrapper.java

echo Finished creating native header...

echo Compiling C++ files...

echo Compiling Condition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Condition.cpp -o Condition.o -m64

echo Compiling CreateStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" CreateStatement.cpp -o CreateStatement.o -m64

echo Compiling Database.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Database.cpp -o Database.o -m64

echo Compiling DatabaseWrapper.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" DatabaseWrapper.cpp -o DatabaseWrapper.o -m64

echo Compiling DeleteStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" DeleteStatement.cpp -o DeleteStatement.o -m64

echo Compiling DropStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" DropStatement.cpp -o DropStatement.o -m64

echo Compiling EqualCondition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" EqualCondition.cpp -o EqualCondition.o -m64

echo Compiling Filter.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Filter.cpp -o Filter.o -m64

echo Compiling Format.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Format.cpp -o Format.o -m64

echo Compiling InsertStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" InsertStatement.cpp -o InsertStatement.o -m64

echo Compiling NotEqualCondition.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" NotEqualCondition.cpp -o NotEqualCondition.o -m64

echo Compiling Query.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Query.cpp -o Query.o -m64

echo Compiling Record.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Record.cpp -o Record.o -m64

echo Compiling SelectStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" SelectStatement.cpp -o SelectStatement.o -m64

echo Compiling ShowStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" ShowStatement.cpp -o ShowStatement.o -m64

echo Compiling Statement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Statement.cpp -o Statement.o -m64

echo Compiling Table.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Table.cpp -o Table.o -m64

echo Compiling UpdateStatement.cpp...
g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" UpdateStatement.cpp -o UpdateStatement.o -m64

@REM echo Compiling Menu.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Menu.cpp -o Menu.o -m64
@REM
@REM echo Compiling MenuController.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" MenuController.cpp -o MenuController.o -m64
@REM
@REM echo Compiling MenuController.cpp...
@REM g++ -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" main.cpp -o main.o -m64

echo Compilation completed.

rem Linking phase
echo Linking object files into dbnative.dll...

g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o dbnative.dll -m64 Condition.o CreateStatement.o Database.o DatabaseWrapper.o DeleteStatement.o DropStatement.o EqualCondition.o Filter.o Format.o InsertStatement.o NotEqualCondition.o Query.o Record.o SelectStatement.o ShowStatement.o Statement.o Table.o UpdateStatement.o

echo Linking completed.

rem Cleanup intermediate object files (optional)
rem del *.o

echo All processes completed successfully.
