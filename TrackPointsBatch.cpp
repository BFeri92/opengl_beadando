#include "TrackPointsBatch.h"

#include "Game.h"
#include <iostream>
#include <GLTools.h>
TrackPointsBatch::TrackPointsBatch(Track& _track)
{
	trackPointsBatch = _track.getControlPointBatch();
}

void TrackPointsBatch::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	glPointSize(10);
	static const GLfloat vGreen[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	M3DMatrix44f mvpMatrix;
	m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
	Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_FLAT, mvpMatrix, vGreen);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	trackPointsBatch->Draw();
}

void TrackPointsBatch::update(Track& _track)
{
	trackPointsBatch = _track.getControlPointBatch();	
}
