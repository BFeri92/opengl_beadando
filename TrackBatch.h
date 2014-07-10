#ifndef TRACKBATCH_H_INCLUDED
#define TRACKBATCH_H_INCLUDED


#include "Drawable.h"
#include "Track.h"
#include <GLTriangleBatch.h>
#include <math3d.h>

class TrackBatch : public Drawable
{
	private:
	GLTriangleBatch* trackBatch;
	public:
	TrackBatch(Track& _track);
	void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
	void update(Track& _track);
};

#endif
