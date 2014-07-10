#include "Drawable.h"
#include "Track_d.h"
#include <GLTriangleBatch.h>
#include <math3d.h>

class TrackBatch : public Drawable
{
	private:
	GLTriangleBatch* trackBatch;
	public:
	TrackBatch(Track _track);
	void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
};
