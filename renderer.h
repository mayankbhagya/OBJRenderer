#ifndef __renderer_h_
#define __renderer_h_

#include "objparser.h"

class Renderer
{
 public:
  Renderer();
  void init(int *argc, char *argv[]);
  void render(OBJMesh *mesh);

 private:
  OBJMesh *mMesh;
  std::vector<OBJMeshTriangle> displayList;

  void loop(void);
  void keyb(unsigned char key, int x, int y);
  void updateDisplayList();
  void rotateDisplayList(enum DIRECTION);
  void drawTriangles();
  void debugDrawTriangles();


  static void static_keyb(unsigned char key, int x, int y);
  static void static_loop(void);
  static Renderer *currentInstance;
};

#endif /* __renderer_h_ */
