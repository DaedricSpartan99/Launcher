#ifndef OPWINDOW_H
#define OPWINDOW_H

#include <QDialog>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include "playlist.h"

namespace options {

    class Directories;
    class Music;
    class Launching;
}

class OpWindow : QDialog {

    Q_OBJECT

public:

    OpWindow(QWidget * parent = 0);
    ~OpWindow();

    //options::Directories * dir;
    //options::Music * mus;
    //options::Launching * launch;

    void addToStack(QWidget * w);

private slots:

    void switchToStack();

private:

    QSplitter * splitter;
    QListWidget * oplist;
    QStackedWidget * stack;
};

class options::Directories : QWidget {

    Q_OBJECT

public:

    Directories(QWidget * parent = 0);
    ~Directories();

    QString lbdgdir();
    QString mcdir();

    bool enabled;

private slots:

    void mod_enable();

private:

    QLineEdit * lbdg_dir_edit;
    QLineEdit * mc_dir_edit;

    QLabel * lbdg_lab;
    QLabel * mc_lab;

    QCheckBox * enable;
};

class options::Music : QWidget {

    Q_OBJECT

public:

    Music(QWidget * parent = 0);
    ~Music();

private:

    Playlist * list;
    // to implement later
};

class options::Launching : QWidget {

    Q_OBJECT

public:

    Launching(QWidget * parent = 0);
    ~Launching();

    QString genCmd(const QString& nick, const QString& uuid);

    bool enabled;

private slots:

    void mod_enable();

private:

    QListWidget * list;

    QCheckBox * enable;
};

#endif // OPWINDOW_H
