#include "stdafx.h"
#include "qtcyberdip.h"
#include "ui_qtcyberdip.h"
#include <opencv2/nonfree/nonfree.hpp>  
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <iostream>
#include <iostream>
#include <cmath>


#define ADB_PATH "prebuilts/adb.exe"
using namespace std;
using namespace cv;


int tmpx, tmpy;
int t = 0; int tt = 0;
int t1 = 0; int t2 = 0; int t3 = 0;
int t4 = 0;
int n = 0;// ROI����������ѵ�Ĵ���
int m = 0;//��������
int m1 = 0;//��������
int m2 = 0;//ƥ�������м���ѵ����
int p = 0;//ƥ����ɵĿ���
int countCenter = 1;

bool flag = false; bool flag2 = false; bool flag3 = false; bool flag4 = true; bool flag5 = false;  bool flag6 = false; bool flag7 = false;
bool inputFlag = false;
int total = 0;


Mat img_1;
Mat img_2;
Mat img_11;
Mat img_22;

int k = 0;
double kk = 0;
int xx = 0, yy = UP_CUT;//���Ͻ�����
double width2;
double height2;
double offset;

int step;//����
int value = 1000;//��ֵ
int background = 0;

void match(Mat img_1, Mat img_2);

qtCyberDip::qtCyberDip(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::qtCyberDip), bbqADBProcess(NULL), bbqDebugWidget(nullptr), bbqServiceShouldRun(false), bbqCrashCount(0),
comSPH(nullptr), comPosX(0), comPosY(0), initImg(true), hitDown(false), fetch(false)
{
	ui->setupUi(this);

	// Setup UDP discovery socket
	bbqAnnouncer = new QUdpSocket(this);
	bbqAnnouncer->bind(QHostAddress::Any, 9876);
	connect(bbqAnnouncer, SIGNAL(readyRead()), this, SLOT(bbqDiscoveryReadyRead()));

	// Connect UI slots
	connect(ui->bbqListDevices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(bbqSelectDevice(QListWidgetItem*)));
	connect(ui->bbqListDevices, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(bbqDoubleClickDevice(QListWidgetItem*)));
	connect(ui->bbqConnect, SIGNAL(clicked()), this, SLOT(bbqClickConnect()));
	connect(ui->bbqBootstrapUSB, SIGNAL(clicked()), this, SLOT(bbqClickBootstrapUSB()));
	connect(ui->bbqConnectUSB, SIGNAL(clicked()), this, SLOT(bbqClickConnectUSB()));
	connect(ui->bbqCbQuality, SIGNAL(currentIndexChanged(int)), this, SLOT(bbqQualityChanged(int)));
	connect(ui->bbqSpinBitrate, SIGNAL(valueChanged(int)), this, SLOT(bbqBitrateChanged(int)));
	connect(ui->bbqDebugLog, SIGNAL(clicked()), this, SLOT(bbqClickShowDebugLog()));
	connect(ui->comInitButton, SIGNAL(clicked()), this, SLOT(comInitPara()));
	connect(ui->comConnectButton, SIGNAL(clicked()), this, SLOT(comClickConnectButton()));
	connect(ui->comSendButton, SIGNAL(clicked()), this, SLOT(comClickSendButton()));
	connect(ui->comSendEdit, SIGNAL(returnPressed()), this, SLOT(comClickSendButton()));
	connect(ui->comClcButton, SIGNAL(clicked()), this, SLOT(comClickClearButton()));
	connect(ui->comHitButton, SIGNAL(clicked()), this, SLOT(comClickHitButton()));
	connect(ui->comReturnButton, SIGNAL(clicked()), this, SLOT(comClickRetButton()));
	connect(ui->comUpButton, SIGNAL(clicked()), this, SLOT(comMoveStepUp()));
	connect(ui->comDownButton, SIGNAL(clicked()), this, SLOT(comMoveStepDown()));
	connect(ui->comLeftButton, SIGNAL(clicked()), this, SLOT(comMoveStepLeft()));
	connect(ui->comRightButton, SIGNAL(clicked()), this, SLOT(comMoveStepRight()));
	connect(ui->capClcButton, SIGNAL(clicked()), this, SLOT(capClickClearButton()));
	connect(ui->capScanButton, SIGNAL(clicked()), this, SLOT(capClickScanButton()));
	connect(ui->capStartButton, SIGNAL(clicked()), this, SLOT(capClickConnect()));
	connect(ui->capList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(capDoubleClickWin(QListWidgetItem*)));

	comUpdatePos();

	//�����ӿؼ��¼�
	ui->comSelList->installEventFilter(this);
	//     | Who sends event &&         | Who will watch event


	startTimer(500);
}

qtCyberDip::~qtCyberDip()
{
	delete ui;
}

void qtCyberDip::closeEvent(QCloseEvent* evt)
{
	Q_UNUSED(evt);
	if (bbqADBProcess)
	{
		disconnect(bbqADBProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(bbqADBProcessFinishes()));
		bbqADBProcess->terminate();
		delete bbqADBProcess;
	}
	if (bbqDebugWidget)
	{
		bbqDebugWidget->close();
	}
	if (comSPH)
	{
		comSPH->disConnect();

		delete comSPH;
	}
}

void qtCyberDip::timerEvent(QTimerEvent* evt)
{
	Q_UNUSED(evt);

	// See if we have devices that disappeared. We make them timeout after 3 seconds.
	for (auto it = bbqDevices.begin(); it != bbqDevices.end(); ++it)
	{
		if ((*it)->lastPing.elapsed() > 3000)
		{
			ui->bbqListDevices->takeItem(bbqDevices.indexOf(*it));
			delete (*it);
			it = bbqDevices.erase(it);
			break;
		}
	}
}

bool qtCyberDip::eventFilter(QObject* watched, QEvent* event)
{
	//������combobox֮��ˢ�¿���COM��
	if (watched == ui->comSelList && event->type() == QEvent::MouseButtonPress)
	{
		comScanPorts();
	}
	return QObject::eventFilter(watched, event);
}

