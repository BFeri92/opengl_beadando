 #include "PositionData.h"

    PositionData::PositionData(){};

    PositionData::PositionData(GLdouble _x,GLdouble _y,GLdouble _alfa){
        x=_x;
        y=_y;
        alfa=_alfa;
    };

	void PositionData::getTransformationMatrix(M3DMatrix44f& res)
	{
		M3DMatrix44f rot;
		
		M3DMatrix44f transl;
		m3dTranslationMatrix44(transl, x,0,y);
		m3dRotationMatrix44(rot, alfa, 0.0, 1.0, 0.0);
		m3dMatrixMultiply44(res, transl, rot);
	}
