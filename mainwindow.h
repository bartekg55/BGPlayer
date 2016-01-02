#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include <QString>
#include <QList>
#include <QMediaContent>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sliderProgress_sliderMoved(int position);

    void on_sliderVolume_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_actionOpen_triggered();

    void on_actionAdd_triggered();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_actionOpen_audio_CD_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QList<QString> *string;
};

#endif // MAINWINDOW_H
