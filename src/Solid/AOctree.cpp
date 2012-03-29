#ifdef _DEBUG
#include <assert.h>
#endif

#include "AOctree.h"

AOctree::AOctree() :
    occupyType(OT_NONE),
    depth(1)
{
    for (int i = 0; i < QUADRANT_COUNT; ++i) {
        children[i] = 0;
    }
}

AOctree::OccupyType AOctree::getOccupyType()
{
    return occupyType;
}

void AOctree::setOccupyType(OccupyType type)
{
    switch (type) {
    case OT_NONE:
        removeChildren();
        occupyType = OT_NONE;
        break;

    case OT_FULL:
        removeChildren();
        occupyType = OT_FULL;
        break;

    case OT_PARTIAL:
        occupyType = OT_PARTIAL;
        break;
    }
}

AOctree* AOctree::getChild(int index)
{
#ifdef _DEBUG
    assert(index > 0 && index < QUADRANT_COUNT);
#endif
    return children[index];
}

void AOctree::setChild(int index, AOctree* child)
{
#ifdef _DEBUG
    assert(index > 0 && index < QUADRANT_COUNT);
#endif
    if (OT_PARTIAL) {
        this->children[index] = child;
        int childDepth = child->getDepth();
        if (childDepth + 1 > depth) {
            depth = childDepth + 1;
        }
    }
}

int AOctree::getDepth()
{
    return depth;
}

void AOctree::removeChildren()
{
    depth = 1;
    for (int i = 0; i < QUADRANT_COUNT; ++i) {
        children[i] = 0;
    }
}
