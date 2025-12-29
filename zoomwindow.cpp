#include "zoomwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

ZoomWindow::ZoomWindow(const QImage &image, double zoomRatio, QWidget *parent)
    : QWidget(parent), originalImage(image), brushMode(false), isDrawing(false),
      brushSize(5), brushColor(Qt::red)
{
    setWindowTitle(QStringLiteral("放大視窗"));
    
    // Scale the image
    int newWidth = static_cast<int>(image.width() * zoomRatio);
    int newHeight = static_cast<int>(image.height() * zoomRatio);
    displayImage = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    // Create main layout
    mainLayout = new QVBoxLayout(this);
    
    // Create toolbar
    toolBar = new QToolBar(this);
    
    saveAction = new QAction(QStringLiteral("另存新檔"), this);
    saveAction->setStatusTip(QStringLiteral("儲存影像"));
    connect(saveAction, &QAction::triggered, this, &ZoomWindow::saveImage);
    
    brushAction = new QAction(QStringLiteral("畫筆工具"), this);
    brushAction->setCheckable(true);
    brushAction->setStatusTip(QStringLiteral("啟用/停用畫筆"));
    connect(brushAction, &QAction::triggered, this, &ZoomWindow::toggleBrushMode);
    
    toolBar->addAction(saveAction);
    toolBar->addAction(brushAction);
    
    // Create image label
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap::fromImage(displayImage));
    imageLabel->setScaledContents(false);
    imageLabel->setMouseTracking(true);
    
    // Add widgets to layout
    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(imageLabel);
    
    // Set window size
    resize(displayImage.width() + 20, displayImage.height() + 70);
}

ZoomWindow::~ZoomWindow()
{
}

void ZoomWindow::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    QStringLiteral("另存新檔"),
                                                    "",
                                                    QStringLiteral("PNG檔(*.png);;JPG檔(*.jpg);;BMP檔(*.bmp);;所有檔案(*.*)"));
    
    if (!filename.isEmpty())
    {
        if (displayImage.save(filename))
        {
            QMessageBox::information(this, QStringLiteral("成功"), QStringLiteral("影像已儲存"));
        }
        else
        {
            QMessageBox::warning(this, QStringLiteral("錯誤"), QStringLiteral("無法儲存影像"));
        }
    }
}

void ZoomWindow::toggleBrushMode()
{
    brushMode = brushAction->isChecked();
    if (brushMode)
    {
        imageLabel->setCursor(Qt::CrossCursor);
    }
    else
    {
        imageLabel->setCursor(Qt::ArrowCursor);
        isDrawing = false;
    }
}

void ZoomWindow::mousePressEvent(QMouseEvent *event)
{
    if (brushMode && event->button() == Qt::LeftButton)
    {
        // Get position relative to image label using global coordinates
        QPoint globalPos = mapToGlobal(event->pos());
        QPoint pos = imageLabel->mapFromGlobal(globalPos);
        
        // Check if click is within image bounds
        if (pos.x() >= 0 && pos.x() < displayImage.width() &&
            pos.y() >= 0 && pos.y() < displayImage.height())
        {
            isDrawing = true;
            lastPoint = pos;
        }
    }
}

void ZoomWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (brushMode && isDrawing)
    {
        // Get position relative to image label using global coordinates
        QPoint globalPos = mapToGlobal(event->pos());
        QPoint pos = imageLabel->mapFromGlobal(globalPos);
        
        // Check if position is within image bounds
        if (pos.x() >= 0 && pos.x() < displayImage.width() &&
            pos.y() >= 0 && pos.y() < displayImage.height())
        {
            // Draw line on the image
            QPainter painter(&displayImage);
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, pos);
            
            lastPoint = pos;
            updateDisplay();
        }
    }
}

void ZoomWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (brushMode && event->button() == Qt::LeftButton)
    {
        isDrawing = false;
    }
}

void ZoomWindow::updateDisplay()
{
    imageLabel->setPixmap(QPixmap::fromImage(displayImage));
}
