#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("BG Player /ELO");

    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 328);

    QStringList labels;
    labels << "Playing" << "Title";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    string = new QList<QString>;

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::on_pushButton_clicked()
{
    playlist->previous();
    player->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(player->state() == 2 || player->mediaStatus() == 3)
    {
        player->play();
        ui->pushButton_2->setText("Pause");
    }
    else if(player->state() == 1)
    {
        player->pause();
        ui->pushButton_2->setText("Play");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    playlist->next();
    player->play();
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl fileName = QFileDialog::getOpenFileUrl(this, "Select Song");
    if (!fileName.isEmpty())
    {
        player->setMedia(fileName);
        player->play();
    }
    else
    {

    }
}

void MainWindow::on_actionAdd_triggered()
{
    QList<QMediaContent> content;
    QList<QUrl> listPath = QFileDialog::getOpenFileUrls(this, "Add Songs");

    for(int x = 0; x < listPath.count(); x++)
    {
        content.append(listPath.at(x));
        QFileInfo info(listPath.at(x).toString());
        string->append(info.fileName());
    }

    playlist->addMedia(content);
    ui->tableWidget->setRowCount(playlist->mediaCount());

    for(int a = 0; a < playlist->mediaCount(); a++)
    {
        QTableWidgetItem *item;
        item = new QTableWidgetItem(string->at(a));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(a,1, item);
    }

    player->setPlaylist(playlist);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(column == 1)
    {
        for(int y = 0; y < playlist->mediaCount(); y++)
        {
            if(ui->tableWidget->item(row, column)->text() == string->at(y))
            {
                playlist->setCurrentIndex(y);
                player->play();
                ui->pushButton_2->setText("Pause");
                break;
            }
            else
                continue;
        }
    }
    else
    {

    }

}

void MainWindow::on_actionOpen_audio_CD_triggered()
{
    QUrl cdName = QFileDialog::getOpenFileName(this, "Select Disc");
    if (!cdName.isEmpty())
    {
        player->setMedia(cdName);
        player->play();
    }
    else
    {

    }
}




















