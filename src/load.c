#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/load.h"

extern Library library;
MasterLibrary masterLibrary = {NULL};
static int nextAlbumId = 1;

Library* getLibrary() {
    return &library;
}

MasterLibrary* getMasterLibrary() {
    return &masterLibrary;
}

Song* findSongById(int id) {
    Song *temp = masterLibrary.songsHead;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void loadMasterSongLibrary() {
    FILE *fp = fopen("data/songs.txt", "r");
    if (fp == NULL) {
        printf("Error: songs.txt not found!\n");
        return;
    }
    
    char line[500];
    Song *lastSong = NULL;
    
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        
        Song *newSong = malloc(sizeof(Song));
        
        char *token = strtok(line, "|");
        newSong->id = atoi(token);
        
        token = strtok(NULL, "|");
        strcpy(newSong->title, token);
        
        token = strtok(NULL, "|");
        strcpy(newSong->artist, token);
        
        token = strtok(NULL, "|");
        strcpy(newSong->duration, token);
        
        token = strtok(NULL, "|");
        strcpy(newSong->filepath, token);
        
        newSong->next = NULL;
        
        if (!masterLibrary.songsHead) {
            masterLibrary.songsHead = newSong;
        } else {
            lastSong->next = newSong;
        }
        lastSong = newSong;
    }
    
    fclose(fp);
    printf("Master song library loaded successfully.\n");
}

void saveLibrary() {
    FILE *fp = fopen("data/library.txt", "w");
    if (fp == NULL) {
        perror("Error saving library");
        return;
    }

    Album *album = library.albumsHead;
    while (album) {
        fprintf(fp, "ALBUM:%d|%s\n", album->id, album->name);
        Song *song = album->songsHead;
        while (song) {
            fprintf(fp, "SONG:%d|%s|%s|%s|%s\n", 
                    song->id, song->title, song->artist, 
                    song->duration, song->filepath);
            song = song->next;
        }
        album = album->next;
    }
    fclose(fp);
}

void loadLibrary() {
    FILE *fp = fopen("data/library.txt", "r");
    if (fp == NULL) {
        return;
    }

    char line[500];
    Album *currentAlbum = NULL;
    Album *lastAlbum = NULL;
    int maxId = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strncmp(line, "ALBUM:", 6) == 0) {
            char *albumData = line + 6;
            char *idStr = strtok(albumData, "|");
            char *albumName = strtok(NULL, "|");
            
            Album *newAlbum = malloc(sizeof(Album));
            newAlbum->id = atoi(idStr);
            strcpy(newAlbum->name, albumName);
            newAlbum->songsHead = NULL;
            newAlbum->next = NULL;
            
            if (newAlbum->id > maxId) maxId = newAlbum->id;
            
            if (library.albumsHead == NULL) {
                library.albumsHead = newAlbum;
            } else {
                lastAlbum->next = newAlbum;
            }
            lastAlbum = newAlbum;
            currentAlbum = newAlbum;
        }
        else if (strncmp(line, "SONG:", 5) == 0 && currentAlbum != NULL) {
            char *songData = line + 5;
            
            Song *newSong = malloc(sizeof(Song));
            
            char *token = strtok(songData, "|");
            newSong->id = atoi(token);
            
            token = strtok(NULL, "|");
            strcpy(newSong->title, token);
            
            token = strtok(NULL, "|");
            strcpy(newSong->artist, token);
            
            token = strtok(NULL, "|");
            strcpy(newSong->duration, token);
            
            token = strtok(NULL, "|");
            strcpy(newSong->filepath, token);
            
            newSong->next = NULL;
            
            if (currentAlbum->songsHead == NULL) {
                currentAlbum->songsHead = newSong;
            } else {
                Song *temp = currentAlbum->songsHead;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newSong;
            }
        }
    }

    nextAlbumId = maxId + 1;
    fclose(fp);
    printf("Library loaded successfully.\n");
}

int getNextAlbumId() {
    return nextAlbumId++;
}