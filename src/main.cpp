
#include <iostream>
#include <Ogre.h>
#include <OgreSkeletonSerializer.h>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace Ogre;


SkeletonPtr getSkeletonFromFile(std::string name, SkeletonSerializer& serializer) {
    SkeletonPtr skel = SkeletonManager::getSingleton().create(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // XXX: Handle error better
    std::ifstream ifs;
    ifs.open(name, std::ios_base::in | std::ios_base::binary);
    if (ifs.bad()) {
      std::cout << "Unable to load file high" << std::endl;
      exit(1);
    }
    DataStreamPtr stream(new FileStreamDataStream("./../resources/high.skeleton", &ifs, false));

    serializer.importSkeleton(stream, skel.get());

    return skel;
}


int main() {
    int retCode = 0;

    // Ogre depends on many different singletons - these all need to be created
    // initially and together with all depedencies they have.
    auto mLogManager = std::make_unique<LogManager>();
    mLogManager->createLog("Temporary log", false, true, true); 
    mLogManager->setDefaultLog(mLogManager->createLog("OgreTemp.log", false, false));

    mLogManager->destroyLog("Temporary log");

    auto mResourceGroupManager = std::make_unique<ResourceGroupManager>();
    auto mSkeletonManager = std::make_unique<SkeletonManager>();
    auto serializer = std::make_unique<SkeletonSerializer>();


    auto base_name = "./../resources/roedeer.skeleton";

    SkeletonPtr base = getSkeletonFromFile(base_name, *serializer);

    std::cout << base->getNumAnimations() << std::endl;

    std::cout << base_name << " " << base->getNumBones() << std::endl;

    Skeleton::BoneHandleMap bmap;
    base->_buildMapBoneByHandle(base.get(), bmap);


    fs::path const dir {"./../resources"};
    if (fs::exists(dir)) {
      for (auto & entry : fs::directory_iterator(dir)) {
        if (!(entry.path().extension() == ".skeleton") || !entry.path().compare(base_name)) {
          continue;
        }
        std::cout << entry.path() << std::endl;

        SkeletonPtr other = getSkeletonFromFile(entry.path().c_str(), *serializer);

        size = other->getNumAnimations();
        for (ushort i = 0; i < size; ++i) {
          auto anim = other->getAnimation(i);
        }

        try {
          base->_mergeSkeletonAnimations(other.get(), bmap);
        } catch (InternalErrorException& e) {
          std::cout << entry.path() << "ERROR ERROR" << std::endl;
          std::cout << e.what() << std::endl;
        }
      }
    }

    std::cout << base->getNumAnimations() << std::endl;


    serializer->exportSkeleton(base.get(), "../combined.skeleton", SKELETON_VERSION_LATEST, Serializer::ENDIAN_NATIVE);
    std::cout << "Wer are done!" << std::endl;

    // Ogre::Skeleton* mSkel = Ogre::SkeletonManager::getSingleton().getSkeleton

  // Ogre::Skeleton::_mergeSkeletonAnimations(const Skeleton *source, const BoneHandleMap &boneHandleMap)
  // std:cout << Ogre::SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE << std::endl;

    return retCode;
}
