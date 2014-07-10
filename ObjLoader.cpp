#include "ObjLoader.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "math3d.h"

struct ObjLoader::Vertex
{
    Vertex(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
    bool operator ==(const Vertex &op2)
    {
        if ((this->x==op2.x) && (this->y==op2.y) && (this->z==op2.z)) return true;
        else return false;
    }
    GLfloat x,y,z;
};
struct ObjLoader::Face
{
    Face(int _a, int _t1, int _b, int _t2, int _c, int _t3) : a(_a), t1(_t1), b(_b), t2(_t2), c(_c), t3(_t3) {}
    int a,b,c, t1, t2, t3;
};
struct ObjLoader::TextureCoordinate
{
    TextureCoordinate(float _a, float _b) : a(_a), b(_b) {}
    float a,b;
};

GLTriangleBatch* ObjLoader::getBatch(std::string fname)
{
	//std::cout << "aaaa" << std::endl;
    GLTriangleBatch* batch = new GLTriangleBatch();
    
    std::vector<ObjLoader::Vertex> vertices;
	std::vector<ObjLoader::Face> faces;
	std::vector<ObjLoader::TextureCoordinate> textureCoordinates;
    
    std::ifstream ifs(fname.c_str());
    while (!(ifs.eof()) && ifs.good())
    {
        std::string propType;
        ifs>>propType;
	//std::cout << propType << std::endl;
        if (propType=="v")
        {
            float c1,c2,c3;
            ifs>>c1>>c2>>c3;
            vertices.push_back(Vertex(c1,c2,c3));
        }
        else if (propType=="vt")
        {
            float v1,v2;
            ifs>>v1>>v2;
            textureCoordinates.push_back(TextureCoordinate(v1,v2));
        }
        else if (propType=="f")
        {
            int i1,i2,i3,t1,t2,t3;
	    char c;
            ifs>>i1>>c>>t1>>i2>>c>>t2>>i3>>c>>t3;
		//std::cout << i1 << " " << t1 << " " << i2 << " " << t2 << " " << i3 << " " << t3 << std::endl;
            faces.push_back(Face(i1,t1,i2,t2,i3,t3));
        }
        else
        {
            std::getline(ifs, propType);
        }
        //std::cout<<ifs.good()<<ifs.bad()<<ifs.fail()<<ifs.eof()<<std::endl;
    }
    
    batch->BeginMesh(3*3*faces.size());
    for (int i=0; i<faces.size(); i++)
    {
    
        M3DVector3f verts[3];
        
		verts[0][0]=vertices[faces[i].a-1].x;
		verts[0][1]=vertices[faces[i].a-1].y;
		verts[0][2]=vertices[faces[i].a-1].z;

		verts[1][0]=vertices[faces[i].b-1].x;
		verts[1][1]=vertices[faces[i].b-1].y;
		verts[1][2]=vertices[faces[i].b-1].z;

		verts[2][0]=vertices[faces[i].c-1].x;
		verts[2][1]=vertices[faces[i].c-1].y;
		verts[2][2]=vertices[faces[i].c-1].z;
        
        M3DVector3f norms[3];
		
		m3dFindNormal(norms[0], verts[2], verts[1], verts[0]);
		norms[2][0]=norms[1][0]=norms[0][0];
		norms[2][1]=norms[1][1]=norms[0][1];
		norms[2][2]=norms[1][2]=norms[0][2];
        
		m3dNormalizeVector3(norms[0]);
		m3dNormalizeVector3(norms[1]);
		m3dNormalizeVector3(norms[2]);
        
        M3DVector2f tex[3];
        
		tex[0][0] = textureCoordinates[faces[i].t1-1].a;
		tex[0][1] = textureCoordinates[faces[i].t1-1].b;
		tex[1][0] = textureCoordinates[faces[i].t2-1].a;
		tex[1][1] = textureCoordinates[faces[i].t2-1].b;
		tex[2][0] = textureCoordinates[faces[i].t3-1].a;
		tex[2][1] = textureCoordinates[faces[i].t3-1].b;
        
		batch->AddTriangle(verts, norms, tex);
        
    }
	batch->End();
    
    return batch;

}



