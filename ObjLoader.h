#include "AbstractObjLoader.h"

class ObjLoader: public AbstractObjLoader {

    private :
        struct Face;
        struct Vertex;
        struct TextureCoordinate;
    
	public:
		GLTriangleBatch* getBatch(std::string fname);
        
};
