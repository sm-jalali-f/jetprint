#ifndef PAINTFRAMEEVENTDISPATCHER_H
#define PAINTFRAMEEVENTDISPATCHER_H

class PaintFrameEventDispatcher
{
public:
    void addListener( Listener* );
    void removeListener( Listener* );

protected:
    std::vector<Listener*> mListeners;
    virtual void dispatchEvent();

};

#endif // PAINTFRAMEEVENTDISPATCHER_H
