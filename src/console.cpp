#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);

    echo_ = true;
    connect(ui->lineEdit, SIGNAL(returnPressed()),
            this,         SLOT(returnPressed()));
}

Console::~Console()
{
    delete ui;
}

void Console::setEchoEnable(bool value)
{
    echo_ = value;
}

void Console::write(const QString &msg)
{
    ui->plainTextEdit->appendPlainText(msg);
}

void Console::returnPressed()
{
    if (ui->lineEdit->text().length() == 0)
        return;

    if (echo_)
        write(":: " + ui->lineEdit->text());

    emit command(ui->lineEdit->text());

    ui->lineEdit->clear();
}

