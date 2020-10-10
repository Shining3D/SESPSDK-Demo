#include "mesh.h"
#include "ui_mesh.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
mesh::mesh(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesh)
{
    ui->setupUi(this);
	this->setWindowTitle("Mesh");
	//ui->comboBox_2->setDisabled(true);
	QObject::connect(ui->comboBox_type, SIGNAL(QComboBox::currentIndexChanged(int)), this, SLOT(mesh::typeCBox_changed(int)));
}

mesh::~mesh()
{
    delete ui;
}

void mesh::on_pushButton_mesh_clicked()
{
	QString type = ui->comboBox_type->currentText();
	QString resolution = ui->comboBox_2->currentText();

	QJsonObject jsonobject;
	jsonobject.insert("type", type);
	jsonobject.insert("resolution", resolution);
	QJsonDocument document;
	document.setObject(jsonobject);
	QByteArray result = document.toJson();
	emit meshSignal(result);
	this->hide();
}

void mesh::typeCBox_changed(int index)
{
	if (index == 0)
		ui->comboBox_2->setDisabled(true);
	else
		ui->comboBox_2->setDisabled(false);

}
