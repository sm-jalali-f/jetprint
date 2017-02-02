#ifndef DRAWITEMSTATE_H
#define DRAWITEMSTATE_H


enum DrawItemState
{
    NOTHING_STATE = 0,
    PREPARE_FOR_DRAGING =1,
    DRAGING = 2,
    SELECTED = 3,
    REMOVED  = 4,
    TOP_RESIZING = 5,
    RIGHT_RESIZING = 6,
    LEFT_RESIZING = 7,
    BOTTOM_RESIZING = 8,
    LEFT_TOP_RESIZING = 9,
    LEFT_BOTTOM_RESIZING = 10,
    RIGHT_TOP_RESIZING = 11,
    RIGHT_BOTTOM_RESIZING = 12,
    ROTATING = 13
};

#endif // DRAWITEMSTATE_H
