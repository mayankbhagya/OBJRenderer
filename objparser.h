#ifndef __objparser_h_
#define __objparser_h_

#include "glm.h"
#include <vector>

enum DIRECTION {XMINUS, XPLUS, YMINUS, YPLUS};

class OBJMeshPoint
{
 public:
  OBJMeshPoint();
  OBJMeshPoint(float x, float y, float z);
  float x, y, z;
};

class OBJMeshNormal
{
 public:
  OBJMeshNormal();
  OBJMeshNormal(float i, float j, float k);
  float i, j, k;
};

class OBJMeshTriangle
{
 public:
  OBJMeshPoint v1, v2, v3;
  OBJMeshNormal n1, n2, n3;
  OBJMeshPoint getCentroid() const;
  bool operator < (const OBJMeshTriangle& other) const;
};

class OBJMesh
{
 public:
  OBJMesh(GLMmodel *model);
  ~OBJMesh();

  int numTriangles();
  std::vector<OBJMeshTriangle> getTriangles();

  void rotate(enum DIRECTION d);

 private:
  GLMmodel *mModel;
  void generateNormals();
};

class OBJParser
{
 public:
  OBJMesh* load(char *path);
};

#endif /* __objparser_h_ */