void qtCyberDip::bbqDiscoveryReadyRead()
{
	QByteArray datagram;
	QHostAddress sender;
	quint16 senderPort;

	while (bbqAnnouncer->hasPendingDatagrams())
	{
		if (datagram.size() != bbqAnnouncer->pendingDatagramSize())
			datagram.resize(bbqAnnouncer->pendingDatagramSize());

		// Read pending UDP datagram
		bbqAnnouncer->readDatagram(datagram.data(), datagram.size(),
			&sender, &senderPort);

		// Format of announcer packet:
		// 0 : Protocol version
		// 1 : Device name size
		// 2+: Device name

		unsigned char protocolVersion = datagram.at(0),
			deviceNameSize = datagram.at(1);

		QString deviceName = QByteArray(datagram.data() + 2, deviceNameSize);
		QString remoteIp = sender.toString();

		// Make sure we don't already know this device
		bool exists = false;
		for (auto it = bbqDevices.begin(); it != bbqDevices.end(); ++it)
		{
			if ((*it)->name == deviceName && (*it)->address == remoteIp)
			{
				(*it)->lastPing.restart();
				exists = true;
				break;
			}
		}

		if (!exists)
		{
			// XXX: Protocol v3 indicates that audio can't be streamed, and v4
			// indicates that we can stream audio. However, the user can choose
			// to turn off audio even on v4. Maybe in the future we could indicate
			// that.
			Device* device = new Device;
			device->name = deviceName;
			device->address = remoteIp;
			device->lastPing.start();

			ui->bbqListDevices->addItem(QString("%1 - (%2)").arg(deviceName, remoteIp));
			bbqDevices.push_back(device);
		}
	}
}
void qtCyberDip::bbqClickConnect()
{
	setCursor(Qt::WaitCursor);
	// Check that the IP entered is valid
	QString ip = ui->bbqIP->text();
	QHostAddress address(ip);
	if (QAbstractSocket::IPv4Protocol != address.protocol())
	{
		QMessageBox::critical(this, "Invalid IP", "The IP address you entered is invalid");
		setCursor(Qt::ArrowCursor);
		return;
	}

	// The IP is valid, connect to there
	bbqScreenForm* screen = new bbqScreenForm(this);
	connect(screen, SIGNAL(imgReady(QImage)), this, SLOT(processImg(QImage)));
	screen->setAttribute(Qt::WA_DeleteOnClose);
	screen->setShowFps(ui->bbqShowFps->isChecked());
	screen->show();
	screen->connectTo(ui->bbqIP->text());

	// Hide this dialog
	hide();
	setCursor(Qt::ArrowCursor);
}
void qtCyberDip::bbqSelectDevice(QListWidgetItem* item)
{
	Q_UNUSED(item);

	int index = ui->bbqListDevices->currentRow();
	if (index >= 0)
	{
		ui->bbqIP->setText(bbqDevices.at(index)->address);
	}
}

void qtCyberDip::bbqDoubleClickDevice(QListWidgetItem* item)
{
	bbqSelectDevice(item);
	bbqClickConnect();
}

QProcess* qtCyberDip::bbqRunAdb(const QStringList& params)
{
	QProcess* process = new QProcess(this);

	connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(bbqADBProcessReadyRead()));
	connect(process, SIGNAL(readyReadStandardError()), this, SLOT(bbqADBErrorReadyRead()));

#ifndef PLAT_APPLE
	process->start(ADB_PATH, params);
#else
	process->start(QDir(QCoreApplication::applicationDirPath()).absolutePath() + "/" + ADB_PATH, params);
#endif	

	return process;
}

void qtCyberDip::bbqClickBootstrapUSB()
{
	//qDebug()<< bbqADBProcess;
	if (!bbqServiceShouldRun)
	{
		bbqCrashCount = 0;
		bbqServiceShouldRun = true;
		bbqStartUsbService();
	}
	else
	{
		bbqServiceShouldRun = false;
		if (bbqADBProcess)
		{
			bbqADBProcess->terminate();
			bbqADBProcess->kill();
			//qDebug() << bbqADBProcess;
		}
	}
}

void qtCyberDip::bbqClickConnectUSB()
{
	// Forward TCP port to localhost and connect to it
	QStringList args;
	args << "forward";
	args << "tcp:9876";
	args << "tcp:9876";

	bbqRunAdb(args);

	ui->bbqIP->setText("127.0.0.1");
	bbqClickConnect();
}

void qtCyberDip::bbqADBProcessFinishes()
{
	//qDebug() << "finish";
	if (bbqServiceShouldRun)
	{
		bbqCrashCount++;

		if (bbqCrashCount > 20)
		{
			QMessageBox::critical(this, "Crash!", "It appears that the streaming process has crashed over 20 times. Please check the debug log window and send a screenshot to the support.");
			bbqServiceShouldRun = false;
		}
		// If the process crashed, reboot it
		bbqStartUsbService();
	}
	else
	{
		//qDebug() << "Normal end";
		// Normal stop
		ui->bbqBootstrapUSB->setText("Start USB service");
		ui->bbqConnectUSB->setEnabled(false);
	}
}

void qtCyberDip::bbqADBProcessReadyRead()
{
	//qDebug() << "ReadyRead";
	QProcess* process = (QProcess*)QObject::sender();

	QByteArray stdOut = process->readAllStandardOutput();
	QString stdOutLine = QString(stdOut).trimmed();

	if (stdOutLine.contains("/data/data") && stdOutLine.contains("No such file or directory"))
	{
		bbqServiceShouldRun = false;
		bbqServiceStartError = true;
	}
	else if (stdOutLine.contains("Unable to chmod"))
	{
		bbqServiceShouldRun = false;
		bbqServiceStartError = true;
	}

	if (!stdOutLine.isEmpty())
	{
		bbqADBLog.push_back(stdOutLine);

		if (bbqDebugWidget != nullptr)
		{
			bbqDebugWidget->addItem(stdOutLine);
		}
	}
}

void qtCyberDip::bbqADBErrorReadyRead()
{
	QProcess* process = (QProcess*)QObject::sender();

	QByteArray stdErr = process->readAllStandardError();
	QString stdErrLine = QString(stdErr).trimmed();

	if (stdErrLine.contains("device not found"))
	{
		bbqServiceShouldRun = false;
		QMessageBox::critical(this, "Device not found or unplugged", "Cannot find an Android device connected via ADB. Make sure USB Debugging is enabled on your device, and that the ADB drivers are installed. Follow the guide on our website for more information.");
	}
	else if (stdErrLine.contains("device offline"))
	{
		bbqServiceShouldRun = false;
		QMessageBox::critical(this, "Device offline", "An Android device is connected but reports as offline. Check your device for any additional information, or try to unplug and replug your device");
	}
	else if (stdErrLine.contains("unauthorized"))
	{
		bbqServiceShouldRun = false;
		QMessageBox::critical(this, "Device unauthorized", "An Android device is connected but reports as unauthorized. Please check the confirmation dialog on your device.");
	}

	if (!stdErrLine.isEmpty())
	{
		bbqADBErrorLog.push_back(stdErrLine);

		if (bbqDebugWidget != nullptr)
		{
			QListWidgetItem* item = new QListWidgetItem(stdErrLine);
			item->setTextColor(QColor(255, 0, 0));
			bbqDebugWidget->addItem(item);
		}
	}
	bbqADBProcess->terminate();
	bbqADBProcess->kill();

}

