#include "mainwindow.h"
#include <stdio.h>
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QLayout>
#include <vector>
#include <QtGui>
#include <QFontDatabase>

using namespace std;

volatile bool mc_running = false;
volatile TxtTemp * _log = 0;

MineThread * th = 0;

MineThread::MineThread() {

    this->cmd = "";
}

MineThread::~MineThread() {}

void MineThread::setcmd(const string& cmd) {

    this->cmd = cmd;
}

void MineThread::run() {

    cout << "Launching Minecraft" << endl;

    mc_running = true;

    TxtTemp * log = const_cast<TxtTemp*>(_log);

    log->logcmd(cmd);

    mc_running = false;

    cout << "Closing minecraft" << endl;
}

MainWindow::MainWindow(QApplication * app, QWidget *parent) : QMainWindow(parent) {

    this->setGeometry(300, 50, 750, 580);
    this->setMaximumSize(750, 580);
    this->setWindowTitle("SharkCraft Launcher");

    this->app = app;

    int id = QFontDatabase::addApplicationFont(":/fonts/creerg.ttf");

    //QtGui.QFontDatabase.addApplicationFont("Font/Mf Wedding Bells.ttf");

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    options = new TxtTemp("options.txt", "");

    lbdg_dir = "%APPDATA%\\.LaBiscaDeiGamer\\";
    mc_dir = "%APPDATA%\\.minecraft\\";

    if (options->exists())
        getOptions();

    QFile file(lbdg_dir + "launcher.qss");
    file.open(QFile::ReadOnly);

    stylesheet = file.readAll();

    file.close();

    setAutoFillBackground(true);

    setStyleSheet(stylesheet);

    logo = new QWidget(this);
    logo->setGeometry(20, 430, 130, 130);
    logo->setObjectName("logo");

    title = new QLabel("SharkCraft", this);
    //title->setAutoFillBackground(true);
    title->setGeometry(70, 30, 340, 140);
    title->setObjectName("title");

    border_title = new QLabel("SharkCraft", this);
    border_title->setGeometry(70, 30, 340, 140);
    border_title->setObjectName("border_title");

    title->raise();

    nick = new QLineEdit(this);
    nick->setGeometry(310, 500, 350, 35);

    nick_lab = new QLabel("Nickname:", this);
    nick_lab->setGeometry(150, 500, 150, 50);
    nick_lab->setObjectName("nick_lab");

    QFont creepygirl(family);
    creepygirl.setLetterSpacing(QFont::PercentageSpacing, 110);

    nick_lab->setFont(creepygirl);
    title->setFont(creepygirl);
    border_title->setFont(creepygirl);

    play_button = new QPushButton("PLAY", this);
    play_button->setGeometry(550, 400, 120, 50);

    connect(play_button, SIGNAL (released()), this, SLOT (play()));
    connect(nick, SIGNAL (returnPressed()), this, SLOT (play()));

    log = new TxtTemp("log.txt", lbdg_dir.toStdString());

    access = new TxtTemp("access.logs", lbdg_dir.toStdString());

    account = Account::readLastData(access);

    if (account != 0) {

        nick->setText(account->getUserName().c_str());
    }

    menu = menuBar();

    m_file = menu->addMenu("&File");
    m_settings = menu->addMenu("&Settings");

    f_quit = new QAction("&Quit", this);
    s_options = new QAction("&Options", this);

    m_file->addAction(f_quit);
    m_settings->addAction(s_options);

    connect(f_quit, SIGNAL(triggered()), this, SLOT (quit()));
}

MainWindow::~MainWindow() {

    delete title;
    delete border_title;
    delete logo;
    delete nick;
    delete nick_lab;
    delete play_button;
    delete log;
    delete access;
    delete account;
    delete f_quit;
    delete s_options;
}

Temp * MainWindow::getLog() {

    return log;
}

void MainWindow::getOptions() {

    vector<string> v = options->readLines();

    for (int i = 0; i < (int)v.size(); i++) {

        string * tmp = &v[i];

        if (tmp->find("mcdir", 0) != string::npos) {

            size_t pos0 = tmp->find('\"') + 1;
            size_t pos = tmp->find('\"', pos0);

            mc_dir = tmp->substr(pos0, pos - pos0).c_str();
        }

        else if (tmp->find("lbdgdir", 0) != string::npos) {

            size_t pos0 = tmp->find('\"') + 1;
            size_t pos = tmp->find('\"', pos0);

            lbdg_dir = tmp->substr(pos0, pos - pos0).c_str();
        }
    }
}

void MainWindow::play() {

    if (!mc_running) {

        th = new MineThread();

        connect(th, SIGNAL(finished()), this, SLOT(reshow()));

        _log = log;

        string nickname = nick->text().toStdString();

        if (nickname.empty()) {

            cout << "No nickname inserted" << endl;
            return;
        }

        if (account == 0) {

            account = new Account(nickname, access);
            account->requestUuid();
        }

        if (nickname != account->getUserName()) {

            account->setUserName(nickname);
            account->requestUuid();
        }

        account->writeData();

        string cmd = gencmd(account->getUserName(), account->getUuid(), mc_dir.toStdString(), lbdg_dir.toStdString());

        th->setcmd(cmd);

        log->writeLine(cmd);

        th->start();

        if (!th->isRunning()) {

            cout << "Cannot launch Minecraft: Thread error" << endl;

        } else {

            hide();
        }

    } else {

        cout << "Minecraft is already running" << endl;
    }

}

void MainWindow::quit() {

    //cout << "Exiting" << endl;
    QApplication::quit();
    //app->exit();
}

void MainWindow::reshow() {

    if (th != 0) {

        delete th;
        th = 0;
    }

    show();

    this->raise();
    app->setActiveWindow(this);

    update();
    repaint();
    nick->repaint();
    play_button->repaint();
}

void MainWindow::showEvent( QShowEvent* event ) {

    return QWidget::showEvent( event );
}

void MainWindow::paintEvent(QPaintEvent * )
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }
