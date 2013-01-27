#BUILD INSTRUCTIONS FOR OSX
BUILDDIR=build
FLAGS="-g"

rm -rf $BUILDDIR
mkdir $BUILDDIR
mkdir $BUILDDIR/tmp
mkdir $BUILDDIR/bin

g++ $FLAGS -o $BUILDDIR/tmp/glm.o -c glm.cpp
g++ $FLAGS -o $BUILDDIR/tmp/objparser.o -c objparser.cpp
g++ $FLAGS -o $BUILDDIR/tmp/renderer.o -c renderer.cpp
g++ $FLAGS -o $BUILDDIR/tmp/main.o -c main.cpp

g++ $FLAGS -o $BUILDDIR/bin/objrenderer $BUILDDIR/tmp/glm.o $BUILDDIR/tmp/objparser.o $BUILDDIR/tmp/renderer.o $BUILDDIR/tmp/main.o -framework OpenGL -framework GLUT
