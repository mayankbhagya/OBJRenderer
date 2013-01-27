#include "objparser.h"
#include <iostream>
#include <cmath>

using namespace std;

/****************
 * OBJMeshPoint
 ****************/
OBJMeshPoint::OBJMeshPoint() {}

OBJMeshPoint::OBJMeshPoint(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

/****************
 * OBJMeshNormal
 ****************/
OBJMeshNormal::OBJMeshNormal() 
{
  i = 0;
  j = 0;
  k = 0;
}

OBJMeshNormal::OBJMeshNormal(float i, float j, float k)
{
  this->i = i;
  this->j = j;
  this->k = k;
}

/****************
 * OBJMeshTriangle
 ****************/

OBJMeshPoint OBJMeshTriangle::getCentroid() const
{
  OBJMeshPoint c;
  c.x = (v1.x + v2.x + v3.x) / 3;
  c.y = (v1.y + v2.y + v3.y) / 3;
  c.z = (v1.z + v2.z + v3.z) / 3;
  return c;
}

bool OBJMeshTriangle::operator < (const OBJMeshTriangle& other) const
{
  return getCentroid().z < other.getCentroid().z;
}

/****************
 * OBJParser
 ****************/

OBJMesh* OBJParser::load(char *path)
{
  if (!path)
    return NULL;
  
  GLMmodel *model = glmReadOBJ(path);

  OBJMesh *m = new OBJMesh(model);
  return m;
}

/****************
 * OBJMesh
 *****************/

OBJMesh::OBJMesh(GLMmodel *model)
{
  mModel = model;
  glmUnitize(mModel);

  generateNormals();
}

void OBJMesh::generateNormals()
{
  glmFacetNormals(mModel);
  glmVertexNormals(mModel, 30);
}

void OBJMesh::rotate(enum DIRECTION d)
{
  for (int i = 0; i < mModel->numvertices; i++)
  {
    float x, y, z;
    x = mModel->vertices[3*i + 0];
    y = mModel->vertices[3*i + 1];
    z = mModel->vertices[3*i + 2];
    switch(d)
    {
    case XPLUS:
      mModel->vertices[3*i + 1] = y*cos(M_PI/12) + z*sin(M_PI/12);
      mModel->vertices[3*i + 2] = -y*sin(M_PI/12) + z*cos(M_PI/12);      
      break;
    case XMINUS:
      mModel->vertices[3*i + 1] = y*cos(M_PI/12) - z*sin(M_PI/12);
      mModel->vertices[3*i + 2] = y*sin(M_PI/12) + z*cos(M_PI/12);
      break;
    case YMINUS:
      mModel->vertices[3*i + 0] = x*cos(M_PI/12) - z*sin(M_PI/12);
      mModel->vertices[3*i + 2] = x*sin(M_PI/12) + z*cos(M_PI/12);
      break;
    case YPLUS:
      mModel->vertices[3*i + 0] = x*cos(M_PI/12) + z*sin(M_PI/12);
      mModel->vertices[3*i + 2] = -x*sin(M_PI/12) + z*cos(M_PI/12);
      break;
    }
  }
  generateNormals();
}

int OBJMesh::numTriangles()
{
  return mModel->numtriangles;
}

std::vector<OBJMeshTriangle> OBJMesh::getTriangles()
{
  int listSize = numTriangles();
  std::vector<OBJMeshTriangle> list (listSize);

  std::vector<OBJMeshTriangle>::iterator i;
  for (i = list.begin(); i != list.end(); ++i)
  {
    //get corresponding model triangle
    GLMtriangle t = mModel->triangles[std::distance(list.begin(), i)];

    //get v1
    int vidx = t.vindices[0];
    (*i).v1.x = (float)mModel->vertices[3*vidx + 0];
    (*i).v1.y = (float)mModel->vertices[3*vidx + 1];
    (*i).v1.z = (float)mModel->vertices[3*vidx + 2];
    //get v2
    vidx = t.vindices[1];
    (*i).v2.x = (float)mModel->vertices[3*vidx + 0];
    (*i).v2.y = (float)mModel->vertices[3*vidx + 1];
    (*i).v2.z = (float)mModel->vertices[3*vidx + 2];
    //get v3
    vidx = t.vindices[2];
    (*i).v3.x = (float)mModel->vertices[3*vidx + 0];
    (*i).v3.y = (float)mModel->vertices[3*vidx + 1];
    (*i).v3.z = (float)mModel->vertices[3*vidx + 2];

    //get n1
    int nidx = t.nindices[0];
    (*i).n1.i = (float)mModel->normals[3*nidx + 0];
    (*i).n1.j = (float)mModel->normals[3*nidx + 1];
    (*i).n1.k = (float)mModel->normals[3*nidx + 2];
    //get n2
    nidx = t.nindices[1];
    (*i).n2.i = (float)mModel->normals[3*nidx + 0];
    (*i).n2.j = (float)mModel->normals[3*nidx + 1];
    (*i).n2.k = (float)mModel->normals[3*nidx + 2];
    //get n3
    nidx = t.nindices[2];
    (*i).n3.i = (float)mModel->normals[3*nidx + 0];
    (*i).n3.j = (float)mModel->normals[3*nidx + 1];
    (*i).n3.k = (float)mModel->normals[3*nidx + 2];
  }
  return list;
}

