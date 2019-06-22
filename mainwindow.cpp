#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"
#include "unistd.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ESPEN = new espendata;
    MyThread *thread = new MyThread;

    connect(thread, SIGNAL(timeToDownload()),this, SLOT(goForDownloadAndRead()));
    connect(ESPEN, SIGNAL(dataArrive(QMap<QString,QString>)), this, SLOT(dataArrives(QMap<QString,QString>)));

    ESPEN->downloadEspenData();
    ESPEN->readJsonFile();
    thread->start();
}

void MainWindow::getJsonData(QMap<QString, QVariant> var, QMap<QString, QVariant> var2)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataArrives(QMap<QString, QString> data)
{
    QString strLive_match, strMatch_clock, strStart_string, strStart_time, strTeam1_abbrev, strTeam1_name, strTeam1_score, strTeam2_abbrev, strTeam2_name, strTeam2_score, strUrl;

    QString strCurrntData = ui->CB_MatchCount->currentText();

    foreach( QString key, data.keys() )
    {
        if(key == "match_clock")
            strMatch_clock = data.value(key).trimmed();
        if(key == "live_match")
            strLive_match = data.value(key);
        if(key == "start_string")
            strStart_string == data.value(key);
        if(key == "start_time")
            strStart_time = data.value(key);
        if(key == "team1_abbrev")
            strTeam1_abbrev = data.value(key);
        if(key == "team1_name")
            strTeam1_name = data.value(key);
        if(key == "team1_score")
            strTeam1_score = data.value(key);
        if(key == "team2_abbrev")
            strTeam2_abbrev = data.value(key);
        if(key == "team2_name")
            strTeam2_name = data.value(key);
        if(key == "team2_score")
            strTeam2_score = data.value(key);
        if(key == "url")
            strUrl = data.value(key);
    }

    if(strLive_match == "Y")
    {
        QString strTeamName = strTeam1_name + " vc "+strTeam2_name;
        bool nFind = true;
        for(int i=0; i<listTeam1_name.count(); i++)
        {
            if(listTeam1_name.at(i).contains(strTeam1_name,Qt::CaseSensitive))
            {
                nFind = false;
                listMatch_clock.replace(i, strMatch_clock);
                listStart_string.replace(i, strStart_string);
                listStart_time.replace(i, strStart_time);
                listTeam1_abbrev.replace(i, strTeam1_abbrev);
                listTeam1_name.replace(i, strTeam1_name);
                listTeam1_score.replace(i, strTeam1_score);
                listTeam2_abbrev.replace(i, strTeam2_abbrev);
                listTeam2_name.replace(i, strTeam2_name);
                listTeam2_score.replace(i, strTeam2_score);
                listUrl.replace(i, strUrl);
                ui->CB_MatchCount->removeItem(i);
                ui->CB_MatchCount->insertItem(i,strTeamName);
                break;
            }
        }

        if(nFind)
        {
            listMatch_clock.insert(matchsCount,strMatch_clock);
            listStart_string.insert(matchsCount, strStart_string);
            listStart_time.insert(matchsCount, strStart_time);
            listTeam1_abbrev.insert(matchsCount, strTeam1_abbrev);
            listTeam1_name.insert(matchsCount, strTeam1_name);
            listTeam1_score.insert(matchsCount, strTeam1_score);
            listTeam2_abbrev.insert(matchsCount, strTeam2_abbrev);
            listTeam2_name.insert(matchsCount, strTeam2_name);
            listTeam2_score.insert(matchsCount, strTeam2_score);
            listUrl.insert(matchsCount, strUrl);
            ui->CB_MatchCount->insertItem(matchsCount,strTeamName);
            matchsCount++;
        }

        if(!strCurrntData.isEmpty())
            ui->CB_MatchCount->setCurrentText(strCurrntData);
    }
}

void MainWindow::goForDownloadAndRead()
{
    ESPEN->downloadEspenData();
    ESPEN->readJsonFile();
        matchsCount=0;
}

void MainWindow::on_CB_MatchCount_currentIndexChanged(int index)
{

    ui->LB_Live_match->setText("Live : No");

    if(listMatch_clock.count() < index)
        return;

    if(!listMatch_clock.at(index).isEmpty())
        ui->LB_Match_Time->setText(listMatch_clock.at(index));
    else if(!listStart_string.at(index).isEmpty())
        ui->LB_Match_Time->setText(listStart_string.at(index));
    else if(!listStart_time.at(index).isEmpty())
        ui->LB_Match_Time->setText(listStart_time.at(index));
    else
    {
        ui->LB_Match_Time->clear();
        ui->LB_Live_match->setText("Live : Yes");
    }

    ui->LB_Team1_name->setText(listTeam1_name.at(index));
    ui->LB_Team2_name->setText(listTeam2_name.at(index));
    ui->LB_Team1_score->setText(listTeam1_score.at(index));
    ui->LB_Team2_score->setText(listTeam2_score.at(index));

}
