#include "Drawable.h"

#include <GLTools.h>	// OpenGL toolkit
#include <math3d.h>
#include <iostream>

class Sphere : public Drawable
{
	private:
		GLTriangleBatch sphere;
	public:
		Sphere()
		{
			gltMakeSphere(sphere, 1.0f, 52, 26);
		}
		virtual void paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
		{
			std::cout<<"Painting sphere"<<std::endl;
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			static const GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
			GLShaderManager shaderManager;
			shaderManager.InitializeStockShaders();
			M3DMatrix44f mvpMatrix;
		    for (int i=0; i<4; i++)
			{
				for (int j=0; j<4; j++)
					std::cout<<mvpMatrix[i*4+j]<<" ";
				std::cout<<std::endl;
			}
			m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
			shaderManager.UseStockShader(GLT_SHADER_FLAT, mvpMatrix, vGreen);
			//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
			sphere.Draw();
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
};