void qtCyberDip::bbqStartUsbService()
{
	bbqServiceStartError = false;

	ui->bbqBootstrapUSB->setEnabled(false);
	ui->bbqBootstrapUSB->setText("Starting...");


	setCursor(Qt::WaitCursor);
	qApp->processEvents();

	if (!bbqADBProcess)
	{
		bbqADBProcess = new QProcess(this);
		connect(bbqADBProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(bbqADBProcessFinishes()));
		connect(bbqADBProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(bbqADBProcessReadyRead()));
		connect(bbqADBProcess, SIGNAL(readyReadStandardError()), this, SLOT(bbqADBErrorReadyRead()));
	}

	// Copy binary to workaround some security restrictions on Lollipop and Knox
	QStringList args;
	args << "shell";
	args << "cp";
	args << "/data/data/org.bbqdroid.bbqscreen/files/bbqscreen";
	args << "/data/local/tmp/bbqscreen";
	QProcess* copyProc = bbqRunAdb(args);
	copyProc->waitForFinished();
	if (bbqServiceStartError)
	{
		QMessageBox::critical(this, "Unable to prepare the USB service", "Unable to copy the BBQScreen service to an executable zone on your device, as it hasn't been found. Please make sure the BBQScreen app is installed, and that you opened it once, and pressed 'USB' if prompted or turned it on once.");
		delete copyProc;
		return;
	}

	args.clear();
	args << "shell";
	args << "chmod";
	args << "755";
	args << "/data/local/tmp/bbqscreen";
	QProcess* chmodProc = bbqRunAdb(args);
	chmodProc->waitForFinished();
	if (bbqServiceStartError)
	{
		QMessageBox::critical(this, "Unable to prepare the USB service", "Unable to set the permissions of the BBQScreen service to executable. Please contact support.");
		delete chmodProc;
		return;
	}

	args.clear();
	args << "shell";
	args << "/data/local/tmp/bbqscreen";
	args << "-s";
	args << "50";
	switch (ui->bbqCbQuality->currentIndex())
	{
	case 0:
		args << "-1080";
		break;
	case 1:
		args << "-720";
		break;
	case 2:
		args << "-540";
		break;
	case 3:
		args << "-360";
		break;
	}
	args << "-q";
	args << QString::number(ui->bbqSpinBitrate->value());
	args << "-i";

	bbqADBProcess->start(ADB_PATH, args);
	ui->bbqConnectUSB->setEnabled(true);
	ui->bbqBootstrapUSB->setEnabled(true);
	ui->bbqBootstrapUSB->setText("Stop USB service");
	setCursor(Qt::ArrowCursor);
	delete chmodProc;
	delete copyProc;
}

void qtCyberDip::bbqQualityChanged(int index)
{
	if (bbqADBProcess)
	{
		bbqCrashCount = 0;
		// Restart the app
		bbqADBProcess->terminate();
		bbqADBProcess->kill();
	}
}

void qtCyberDip::bbqBitrateChanged(int value)
{
	if (bbqADBProcess)
	{
		bbqCrashCount = 0;
		// Restart the app
		bbqADBProcess->terminate();
		bbqADBProcess->kill();
	}
}
void qtCyberDip::bbqClickShowDebugLog()
{
	if (bbqDebugWidget != nullptr) {
		delete bbqDebugWidget;
	}
	bbqDebugWidget = new QListWidget();
	bbqDebugWidget->addItems(bbqADBLog);

	for (auto it = bbqADBErrorLog.begin(); it != bbqADBErrorLog.end(); ++it) {
		QListWidgetItem* item = new QListWidgetItem(*it);
		item->setTextColor(QColor(255, 0, 0));
		bbqDebugWidget->addItem(item);
	}

	bbqDebugWidget->show();

}

