/********************************************************************************
** Form generated from reading UI file 'qtcyberdip.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCYBERDIP_H
#define UI_QTCYBERDIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtCyberDip
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *mainTabWidget;
    QWidget *comTab;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *comLogBox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *comMainLog;
    QGridLayout *comSendGridLayout;
    QPushButton *comSendButton;
    QLineEdit *comSendEdit;
    QPushButton *comClcButton;
    QGroupBox *comContrlBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *comPortGridLayout;
    QLabel *comPortLabel;
    QComboBox *comSelList;
    QCheckBox *comCheckS;
    QPushButton *comConnectButton;
    QSpacerItem *verticalSpacer;
    QGridLayout *comDirectionGridLayout;
    QPushButton *comRightButton;
    QPushButton *comDownButton;
    QPushButton *comLeftButton;
    QPushButton *comUpButton;
    QPushButton *comInitButton;
    QLabel *comDeltaLabel;
    QDoubleSpinBox *comSpinBox;
    QLabel *comPosLabel;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *comButtonGridLayout;
    QPushButton *comReturnButton;
    QPushButton *comHitButton;
    QWidget *bbqTab;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *bbqListBox;
    QVBoxLayout *verticalLayout_5;
    QListWidget *bbqListDevices;
    QGridLayout *gridLayout_4;
    QLabel *bbqIPText;
    QLineEdit *bbqIP;
    QPushButton *bbqConnect;
    QGroupBox *bbqUSBBox;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *bbqBitGridLayout;
    QSpinBox *bbqSpinBitrate;
    QComboBox *bbqCbQuality;
    QPushButton *bbqBootstrapUSB;
    QPushButton *bbqConnectUSB;
    QSpacerItem *verticalSpacer_2;
    QPushButton *bbqDebugLog;
    QCheckBox *bbqCbHighQuality;
    QCheckBox *bbqShowFps;
    QWidget *capTab;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *capListWinBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *capList;
    QGroupBox *capControlBox;
    QVBoxLayout *verticalLayout;
    QPushButton *capScanButton;
    QPushButton *capStartButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *capClcButton;

    void setupUi(QMainWindow *qtCyberDip)
    {
        if (qtCyberDip->objectName().isEmpty())
            qtCyberDip->setObjectName(QStringLiteral("qtCyberDip"));
        qtCyberDip->setWindowModality(Qt::NonModal);
        qtCyberDip->resize(700, 423);
        centralWidget = new QWidget(qtCyberDip);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        mainTabWidget = new QTabWidget(centralWidget);
        mainTabWidget->setObjectName(QStringLiteral("mainTabWidget"));
        mainTabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        mainTabWidget->setTabPosition(QTabWidget::North);
        mainTabWidget->setTabShape(QTabWidget::Rounded);
        mainTabWidget->setUsesScrollButtons(true);
        mainTabWidget->setMovable(true);
        mainTabWidget->setTabBarAutoHide(false);
        comTab = new QWidget();
        comTab->setObjectName(QStringLiteral("comTab"));
        horizontalLayout_4 = new QHBoxLayout(comTab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        comLogBox = new QGroupBox(comTab);
        comLogBox->setObjectName(QStringLiteral("comLogBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comLogBox->sizePolicy().hasHeightForWidth());
        comLogBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(comLogBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comMainLog = new QTextEdit(comLogBox);
        comMainLog->setObjectName(QStringLiteral("comMainLog"));
        comMainLog->setUndoRedoEnabled(false);
        comMainLog->setReadOnly(true);

        verticalLayout_2->addWidget(comMainLog);

        comSendGridLayout = new QGridLayout();
        comSendGridLayout->setSpacing(6);
        comSendGridLayout->setObjectName(QStringLiteral("comSendGridLayout"));
        comSendButton = new QPushButton(comLogBox);
        comSendButton->setObjectName(QStringLiteral("comSendButton"));
        comSendButton->setEnabled(false);

        comSendGridLayout->addWidget(comSendButton, 0, 1, 1, 1);

        comSendEdit = new QLineEdit(comLogBox);
        comSendEdit->setObjectName(QStringLiteral("comSendEdit"));
        comSendEdit->setMinimumSize(QSize(0, 23));
        comSendEdit->setMaxLength(256);

        comSendGridLayout->addWidget(comSendEdit, 0, 0, 1, 1);

        comClcButton = new QPushButton(comLogBox);
        comClcButton->setObjectName(QStringLiteral("comClcButton"));

        comSendGridLayout->addWidget(comClcButton, 0, 2, 1, 1);


        verticalLayout_2->addLayout(comSendGridLayout);


        horizontalLayout_4->addWidget(comLogBox);

        comContrlBox = new QGroupBox(comTab);
        comContrlBox->setObjectName(QStringLiteral("comContrlBox"));
        comContrlBox->setMinimumSize(QSize(0, 0));
        comContrlBox->setCursor(QCursor(Qt::ArrowCursor));
        verticalLayout_3 = new QVBoxLayout(comContrlBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        comPortGridLayout = new QGridLayout();
        comPortGridLayout->setSpacing(6);
        comPortGridLayout->setObjectName(QStringLiteral("comPortGridLayout"));
        comPortLabel = new QLabel(comContrlBox);
        comPortLabel->setObjectName(QStringLiteral("comPortLabel"));
        comPortLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        comPortGridLayout->addWidget(comPortLabel, 0, 0, 1, 1);

        comSelList = new QComboBox(comContrlBox);
        comSelList->setObjectName(QStringLiteral("comSelList"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comSelList->sizePolicy().hasHeightForWidth());
        comSelList->setSizePolicy(sizePolicy1);
        comSelList->setMinimumSize(QSize(150, 25));

        comPortGridLayout->addWidget(comSelList, 0, 1, 1, 1);

        comCheckS = new QCheckBox(comContrlBox);
        comCheckS->setObjectName(QStringLiteral("comCheckS"));

        comPortGridLayout->addWidget(comCheckS, 0, 2, 1, 1);


        verticalLayout_3->addLayout(comPortGridLayout);

        comConnectButton = new QPushButton(comContrlBox);
        comConnectButton->setObjectName(QStringLiteral("comConnectButton"));
        comConnectButton->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(comConnectButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        comDirectionGridLayout = new QGridLayout();
        comDirectionGridLayout->setSpacing(6);
        comDirectionGridLayout->setObjectName(QStringLiteral("comDirectionGridLayout"));
        comRightButton = new QPushButton(comContrlBox);
        comRightButton->setObjectName(QStringLiteral("comRightButton"));
        comRightButton->setEnabled(false);
        comRightButton->setMinimumSize(QSize(0, 40));

        comDirectionGridLayout->addWidget(comRightButton, 3, 3, 1, 1);

        comDownButton = new QPushButton(comContrlBox);
        comDownButton->setObjectName(QStringLiteral("comDownButton"));
        comDownButton->setEnabled(false);
        comDownButton->setMinimumSize(QSize(0, 40));
        comDownButton->setCheckable(false);
        comDownButton->setAutoDefault(false);

        comDirectionGridLayout->addWidget(comDownButton, 4, 1, 1, 1);

        comLeftButton = new QPushButton(comContrlBox);
        comLeftButton->setObjectName(QStringLiteral("comLeftButton"));
        comLeftButton->setEnabled(false);
        comLeftButton->setMinimumSize(QSize(0, 40));

        comDirectionGridLayout->addWidget(comLeftButton, 3, 0, 1, 1);

        comUpButton = new QPushButton(comContrlBox);
        comUpButton->setObjectName(QStringLiteral("comUpButton"));
        comUpButton->setEnabled(false);
        comUpButton->setMinimumSize(QSize(0, 40));

        comDirectionGridLayout->addWidget(comUpButton, 2, 1, 1, 1);

        comInitButton = new QPushButton(comContrlBox);
        comInitButton->setObjectName(QStringLiteral("comInitButton"));
        comInitButton->setEnabled(false);
        comInitButton->setMinimumSize(QSize(0, 40));

        comDirectionGridLayout->addWidget(comInitButton, 3, 1, 1, 1);

        comDeltaLabel = new QLabel(comContrlBox);
        comDeltaLabel->setObjectName(QStringLiteral("comDeltaLabel"));
        comDeltaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        comDirectionGridLayout->addWidget(comDeltaLabel, 5, 0, 1, 1);

        comSpinBox = new QDoubleSpinBox(comContrlBox);
        comSpinBox->setObjectName(QStringLiteral("comSpinBox"));
        comSpinBox->setMinimumSize(QSize(0, 25));
        comSpinBox->setValue(5);

        comDirectionGridLayout->addWidget(comSpinBox, 5, 1, 1, 1);

        comPosLabel = new QLabel(comContrlBox);
        comPosLabel->setObjectName(QStringLiteral("comPosLabel"));
        comPosLabel->setWordWrap(false);

        comDirectionGridLayout->addWidget(comPosLabel, 5, 3, 1, 1);


        verticalLayout_3->addLayout(comDirectionGridLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        comButtonGridLayout = new QGridLayout();
        comButtonGridLayout->setSpacing(6);
        comButtonGridLayout->setObjectName(QStringLiteral("comButtonGridLayout"));
        comReturnButton = new QPushButton(comContrlBox);
        comReturnButton->setObjectName(QStringLiteral("comReturnButton"));
        comReturnButton->setEnabled(false);
        comReturnButton->setMinimumSize(QSize(0, 40));

        comButtonGridLayout->addWidget(comReturnButton, 0, 0, 1, 1);

        comHitButton = new QPushButton(comContrlBox);
        comHitButton->setObjectName(QStringLiteral("comHitButton"));
        comHitButton->setEnabled(false);
        comHitButton->setMinimumSize(QSize(0, 40));

        comButtonGridLayout->addWidget(comHitButton, 0, 1, 1, 1);


        verticalLayout_3->addLayout(comButtonGridLayout);


        horizontalLayout_4->addWidget(comContrlBox);

        mainTabWidget->addTab(comTab, QString());
        bbqTab = new QWidget();
        bbqTab->setObjectName(QStringLiteral("bbqTab"));
        horizontalLayout_2 = new QHBoxLayout(bbqTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        bbqListBox = new QGroupBox(bbqTab);
        bbqListBox->setObjectName(QStringLiteral("bbqListBox"));
        bbqListBox->setMinimumSize(QSize(261, 0));
        verticalLayout_5 = new QVBoxLayout(bbqListBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        bbqListDevices = new QListWidget(bbqListBox);
        bbqListDevices->setObjectName(QStringLiteral("bbqListDevices"));

        verticalLayout_5->addWidget(bbqListDevices);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        bbqIPText = new QLabel(bbqListBox);
        bbqIPText->setObjectName(QStringLiteral("bbqIPText"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(bbqIPText->sizePolicy().hasHeightForWidth());
        bbqIPText->setSizePolicy(sizePolicy2);
        bbqIPText->setMinimumSize(QSize(120, 0));
        QFont font;
        font.setFamily(QStringLiteral("Trebuchet MS"));
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        bbqIPText->setFont(font);
        bbqIPText->setWordWrap(true);

        gridLayout_4->addWidget(bbqIPText, 0, 0, 1, 1);

        bbqIP = new QLineEdit(bbqListBox);
        bbqIP->setObjectName(QStringLiteral("bbqIP"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(bbqIP->sizePolicy().hasHeightForWidth());
        bbqIP->setSizePolicy(sizePolicy3);
        bbqIP->setAlignment(Qt::AlignCenter);
        bbqIP->setCursorMoveStyle(Qt::LogicalMoveStyle);

        gridLayout_4->addWidget(bbqIP, 0, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);

        bbqConnect = new QPushButton(bbqListBox);
        bbqConnect->setObjectName(QStringLiteral("bbqConnect"));
        bbqConnect->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setFamily(QStringLiteral("Trebuchet MS"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        bbqConnect->setFont(font1);
        bbqConnect->setStyleSheet(QStringLiteral(""));
        bbqConnect->setAutoExclusive(false);

        verticalLayout_5->addWidget(bbqConnect);


        horizontalLayout_2->addWidget(bbqListBox);

        bbqUSBBox = new QGroupBox(bbqTab);
        bbqUSBBox->setObjectName(QStringLiteral("bbqUSBBox"));
        verticalLayout_6 = new QVBoxLayout(bbqUSBBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        bbqBitGridLayout = new QGridLayout();
        bbqBitGridLayout->setSpacing(6);
        bbqBitGridLayout->setObjectName(QStringLiteral("bbqBitGridLayout"));
        bbqSpinBitrate = new QSpinBox(bbqUSBBox);
        bbqSpinBitrate->setObjectName(QStringLiteral("bbqSpinBitrate"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(bbqSpinBitrate->sizePolicy().hasHeightForWidth());
        bbqSpinBitrate->setSizePolicy(sizePolicy4);
        bbqSpinBitrate->setMinimumSize(QSize(0, 25));
        bbqSpinBitrate->setMinimum(500);
        bbqSpinBitrate->setMaximum(10000);
        bbqSpinBitrate->setValue(4500);

        bbqBitGridLayout->addWidget(bbqSpinBitrate, 0, 0, 1, 1);

        bbqCbQuality = new QComboBox(bbqUSBBox);
        bbqCbQuality->setObjectName(QStringLiteral("bbqCbQuality"));
        bbqCbQuality->setMinimumSize(QSize(0, 25));

        bbqBitGridLayout->addWidget(bbqCbQuality, 0, 1, 1, 1);


        verticalLayout_6->addLayout(bbqBitGridLayout);

        bbqBootstrapUSB = new QPushButton(bbqUSBBox);
        bbqBootstrapUSB->setObjectName(QStringLiteral("bbqBootstrapUSB"));
        bbqBootstrapUSB->setMinimumSize(QSize(120, 50));

        verticalLayout_6->addWidget(bbqBootstrapUSB);

        bbqConnectUSB = new QPushButton(bbqUSBBox);
        bbqConnectUSB->setObjectName(QStringLiteral("bbqConnectUSB"));
        bbqConnectUSB->setEnabled(false);
        bbqConnectUSB->setMinimumSize(QSize(120, 50));

        verticalLayout_6->addWidget(bbqConnectUSB);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        bbqDebugLog = new QPushButton(bbqUSBBox);
        bbqDebugLog->setObjectName(QStringLiteral("bbqDebugLog"));
        sizePolicy4.setHeightForWidth(bbqDebugLog->sizePolicy().hasHeightForWidth());
        bbqDebugLog->setSizePolicy(sizePolicy4);
        bbqDebugLog->setMinimumSize(QSize(0, 25));

        verticalLayout_6->addWidget(bbqDebugLog);

        bbqCbHighQuality = new QCheckBox(bbqUSBBox);
        bbqCbHighQuality->setObjectName(QStringLiteral("bbqCbHighQuality"));
        bbqCbHighQuality->setChecked(false);

        verticalLayout_6->addWidget(bbqCbHighQuality);

        bbqShowFps = new QCheckBox(bbqUSBBox);
        bbqShowFps->setObjectName(QStringLiteral("bbqShowFps"));
        bbqShowFps->setChecked(true);

        verticalLayout_6->addWidget(bbqShowFps);


        horizontalLayout_2->addWidget(bbqUSBBox);

        mainTabWidget->addTab(bbqTab, QString());
        capTab = new QWidget();
        capTab->setObjectName(QStringLiteral("capTab"));
        horizontalLayout_3 = new QHBoxLayout(capTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        capListWinBox = new QGroupBox(capTab);
        capListWinBox->setObjectName(QStringLiteral("capListWinBox"));
        horizontalLayout = new QHBoxLayout(capListWinBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        capList = new QListWidget(capListWinBox);
        capList->setObjectName(QStringLiteral("capList"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(capList->sizePolicy().hasHeightForWidth());
        capList->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(capList);


        horizontalLayout_3->addWidget(capListWinBox);

        capControlBox = new QGroupBox(capTab);
        capControlBox->setObjectName(QStringLiteral("capControlBox"));
        verticalLayout = new QVBoxLayout(capControlBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        capScanButton = new QPushButton(capControlBox);
        capScanButton->setObjectName(QStringLiteral("capScanButton"));
        capScanButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(capScanButton);

        capStartButton = new QPushButton(capControlBox);
        capStartButton->setObjectName(QStringLiteral("capStartButton"));
        capStartButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(capStartButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        capClcButton = new QPushButton(capControlBox);
        capClcButton->setObjectName(QStringLiteral("capClcButton"));
        capClcButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(capClcButton);


        horizontalLayout_3->addWidget(capControlBox);

        mainTabWidget->addTab(capTab, QString());

        verticalLayout_4->addWidget(mainTabWidget);

        qtCyberDip->setCentralWidget(centralWidget);

        retranslateUi(qtCyberDip);

        mainTabWidget->setCurrentIndex(0);
        bbqConnect->setDefault(true);
        bbqCbQuality->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(qtCyberDip);
    } // setupUi

    void retranslateUi(QMainWindow *qtCyberDip)
    {
        qtCyberDip->setWindowTitle(QApplication::translate("qtCyberDip", "qtCyberDip", 0));
        comLogBox->setTitle(QApplication::translate("qtCyberDip", "COM Log", 0));
        comSendButton->setText(QApplication::translate("qtCyberDip", "Send", 0));
        comClcButton->setText(QApplication::translate("qtCyberDip", "Clear", 0));
        comContrlBox->setTitle(QApplication::translate("qtCyberDip", "COM Control", 0));
        comPortLabel->setText(QApplication::translate("qtCyberDip", "Port:", 0));
        comCheckS->setText(QApplication::translate("qtCyberDip", "1s", 0));
        comConnectButton->setText(QApplication::translate("qtCyberDip", "Connect", 0));
        comRightButton->setText(QApplication::translate("qtCyberDip", "\342\206\222", 0));
        comDownButton->setText(QApplication::translate("qtCyberDip", "\342\206\223", 0));
        comLeftButton->setText(QApplication::translate("qtCyberDip", "\342\206\220", 0));
        comUpButton->setText(QApplication::translate("qtCyberDip", "\342\206\221", 0));
        comInitButton->setText(QString());
        comDeltaLabel->setText(QApplication::translate("qtCyberDip", "Delta:", 0));
        comPosLabel->setText(QApplication::translate("qtCyberDip", "<html><head/><body><p>X:--</p><p>Y:--</p></body></html>", 0));
        comReturnButton->setText(QApplication::translate("qtCyberDip", "Return", 0));
        comHitButton->setText(QApplication::translate("qtCyberDip", "Hit", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(comTab), QApplication::translate("qtCyberDip", "COM", 0));
        bbqListBox->setTitle(QApplication::translate("qtCyberDip", "List of detected devices (rooted)", 0));
        bbqIPText->setText(QApplication::translate("qtCyberDip", "Or manually enter IP:", 0));
        bbqIP->setInputMask(QApplication::translate("qtCyberDip", "999.999.999.999", 0));
        bbqConnect->setText(QApplication::translate("qtCyberDip", "CONNECT", 0));
        bbqUSBBox->setTitle(QApplication::translate("qtCyberDip", "Connect via USB (not root)", 0));
        bbqSpinBitrate->setSuffix(QApplication::translate("qtCyberDip", "kbps", 0));
        bbqSpinBitrate->setPrefix(QApplication::translate("qtCyberDip", "Bitrate: ", 0));
        bbqCbQuality->clear();
        bbqCbQuality->insertItems(0, QStringList()
         << QApplication::translate("qtCyberDip", "1080p", 0)
         << QApplication::translate("qtCyberDip", "720p", 0)
         << QApplication::translate("qtCyberDip", "540p", 0)
         << QApplication::translate("qtCyberDip", "360p", 0)
        );
        bbqCbQuality->setCurrentText(QApplication::translate("qtCyberDip", "720p", 0));
        bbqBootstrapUSB->setText(QApplication::translate("qtCyberDip", "Start USB service", 0));
        bbqConnectUSB->setText(QApplication::translate("qtCyberDip", "Connect via USB", 0));
        bbqDebugLog->setText(QApplication::translate("qtCyberDip", "Show debug log (for support)", 0));
        bbqCbHighQuality->setText(QApplication::translate("qtCyberDip", "HD processing (slower)", 0));
        bbqShowFps->setText(QApplication::translate("qtCyberDip", "Show FPS", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(bbqTab), QApplication::translate("qtCyberDip", "bbqClient", 0));
        capListWinBox->setTitle(QApplication::translate("qtCyberDip", "List of Windows", 0));
        capControlBox->setTitle(QApplication::translate("qtCyberDip", "Capture Control", 0));
        capScanButton->setText(QApplication::translate("qtCyberDip", "Scan", 0));
        capStartButton->setText(QApplication::translate("qtCyberDip", "Capture", 0));
        capClcButton->setText(QApplication::translate("qtCyberDip", "Clear", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(capTab), QApplication::translate("qtCyberDip", "ScreenCapture", 0));
    } // retranslateUi

};

namespace Ui {
    class qtCyberDip: public Ui_qtCyberDip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCYBERDIP_H
