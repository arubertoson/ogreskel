// Mesh Merger
#include <CLI11.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "OgreDistanceLodStrategy.h"
#include "OgreLodStrategyManager.h"
#include "OgreMeshLodGenerator.h"

#include "OgreDefaultHardwareBufferManager.h"
#include <OgreLogManager.h>
#include <OgreMaterialManager.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreMeshSerializer.h>
#include <OgreResourceManager.h>
#include <OgreSkeleton.h>
#include <OgreSkeletonManager.h>
#include <OgreSkeletonSerializer.h>
#include <OgreSubMesh.h>

struct MaterialCreator : public Ogre::MeshSerializerListener {
        void processMaterialName(Ogre::Mesh *mesh, Ogre::String *name) {
                if (Ogre::MaterialManager::getSingleton().resourceExists(*name)) {
                        return;
                }

                // create material because we do not load any .material files
                Ogre::MaterialManager::getSingleton().create(*name, mesh->getGroup());
        }

        void processSkeletonName(Ogre::Mesh *mesh, Ogre::String *name) {}
        void processMeshCompleted(Ogre::Mesh *mesh) {}
};

Ogre::MeshPtr getMeshFromFile(std::string name, Ogre::MeshSerializer &serializer) {

        // XXX: Handle error better
        std::ifstream ifs;
        ifs.open(name, std::ios_base::in | std::ios_base::binary);
        if (ifs.bad()) {
                std::cout << "Unable to load file high" << std::endl;
                exit(1);
        }
        Ogre::DataStreamPtr stream(new Ogre::FileStreamDataStream(name, &ifs, false));

        // Ogre::MeshPtr getMeshFromFile(std::string name, Ogre::MeshSerializer &serializer) {
        Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().create(
            name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        serializer.importMesh(stream, mesh.get());

        return mesh;
}

int main(int argc, char *argv[]) {
        CLI::App app;
        //
        // std::string output;
        // app.add_option("--output", output, "Where to output file");
        //
        // std::string skeleton;
        // app.add_option("--skeleton", skeleton, "Where to output file");

        std::vector<std::string> meshfiles;
        app.add_option("inputs", meshfiles, "Files to work on");

        CLI11_PARSE(app, argc, argv);

        // Ogre depends on many different singletons - these all need to be created
        // initially and together with all dependencies they have. There needs
        // to exists a default log, otherwise Ogre will throw when it tries to
        // log internally
        auto mLogManager = std::make_unique<Ogre::LogManager>();
        mLogManager->setDefaultLog(mLogManager->createLog("OgreTemp.log", false, false));

        // The argument list is purpusfully kept simple, the first input will be
        // a path to the base skeleton, the following is everything we want to
        // merge to it.
        // if (meshfiles.size() < 2) {
        //         Ogre::LogManager::getSingleton().logError(
        //             "Source skeleton needs to be followed by input skeletons");
        //         exit(1);
        // }

        // For resource management we also rely on singletons, the skeleton
        // manager depends on the ResourceGroupManager and thus both needs to be
        // initialized with their unique pointers
        auto mResourceGroupManager = std::make_unique<Ogre::ResourceGroupManager>();

        auto mLodStrategyManager = std::make_unique<Ogre::LodStrategyManager>();
        auto mMeshManager = std::make_unique<Ogre::MeshManager>();
        auto mMeshSerializer = std::make_unique<Ogre::MeshSerializer>();

        // Necessary for mesh serializer
        auto mMaterialManager = std::make_unique<Ogre::MaterialManager>();
        auto mSkeletonManager = std::make_unique<Ogre::SkeletonManager>();
        auto mBuf = std::make_unique<Ogre::DefaultHardwareBufferManager>();

        mMaterialManager->initialise();
        // The listner will process certain things when a mesh is initialized,
        // in this case it will go over all the material names. Our case uses
        // this to populate the resource manager with "faked" materials to
        // keep dependencies clean and correct.
        auto MatListner = std::make_unique<MaterialCreator>();
        mMeshSerializer->setListener(MatListner.get());

        // First input is always the "root", the file we will flatten the other
        // files into.
        // auto base_name = meshfiles[0];
        // meshfiles.erase(meshfiles.begin());
        // auto base_mesh = getMeshFromFile(base_name, *mMeshSerializer);


        for (auto p : meshfiles) {
                if (Ogre::MeshManager::getSingleton().resourceExists(p)) {
                        continue;
                }

                auto mesh = getMeshFromFile(p, *mMeshSerializer);
                std::cout << mesh->getName() << std::endl;

                auto subidx = mesh->getSubMeshNameMap().size();
                std::cout << subidx << std::endl;
                for (auto name_idx : mesh->getSubMeshNameMap()) {
                        auto src_sub = mesh->getSubMesh(name_idx.second);

                        // Base Setup
                        std::cout << name_idx.first  << " : " << name_idx.second << std::endl;
                }
        }
}
