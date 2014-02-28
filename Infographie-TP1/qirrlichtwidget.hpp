#ifndef QIRRLICHTWIDGET_HPP
#define QIRRLICHTWIDGET_HPP

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <irrlicht/irrlicht.h>

class MainWindow;
class Entity;
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

        /**
         * @brief takeScreenshot and save it to a file.
         * @param fileName
         */
        void screenshot(const QString &fileName);

        /**
         * @brief launch a ray from camera en return Entity if hit.
         * @return
         */
        Entity *findWithRaycast(irr::core::line3d<irr::f32> ray);

        irr::scene::ISceneCollisionManager *getCollisionManager() const;


        void setMainWindow(MainWindow *m) // to set selected entity when raycasting
        {
            main_ = m;
        }

        void setCamera(irr::scene::ICameraSceneNode *cam)
        {
            camera = cam;
        }

        void mousePressEvent(QMouseEvent *)override;

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
        MainWindow *main_;
};

#endif // QIRRLICHTWIDGET_HPP
