
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->lblVersion->setText("1.0");
    ui->lblDescription->setText("A relational algebra to SQL converter created in C++.");

    QFont font = ui->lblProjectTitle->font();
    font.setBold(true);
    ui->lblProjectTitle->setFont(font);
    ui->lblProjectTitle->setText("RATSQL");

    ui->lblDescription->setText("RATSQL was created for the course Machines and Complexity at the University of Antwerp. Queries in relational algebra form can be entered inside the editor with the help of the special symbol buttons.The query can be translated to SQL using the convert button. Some options can be aplied like the choice to optimize the query or choosing the amount of deviations can take place when requesting a replacement for a selected word.");
    ui->lblDescription->setWordWrap(true);

    QString domainTxt("<html><head/><body><a href=\"http://%1\">Web page</a></body></html>");
    ui->lblDomain->setText(domainTxt.arg("https://github.com/RobbeNooyens/RATSQL"));

    ui->lblCopying->setText(QString("Copyright (c) 2022 %1").arg("Cedric, Maarten, Pablo and Robbe"));

    ui->txtBws->setVisible(false);
}

AboutDialog::~AboutDialog() { delete ui; }
