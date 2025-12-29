#ifndef ZOOMWINDOW_H
#define ZOOMWINDOW_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>

class ZoomWindow : public QWidget
{
    Q_OBJECT

public:
    ZoomWindow(const QImage &image, double zoomRatio = 2.0, QWidget *parent = nullptr);
    ~ZoomWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void saveImage();
    void toggleBrushMode();

private:
    QImage originalImage;
    QImage displayImage;
    QLabel *imageLabel;
    QToolBar *toolBar;
    QAction *saveAction;
    QAction *brushAction;
    QVBoxLayout *mainLayout;
    
    bool brushMode;
    bool isDrawing;
    QPoint lastPoint;
    int brushSize;
    QColor brushColor;
    
    void updateDisplay();
};

#endif // ZOOMWINDOW_H
