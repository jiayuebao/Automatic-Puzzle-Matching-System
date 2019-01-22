/********************************************************************************
** Form generated from reading UI file 'bbqScreenForm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BBQSCREENFORM_H
#define UI_BBQSCREENFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "ShrinkableQLabel.h"

QT_BEGIN_NAMESPACE

class Ui_bbqScreenForm
{
public:
    QGridLayout *gridLayout;
    QLabel *lblFps;
    ShrinkableQLabel *lblDisplay;

    void setupUi(QWidget *bbqScreenForm)
    {
        if (bbqScreenForm->objectName().isEmpty())
            bbqScreenForm->setObjectName(QStringLiteral("bbqScreenForm"));
        bbqScreenForm->resize(480, 560);
        bbqScreenForm->setContextMenuPolicy(Qt::NoContextMenu);
        bbqScreenForm->setAutoFillBackground(false);
        bbqScreenForm->setStyleSheet(QStringLiteral("#bbqScreenForm { background: black;}"));
        gridLayout = new QGridLayout(bbqScreenForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblFps = new QLabel(bbqScreenForm);
        lblFps->setObjectName(QStringLiteral("lblFps"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblFps->sizePolicy().hasHeightForWidth());
        lblFps->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Trebuchet MS"));
        lblFps->setFont(font);
        lblFps->setAutoFillBackground(false);
        lblFps->setStyleSheet(QStringLiteral("color:white;"));

        gridLayout->addWidget(lblFps, 0, 0, 1, 2);

        lblDisplay = new ShrinkableQLabel(bbqScreenForm);
        lblDisplay->setObjectName(QStringLiteral("lblDisplay"));
        lblDisplay->setMouseTracking(true);
        lblDisplay->setFocusPolicy(Qt::NoFocus);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        lblDisplay->setBackgroundBrush(brush);
        lblDisplay->setInteractive(false);
        lblDisplay->setSceneRect(QRectF(0, 0, 0, 0));

        gridLayout->addWidget(lblDisplay, 1, 0, 1, 2);


        retranslateUi(bbqScreenForm);

        QMetaObject::connectSlotsByName(bbqScreenForm);
    } // setupUi

    void retranslateUi(QWidget *bbqScreenForm)
    {
        bbqScreenForm->setWindowTitle(QApplication::translate("bbqScreenForm", "Screen mirror", 0));
        lblFps->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class bbqScreenForm: public Ui_bbqScreenForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BBQSCREENFORM_H
