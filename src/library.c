#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/library.h"
#include "../include/load.h"
#include "../include/playlist.h"

Library library = {NULL};

Album* findAlbumById(int id) {
    Album *temp = library.albumsHead;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void createAlbumMenu() {
    char name[100];
    printf("\nEnter album name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    
    // Check if album already exists
    Album *temp = library.albumsHead;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            printf("Album '%s' already exists!\n", name);
            return;
        }
        temp = temp->next;
    }

    Album *newAlbum = malloc(sizeof(Album));
    newAlbum->id = getNextAlbumId();
    strcpy(newAlbum->name, name);
    newAlbum->songsHead = NULL;
    newAlbum->next = library.albumsHead;
    library.albumsHead = newAlbum;

    printf("Album '%s' created successfully.\n", name);
    saveLibrary();
}

void listAlbums() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library.\n");
        return;
    }

    printf("\n========== Albums ==========\n");
    Album *temp = library.albumsHead;
    int count = 1;
    while (temp) {
        printf("%d. %s\n", count, temp->name);
        temp = temp->next;
        count++;
    }
    printf("============================\n");
}

void viewAlbumMenu() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library.\n");
        return;
    }
    
    listAlbums();
    
    printf("\nEnter album number to view (0 to cancel): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 0) return;
    
    Album *temp = library.albumsHead;
    int count = 1;
    while (temp && count < choice) {
        temp = temp->next;
        count++;
    }
    
    if (!temp) {
        printf("Invalid album number.\n");
        return;
    }
    
    printf("\n===== Songs in '%s' =====\n", temp->name);
    Song *s = temp->songsHead;
    if (!s) {
        printf("No songs in this album.\n");
    } else {
        count = 1;
        while (s) {
            printf("%d. %s - %s (%s)\n", count, s->title, s->artist, s->duration);
            s = s->next;
            count++;
        }
    }
    printf("============================\n");
}

void deleteAlbumMenu() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library.\n");
        return;
    }
    
    listAlbums();
    
    printf("\nEnter album number to delete (0 to cancel): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 0) return;
    
    Album *temp = library.albumsHead;
    Album *prev = NULL;
    int count = 1;
    
    while (temp && count < choice) {
        prev = temp;
        temp = temp->next;
        count++;
    }
    
    if (!temp) {
        printf("Invalid album number.\n");
        return;
    }
    
    char albumName[100];
    strcpy(albumName, temp->name);
    
    if (prev) prev->next = temp->next;
    else library.albumsHead = temp->next;
    
    // Free songs in the album since they are copies
    Song *song = temp->songsHead;
    while (song) {
        Song *nextSong = song->next;
        free(song);
        song = nextSong;
    }
    
    free(temp);
    
    printf("Album '%s' deleted successfully.\n", albumName);
    saveLibrary();
}

void addAlbumToPlaylistMenu() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library.\n");
        return;
    }
    
    listAlbums();
    
    printf("\nEnter album number to add to playlist (0 to cancel): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 0) return;
    
    Album *temp = library.albumsHead;
    int count = 1;
    while (temp && count < choice) {
        temp = temp->next;
        count++;
    }
    
    if (!temp) {
        printf("Invalid album number.\n");
        return;
    }
    
    extern Playlist playlist;
    addAlbumToPlaylist(&playlist, temp);
}