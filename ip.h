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
#include "gtransform.h"

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

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

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
};
#endif // IP_H
