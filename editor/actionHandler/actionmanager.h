#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QList>
#include "paintaction.h"
class ActionManager
{
public:
    ActionManager();

private:
    QList<PaintAction> actionList;
    int index; // point to one of the action list that paintpage present.


};

#endif // ACTIONMANAGER_H
