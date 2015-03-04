rd /s /q bin.pruned
mkdir bin.pruned
java -jar %PROGUARD_HOME%\lib\proguard.jar -libraryjars "%JAVA_HOME%\lib\rt.jar" @proguard-prune-alox-all.pro