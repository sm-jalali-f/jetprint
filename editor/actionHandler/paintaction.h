#ifndef PAINTACTION_H
#define PAINTACTION_H


class PaintAction
{
public:
    PaintAction();
    enum PaintActionType{
        DRAG_ITEM,
        RESIZE_ITEM,
        DELETE_ITEM,
        ADD_ITEM
    };

private:
    PaintActionType actionType;


};

#endif // PAINTACTION_H
