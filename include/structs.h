#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Song {
    int id;                    // Unique ID from master library
    char title[100];
    char artist[100];
    char duration[10];         // e.g., "5:55"
    char filepath[200];
    struct Song *next;
} Song;

typedef struct Album {
    int id;                    // Unique album ID
    char name[100];
    Song *songsHead;           // References to songs from master library
    struct Album *next;
} Album;

typedef struct Library {
    Album *albumsHead;
} Library;

typedef struct MasterLibrary {
    Song *songsHead;           // All available songs (read-only)
} MasterLibrary;

typedef struct PlaylistSong {
    Song *song;
    struct PlaylistSong *next;
    struct PlaylistSong *prev;
} PlaylistSong;

typedef struct Playlist {
    PlaylistSong *head;
    PlaylistSong *current;
    int isPlaying;
} Playlist;

#endif