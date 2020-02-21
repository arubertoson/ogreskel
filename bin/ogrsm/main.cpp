// Skeleton Merger
#include <CLI11.hpp>

#include <iostream>
#include <string>
#include <vector>

// #include <Ogre.h>
// To keep the executable minimal we don't want to rely on the heavy OgreMain
// header, lightweight appraoch is to just import what we need
#include <OgreLogManager.h>
#include <OgreResourceManager.h>
#include <OgreSkeleton.h>
#include <OgreSkeletonManager.h>
#include <OgreSkeletonSerializer.h>

using namespace Ogre;

SkeletonPtr getSkeletonFromFile(std::string name, SkeletonSerializer &serializer) {
        // Thisi s a pretty silly side-effect and needs to be cleaned up.
        SkeletonPtr skeleton = SkeletonManager::getSingleton().create(
            name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        // XXX: Handle error better
        std::ifstream ifs;
        ifs.open(name, std::ios_base::in | std::ios_base::binary);
        if (ifs.bad()) {
                std::cout << "Unable to load file high" << std::endl;
                exit(1);
        }
        DataStreamPtr stream(new FileStreamDataStream(name, &ifs, false));

        serializer.importSkeleton(stream, skeleton.get());

        return skeleton;
}

int main(int argc, char *argv[]) {
        CLI::App app;

        std::string output;
        app.add_option("--output", output, "Output file");

        std::vector<std::string> inputs;
        app.add_option("inputs", inputs, "Files to work on");

        CLI11_PARSE(app, argc, argv);

        // Ogre depends on many different singletons - these all need to be created
        // initially and together with all dependencies they have. There needs
        // to exists a default log, otherwise Ogre will throw when it tries to
        // log internally
        auto mLogManager = std::make_unique<LogManager>();
        mLogManager->setDefaultLog(mLogManager->createLog("OgreTemp.log", false, false));

        // The argument list is purpusfully kept simple, the first input will be
        // a path to the base skeleton, the following is everythign we want to
        // merge to it.
        if (inputs.size() < 2) {
                LogManager::getSingleton().logError(
                    "Source skeleton needs to be followed by input skeletongs");
                exit(1);
        }

        // For resource management we also rely on singletons, the skeleton
        // manager depends on the ResourceGroupManager and thus both needs to be
        // initialized with their unique pointers
        auto mResourceGroupManager = std::make_unique<ResourceGroupManager>();
        auto mSkeletonManager = std::make_unique<SkeletonManager>();
        auto serializer = std::make_unique<SkeletonSerializer>();

        // XXX: Should take argumetn list (should not be hardcoded)
        auto baseName = inputs[0];
        inputs.erase(inputs.begin());

        // We create the base skeleton which will consume the animations in the
        // other skeleton files.
        SkeletonPtr base = getSkeletonFromFile(baseName, *serializer);

        // BoneHandleMap is necessary to make ensure that the source and
        // destination skeleton have compatible bone setup. We build the handle
        // map from our base skeleton
        Skeleton::BoneHandleMap bmap;
        base->_buildMapBoneByHandle(base.get(), bmap);

        for (auto p : inputs) {
                // If a skeleton resource already exists just meanss that we
                // have given a skeleton that points to the same file as our
                // base skeleton and we can safely ignore it.
                if (SkeletonManager::getSingleton().resourceExists(p)) {
                        continue;
                }

                auto other = getSkeletonFromFile(p, *serializer);

                // Trying to populate the base skeleton with duplicate animation will
                // result in a unnecessary throw of Ogre::ItemIdentifyException. To
                // avoid this we simply make sure that we skip any animation that we've
                // already populated in the skeleton
                StringVector animations;

                ushort size = other->getNumAnimations();
                for (ushort i = 0; i < size; ++i) {
                        auto name = other->getAnimation(i)->getName();
                        if (base->hasAnimation(name)) {
                                continue;
                        }

                        animations.emplace_back(name);
                }

                // If we couldn't find any unique animations in the skeleton
                // just continue the loop
                if (animations.empty()) {
                        continue;
                }

                // At least we merge the two skeletons with the given animation list to
                // ensure we avoid duplicates
                base->_mergeSkeletonAnimations(other.get(), bmap, animations);

                // Clean up other skeleton from resource pool
                SkeletonManager::getSingleton().remove(p);
        }

        // Finally we write the skeleton out the output file
        serializer->exportSkeleton(base.get(), output, SKELETON_VERSION_LATEST,
                                   Serializer::ENDIAN_NATIVE);

        return 0;
}
