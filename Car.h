#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <StopWatch.h>

#include "Drawable.h"
#include "PositionData.h"

class Car : public Drawable
{
	
	private:
		CStopWatch timer;
		PositionData pos;
		GLTriangleBatch* batch;
		double speed;
		double positionOnTrack;
		double horizPosOnTrack;
		int speedChange;
		static const double maxSpeed=0.1;
		static const double speedIncPerSec=0.00001;
	public:
		static const int KEEP_SPEED=0;
		static const int FASTER=1;
		static const int SLOWER=-1;
		Car(GLTriangleBatch *_batch, double _horizPosOnTrack);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
		void step();
		void setSpeedChange(int _speedChange);
		PositionData getPositionData();
};

#endif