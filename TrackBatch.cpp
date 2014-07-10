
#include "TrackBatch.h"
#include "Game.h"
#include <iostream>
#include <GLTools.h>
TrackBatch::TrackBatch(Track& _track)
{
	trackBatch = _track.getBatch();
	/*
	trackBatch = new GLTriangleBatch();
	gltMakeSphere(*trackBatch, 1.0f, 52, 26);*/
}

void TrackBatch::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	static const GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat vLightPos[] = { 100.0f, 100.0f, 1000.0f, 1.0f };
	M3DVector4f	vLightTransformed;
	m3dTransformVector4(vLightTransformed, vLightPos, viewMatrix);
	M3DMatrix44f mvpMatrix;
	m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
	Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
                                         viewMatrix,
                                         projectionMatrix,
                                         vLightTransformed,
                                         vWhite,
                                         0);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	trackBatch->Draw();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void TrackBatch::update(Track& _track)
{
	delete trackBatch;
	trackBatch = _track.getBatch();
}

