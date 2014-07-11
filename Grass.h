
#include "Drawable.h"

class Grass : public Drawable
{
	private:
		static const double height = -0.1;
		int textureID;
		GLTriangleBatch* batch;
	public:
		Grass(int _textureID);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
};