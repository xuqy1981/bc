#include "irrlicht.h"

#include "Buoy.hpp"
#include "IniFile.hpp"

using namespace irr;

Buoy::Buoy(const std::string& name, const irr::core::vector3df& location, irr::scene::ISceneManager* smgr)
{

    //Load from individual buoy.ini file if it exists
    std::string buoyIniFilename = "Models/Buoy/";
    buoyIniFilename.append(name);
    buoyIniFilename.append("/buoy.ini");

    //get filename from ini file (or empty string if file doesn't exist)
    std::string buoyFileName = IniFile::iniFileToString(buoyIniFilename,"FileName");
    if (buoyFileName=="") {
        buoyFileName = "buoy.x"; //Default if not set
    }

    //get scale factor from ini file (or zero if not set - assume 1)
    f32 buoyScale = IniFile::iniFileTof32(buoyIniFilename,"Scalefactor");
    if (buoyScale==0.0) {
        buoyScale = 1.0; //Default if not set
    }

    std::string buoyFullPath = "Models/Buoy/"; //FIXME: Use proper path handling
    buoyFullPath.append(name);
    buoyFullPath.append("/");
    buoyFullPath.append(buoyFileName);

    //Load the mesh
    scene::IMesh* buoyMesh = smgr->getMesh(buoyFullPath.c_str());
	buoy = smgr->addMeshSceneNode( buoyMesh, 0, -1, location );

    //Set lighting to use diffuse and ambient, so lighting of untextured models works
	if(buoy->getMaterialCount()>0) {
        for(int mat=0;mat<buoy->getMaterialCount();mat++) {
            buoy->getMaterial(mat).ColorMaterial = video::ECM_DIFFUSE_AND_AMBIENT;
        }
    }

    buoy->setScale(core::vector3df(buoyScale,buoyScale,buoyScale));
}

Buoy::~Buoy()
{
    //dtor
}
