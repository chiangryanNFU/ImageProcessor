#include "ip.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

IP::IP(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    central->setMouseTracking(true);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    imgWin = new QLabel();
    QPixmap     *initPixmap = new QPixmap(300,200);
    gWin = new GTransform();

    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    imgWin->setMouseTracking(true);
    mainLayout->addWidget(imgWin);

    statusLabel = new QLabel;
    statusLabel->setText(QStringLiteral("指標位置"));
    statusLabel->setFixedWidth(100);
    MousePosLabel = new QLabel;
    MousePosLabel->setText(tr(" "));
    MousePosLabel->setFixedWidth(100);
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(MousePosLabel);

    setMouseTracking(true);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}
IP::~IP()
{

}
void IP::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟影像&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束&Q"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    zoomOutAction = new QAction(QStringLiteral("縮小"), this);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(imgZoomOut()));
    zoomInAction = new QAction(QStringLiteral("放大"), this);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(imgZoomIn()));

    geometryAction = new QAction(QStringLiteral("幾何變換"), this);
    geometryAction -> setShortcut(tr("Ctrl+G"));
    geometryAction -> setStatusTip(QStringLiteral("影像幾何變換"));
    connect(geometryAction, SIGNAL(triggered()), this, SLOT(showGeometryTransform()));
    connect(exitAction, SIGNAL(triggered()), gWin, SLOT(close()));
}
void IP::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(exitAction);

    zoomMenu = menuBar()->addMenu(QStringLiteral("工具"));
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);
}
void IP::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
    fileTool->addAction(geometryAction);

    zoomTool = addToolBar("zoom");
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);
}
void IP::loadFile(QString filename)
{
    qDebug() << QString("file name:%1").arg(filename);
    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n",(char *) ba.data());
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}
void IP::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,
                                        QStringLiteral("開啟影像"),
                                        tr("."),
                                        QStringLiteral("任何檔案(*.*);;"
                                        "BMP檔(*.bmp);;PNG檔(*.png)"
                                        ";;JPG檔(*.jpg)")
                                        );
    if(!filename.isEmpty())
    {
        if(img.isNull())
            loadFile(filename);
        else
        {
            IP *newIPWin = new IP();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}
void IP::imgZoomOut()
{
    QImage zoomImg;
    zoomImg = img.scaled(img.width()*0.5, img.height()*0.5);
    QLabel *zoomOut = new QLabel();
    zoomOut->setPixmap(QPixmap::fromImage(zoomImg));
    zoomOut->setWindowTitle(QStringLiteral("處理結果"));
    zoomOut->show();
}
void IP::imgZoomIn()
{
    QImage zoomImg;
    zoomImg = img.scaled(img.width()*2, img.height()*2);
    QLabel *zoomIn = new QLabel();
    zoomIn->setPixmap(QPixmap::fromImage(zoomImg));
    zoomIn->setWindowTitle(QStringLiteral("處理結果"));
    zoomIn->resize(zoomImg.width(), zoomImg.height());
    zoomIn->show();
}
void IP::showGeometryTransform()
{
    if(!img.isNull())
    gWin->srcImage = img;
    gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImage));
    gWin->show();
}

void IP::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    QString str = "(" + QString::number(x) + "," +
                    QString::number(y) + ")";
    if(!img.isNull() && -1 < x && x < imgWin->width()
       && -1 < y && y < imgWin->height())
    {
        int gray = qGray(img.pixel(x, y));
        str += (" = " + QString::number(gray));
    }
    MousePosLabel->setText(str);
}

void IP::mousePressEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";

    if(event->button() == Qt::LeftButton)
    {
        statusLabel->setText(QStringLiteral("左鍵:") + str);
    }
    else if(event->button() == Qt::RightButton)
    {
        statusLabel->setText(QStringLiteral("右鍵:") + str);
    }
    else if(event->button() == Qt::MiddleButton)
    {
        statusLabel->setText(QStringLiteral("中鍵:") + str);
    }
}

void IP::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    statusLabel->setText(QStringLiteral("雙擊:") + str);
}

void IP::mouseReleaseEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    statusLabel->setText(QStringLiteral("釋放:") + str);
}
