#include "playlist.h"

Playlist::Playlist(const track& current, playmode mode) {

    plist = new QMediaPlaylist;
    player = new QMediaPlayer;

    player->setPlaylist(plist);

    this->current = current;
    setPlaymode(mode);

    playing = false;
}

Playlist::Playlist(const std::vector<std::string>& list, const track& current, playmode mode) {

    plist = new QMediaPlaylist;
    player = new QMediaPlayer;

    for (track i = 0; i < list.size(); i++) {

        plist->addMedia(QUrl::fromLocalFile( list[i].c_str() ));
        this->list.push_back( list[i] );
    }

    player->setPlaylist(plist);

    this->current = current;
    setPlaymode(mode);

    playing = false;
}

Playlist::~Playlist() {

    delete plist;
    delete player;
}

void Playlist::addTrack(const std::string& filename) {

    this->list.push_back(filename);
    plist->addMedia( QUrl::fromLocalFile( filename.c_str() ));
}

void Playlist::setPlaymode(playmode mode) {

    switch (mode) {

    case CURRENT_LOOP:
        plist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;

    case CURRENT_ONCE:
        plist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        break;

    case LOOP:
        plist->setPlaybackMode(QMediaPlaylist::Loop);
        break;

    case SKIP:
        plist->setPlaybackMode(QMediaPlaylist::Sequential);
        break;

    case RANDOM:
        plist->setPlaybackMode(QMediaPlaylist::Random);
        break;

    default:
        return;
    }

    this->mode = mode;
}

void Playlist::change(const track& item) {

    if (playing) {
        stop();
    }

    plist->setCurrentIndex(item);
    this->current = item;

    if (playing) {
        play();
    }
}

std::string Playlist::getName(const track& item) {

    return list[item];
}

void Playlist::removeTrack(const track& item) {

    plist->removeMedia(item);
    list.erase(list.begin() + item);
}

void Playlist::clear() {

    plist->clear();
    list.clear();
}

void Playlist::play() {

    player->play();
}

void Playlist::stop() {

    player->stop();
}

void Playlist::pause() {

    player->pause();
}

track Playlist::size() {

    return list.size();
}

bool Playlist::isPlaying() {

    return playing;
}
