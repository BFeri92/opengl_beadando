#include <GLTools.h>
#include <string>
class AbstractObjLoader
{
	public:
		//A paraméterben megadott .obj fájlból be kell, hogy olvassa
		//a mesht. A face-k vertex/texture-coordinate formátumban lesznek megadva.
		virtual void loadObject(std::string fname) = 0;
		//A beolvasott mesh alapján készített GLTrianlgeBatch-t kell
		//visszaadnia.
		virtual const GLTriangleBatch& getBatch() = 0;
};
