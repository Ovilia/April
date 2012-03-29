#ifndef AOCTREE_H
#define AOCTREE_H

class AOctree
{
public:
    AOctree();

    static const int QUADRANT_COUNT = 4;

    enum OccupyType {
        OT_NONE = 0,
        OT_FULL,
        OT_PARTIAL
    };

    OccupyType getOccupyType();
    void setOccupyType(OccupyType type);

    // index is quadrant number - 1, within [0, QUADRANT_COUNT)
    // e.g.: the offset of first quadrant is 0
    AOctree* getChild(int index);
    // only used when OT_PARTIAL, otherwise it will be ignored
    void setChild(int index, AOctree* child);

    // depth of octree, for a single element octree, depth is 1
    int getDepth();

private:
    void removeChildren();

    AOctree* children[QUADRANT_COUNT];

    OccupyType occupyType;

    int depth;
};

#endif // AOCTREE_H
