#ifndef TRACKPOINTSBATCH_H_INCLUDED
#define TRACKPOINTSBATCH_H_INCLUDED
#include "Drawable.h"
#include "Track.h"
#include <GLBatch.h>
#include <math3d.h>

class TrackPointsBatch : public Drawable
{
	private:
		GLBatch* trackPointsBatch;
	public:
		TrackPointsBatch(Track& _track);
		void update(Track& _track);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
};
#endif
