#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <GLMatrixStack.h>

class Drawable{
	public:
		virtual void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix) = 0;
};

#endif
