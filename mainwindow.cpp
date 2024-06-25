#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qfile>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Read previous saved tasks
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());   // Error checking
    }

    QTextStream openfile(&file);  // Create stream to read file
    while (!openfile.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(openfile.readLine(), ui->tasks);
        ui->tasks->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}


MainWindow::~MainWindow()
{
    delete ui;

    // Save new tasks
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());   // Error checking
    }

    QTextStream savefile(&file);  // Create stream to save file
    for (int i = 0; i < ui->tasks->count(); i++) {
        savefile << ui->tasks->item(i)->text() << "\n"; // Output tasks to file and save
    }

    file.close();
}


void MainWindow::on_addButton_clicked()
{
    QListWidgetItem* item = new QListWidgetItem(ui->prompt->text(), ui->tasks);
    ui->tasks->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable); // Allow tasks to be edited
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
    ui->tasks->clear();     // Delete all tasks
}

