/********************************************************************************
** Form generated from reading UI file 'capScreenForm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPSCREENFORM_H
#define UI_CAPSCREENFORM_H

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

class Ui_capScreenForm
{
public:
    QGridLayout *gridLayout;
    QLabel *capFps;
    ShrinkableQLabel *capDisplay;

    void setupUi(QWidget *capScreenForm)
    {
        if (capScreenForm->objectName().isEmpty())
            capScreenForm->setObjectName(QStringLiteral("capScreenForm"));
        capScreenForm->resize(480, 560);
        capScreenForm->setAutoFillBackground(false);
        capScreenForm->setStyleSheet(QStringLiteral("#capScreenForm { background: black;}"));
        gridLayout = new QGridLayout(capScreenForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        capFps = new QLabel(capScreenForm);
        capFps->setObjectName(QStringLiteral("capFps"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(capFps->sizePolicy().hasHeightForWidth());
        capFps->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Trebuchet MS"));
        capFps->setFont(font);
        capFps->setAutoFillBackground(false);
        capFps->setStyleSheet(QStringLiteral("color:white;"));

        gridLayout->addWidget(capFps, 0, 0, 1, 1);

        capDisplay = new ShrinkableQLabel(capScreenForm);
        capDisplay->setObjectName(QStringLiteral("capDisplay"));
        capDisplay->setMouseTracking(true);
        capDisplay->setFocusPolicy(Qt::NoFocus);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        capDisplay->setBackgroundBrush(brush);
        capDisplay->setInteractive(false);
        capDisplay->setSceneRect(QRectF(0, 0, 0, 0));

        gridLayout->addWidget(capDisplay, 1, 0, 1, 1);


        retranslateUi(capScreenForm);

        QMetaObject::connectSlotsByName(capScreenForm);
    } // setupUi

    void retranslateUi(QWidget *capScreenForm)
    {
        capScreenForm->setWindowTitle(QApplication::translate("capScreenForm", "capScreenForm", 0));
        capFps->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class capScreenForm: public Ui_capScreenForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPSCREENFORM_H
