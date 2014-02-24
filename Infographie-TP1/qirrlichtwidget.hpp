#ifndef QIRRLICHTWIDGET_HPP
#define QIRRLICHTWIDGET_HPP

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <irrlicht/irrlicht.h>

class QIrrlichtWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit QIrrlichtWidget (QWidget *parent = 0);
        ~QIrrlichtWidget ();

        irr::IrrlichtDevice *getIrrlichtDevice () const;
        irr::video::IVideoDriver *getVideoDriver () const;
        irr::scene::ISceneManager *getSceneManager () const;

        void init ();

    signals:
        void onInit (QIrrlichtWidget *irrWidget);
        void updateIrrlichtQuery (QIrrlichtWidget *irrWidget);

    public slots:
        void updateIrrlicht (QIrrlichtWidget *irrWidget);

    protected:
        virtual void paintEvent (QPaintEvent *ev);
        virtual void timerEvent (QTimerEvent *ev);
        virtual void resizeEvent (QResizeEvent *ev);
        virtual void keyPressEvent (QKeyEvent *ev);

    private:
        irr::IrrlichtDevice *device;
        irr::scene::ICameraSceneNode *camera;
};

#endif // QIRRLICHTWIDGET_HPP
