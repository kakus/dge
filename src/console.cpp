#include "console.h"
#include "ui_console.h"
#include <QTextBlock>

Console::Console(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);

    echo_ = true;
    historyIt_ = commandHistory_.begin();

    connect(ui->lineEdit, SIGNAL(returnPressed()),
            this,         SLOT(returnPressed()));

    ui->lineEdit->setFocus();
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
    commandHistory_.push_front(ui->lineEdit->text());
    historyIt_ = commandHistory_.begin();

    ui->lineEdit->clear();
}

void Console::keyPressEvent(QKeyEvent *evt)
{
    if (evt->key() == Qt::Key_Up)
    {
        if (historyIt_ != commandHistory_.end())
        {
            ui->lineEdit->clear();
            ui->lineEdit->setText(*historyIt_);
            ++historyIt_;
        }
    }
    else if (evt->key() == Qt::Key_Down)
    {
        if (historyIt_ != commandHistory_.begin()) --historyIt_;
        ui->lineEdit->clear();
        ui->lineEdit->setText(*historyIt_);
    }
}
