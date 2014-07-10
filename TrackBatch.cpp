#include "TrackBatch.h"
#include "Game.h"
#include <iostream>
#include <GLTools.h>
TrackBatch::TrackBatch(Track _track)
{
	trackBatch = _track.getBatch();
	/*
	trackBatch = new GLTriangleBatch();
	gltMakeSphere(*trackBatch, 1.0f, 52, 26);*/
}

void TrackBatch::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	
	static const GLfloat vGreen[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	M3DMatrix44f mvpMatrix;
	m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
	Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_FLAT, mvpMatrix, vGreen);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	trackBatch->Draw();
}

