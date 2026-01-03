#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/song.h"
#include "../include/load.h"
#include "../include/structs.h"

extern Library library;
extern MasterLibrary masterLibrary;

void listAllSongs() {
    if (!masterLibrary.songsHead) {
        printf("\nNo songs in the master library.\n");
        return;
    }
    
    Song *s = masterLibrary.songsHead;
    int count = 1;
    
    printf("\n========== All Songs ==========\n");
    while (s) {
        printf("%d. %s - %s (%s)\n", count, s->title, s->artist, s->duration);
        s = s->next;
        count++;
    }
    printf("================================\n");
}

void addSongToAlbumMenu() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library. Create an album first.\n");
        return;
    }
    
    // Show albums
    printf("\n========== Albums ==========\n");
    Album *temp = library.albumsHead;
    int count = 1;
    while (temp) {
        printf("%d. %s\n", count, temp->name);
        temp = temp->next;
        count++;
    }
    printf("============================\n");
    
    printf("\nSelect album number (0 to cancel): ");
    int albumChoice;
    if (scanf("%d", &albumChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (albumChoice == 0) return;
    
    // Find selected album
    temp = library.albumsHead;
    count = 1;
    while (temp && count < albumChoice) {
        temp = temp->next;
        count++;
    }
    
    if (!temp) {
        printf("Invalid album number.\n");
        return;
    }
    
    Album *selectedAlbum = temp;
    
    // Show available songs from master library
    listAllSongs();
    
    printf("\nEnter song numbers to add (space-separated, 0 to cancel): ");
    char input[200];
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error reading input.\n");
        return;
    }
    
    char *token = strtok(input, " \n");
    int songsAdded = 0;
    
    while (token != NULL) {
        int songNum = atoi(token);
        
        if (songNum == 0) break;
        
        // Find song by number
        Song *song = masterLibrary.songsHead;
        count = 1;
        while (song && count < songNum) {
            song = song->next;
            count++;
        }
        
        if (!song) {
            printf("Invalid song number: %d\n", songNum);
            token = strtok(NULL, " \n");
            continue;
        }
        
        // Check if song already in album
        Song *check = selectedAlbum->songsHead;
        int duplicate = 0;
        while (check) {
            if (strcmp(check->title, song->title) == 0 && 
                strcmp(check->artist, song->artist) == 0) {
                duplicate = 1;
                break;
            }
            check = check->next;
        }
        
        if (duplicate) {
            printf("Song '%s' is already in the album.\n", song->title);
            token = strtok(NULL, " \n");
            continue;
        }
        
        // Create a copy of the song for this album
        Song *newSongNode = malloc(sizeof(Song));
        *newSongNode = *song;  // Copy song data
        newSongNode->next = NULL;  // Important: set next to NULL
        
        if (!selectedAlbum->songsHead) {
            selectedAlbum->songsHead = newSongNode;
        } else {
            Song *lastSong = selectedAlbum->songsHead;
            while (lastSong->next) {
                lastSong = lastSong->next;
            }
            lastSong->next = newSongNode;
        }
        
        printf("Added: %s - %s\n", song->title, song->artist);
        songsAdded++;
        
        token = strtok(NULL, " \n");
    }
    
    if (songsAdded > 0) {
        printf("\n%d song(s) added to album '%s'.\n", songsAdded, selectedAlbum->name);
        saveLibrary();
    } else {
        printf("No songs were added.\n");
    }
}

void deleteSongFromAlbumMenu() {
    if (!library.albumsHead) {
        printf("\nNo albums in the library.\n");
        return;
    }
    
    // Show albums
    printf("\n========== Albums ==========\n");
    Album *temp = library.albumsHead;
    int count = 1;
    while (temp) {
        printf("%d. %s\n", count, temp->name);
        temp = temp->next;
        count++;
    }
    printf("============================\n");
    
    printf("\nSelect album number (0 to cancel): ");
    int albumChoice;
    if (scanf("%d", &albumChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (albumChoice == 0) return;
    
    // Find selected album
    temp = library.albumsHead;
    count = 1;
    while (temp && count < albumChoice) {
        temp = temp->next;
        count++;
    }
    
    if (!temp) {
        printf("Invalid album number.\n");
        return;
    }
    
    Album *selectedAlbum = temp;
    
    if (!selectedAlbum->songsHead) {
        printf("No songs in album '%s'.\n", selectedAlbum->name);
        return;
    }
    
    // Show songs in the album
    printf("\n===== Songs in '%s' =====\n", selectedAlbum->name);
    Song *s = selectedAlbum->songsHead;
    count = 1;
    while (s) {
        printf("%d. %s - %s\n", count, s->title, s->artist);
        s = s->next;
        count++;
    }
    printf("============================\n");
    
    printf("\nSelect song number to delete (0 to cancel): ");
    int songChoice;
    if (scanf("%d", &songChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (songChoice == 0) return;
    
    // Find and remove song from album
    Song *songToRemove = selectedAlbum->songsHead;
    Song *prev = NULL;
    count = 1;
    
    while (songToRemove && count < songChoice) {
        prev = songToRemove;
        songToRemove = songToRemove->next;
        count++;
    }
    
    if (!songToRemove) {
        printf("Invalid song number.\n");
        return;
    }
    
    char songTitle[100];
    strcpy(songTitle, songToRemove->title);
    
    // Remove from linked list and free (since we now own copies)
    if (prev) {
        prev->next = songToRemove->next;
    } else {
        selectedAlbum->songsHead = songToRemove->next;
    }
    
    free(songToRemove);
    
    printf("Song '%s' removed from album '%s'.\n", songTitle, selectedAlbum->name);
    saveLibrary();
}