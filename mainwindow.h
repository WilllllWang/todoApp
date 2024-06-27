#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QstandardPaths>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_removeAllButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;

    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\tasks.txt";
};
#endif // MAINWINDOW_H
