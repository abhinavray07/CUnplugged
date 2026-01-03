#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cli.h"
#include "../include/library.h"
#include "../include/song.h"
#include "../include/playlist.h"

void showHomeScreen() {
    printf("\n\n========================================\n");
    printf("              C-Unplugged               \n");
    printf("========================================\n\n");
}

void showMainMenu() {
    printf("\n========== Main Menu ==========\n");
    printf("1. List all songs\n");
    printf("2. List all albums\n");
    printf("3. Create album\n");
    printf("4. Delete album\n");
    printf("5. View album songs\n");
    printf("6. Add song to album\n");
    printf("7. Delete song from album\n");
    printf("8. Playlist options\n");
    printf("9. Show command log\n");
    printf("10. Exit\n");
    printf("================================\n");
    printf("Enter your choice: ");
}

void showPlaylistMenu() {
    printf("\n===== Playlist Menu =====\n");
    printf("1. Show playlist\n");
    printf("2. Add album to playlist\n");
    printf("3. Remove song from playlist\n");
    printf("4. Clear entire playlist\n");
    printf("5. Play\n");
    printf("6. Pause\n");
    printf("7. Next song\n");
    printf("8. Previous song\n");
    printf("9. Back to main menu\n");
    printf("=========================\n");
    printf("Enter your choice: ");
}

void logCommand(const char *command) {
    FILE *fp = fopen("data/log.txt", "a");
    if (fp == NULL) {
        perror("Error opening log file");
        return;
    }
    fprintf(fp, "%s\n", command);
    fclose(fp);
}

void showLog() {
    FILE *fp = fopen("data/log.txt", "r");
    if (fp == NULL) {
        printf("No logs yet.\n");
        return;
    }

    char line[256];
    printf("\n--- Command Log ---\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    printf("-------------------\n");
    fclose(fp);
}

void removeSongFromPlaylistMenu() {
    if (!playlist.head) {
        printf("\nPlaylist is empty.\n");
        return;
    }
    
    showPlaylist(&playlist);
    
    printf("\nEnter song number to remove (0 to cancel): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 0) return;
    
    removeSongFromPlaylist(&playlist, choice);
}

void handlePlaylistMenu() {
    int choice;
    
    while (1) {
        showPlaylistMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        char logMsg[100];
        sprintf(logMsg, "Playlist Menu - Choice: %d", choice);
        logCommand(logMsg);
        
        switch (choice) {
            case 1:
                showPlaylist(&playlist);
                break;
            case 2:
                addAlbumToPlaylistMenu();
                break;
            case 3:
                removeSongFromPlaylistMenu();
                break;
            case 4:
                clearPlaylist(&playlist);
                break;
            case 5:
                play(&playlist);
                break;
            case 6:
                pause(&playlist);
                break;
            case 7:
                nextSong(&playlist);
                break;
            case 8:
                previousSong(&playlist);
                break;
            case 9:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void handleMainMenu() {
    int choice;
    
    while (1) {
        showMainMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        char logMsg[100];
        sprintf(logMsg, "Main Menu - Choice: %d", choice);
        logCommand(logMsg);
        
        switch (choice) {
            case 1:
                listAllSongs();
                break;
            case 2:
                listAlbums();
                break;
            case 3:
                createAlbumMenu();
                break;
            case 4:
                deleteAlbumMenu();
                break;
            case 5:
                viewAlbumMenu();
                break;
            case 6:
                addSongToAlbumMenu();
                break;
            case 7:
                deleteSongFromAlbumMenu();
                break;
            case 8:
                handlePlaylistMenu();
                break;
            case 9:
                showLog();
                break;
            case 10:
                printf("Exiting C-Unplugged. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}