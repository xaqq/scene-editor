#include "qirrlichtwidget.hpp"
#include <QTimer>

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

    /* une fois initialisé, on émet le signal onInit, c'est la que nous
     * ajouterons nos modèles et nos textures.
     */
    emit onInit (this);

    if (device)
    {
        // on créé une caméra pour visualiser la scène
  //      camera = getSceneManager ()->addCameraSceneNode (0, vector3df (0,0,20), vector3df (0,0,0));
       IAnimatedMesh* mesh = getSceneManager()->getMesh("/home/xaqq/boapclient/BoapClient/Hulk/Hulk.obj");
           if (!mesh)
           {
               device->drop();
               return;
           }           IAnimatedMeshSceneNode* node = getSceneManager()->addAnimatedMeshSceneNode( mesh );
           if (node)
              {
                  node->setMaterialFlag(EMF_LIGHTING, false);
                  node->setMD2Animation(scene::EMAT_STAND);
                  node->setMaterialTexture( 0, device->getVideoDriver()->getTexture("/home/xaqq/boapclient/BoapClient/Hulk/Hulk_body_diff.tga") );
               // node->setDebugDataVisible(true);
           }
           /*
           IMeshSceneNode *node2 = getSceneManager()->addMeshSceneNode(getSceneManager()->getGeometryCreator()->createCubeMesh());
           node2->setDebugDataVisible(true);
           node2->setMaterialFlag(EMF_LIGHTING, false);
           node2->setMaterialTexture(0, device->getVideoDriver()->getTexture("/home/xaqq/boapclient/BoapClient/Hulk/rock.jpeg"));
           node2->setPosition(vector3df(0, 0, -20));*/
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
