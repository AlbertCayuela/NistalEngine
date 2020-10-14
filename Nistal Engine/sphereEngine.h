#define _USE_MATH_DEFINES

#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include <cmath>

using namespace std;

class SphereRender
{
protected:

	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> texcoords;
	vector<GLushort> indices;

public:
	SphereRender(float radius, unsigned int rings, unsigned int sectors);
	void DrawSphere(GLfloat x, GLfloat y, GLfloat z);
};