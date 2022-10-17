#include "startscan.h"
#include "ui_startscan.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
startScan::startScan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startScan)
{
    ui->setupUi(this);
	this->setWindowTitle("Start scan");

	connect(ui->checkBox, &QCheckBox::stateChanged, this, &startScan::Signal_HdrStateChanged);
}

startScan::~startScan()
{
    delete ui;
}

void startScan::on_pushButton_clicked()
{
	bool enableHDR = ui->checkBox->isChecked();
	QString alignType = ui->comboBox_alignType->currentText();
	QString subScanType = ui->comboBox_subScanType->currentText();
	QString turntableTimes = ui->lineEdit_turnableTimes->text();
	int turntableSpeeds = ui->comboBox_motorSpeed->currentText().toInt();
	double turntableNum = 0.0;
	if (ui->radioButton_oneRound->isChecked())
	{
		turntableNum = 1.0;
	}
	else if (ui->radioButton_halfRound->isChecked())
	{
		turntableNum = 0.5;
	}

	QJsonObject paramsJsonObject;
	paramsJsonObject.insert("enableHDR", enableHDR);
	paramsJsonObject.insert("alignType", alignType);
	paramsJsonObject.insert("subScanType", subScanType);
	paramsJsonObject.insert("turntableTimes", turntableTimes.toInt());
	paramsJsonObject.insert("turntableSpeeds", turntableSpeeds);
	paramsJsonObject.insert("turntableNum", turntableNum);

	QJsonObject jsonObject;
	jsonObject.insert("action", m_action);
	jsonObject.insert("params", paramsJsonObject); 

	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray result = document.toJson();

	emit startScanSignal(result);
	this->hide();
}



void startScan::setAction(QString action)
{
	m_action = action;
}

void startScan::setSubType(int index)
{
	ui->comboBox_subScanType->setCurrentIndex(index-1);
	ui->comboBox_subScanType->setEnabled(false);
}
void startScan::setEnable_turnableTimes(bool b)
{
	if (!b)
	{
		ui->lineEdit_turnableTimes->clear();
		ui->label_point->hide();
	}
	else
	{
		ui->lineEdit_turnableTimes->setText("8");
		ui->label_point->show();
	}
	ui->lineEdit_turnableTimes->setEnabled(b);
	ui->comboBox_alignType->setEnabled(b);
	ui->comboBox_motorSpeed->setEnabled(b);
	ui->radioButton_halfRound->setEnabled(b);
	ui->radioButton_oneRound->setEnabled(b);
}

