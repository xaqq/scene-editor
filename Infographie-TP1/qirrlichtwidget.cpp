#include "qirrlichtwidget.hpp"
#include <QTimer>
#include <QMessageBox>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

QIrrlichtWidget::QIrrlichtWidget (QWidget *parent) :
    QWidget (parent),
    device (NULL)
{
    // on écrit directement dans la mémoire vidéo du widget
    setAttribute (Qt::WA_PaintOnScreen);
    setAttribute (Qt::WA_OpaquePaintEvent);
    setFocusPolicy (Qt::StrongFocus);
    setAutoFillBackground (false);

    qDebug("Constructing QIrrlichWidget");
}

QIrrlichtWidget::~QIrrlichtWidget ()
{
    if (device)
    {
        device->closeDevice ();
        device->drop ();
    }
}

IrrlichtDevice *QIrrlichtWidget::getIrrlichtDevice () const
{
    return device;
}

IVideoDriver* QIrrlichtWidget::getVideoDriver () const
{
    return device->getVideoDriver();
}

ISceneManager* QIrrlichtWidget::getSceneManager () const
{
    return device->getSceneManager();
}

ISceneCollisionManager *QIrrlichtWidget::getCollisionManager() const
{
    return device->getSceneManager()->getSceneCollisionManager();
}

void QIrrlichtWidget::init ()
{
    SIrrlichtCreationParameters params;

    // on utilise OpenGL, et on lui donne l'identifiant de la fenêtre de notre widget
    params.DriverType        = EDT_OPENGL;
    params.WindowId          = reinterpret_cast<void*> (winId ());

    // ainsi que la taille de notre widget
    params.WindowSize.Width  = width ();
    params.WindowSize.Height = height ();

    params.AntiAlias         = true;
    params.Bits              = 16;
    params.HighPrecisionFPU  = false;
    params.Stencilbuffer     = true;
    params.Vsync             = true;

    // enfin, on initialise notre moteur de rendu
    device = createDeviceEx (params);

    if (device)
    {
        emit onInit(this);
    }
    qDebug("Created Irrlicht Device");


    /* puis on connecte notre slot updateIrrlicht (), qui s'occupe du rendu
     * à notre signal updateIrrlichtQuery ()
     */
    connect (this, SIGNAL (updateIrrlichtQuery (QIrrlichtWidget*)), this, SLOT (updateIrrlicht (QIrrlichtWidget*)));

    // et on lance notre timer
    startTimer (0);
}

void QIrrlichtWidget::updateIrrlicht (QIrrlichtWidget *irrWidget)
{
    if (device)
    {

        // Draw the scene
        device->getTimer ()->tick ();
        SColor color  (255, 100, 100, 140);
        getVideoDriver ()->beginScene (true, true, color);
        getSceneManager ()->drawAll ();
        getVideoDriver ()->endScene ();
    }
}

void QIrrlichtWidget::paintEvent (QPaintEvent *ev)
{
    if (device)
    {
        /* lorsque le widget demande a être affiché, on emet le signal updateIrrlichtQuery (),
         * ainsi, notre slot updateIrrlicht () sera appelé.
         */
        emit updateIrrlichtQuery (this);
    }
}

void QIrrlichtWidget::timerEvent (QTimerEvent *ev)
{
    if (device)
    {
        // pareil que pour la méthode paintEvent ()
        emit updateIrrlichtQuery (this);
    }

    ev->accept ();
}

void QIrrlichtWidget::keyPressEvent (QKeyEvent *ev)
{

}

void QIrrlichtWidget::resizeEvent (QResizeEvent *ev)
{
    if (device)
    {
        // lors d'un redimensionnement, on récupe la nouvelle taille du widget
        dimension2d<u32> widgetSize;

        widgetSize.Width  = ev->size ().width ();
        widgetSize.Height = ev->size ().height ();

        // et on précise à Irrlicht la nouvelle taille.
        getVideoDriver ()->OnResize (widgetSize);
     }

    QWidget::resizeEvent (ev);
}

// this is from irrlicht wiki
void QIrrlichtWidget::screenshot(const QString &fileName)
{
   irr::video::IVideoDriver* const driver = device->getVideoDriver();

   //get image from the last rendered frame
   irr::video::IImage* const image = driver->createScreenShot();
   if (image)
   {
      //construct a filename, consisting of local time and file extension
      irr::c8 filename[64];
      snprintf(filename, 64, "screenshot_%u.png", device->getTimer()->getRealTime());


      //write screenshot to file
      if (!driver->writeImageToFile(image, fileName.toStdString().c_str()))
         device->getLogger()->log(L"Failed to take screenshot.", irr::ELL_WARNING);

      //Don't forget to drop image since we don't need it anymore.
      image->drop();
   }
}

void QIrrlichtWidget::mousePressEvent(QMouseEvent *e)
{
    line3d<f32> ret = getCollisionManager()->getRayFromScreenCoordinates(vector2d<s32>(e->pos().x(), e->pos().y()));
    qDebug(QString("Mouse coord: " + QString::number(e->pos().x()) + "," + QString::number(e->pos().y())).toStdString().c_str());
 findWithRaycast(ret);
}


Entity *QIrrlichtWidget::findWithRaycast(line3d<f32> ray)
{
    if (!camera)
    {
        qDebug("No camera.");
        return nullptr;

    }          scene::ISceneNode * selectedSceneNode =
               getCollisionManager()->getSceneNodeFromRayBB(
                       ray);

    if (selectedSceneNode)
    {
        QMessageBox::critical(this, "resultat", "EH GG BIEN VISER: " +
                              QString(selectedSceneNode->getName()));
    }
}