void qtCyberDip::comInitPara()
{
	/* 0.8c*/
	/*
	$0=250.000 (x, step/mm)
	$1=250.000 (y, step/mm)
	$2=250.000 (z, step/mm)
	$3=10 (step pulse, usec)
	$4=50.000 (default feed, mm/min)
	$5=2000.000 (default seek, mm/min)
	$6=192 (step port invert mask, int:11000000)
	$7=25 (step idle delay, msec)
	$8=120.000 (acceleration, mm/sec^2)
	$9=0.050 (junction deviation, mm)
	$10=0.100 (arc, mm/segment)
	$11=25 (n-arc correction, int)
	$12=3 (n-decimals, int)
	$13=0 (report inches, bool)
	$14=1 (auto start, bool)
	$15=0 (invert step enable, bool)
	$16=0 (hard limits, bool)
	$17=0 (homing cycle, bool)
	$18=0 (homing dir invert mask, int:00000000)
	$19=25.000 (homing feed, mm/min)
	$20=250.000 (homing seek, mm/min)
	$21=100 (homing debounce, msec)
	$22=1.000 (homing pull-off, mm)

	*/

	/*	0.9j */
	/*$0=10 (step pulse, usec)
	$1=25 (step idle delay, msec)
	$2=0 (step port invert mask:00000000)
	$3=0 (dir port invert mask:00000000)
	$4=0 (step enable invert, bool)
	$5=0 (limit pins invert, bool)
	$6=0 (probe pin invert, bool)
	$10=3 (status report mask:00000011)
	$11=0.010 (junction deviation, mm)
	$12=0.002 (arc tolerance, mm)
	$13=0 (report inches, bool)
	$20=0 (soft limits, bool)
	$21=0 (hard limits, bool)
	$22=0 (homing cycle, bool)
	$23=0 (homing dir invert mask:00000000)
	$24=25.000 (homing feed, mm/min)
	$25=500.000 (homing seek, mm/min)
	$26=250 (homing debounce, msec)
	$27=1.000 (homing pull-off, mm)
	$100=250.000 (x, step/mm)
	$101=250.000 (y, step/mm)
	$102=250.000 (z, step/mm)
	$110=2500.000 (x max rate, mm/min)
	$111=2500.000 (y max rate, mm/min)
	$112=500.000 (z max rate, mm/min)
	$120=120.000 (x accel, mm/sec^2)
	$121=120.000 (y accel, mm/sec^2)
	$122=10.000 (z accel, mm/sec^2)
	$130=200.000 (x max travel, mm)
	$131=200.000 (y max travel, mm)
	$132=200.000 (z max travel, mm)*/
	QList<QPair<int, float>> para;
	if (ui->comCheckS->isChecked())
	{

		para.push_back(qMakePair(0, 10));
		para.push_back(qMakePair(1, 25));
		para.push_back(qMakePair(2, 0));
		para.push_back(qMakePair(3, 0));
		para.push_back(qMakePair(4, 0));
		para.push_back(qMakePair(5, 0));
		para.push_back(qMakePair(6, 0));

		para.push_back(qMakePair(10, 3));
		para.push_back(qMakePair(11, 0.010));
		para.push_back(qMakePair(12, 0.002));
		para.push_back(qMakePair(13, 0));

		para.push_back(qMakePair(20, 0));
		para.push_back(qMakePair(21, 0));
		para.push_back(qMakePair(22, 0));
		para.push_back(qMakePair(23, 0));
		para.push_back(qMakePair(24, 25));
		para.push_back(qMakePair(25, 500));
		para.push_back(qMakePair(26, 250));
		para.push_back(qMakePair(27, 1));

		para.push_back(qMakePair(100, 250));
		para.push_back(qMakePair(101, 250));
		para.push_back(qMakePair(102, 250));

		para.push_back(qMakePair(110, 2500));
		para.push_back(qMakePair(111, 2500));
		para.push_back(qMakePair(112, 500));

		para.push_back(qMakePair(120, 120));
		para.push_back(qMakePair(121, 120));
		para.push_back(qMakePair(122, 10));

		para.push_back(qMakePair(130, 200));
		para.push_back(qMakePair(131, 200));
		para.push_back(qMakePair(132, 200));
	}
	else
	{
		para.push_back(qMakePair(0, 250));
		para.push_back(qMakePair(1, 250));
		para.push_back(qMakePair(2, 200));
		para.push_back(qMakePair(3, 10));
		para.push_back(qMakePair(4, 50));
		para.push_back(qMakePair(5, 2000));
		para.push_back(qMakePair(6, 192));
		para.push_back(qMakePair(7, 25));
		para.push_back(qMakePair(8, 120));
		para.push_back(qMakePair(9, 0.05));
		para.push_back(qMakePair(10, 0.1));
		para.push_back(qMakePair(11, 25));
		para.push_back(qMakePair(12, 3));
		para.push_back(qMakePair(13, 0));
		para.push_back(qMakePair(14, 1));
		para.push_back(qMakePair(15, 0));
		para.push_back(qMakePair(16, 0));
		para.push_back(qMakePair(17, 0));
		para.push_back(qMakePair(18, 0));
		para.push_back(qMakePair(19, 25));
		para.push_back(qMakePair(20, 250));
		para.push_back(qMakePair(21, 100));
		para.push_back(qMakePair(22, 1.0));

	}

	QList<QPair<int, float>>::iterator tp = para.begin();
	while (tp != para.end())
	{
		char cache[64];
		sprintf(cache, "$%d=%0.3f", tp->first, tp->second);
		comRequestToSend(QString(cache));
		tp++;
		Sleep(500);
	}

}

void qtCyberDip::comClickConnectButton()
{
	setCursor(Qt::WaitCursor);
	bool built = comSPH;
	bool online = false;
	if (built){ online = comSPH->isOpen(); }
	if (online)
	{
		comLogAdd("Disconnecting..", 2);
		comSPH->disConnect();
		if (!(comSPH->isOpen())){ comLogAdd("Done.", 2); }
		ui->comSelList->setCurrentIndex(-1);
	}
	else
	{
		int index = ui->comSelList->currentIndex();
		if (index >= 0 && index<comPorts.length())
		{
			comLogAdd("Connecting..", 2);
			if (!built)
			{
				comSPH = new comSPHandler(this);
				connect(comSPH, SIGNAL(serialPortSignals(QString, int)), this, SLOT(comLogAdd(QString, int)));
			}
			comSPH->setPort(comPorts[index]);

			if (comSPH->connectTo((ui->comCheckS->isChecked()) ? QSerialPort::Baud115200 : QSerialPort::Baud9600))
			{
				comLogAdd("Done.", 2);
			}
			else
			{
				comLogAdd("Failed", 2);
			}
		}
	}
	comUpdateUI();
	setCursor(Qt::ArrowCursor);
}

void qtCyberDip::comUpdateUI()
{
	bool online = comSPH;
	if (online){ online = comSPH->isOpen(); }
	ui->comConnectButton->setText((online) ? "Disconnect" : "Connect");
	ui->comSendButton->setEnabled(online);
	ui->comHitButton->setEnabled(online);
	ui->comHitButton->setEnabled(online);
	ui->comReturnButton->setEnabled(online);
	ui->comUpButton->setEnabled(online);
	ui->comDownButton->setEnabled(online);
	ui->comLeftButton->setEnabled(online);
	ui->comRightButton->setEnabled(online);
	ui->comSelList->setEnabled(!online);
}

void qtCyberDip::comUpdatePos()
{
	ui->comPosLabel->setText("X: " + QString::number(comPosX) + "\nY: " + QString::number(comPosY));
}


void  qtCyberDip::comLogAdd(QString txt, int type = 0)
{
	//0 -normal&receive
	//1 -send
	//2 -system
	switch (type)
	{
	case 1:ui->comMainLog->append(">>" + txt + "\n"); break;
	case 2:ui->comMainLog->append("/***   " + txt + "   ***/"); break;
	default:
		ui->comMainLog->insertPlainText(txt);
		break;
	}
	ui->comMainLog->moveCursor(QTextCursor::End);
}

void qtCyberDip::comScanPorts()
{
	ui->comSelList->clear();
	comPorts.clear();
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		//qDebug() << "Name        : " << info.portName();
		//qDebug() << "Description : " << info.description();
		//qDebug() << "Manufacturer: " << info.manufacturer();
		ui->comSelList->addItem(info.portName() + " " + info.description());
		comPorts.push_back(info);
	}
}

void qtCyberDip::comMoveTo(double x, double y)
{
	if (x == comPosX && y == comPosY){ return; }
	comPosX = x;
	comPosY = y;
	comRequestToSend("G90");//��������
	comRequestToSend("G0 X" + QString::number(-comPosX) + " Y" + QString::number(-comPosY));
	comUpdatePos();
}

void qtCyberDip::comMoveToScale(double ratioX, double ratioY)
{
	double px = std::max(std::min(ratioX, 1.0), 0.0);
	double py = std::max(std::min(ratioY, 1.0), 0.0);
	comMoveTo(px*RANGE_X, py*RANGE_Y);
}

void  qtCyberDip::comClickSendButton()
{
	if (ui->comSendEdit->text().length() > 0)
	{
		comRequestToSend(ui->comSendEdit->text());
	}
}

void qtCyberDip::comClickClearButton()
{
	ui->comMainLog->clear();
	ui->comSendEdit->clear();
}

