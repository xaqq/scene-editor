#include "qirrlichtwidget.hpp"
#include <QTimer>
#include <QMessageBox>
#include "mainwindow.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

QIrrlichtWidget::QIrrlichtWidget (QWidget *parent) :
    QWidget (parent),
    device (NULL),
    main_(nullptr)
{
    // on écrit directement dans la mémoire vidéo du widget
    setAttribute (Qt::WA_PaintOnScreen);
    setAttribute (Qt::WA_OpaquePaintEvent);
    setFocusPolicy (Qt::StrongFocus);
    setAutoFillBackground (false);
    grabKeyboard();

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

void QIrrlichtWidget::updateIrrlicht (QIrrlichtWidget *)
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

void QIrrlichtWidget::paintEvent (QPaintEvent *)
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
    if ( device != 0 )
          {
        if (ev->key() == Qt::Key_X)
        {
            // send raycast to select object
            QPoint pos = this->mapFromGlobal(QCursor::pos());
             line3d<f32> ray = getCollisionManager()->getRayFromScreenCoordinates(vector2d<s32>(pos.x(), pos.y()));
            findWithRaycast(ray);
            ev->ignore();
            return;
        }
              sendKeyEventToIrrlicht( ev, true );
          }
          ev->ignore();
}


void QIrrlichtWidget::keyReleaseEvent( QKeyEvent* ev )
{
    if ( device != 0 )
    {
        sendKeyEventToIrrlicht( ev, false );
    }
    ev->ignore();
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

void QIrrlichtWidget::mousePressEvent(QMouseEvent *event)
{ if ( device != 0 )
    {
        sendMouseEventToIrrlicht( event, true );
    }
    event->ignore();

    /*
    line3d<f32> ret = getCollisionManager()->getRayFromScreenCoordinates(vector2d<s32>(e->pos().x(), e->pos().y()));
    qDebug(QString("Mouse coord: " + QString::number(e->pos().x()) + "," + QString::number(e->pos().y())).toStdString().c_str());
 findWithRaycast(ret);
*/

}

void QIrrlichtWidget::mouseReleaseEvent( QMouseEvent* event )
{
    if ( device != 0 )
    {
        sendMouseEventToIrrlicht( event, false );
    }
    event->ignore();
}

void QIrrlichtWidget::wheelEvent( QWheelEvent* event )
    {
        if ( device != 0 && event->orientation() == Qt::Vertical )
        {
            irr::SEvent irrEvent;

            irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

            irrEvent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
            irrEvent.MouseInput.X = 0; // We don't know these,
            irrEvent.MouseInput.Y = 0; // but better zero them instead of letting them be undefined
            irrEvent.MouseInput.Wheel = event->delta() / 120.0f;

            device->postEventFromUser( irrEvent );
        }
        event->ignore();
    }


void QIrrlichtWidget::mouseMoveEvent( QMouseEvent* event ){
    irr::SEvent irrEvent;

         irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

          if ( device != 0 )
         {
         irrEvent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;

         irrEvent.MouseInput.X = event->x();
         irrEvent.MouseInput.Y = event->y();
         irrEvent.MouseInput.Wheel = 0.0f; // Zero is better than undefined


         device->postEventFromUser( irrEvent );
         }
        event->ignore();
}

void QIrrlichtWidget::sendMouseEventToIrrlicht( QMouseEvent* event, bool pressedDown )
{
    irr::SEvent irrEvent;
    irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    switch ( event->button() )
    {
    case Qt::LeftButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_LMOUSE_PRESSED_DOWN : irr::EMIE_LMOUSE_LEFT_UP;
        break;

    case Qt::MidButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_MMOUSE_PRESSED_DOWN : irr::EMIE_MMOUSE_LEFT_UP;
        break;

    case Qt::RightButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_RMOUSE_PRESSED_DOWN : irr::EMIE_RMOUSE_LEFT_UP;
        break;

    default:
        return; // Cannot handle this mouse event
    }

irrEvent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
    irrEvent.MouseInput.X = event->x();
    irrEvent.MouseInput.Y = event->y();
    irrEvent.MouseInput.Wheel = 0.0f;
    device->postEventFromUser( irrEvent );
}

/**
 * Use bouding box, therefore its not that precise.
 */
void QIrrlichtWidget::findWithRaycast(line3d<f32> ray)
{
    if (!camera)
    {
        qDebug("No camera.");
        return;

    }          scene::ISceneNode * selectedSceneNode =
               getCollisionManager()->getSceneNodeFromRayBB(
                       ray);

    if (selectedSceneNode)
    {
        if (main_)
        {
            main_->setSelectedNode(selectedSceneNode);
        }
    }
}



struct SIrrlichtKey
{
    irr::EKEY_CODE code;
    wchar_t ch;
};

SIrrlichtKey convertToIrrlichtKey( int key )
{
    SIrrlichtKey irrKey;
    irrKey.code = (irr::EKEY_CODE)(0);
    irrKey.ch = (wchar_t)(0);

    // Letters A..Z and numbers 0..9 are mapped directly
    if ( (key >= Qt::Key_A && key <= Qt::Key_Z) || (key >= Qt::Key_0 && key <= Qt::Key_9) )
    {
        irrKey.code = (irr::EKEY_CODE)( key );
        irrKey.ch = (wchar_t)( key );
    }
    else

    // map arrow keys
    switch( key )
    {
    case Qt::Key_Up:
        irrKey.code = irr::KEY_UP;
        break;

    case Qt::Key_Down:
        irrKey.code = irr::KEY_DOWN;
        break;

    case Qt::Key_Left:
        irrKey.code = irr::KEY_LEFT;
        break;

    case Qt::Key_Right:
        irrKey.code = irr::KEY_RIGHT;
        break;
    }
    return irrKey;
}

void QIrrlichtWidget::sendKeyEventToIrrlicht( QKeyEvent* event, bool pressedDown )
{
    irr::SEvent irrEvent;

    irrEvent.EventType = irr::EET_KEY_INPUT_EVENT;

    SIrrlichtKey irrKey = convertToIrrlichtKey( event->key() );

    if ( irrKey.code == 0 ) return; // Could not find a match for this key

    irrEvent.KeyInput.Key = irrKey.code;
    irrEvent.KeyInput.Control = ((event->modifiers() & Qt::ControlModifier) != 0);
    irrEvent.KeyInput.Shift = ((event->modifiers() & Qt::ShiftModifier) != 0);
    irrEvent.KeyInput.Char = irrKey.ch;
    irrEvent.KeyInput.PressedDown = pressedDown;

    device->postEventFromUser( irrEvent );
}
