#include "ip.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

IP::IP(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap     *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
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
}
void IP::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    zoomMenu = menuBar()->addMenu(QStringLiteral("工具"));
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);
}
void IP::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);

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
                                        "bmp(*.bmp);;png(*.png)"
                                        ";;Jpeg(*.jpg)");
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
