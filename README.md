# ogreskel

Starting off, before we can even get anywhere we need to initialize all pointers
to singletons. If we have anyting in use that is a singleton that coes not
provide a initialized pointer we will generate a segfault.

## Resources

_mergeSkeleton usage: https://forums.ogre3d.org/viewtopic.php?t=31080
resource management: https://ogrecave.github.io/ogre/api/1.12/_resource-_management.html
