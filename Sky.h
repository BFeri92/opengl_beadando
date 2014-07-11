#ifndef SKY_H_INCLUDED
#define SKY_H_INCLUDED

#include <GLTools.h>
#include <math3d.h>
#include <Drawable.h>

class Sky : public Drawable
{
	private:
		GLuint shader;
		GLint	locAmbientEmit;			// The location of the ambient color
		GLint	locMVPEmit;				// The location of the ModelViewProjection matrix uniform
		GLint	locMVEmit;				// The location of the ModelView matrix uniform
		GLint   locTextureEmit;
		GLTriangleBatch batch;
		int textureID;
	public:
		Sky(int _textureID);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
};

#endif
