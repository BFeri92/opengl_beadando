#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <GLMatrixStack.h>

class Drawable{
	virtual void paint(const GLMatrixStack& modelMatrix, const GLMatrixStack& viewMatrix) = 0;
};

#endif
