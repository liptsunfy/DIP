﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenfile_clicked();

    void on_btnReconst_clicked();

    void on_btnTripleD_clicked();

    void on_btnQualityUwp_clicked();

    void on_btnClear_clicked();

    void on_btnQuickUwp_clicked();

    void on_actionAbout_triggered();

    void on_actionOpenfile_triggered();

    void on_actionQuickUpw_triggered();

    void on_actionQualityUpw_triggered();

    void on_actionReconstruction_triggered();

    void on_actionReset_2_triggered();

    void on_actionDisplay_triggered();

    void on_btnReconstUwp_clicked();

    void on_actionReset_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
