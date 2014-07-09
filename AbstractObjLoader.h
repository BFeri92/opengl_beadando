#include <GLTools.h>
#include <string>
class AbstractObjLoader
{
	public:
		//A paraméterként adott fájlnévhez tartozó fájlból kell beolvasnia
		//a mesht, felépíteni belőle egy GLTriangleBatch-t és azt visszaadni.
		virtual const GLTriangleBatch getBatch(std::string fname) = 0;
};