void qtCyberDip::comClickHitButton()
{
	comHitDown();
	comRequestToSend("G91");//�������
	//�ò����ڵ�Z��ʵ����ʱ����
	if (fetch)
	{
		comRequestToSend("G1 Z-0.01 F5.");
	}
	else
	{
		comRequestToSend("G1 Z0.01 F5.");
	}
	fetch = !fetch;
	comHitUp();
}

void qtCyberDip::comClickRetButton()
{
	comHitUp();
	comMoveTo(0, 0);
}

void qtCyberDip::comRequestToSend(QString txt)
{
	if (!comSPH){ return; }
	comSPH->requestToSend(txt);
}

void qtCyberDip::comMoveStepUp()
{
	comMoveTo(comPosX, comPosY - ui->comSpinBox->value());

}

void qtCyberDip::comMoveStepDown()
{
	comMoveTo(comPosX, comPosY + ui->comSpinBox->value());
}
void qtCyberDip::comMoveStepLeft()
{
	comMoveTo(comPosX - ui->comSpinBox->value(), comPosY);
}
void qtCyberDip::comMoveStepRight()
{

	comMoveTo(comPosX + ui->comSpinBox->value(), comPosY);
}

void qtCyberDip::comHitDown()
{
	hitDown = true;
	comRequestToSend("M3 S1000");
}
void qtCyberDip::comHitUp()
{
	hitDown = false;
	comRequestToSend("M5");
}


void qtCyberDip::capClickClearButton()
{
	ui->capList->clear();
	capWins.clear();
}

void qtCyberDip::capClickScanButton()
{

	capClickClearButton();
	EnumWindows(capEveryWindowProc, (LPARAM) this);
}

void qtCyberDip::capAddhWnd(HWND hWnd, QString nameToShow)
{
	capWins.push_back(hWnd);
	ui->capList->addItem(nameToShow);
}

BOOL CALLBACK capEveryWindowProc(HWND hWnd, LPARAM parameter)
{
	// ���ɼ������ɼ���Ĵ��ڲ������ǡ�
	if (!IsWindowVisible(hWnd)){ return true; }
	if (!IsWindowEnabled(hWnd)){ return true; }
	// ����ʽ���ڲ������ǡ�
	LONG gwl_style = GetWindowLong(hWnd, GWL_STYLE);
	if ((gwl_style & WS_POPUP) && !(gwl_style & WS_CAPTION)){ return true; }

	// �������ǿɼ���ɼ���Ĵ��ڲ������ǡ�
	HWND hParent = (HWND)GetWindowLong(hWnd, GW_OWNER);
	if (IsWindowEnabled(hParent)){ return true; }
	if (IsWindowVisible(hParent)){ return true; }

	wchar_t szCaption[500];
	::GetWindowText(hWnd, szCaption, sizeof(szCaption));
	//if (wcslen(szCaption) <= 0){ return true; }
	((qtCyberDip*)parameter)->capAddhWnd(hWnd, "0x" + QString::number((uint)hWnd, 16) + "  " + QString::fromWCharArray(szCaption));
	return true;
}

void qtCyberDip::capClickConnect()
{

	int index = ui->capList->currentRow();
	if (index>capWins.size() - 1 || index<0){ return; }
	setCursor(Qt::WaitCursor);
	qDebug() << "Windows Handle: " << capWins[index];
	capScreenForm* screen = new capScreenForm(this);
	connect(screen, SIGNAL(imgReady(QImage)), this, SLOT(processImg(QImage)));
	screen->capSetHWND(capWins[index]);
	screen->show();
	hide();
	capClickClearButton();
	screen->capStart();
	setCursor(Qt::ArrowCursor);
}

void qtCyberDip::capDoubleClickWin(QListWidgetItem* item)
{
	capClickConnect();
}

