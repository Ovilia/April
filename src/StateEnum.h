#ifndef STATEENUM_H
#define STATEENUM_H

class StateEnum
{
public:
    enum ViewMode {
        VM_NONE = 0,
        VM_MOVE,
    //        VM_ZOOM_IN,
    //        VM_ZOOM_OUT,
        VM_ROTATE,
        VM_CREATE,
        VM_SELECT
    };
};

#endif // STATEENUM_H
