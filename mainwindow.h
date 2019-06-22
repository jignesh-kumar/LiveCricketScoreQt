#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <defines.h>
#include "espendata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void getJsonData(QMap<QString, QVariant> var, QMap<QString, QVariant> var2);
    ~MainWindow();
    int matchsCount=0;
    espendata *ESPEN;
    QStringList listMatch_clock, listStart_string, listStart_time, listTeam1_abbrev, listTeam1_name, listTeam1_score, listTeam2_abbrev, listTeam2_name, listTeam2_score, listUrl;

public slots:
    void dataArrives(QMap<QString, QString> data);
    void goForDownloadAndRead(void);

private slots:
    void on_CB_MatchCount_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
