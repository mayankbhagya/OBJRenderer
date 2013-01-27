#include <iostream>
#include "objparser.h"
#include "renderer.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Argument required: <meshfile.obj>\n";
    return 1;
  }

  OBJParser parser;
  //char path[]="meshes/clipHead.obj";
  OBJMesh *m = parser.load(argv[1]);

  Renderer renderer;
  renderer.init(&argc, argv);
  renderer.render(m);

  return 0;
}