//STEP3:�滻�����ͼ�������Imgprocess
//ÿ���յ�һ��ͼƬʱ������øú���
void qtCyberDip::processImg(QImage img)
{
	//*************************************************************//
	//                                                             //
	//                                                             //
	//         TODO:ʹ����Ĵ����滻�����ͼ�������             //
	//                                                             //
	//          ����ʹ��comMoveToScale(x,y)���Ϳ���ָ��            //
	//                                                             //
	//*************************************************************//

#ifdef VIA_OPENCV
	cv::String winName = "Frame";

	//��ʼ��
	if (initImg)
	{
		cv::namedWindow(winName);
		cv::setMouseCallback(winName.c_str(), mouseCallback, (void*)&(argM));
		initImg = false;
	}
	cv::Mat pt = QImage2cvMat(img);
	cv::imshow(winName, pt);
	cv::Size imgSize = pt.size();
    
	if (!inputFlag)
	{
		qDebug() << "Please input k:";
		cin >> k;
		if (k > 0)inputFlag = true;
		return;
	}
	//step1����ȡԭͼ
	if (!flag)
	{
		//���ܣ�ϵͳ�Զ���ȡԭͼ
		//ʹ�÷�����ÿ�����Ҽ���������桱���������������桱�����޸ģ�
		if (argM.box.x > 0 && argM.box.x < imgSize.width&&
			argM.box.y > 0 && argM.box.y < imgSize.height)
		{
			qDebug() << "X:" << argM.box.x << " Y:" << argM.box.y;
			if (argM.Hit)
			{
				comHitDown();
			}
			comMoveToScale((1 - ((double)(argM.box.y) + argM.box.height - UP_CUT) / pt.rows),
                           ((double)argM.box.x + argM.box.width) / pt.cols);
			argM.box.x = -1; argM.box.y = -1;
			if (argM.Hit)
			{
				comHitUp();
			}
			else
			{
				comClickHitButton();
				flag2 = true;

			}
		}
		if (flag2)
		{
			//�����ƶ�ʱ��
			t++;
			if (t == 5)
			{
				//��ȡƴͼ����
				img_11 = pt(Range(0.235*pt.rows, 0.815*pt.rows), Range(0.1*pt.cols, 0.91*pt.cols));//ipad ��
				//����image_11
				cv::imwrite("ԭͼ.png", img_11);
				img_1 = imread("ԭͼ.png");
				cv::imshow("ԭͼ", img_1);

				flag = true;
				waitKey(2000);
				xx = 0;
			}
		}
	}
	//step2~3 
	if (flag)
	{
		if (!flag3)
		{
			{
				//����ɨ�跶Χ
				int range1 = pt.cols - width2;//���ҷ�Χ
				int range2 = pt.rows - height2;//���·�Χ

				//y���Ͻ���½�
				int upper = 0;
				int lower = 0.758*pt.rows;

				//���������ֵ
				int threshold;

				if (k<5)threshold = (2 * k - 1) * 5;
				else if (k == 5)
				{
					threshold = (3 * k - 4) * 3;
				}
				else 
				{
					if (k>=7)
					threshold = (3 * k - 3) * 4;
					else threshold = (3 * k - 3) * 3;
				}

				//1.ɨ������
				if (background <threshold)
				{
					//2*2 && 3*3 &&4*4
					if (k<5)
					{
						value = 1000;
						//����img2ͼƬ��С
						if (t1 <= 3)//��������
						{
							width2 = pt.cols / k;
							height2 = pt.rows*0.19;

							range1 = pt.cols - width2;//���ҷ�Χ
							range2 = pt.rows - height2;//���·�Χ

							step = range1 / (2 * k - 1);
							if (xx > range1 - step&&t1 % 4 == 3)
							{
								background = 0;
							}

							//x����
							if (xx + step < range1)
							{

								if (xx == 0) xx = 1;
								else xx = xx + step;
							}
							else
							{
								xx = 0;
								t1++;
							}

							//y����
							if (t1 % 2 == 1)
							{
								qDebug() << "down";
								yy = UP_CUT + 0.758*pt.rows;

							}
							else
							{
								qDebug() << "up";
								yy = UP_CUT;

							}
						}
						else //����
						{
							width2 = pt.cols / (k * 2);
							height2 = pt.rows*0.19;

							range1 = pt.cols - width2;//���ҷ�Χ
							range2 = pt.rows - height2;//���·�Χ

							step = range2 / threshold;

							if (t1 == 4){ yy = UP_CUT; t1++; }
							if (t2 == 2)
							{
								t2 = 0; t1 = 0;
								xx = 0;
							}
							//y����
							if (yy + step < range2)
							{
								yy = yy + step;
							}
							else
							{
								yy = UP_CUT;
								t2++;
							}
							//x����
							if (t2 % 2 == 0)//��
							{
								xx = range1;
							}
							else//��
							{
								xx = 0;
							}

						}//���ҽ���			

					}
					//5*5+
					else
					{
						if (k == 5)
						{
							value = 500 / countCenter;//��ֵ�ݼ�
							//�������� ��������
							if (t1 <= 7)
							{
								//����img2ͼƬ��С
								width2 = pt.cols / k;
								height2 = pt.rows*0.19;
								range1 = pt.cols - width2;//���ҷ�Χ
								range2 = pt.rows - height2;//���·�Χ

								step = range1 / (3 * k);

								if (xx > range1 - step&&t1 % 4 == 3)
									background = 0;
								//x����
								if (xx + step < range1)
								{
									if (xx == 0) xx = 1;
									else xx = xx + step;
								}
								else
								{
									xx = 0;
									t1++;
								}
								//y����
								if (t1 % 4 < 2)//�Ϸ�����
								{
									upper = 0;
									yy = UP_CUT + upper;
								}
								else//�·�����
								{
									lower = 0.758*pt.rows;
									yy = UP_CUT + lower;
								}
							}//���½���
							//����			
							else
							{
								width2 = pt.cols / (k * 2);
								height2 = pt.rows*0.19 / 2;
								range1 = pt.cols - width2;//���ҷ�Χ
								range2 = pt.rows - height2;//���·�Χ
								step = range2 / (4 * k);
								if (t1 == 8){ yy = UP_CUT; t1++; }
								//y����
								if (yy + step < range2)
								{

									yy = yy + step;
								}
								else
								{
									yy = UP_CUT;
									t2++;
								}
								//x����
								if (t2 % 2 == 0)//��
								{
									xx = range1;
								}
								else//��
								{
									xx = 0;
								}
								if (t2 == 2)
								{
									t2 = 0; t1 = 0;
									xx = 0;
								}
							}//���ҽ���
						}
						//k>=6
						else
						{
							if(k>=7)value = 10/countCenter;
							else value = 100 / countCenter;
							//������������
							if (t1 <= 5)
							{
								//����img2ͼƬ��С
								width2 = pt.cols / k;
								height2 = pt.rows*0.19;
								range1 = pt.cols - width2;//���ҷ�Χ
								range2 = pt.rows - height2;//���·�Χ
								step = range1 / (3 * k);
								//x����
								if (xx + step < range1)
								{
									if (xx == 0) xx = 1;
									else xx = xx + step;
								}
								else
								{
									xx = 0;
									t1++;
								}
								//y����
								if (t1 % 6 < 3)//�Ϸ�����
								{
									upper = 0;
									yy = UP_CUT + upper;
								}
								else//�·�����
								{
									lower = 0.758*pt.rows;
									yy = UP_CUT + lower;
								}
							}//���½���
							else
							{
								//��������
								if (t2 % 4 == 0 || t2 % 4 == 2)width2 = pt.cols / (2 * k);
								else width2 = pt.cols / k;
								height2 = pt.rows*0.19 / 2;
								range1 = pt.cols - width2;//���ҷ�Χ
								range2 = pt.rows - height2;//���·�Χ
								step = range2 / (4 * k);
								if (t1 == 6){ yy = UP_CUT; t1++; }
								//y����
								if (yy + step < range2)
								{
									yy = yy + step;
								}
								else
								{
									yy = UP_CUT;
									t2++;
								}
								//x����
								if (t2 % 4 <= 1)//��
								{
									xx = range1;
								}
								else//��
								{
									xx = 0;
								}
								if (t2 == 4)
								{
									t2 = 0; t1 = 0;
									xx = 0;
								}
							}//���ҽ���	
						}//k>=6����
					}//k>=5����
				}//ɨ�����ܽ���

				//2.��Ȥ�����Ƶ��м�
				else if (background >= threshold)
				{
					if (background == threshold)
					{ //������һ�ε�����
						tmpx = xx; tmpy = yy;
						xx = 0;
					}
					background = threshold + 100;

					int layer;//�м�λ��ɨ���ٲ�
					double lapping = 1 / 5;//�ص���
					//����ͼƬ��С
					if (k <= 5)layer = 5;
					else
					{
						if (countCenter == 1) layer = 5;
						else layer = k;
					}
					//����img2��С
					height2 = (0.85*pt.rows - 0.15*pt.rows) / ((layer - 1)*(1 - lapping) + 1);
					if (k <= 5)
					{
						width2 = pt.cols / layer;
					}
					else width2 = pt.cols / (layer*1.5);
					step = width2 *0.4;
                    
					qDebug() << "total:" << total << "m2:" << m2;
					qDebug() << "countCenter:" << countCenter;
					qDebug() << "xx:" << xx << "yy:" << yy << "yy+height2:" << yy + height2;
                    
					//x����
					if (xx + step < range1)
					{
						if (xx == 0) xx = 1;
						else xx = xx + step;
					}
					else
					{
						xx = 0;
						t3++;
					}
					//y����
					yy = 0.15*pt.rows + (t3%layer)*(height2*(1 - lapping));

					if (t3 == layer)
					{
						countCenter++;//��¼�м䴦�����
						t3 = 0;
						//if (countCenter % 2 == 1||k!=6 )
						{
							background = 0;//�ص�1
							xx = tmpx;
							yy = tmpy;
							//t1++;
							return;
						}
					}
				}

				img_22 = pt(Rect(xx, yy, width2, height2));
				cv::imwrite("ƴ��.png", img_22);
				img_2 = imread("ƴ��.png");
				cv::imshow("ƴ��2", img_2);
				flag3 = true;
				/*********************��������*************************/
				//�����
				SurfFeatureDetector detector(value);
				//��ȡ��
				SurfDescriptorExtractor extractor;
				//��һ���Լ��ڶ��������֮���������
				float ratio = 0.65f;
				//�Ƿ��ٴ��Ż�F����
				//bool refineF = true;
				//�����ߵ���С����
				//double distance = 3.0;
				//���ŵȼ������ʣ�
				//double confidence = 0.95;

				/*********************************************************step1******************************************************************/
				vector<KeyPoint>keypoints1, keypoints2;
				//a���surf����
				detector.detect(img_1, keypoints1);
				detector.detect(img_2, keypoints2);
				//����ƥ�����
				tt++;
				qDebug() << tt;
				qDebug() << "background" << background;
				//ʶ��Ϊ����
				if (keypoints2.empty())
				{
					qDebug() << "no keypoints in img2";
					background++;
					flag3 = false;
					return;
				}
				//b����SURF������
				Mat descriptors1, descriptors2;
				extractor.compute(img_1, keypoints1, descriptors1);
				extractor.compute(img_2, keypoints2, descriptors2);
				/*********************************************************step2********************************************************************/
				///*
				//a����ƥ����
				BruteForceMatcher<L2<float>>matcher;

				//b����ͼ1->ͼ2��ͼ2->ͼ1 ��k����ڣ�k=2��
				vector<vector<DMatch>>matches1;
				vector<vector<DMatch>>matches2;
				//����knnMatch

				matcher.knnMatch(descriptors1, descriptors2, matches1, 2);
				matcher.knnMatch(descriptors2, descriptors1, matches2, 2);
				//qDebug() << "matches1:" << matches1.size() << "   matches2:" << matches2.size();
				/******************************************************step3 ���ʲ���**************************************************************/
				///*
				int removed1 = 0;
				for (int i = 0; i < matches1.size(); i++)
				{
					if (matches1[i].size() > 1)
					{
						if (matches1[i][0].distance / matches1[i][1].distance > ratio)
						{
							matches1.erase(matches1.begin() + i);
							i--;
							removed1++;
						}
					}
					else
					{
						matches1.erase(matches1.begin() + i);
						i--;
						removed1++;
					}
				}
                
				int removed2 = 0;
				for (int i = 0; i < matches2.size(); i++)
				{
					if (matches2[i].size() > 1)
					{
						if (matches2[i][0].distance / matches2[i][1].distance > ratio)
						{
							matches2.erase(matches2.begin() + i);
							i--;
							removed2++;
						}
					}
					else
					{
						matches1.erase(matches1.begin() + i);
						i--;
						removed2++;
					}
				}
				//qDebug() << "removed_1:" << removed_1 << "		removed_2:" << removed_2;
				/****************************************************step4 �Գ��Բ���************************************************************/
				vector<DMatch>symMatches;
				int leftx = 0, lefty = 0, rightx = 0, righty = 0;
				//������ƥ��
				for (auto &leftMatchRef : matches1)
				{
					if (leftMatchRef.size() < 2)
						continue;
					//������ƥ��
					for (auto &rightMatchRef : matches2)
					{
						if (rightMatchRef.size() < 2)
							continue;
						//�Գ��Բ���
						if ((leftMatchRef[0].queryIdx == rightMatchRef[0].trainIdx) &&
							(leftMatchRef[0].trainIdx == rightMatchRef[0].queryIdx))
						{
							symMatches.push_back(cv::DMatch(leftMatchRef[0].queryIdx, leftMatchRef[0].trainIdx,
								leftMatchRef[0].distance));
							break;
						}
						//if (symMatches.size() > 0)break;
					}
				}

				vector<DMatch> matches;
				matches = symMatches;
				//qDebug() << "matches:" << matches.size();
				//��ƥ���
				if (matches.size() == 0)
				{
					//��ֵ����ʶ��Ϊ����
					if (value < 50) background++;
					qDebug() << "matches.size() == 0";

					flag3 = false;

					offset = 0.15* pt.cols;
					//��֤ÿ��ƴͼֻ����һ��
					if (t4 % 3 == 0 && k != 2)
					{
						int dst1, dst2;
						if (xx + int(0.5*width2)<pt.cols)
							dst1 = (xx + int(0.5*width2));
						else if (xx + int(0.5*width2) >= pt.cols)dst1 = pt.cols - 1;

						if (yy + int(0.5*height2) < pt.rows)dst2 = yy + int(0.5*height2);
						else if (yy + int(0.5*height2) >= pt.rows) dst2 = pt.rows - 1;

						if (background <= threshold)
						{
							//����
							if ((t1 <= 7 && k <= 5) || (t1 <= 5 && k >= 6))
							{
								//�� ������
								if (yy > UP_CUT + upper - 1 && yy < UP_CUT + lower - 1)
								{
									//������
									comMoveToScale((1 - 1 / (pt.rows-UP_CUT)), ((double)(dst1)+argM.box.width) / pt.cols);
									comHitDown();
									comMoveToScale((1 - (offset + 1) / (pt.rows - UP_CUT)), ((double)(dst1)+argM.box.width) / pt.cols);
									comHitUp();
								}
								//�� ������
								else if (yy > UP_CUT + lower - 1)
								{
									//������
									comMoveToScale((1 - (pt.rows + argM.box.height-UP_CUT) / (pt.rows - UP_CUT)), ((double)(dst1)+argM.box.width) / pt.cols);
									comHitDown();
									comMoveToScale((1 - (pt.rows + argM.box.height - UP_CUT - offset) / (pt.rows - UP_CUT)), ((double)(dst1)+argM.box.width) / pt.cols);
									comHitUp();
								}
							}
							//����
							else
							{
								if (k <= 5)
								{
									if (t2 % 2 == 0)//������
									{
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(0.98*pt.cols) + argM.box.width) / pt.cols);
										comHitDown();
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(0.98*pt.cols) - offset + argM.box.width) / pt.cols);
										comHitUp();
									}
									else if (t2 % 2 == 1)//������
									{
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(5) + argM.box.width) / pt.cols);
										comHitDown();
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(5 + offset) + argM.box.width) / pt.cols);
										comHitUp();
									}
								}
								else if (k >= 6)
								{
									if (t2 % 4 <= 1)//������
									{
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(0.98*pt.cols) + argM.box.width) / pt.cols);
										comHitDown();
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(0.98*pt.cols) - offset + argM.box.width) / pt.cols);
										comHitUp();
									}
									else if (t2 % 4 >1)//������
									{
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(5) + argM.box.width) / pt.cols);
										comHitDown();
										comMoveToScale((1 - (double)(dst2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)(5 + offset) + argM.box.width) / pt.cols);
										comHitUp();
									}
								}
							}
						}
					}
					t4++;
					return;
				}

				/*********************��������*************************/
				double offsetx1 = 0.1*pt.cols;		//ԭͼx������pt��offset
				double offsety1 = 0.235*pt.rows;	//ԭͼy������pt��offset
				double offsetx2 = xx;				//Сƴͼ��x������pt��offset
				double offsety2 = yy;				//Сƴͼ��y������pt��offset

				int index;//ƥ����
				index = tt%matches.size();

				//��ͼ
				vector<DMatch> selectMatch;
				selectMatch.push_back(cv::DMatch(matches[index].queryIdx, matches[index].trainIdx,
					matches[index].distance));
				Mat imgMatch;
				cv::drawMatches(img_1, keypoints1, img_2, keypoints2, selectMatch, imgMatch);
				cv::imshow("3", imgMatch);

				double dstx1 = offsetx1 + keypoints1[matches[index].queryIdx].pt.x;
				double dsty1 = offsety1 + keypoints1[matches[index].queryIdx].pt.y;
				double startx2 = offsetx2 + keypoints2[matches[index].trainIdx].pt.x;
				double starty2 = offsety2 + keypoints2[matches[index].trainIdx].pt.y;

				qDebug() << "x1-x2" << abs(dstx1 - startx2) << "y1-y2" << abs(dsty1 - starty2);
				if (abs(dstx1 - startx2) < 1 && abs(dsty1 - starty2) < 1)
				{
					flag3 = false;
					return;
				}
				//Ӳ��bug
				double deform = 5;//���ʵ��α���
				double hypotenuse = sqrt((dsty1 - starty2)*(dsty1 - starty2) + (dstx1 - startx2)*(dstx1 - startx2));//ƴ��ƥ��㵽ԭͼƥ����б��
				double sin = (dsty1 - starty2) / hypotenuse;
				double cos = (dstx1 - startx2) / hypotenuse;
				startx2 = offsetx2 + keypoints2[matches[index].trainIdx].pt.x - deform*cos;
				starty2 = offsety2 + keypoints2[matches[index].trainIdx].pt.y - deform*sin;

				//if ((tt % 3 == 1&&background<0)||(tt%2==1&&background>0)||countCenter>1)
				if (k >= 6)
				{
					if (t1 % 6 == 0 || t1 % 6 == 3)
					{
						if (tt % 2 == 0)
						{
							comMoveToScale((1 - ((double)starty2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)startx2 + argM.box.width) / pt.cols);

							comHitDown();
							comMoveToScale((1 - ((double)dsty1 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)dstx1 + argM.box.width) / pt.cols);
							comHitUp();
						}
					}
					else if (t1 % 6 == 1 || t1 % 6 == 4)
					{
						if (tt % 1 == 0)
						{
							comMoveToScale((1 - ((double)starty2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)startx2 + argM.box.width) / pt.cols);

							comHitDown();
							comMoveToScale((1 - ((double)dsty1 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)dstx1 + argM.box.width) / pt.cols);
							comHitUp();
						}
					}
					else if (t1 % 6 == 2 || t1 % 6 == 5 || tt>200 || countCenter>1)
					{
						if (tt % 1 == 0)
						{
							comMoveToScale((1 - ((double)starty2 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)startx2 + argM.box.width) / pt.cols);

							comHitDown();
							comMoveToScale((1 - ((double)dsty1 + argM.box.height - UP_CUT) / (pt.rows - UP_CUT)), ((double)dstx1 + argM.box.width) / pt.cols);
							comHitUp();
						}
					}
				}
				else
				{
					if ((k == 5 && ((tt % 3 == 0 && (t1 % 8 == 0 || t1 % 8 == 2)) || ((tt % 3 == 0) && (t1 % 8 == 1 || t1 % 8 == 3)) || (tt % 1 == 0 && t1 % 8 >= 4))) || k < 5 && tt % 2 == 0 || tt>200 || countCenter > 1)
					{
						comMoveToScale((1 - ((double)starty2 - UP_CUT) / (pt.rows - UP_CUT)), ((double)startx2) / pt.cols);
						comHitDown();
						comMoveToScale((1 - ((double)dsty1 - UP_CUT) / (pt.rows - UP_CUT)), ((double)dstx1) / pt.cols);
						comHitUp();
					}
				}
				flag3 = false;
			}
		}//match����
	}//processimg��������
