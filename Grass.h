
#include "Drawable.h"

class Grass : public Drawable
{
	private:
		static const double height = -4.0;
		static const double width = 10000.0;
		int textureID;
		GLTriangleBatch* batch;
	public:
		Grass(int _textureID);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
};
