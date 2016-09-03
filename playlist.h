#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>

#include <vector>
#include <string>

enum playmode {

    CURRENT_ONCE,
    CURRENT_LOOP,
    RANDOM,
    LOOP,
    SKIP
};

typedef unsigned int track;

class Playlist {

public:

    Playlist(const track& current = 0, playmode mode = SKIP);
    Playlist(const std::vector<std::string>& list, const track& current = 0, playmode mode = SKIP);
    ~Playlist();

    void addTrack(const std::string& filename);
    void removeTrack(const track& item);
    void clear();
    void setPlaymode(playmode mode);
    void change(const track& item);
    std::string getName(const track& item);
    void play();
    void stop();
    void pause();
    track size();
    bool isPlaying();

private:

    QMediaPlaylist * plist;
    QMediaPlayer * player;
    std::vector<std::string> list;
    track current;
    playmode mode;
    bool playing;
};

#endif // PLAYLIST_H
