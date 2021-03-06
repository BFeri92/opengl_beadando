#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <StopWatch.h>

#include "Drawable.h"
#include "PositionData.h"
#include "Track.h"
#include <string>

class Car : public Drawable
{

	private:
		CStopWatch timer;
		PositionData pos;
		GLTriangleBatch* batch;
		Track& track;
		double speed;
		double positionOnTrack;
		double horizPosOnTrack;
		int speedChange;
		static const double maxSpeed=0.00035;
		static const double speedIncPerSec=0.0000001;
		static const double speedAutoDecPerSec=0.00000001;
		int textureID;
		int roundCounter;
		std::string name;
	public:
		static const int KEEP_SPEED=0;
		static const int FASTER=1;
		static const int SLOWER=-1;
		Car(GLTriangleBatch *_batch, double _horizPosOnTrack, Track& _track, int _textureID, std::string name);
		void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix);
		void step();
		void setSpeedChange(int _speedChange);
		PositionData getPositionData();
};

#endif
