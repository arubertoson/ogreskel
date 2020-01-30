
#include <iostream>
#include <Ogre.h>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace Ogre;


int main() {
    int retCode = 0;




    std::unique_ptr<LogManager> mLogManager;
    std::unique_ptr<ResourceGroupManager> mResourceGroupManager;
    std::unique_ptr<MeshManager> mMeshManager;
    std::unique_ptr<SkeletonManager> mSkeletonManager;

    mLogManager.reset(new LogManager());
    mResourceGroupManager.reset(new ResourceGroupManager());
    mMeshManager.reset(new MeshManager());
    mSkeletonManager.reset(new SkeletonManager());
    



    // SkeletonManager* sm;
    // sm = SkeletonManager::getSingletonPtr();

    // try {
    // } catch(Exception& e) {
    //     LogManager::getSingleton().logError(e.getDescription());
    //     retCode = 1;
    // }

    // Ogre::Root* mRoot;


    // auto sman = mRoot->createSceneManager();

    SkeletonPtr skel = mSkeletonManager->
        create("conversion", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // Ogre::MeshManager mman;

    // Clean up the conversion skeleton
    // sm->remove("conversion", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // Ogre::ResourceGroupManager::getSingletonPtr()->destroyResourceGroup("UserMesh");
	// Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("UserMesh");
	// Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/scratch/dev/github.com/arubertoson/ogreskel/resources", "FileSystem", "UserMesh", true);
	// Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("UserMesh");
	// Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("UserMesh");

    // Ogre::ResourceGroupManager::getSingleton().createResourceGroup("UserDefinedMesh");
    // Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/mnt/d/anims", "FileSystem");
    // Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    // auto mr = Ogre::MeshManager::getSingleton().getByName("/mnt/d/anims/roedeer.mesh");

    // auto mesh = sman->createEntity("/mnt/d/anims/roedeer.mesh");
    // Ogre::SkeletonSerializer sz;
    // Ogre::Skeleton* mSkel;

    // Ogre::SkeletonPtr mSkel = Ogre::SkeletonManager::getSingleton().getByName("/mnt/d/anims/high.skeleton", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            // "/mnt/d/anims/high.skeleton");
    
    // Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource("/mnt/d/anims/high.skeleton");
    
    // sz.importSkeleton(stream, mSkel);

    fs::path const dir {"/mnt/d/anims"};
    for (auto & entry : fs::directory_iterator(dir)) {
        std::cout << entry.path() << std::endl;
    }

    // Ogre::Skeleton* mSkel = Ogre::SkeletonManager::getSingleton().getSkeleton

  // Ogre::Skeleton::_mergeSkeletonAnimations(const Skeleton *source, const BoneHandleMap &boneHandleMap)
  // std:cout << Ogre::SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE << std::endl;

    return retCode;
}
