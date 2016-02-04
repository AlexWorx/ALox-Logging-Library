rm -r bin.pruned/
mkdir bin.pruned
proguard  -libraryjars "$JAVA_HOME/lib/rt.jar" @proguard-prune-alox-all.pro
