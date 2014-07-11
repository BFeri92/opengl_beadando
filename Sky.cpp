#include "Sky.h"
Sky::Sky(int _textureID):textureID(_textureID)
{
	gltMakeSphere(batch, 3000.0f, 52, 26);
	shader = gltLoadShaderPairWithAttributes("Emit.vp", "Emit.fp", 3, GLT_ATTRIBUTE_VERTEX, "vVertex",
                 GLT_ATTRIBUTE_NORMAL, "vNormal", GLT_ATTRIBUTE_TEXTURE0, "vTexture0");
    
    locAmbientEmit = glGetUniformLocation(shader, "ambientColor");
    locMVPEmit = glGetUniformLocation(shader, "mvpMatrix");
    locMVEmit  = glGetUniformLocation(shader, "mvMatrix");
    locTextureEmit = glGetUniformLocation(shader, "colorMap");
}

void Sky::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	/*
		M3DMatrix44f modelMatrix;
		m3dRotationMatrix44(modelMatrix,1.57079632679,0,0,1);
		M3DMatrix44f mvMatrix;
		m3dMatrixMultiply44(mvMatrix, modelMatrix, viewMatrix);
		M3DMatrix44f mvpMatrix;
		m3dMatrixMultiply44(mvpMatrix, mvMatrix, projectionMatrix);	*/
        glDisable(GL_CULL_FACE);
        glUseProgram(shader);
		M3DMatrix44f modelMatrix;
		m3dRotationMatrix44(modelMatrix,1.57079632679,1,0,0);
		M3DMatrix44f mvMatrix;
		m3dMatrixMultiply44(mvMatrix, viewMatrix, modelMatrix);
		M3DMatrix44f mvpMatrix;
		m3dMatrixMultiply44(mvpMatrix, projectionMatrix, mvMatrix);
        GLfloat vAmbientColor[] = { .7f, .7f, .7f, 1.0f };
        glUniform4fv(locAmbientEmit, 1, vAmbientColor);
        glUniformMatrix4fv(locMVPEmit, 1, GL_FALSE, mvpMatrix);
        glUniformMatrix4fv(locMVEmit, 1, GL_FALSE, mvMatrix);
        glUniform1i(locTextureEmit, textureID);
        batch.Draw();
}

