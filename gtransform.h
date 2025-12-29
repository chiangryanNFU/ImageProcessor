#ifndef GTRANSFORM_H
#define GTRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>

class GTransform : public QWidget
{
    Q_OBJECT

public:
    GTransform(QWidget *parent = nullptr);
    ~GTransform();
    QLabel      *inWin;
    QGroupBox   *mirrorGroup;
    QCheckBox   *hCheckBox;
    QCheckBox   *vCheckBox;
    QPushButton *mirrorButton;
    QPushButton *saveButton;
    QDial       *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage      srcImage;
    QImage      dstImage;

private slots:
    void mirroredImage();
    void rotatedImage();
    void saveDstImage();
};
#endif // GTRANSFORM_H
