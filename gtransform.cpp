#include "gtransform.h"
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>

GTransform::GTransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout();
    mirrorGroup = new QGroupBox(tr("鏡攝"), this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(tr("水平"), mirrorGroup);
    vCheckBox = new QCheckBox(tr("垂直"), mirrorGroup);
    mirrorButton = new QPushButton(tr("執行"), mirrorGroup);
    hCheckBox->setGeometry(QRect(13, 28, 87, 19));
    vCheckBox->setGeometry(QRect(13, 54, 87, 19));
    mirrorButton->setGeometry(QRect(13, 80, 93, 28));
    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    leftLayout->addWidget(mirrorGroup);
    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    saveButton = new QPushButton(tr("存檔"));
    vSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum,
                              QSizePolicy::Expanding);
    leftLayout->addWidget(rotateDial);
    leftLayout->addWidget(saveButton);
    leftLayout->addItem(vSpacer);
    mainLayout->addLayout(leftLayout);

    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(Qt::white);
    QPainter *paint = new QPainter(initPixmap);
    paint->setPen(*(new QColor(0,0,0)));
    paint->begin(initPixmap);
    paint->drawRect(15, 15, 60, 40);
    paint->end();
    if(srcImage.isNull())
    {
        srcImage = initPixmap->toImage();
        inWin->setPixmap(*initPixmap);
    }
    mainLayout->addWidget(inWin);
    connect(mirrorButton, SIGNAL(clicked()), this, SLOT(mirroredImage()));
    connect(rotateDial, SIGNAL(valueChanged(int)), this, SLOT(rotatedImage()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveDstImage()));
}

GTransform::~GTransform()
{

}

void GTransform::mirroredImage()
{
    bool H, V;
    if(srcImage.isNull())
        return;
    H = hCheckBox->isChecked();
    V = vCheckBox->isChecked();
    dstImage = srcImage.mirrored(H, V);
    inWin->setPixmap(QPixmap::fromImage(dstImage));
    srcImage = dstImage;
}

void GTransform::rotatedImage()
{
    QTransform tran;
    int angle;
    if(srcImage.isNull())
        return;
    angle = rotateDial->value();
    tran.rotate(angle);
    dstImage = srcImage.transformed(tran);
    inWin->setPixmap(QPixmap::fromImage(dstImage));
}

void GTransform::saveDstImage()
{
    QString filename;
    filename = QFileDialog::getSaveFileName(this, tr("存檔"), "");
    if(!dstImage.isNull())
        dstImage.save(filename);
}
