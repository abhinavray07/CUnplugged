#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "structs.h"
#include "library.h"

// Playlist initialization
void initPlaylist(Playlist *playlist);

// Playlist operations
void addAlbumToPlaylist(Playlist *playlist, Album *album);
void play(Playlist *playlist);
void pause(Playlist *playlist);
void nextSong(Playlist *playlist);
void previousSong(Playlist *playlist);
void showPlaylist(Playlist *playlist);
void clearPlaylist(Playlist *playlist);
void removeSongFromPlaylist(Playlist *playlist, int songNumber);

// Global playlist (definition in playlist.c)
extern Playlist playlist;

#endif