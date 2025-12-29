#ifndef IP_H
#define IP_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QStatusBar>
#include <QRect>
#include <QPainter>
#include <QInputDialog>
#include "gtransform.h"
#include "zoomwindow.h"

class IP : public QMainWindow
{
    Q_OBJECT

public:
    IP(QWidget *parent = nullptr);
    ~IP();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void imgZoomOut();
    void imgZoomIn();
    void showGeometryTransform();
    void setZoomRatio();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    GTransform  *gWin;
    QWidget     *central;
    QMenu       *fileMenu;
    QMenu       *zoomMenu;
    QToolBar    *fileTool;
    QToolBar    *zoomTool;

    QImage      img;
    QString     filename;
    QLabel      *imgWin;

    QLabel      *statusLabel;
    QLabel      *MousePosLabel;

    QAction     *openFileAction;
    QAction     *exitAction;
    QAction     *zoomOutAction;
    QAction     *zoomInAction;
    QAction     *geometryAction;
    QAction     *setZoomRatioAction;
    
    bool        isSelecting;
    QPoint      selectionStart;
    QPoint      selectionEnd;
    QRect       selectionRect;
    double      zoomRatio;
};
#endif // IP_H
