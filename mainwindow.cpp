#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qfile>
#include <QMessageBox>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color: rgb(250,234,195);");

    ui->title->setStyleSheet(
                            "font: bold 25px;"
                            "color: black;"
                            );

    ui->author->setStyleSheet(
                            "font-size: 10px;"
                            "color: black;"
                            );

    ui->prompt->setStyleSheet(
                            "font: bold 14px;"
                            "color: black;"
                            "background-color: rgb(245,245,220);"
                            "selection-color: white;"
                            "selection-background-color: rgb(120,120,120);");

    ui->addButton->setStyleSheet(
                                "background-color: rgb(245,245,220);"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: gray;"
                                "font: bold 14px;"
                                "min-width: 5em;"
                                "padding: 6px;");

    ui->quitButton->setStyleSheet(
                                    "background-color: rgb(245,245,220);"
                                    "border-style: outset;"
                                    "border-width: 2px;"
                                    "border-radius: 10px;"
                                    "border-color: gray;"
                                    "font: bold 14px;"
                                    "min-width: 5em;"
                                    "padding: 6px;");

    ui->removeButton->setStyleSheet(
                                    "background-color: rgb(245,245,220);"
                                    "border-style: outset;"
                                    "border-width: 2px;"
                                    "border-radius: 10px;"
                                    "border-color: gray;"
                                    "font: bold 14px;"
                                    "min-width: 5em;"
                                    "padding: 6px;");

    ui->removeAllButton->setStyleSheet(
                                    "background-color: rgb(245,245,220);"
                                    "border-style: outset;"
                                    "border-width: 2px;"
                                    "border-radius: 10px;"
                                    "border-color: gray;"
                                    "font: bold 14px;"
                                    "min-width: 5em;"
                                    "padding: 6px;");

    ui->tasks->setStyleSheet(
                            "color: black;"
                            "background-color: rgb(245,245,220);"
                            "selection-color: white;"
                            "selection-background-color: rgb(120,120,120);"
                            "font: bold 14px;"
                            );


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
    bool empty = true;
    for (auto& c: newTask) {
        if (c != " ") {
            empty = false;
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


void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
