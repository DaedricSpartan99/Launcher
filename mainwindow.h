#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPaintEvent>
#include <QMenuBar>
#include "temp.h"
#include <string>
#include <QAction>
#include <QShowEvent>
#include "account.h"
#include <QThread>

string gencmd(const string& nick, const string& uuid, const string& mc_dir, const string& lbdg_dir);


class MineThread : public QThread {

    Q_OBJECT

public:

    MineThread();
    ~MineThread();

    void setcmd(const string& cmd);

protected:

    void run();

private:

    string cmd;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QApplication * app, QWidget *parent = 0);
    ~MainWindow();

    Temp * getLog();

private slots:

    void play();
    void quit();
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent * e);
    void reshow();

private:

    void getOptions();

    QApplication * app;

    QLabel * title;
    QLabel * border_title;
    QWidget * logo;

    QString mc_dir, lbdg_dir, stylesheet;

    QLineEdit * nick;
    QLabel * nick_lab;
    QPushButton * play_button;

    QMenuBar * menu;
    QMenu * m_file, * m_settings;

    QAction * f_quit, * s_options;

    TxtTemp * log, * access, * options;

    Account * account;
};

#endif // MAINWINDOW_H
