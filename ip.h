#ifndef IP_H
#define IP_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
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
private:
    QWidget     *central;
    QMenu       *fileMenu;
    QMenu       *zoomMenu;
    QToolBar    *fileTool;
    QToolBar    *zoomTool;
    QImage      img;
    QString     filename;
    QLabel      *imgWin;
    QAction     *openFileAction;
    QAction     *exitAction;
    QAction     *zoomOutAction;
    QAction     *zoomInAction;
};
#endif // IP_H
