#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qfile>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    // Read previous saved tasks
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // bind it
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            ui->tasks->addItem(line);
        }

        file.close();
    }
}


MainWindow::~MainWindow()
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // bind it
        QTextStream out(&file);
        for (int i = 0; i < ui->tasks->count(); i++) {
            QListWidgetItem *item = ui->tasks->item(i);
            out << item->text() << '\n';
        }

        file.close();
    }

    ui->tasks->clear();
}


void MainWindow::on_addButton_clicked()
{
    // Check if new task is empty
    QString newTask = ui->prompt->text();
    bool empty = false;
    if (newTask == "") {
        empty = true;
    }
    else {
        for (auto& c: newTask) {
            if (c == " ") {
                empty = true;
            }
        }
    }

    // Add to widget list if not empty
    if (!empty) {
        QListWidgetItem* item = new QListWidgetItem(newTask, ui->tasks);
        ui->tasks->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable); // Allow tasks to be edited
    }
    ui->prompt->clear();                                // Clear prompt
    ui->prompt->setFocus();                             // No need to click on prompt again after typing
}


void MainWindow::on_removeButton_clicked()
{
    QListWidgetItem* item = ui->tasks->takeItem(ui->tasks->currentRow());   // Collect pointer to certain task
    delete item;
}


void MainWindow::on_removeAllButton_clicked()
{
    ui->tasks->clear(); // Delete all tasks
}


void MainWindow::on_quitButton_clicked()
{
    qApp->exit(0);
}