#endif
}


#ifdef VIA_OPENCV
cv::Mat qtCyberDip::QImage2cvMat(QImage image)
{
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}


void mouseCallback(int event, int x, int y, int flags, void*param)
{
	MouseArgs* m_arg = (MouseArgs*)param;
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE: // ����ƶ�ʱ
	{
		if (m_arg->Drawing)
		{
			m_arg->box.width = x - m_arg->box.x;
			m_arg->box.height = y - m_arg->box.y;
		}
	}
	break;
	case CV_EVENT_LBUTTONDOWN:case CV_EVENT_RBUTTONDOWN: // ��/�Ҽ�����
	{
		m_arg->Hit = event == CV_EVENT_RBUTTONDOWN;
		m_arg->Drawing = true;
		m_arg->box = cvRect(x, y, 0, 0);
	}
	break;
	case CV_EVENT_LBUTTONUP:case CV_EVENT_RBUTTONUP: // ��/�Ҽ�����
	{
		m_arg->Hit = false;
		m_arg->Drawing = false;
		if (m_arg->box.width<0)
		{
			m_arg->box.x += m_arg->box.width;
			m_arg->box.width *= -1;
		}
		if (m_arg->box.height<0)
		{
			m_arg->box.y += m_arg->box.height;
			m_arg->box.height *= -1;
		}
	}
	break;
	}
}


void qtCyberDip::closeCV()
{
	initImg = true;
	cv::destroyAllWindows();
	comClickRetButton();
}
#endif

