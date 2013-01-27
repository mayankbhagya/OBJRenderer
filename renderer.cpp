#include "renderer.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <GLUT/glut.h>

using namespace std;

Renderer* Renderer::currentInstance;

Renderer::Renderer()
{
  mMesh = NULL;
  currentInstance = this;
}

void Renderer::init(int *argc, char *argv[])
{
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 800);
  glutCreateWindow("OBJRenderer");
}

void Renderer::render(OBJMesh *mesh)
{
  mMesh = mesh;

  //update display list from the mesh
  updateDisplayList();
  
  //wireframe mode
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );  

  //register glut functions
  glutKeyboardFunc(&Renderer::static_keyb);
  glutDisplayFunc(&Renderer::static_loop);

  //launch display loop
  glutMainLoop();
}

void Renderer::updateDisplayList()
{
  //fetch updated list from the mesh
  displayList = mMesh->getTriangles();
  //sort
  std::sort(displayList.begin(), displayList.end());
}

void Renderer::static_keyb(unsigned char key, int x, int y)
{
  currentInstance->keyb(key, x, y);
}


void Renderer::keyb(unsigned char key, int x, int y)
{
  if (key == 's') //xminus
  {
    rotateDisplayList(XMINUS);
  }
  else if (key == 'w') //xplus
  {
    rotateDisplayList(XPLUS);
  }
  else if (key == 'a') //yminus
  {
    rotateDisplayList(YMINUS);
  }
  else if (key == 'd') //yplus
  {
    rotateDisplayList(YPLUS);
  }
  else if (key == 27) //quit
  {
    exit(0);
  }
}

void Renderer::rotateDisplayList(enum DIRECTION d)
{
  //rotate mesh
  mMesh->rotate(d);  
  //update display list form the mesh
  updateDisplayList();
  //post redisplay
  glutPostRedisplay();
}


void Renderer::static_loop(void)
{
  currentInstance->loop();
}

void Renderer::loop(void)
{
  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  debugDrawTriangles();

  glutSwapBuffers();  
}

void Renderer::debugDrawTriangles()
{
  std::vector<OBJMeshTriangle>::iterator i;
  for (i = displayList.begin(); i != displayList.end(); ++i)
  {
    glBegin(GL_TRIANGLES);
    glColor3f(abs((*i).n1.k), 0, 0);
    glVertex3f((*i).v1.x, (*i).v1.y, (*i).v1.z);
    glColor3f(abs((*i).n2.k), 0, 0);
    glVertex3f((*i).v2.x, (*i).v2.y, (*i).v2.z);
    glColor3f(abs((*i).n3.k), 0, 0);
    glVertex3f((*i).v3.x, (*i).v3.y, (*i).v3.z);
    glEnd();
  }
}

void Renderer::drawTriangles()
{

}
