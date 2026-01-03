#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/playlist.h"

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

Playlist playlist;  

void initPlaylist(Playlist *pl) {
    pl->head = NULL;
    pl->current = NULL;
    pl->isPlaying = 0;
}

void addAlbumToPlaylist(Playlist *pl, Album *album) {
    if (!album || !album->songsHead) {
        printf("Album '%s' is empty or does not exist.\n", album ? album->name : "NULL");
        return;
    }

    Song *s = album->songsHead;
    while (s) {
        PlaylistSong *node = malloc(sizeof(PlaylistSong));
        node->song = s;
        node->next = NULL;
        node->prev = NULL;

        if (!pl->head) {
            pl->head = node;
            node->next = node->prev = node; 
            pl->current = node;
        } else {
            PlaylistSong *tail = pl->head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = pl->head;
            pl->head->prev = node;
        }
        s = s->next;
    }

    printf("Album '%s' added to playlist.\n", album->name);
}

void stopAudio() {
#ifdef _WIN32
    // Stop modern Windows Media Player (Music.UI.exe) and other common players
    system("taskkill /F /IM Music.UI.exe >nul 2>&1");
    system("taskkill /F /IM wmplayer.exe >nul 2>&1");
    system("taskkill /F /IM vlc.exe >nul 2>&1");
    system("taskkill /F /IM MediaPlayer.exe >nul 2>&1");
    // Small delay to ensure process is killed
    Sleep(200);
#else
    // Stop common Linux/Mac players
    system("killall -9 mpg123 2>/dev/null");
    system("killall -9 vlc 2>/dev/null");
    system("killall -9 afplay 2>/dev/null");
    system("killall -9 cvlc 2>/dev/null");
    // Small delay to ensure process is killed
    usleep(200000);
#endif
}

void playAudioFile(const char *filepath) {
    char command[512];
    char fullPath[512];
    
#ifdef _WIN32
    // Get the full absolute path
    if (filepath[1] != ':') {  // If not already an absolute path
        // Get current working directory
        char cwd[256];
        GetCurrentDirectory(sizeof(cwd), cwd);
        sprintf(fullPath, "%s\\%s", cwd, filepath);
    } else {
        strcpy(fullPath, filepath);
    }
    
    // Windows - use default association with full path
    sprintf(command, "start \"\" \"%s\"", fullPath);
    system(command);
#elif __APPLE__
    // macOS
    sprintf(command, "afplay \"%s\" &", filepath);
    system(command);
#else
    // Linux - try common players
    // Try mpg123 first (lightweight)
    sprintf(command, "mpg123 -q \"%s\" >/dev/null 2>&1 &", filepath);
    int result = system("which mpg123 >/dev/null 2>&1");
    
    if (result != 0) {
        // If mpg123 not found, try vlc
        sprintf(command, "cvlc --play-and-exit \"%s\" >/dev/null 2>&1 &", filepath);
    }
    system(command);
#endif
}

void play(Playlist *pl) {
    if (!pl->current) {
        printf("Playlist is empty.\n");
        return;
    }
    
    // Stop any currently playing audio
    if (pl->isPlaying) {
        stopAudio();
    }
    
    pl->isPlaying = 1;
    printf("Now playing: %s by %s\n", pl->current->song->title, pl->current->song->artist);
    
    // Play the audio file
    playAudioFile(pl->current->song->filepath);
}

void pause(Playlist *pl) {
    if (!pl->current || !pl->isPlaying) {
        printf("Playback is already paused or playlist is empty.\n");
        return;
    }
    
    // Stop the audio
    stopAudio();
    
    pl->isPlaying = 0;
    printf("Paused: %s by %s\n", pl->current->song->title, pl->current->song->artist);
}

void nextSong(Playlist *pl) {
    if (!pl->current) {
        printf("Playlist is empty.\n");
        return;
    }
    
    // Stop current song if playing
    if (pl->isPlaying) {
        stopAudio();
    }
    
    pl->current = pl->current->next;
    
    if (pl->isPlaying) {
        printf("Now playing: %s by %s\n", pl->current->song->title, pl->current->song->artist);
        playAudioFile(pl->current->song->filepath);
    } else {
        printf("Next song: %s by %s\n", pl->current->song->title, pl->current->song->artist);
    }
}

void previousSong(Playlist *pl) {
    if (!pl->current) {
        printf("Playlist is empty.\n");
        return;
    }
    
    // Stop current song if playing
    if (pl->isPlaying) {
        stopAudio();
    }
    
    pl->current = pl->current->prev;
    
    if (pl->isPlaying) {
        printf("Now playing: %s by %s\n", pl->current->song->title, pl->current->song->artist);
        playAudioFile(pl->current->song->filepath);
    } else {
        printf("Previous song: %s by %s\n", pl->current->song->title, pl->current->song->artist);
    }
}

void showPlaylist(Playlist *pl) {
    if (!pl->head) {
        printf("Playlist is empty.\n");
        return;
    }

    PlaylistSong *temp = pl->head;
    int count = 1;
    printf("\nPlaylist:\n");
    do {
        if (temp == pl->current)
            printf("-> %d. %s by %s\n", count, temp->song->title, temp->song->artist);
        else
            printf("   %d. %s by %s\n", count, temp->song->title, temp->song->artist);
        temp = temp->next;
        count++;
    } while (temp != pl->head);
}

void clearPlaylist(Playlist *pl) {
    if (!pl->head) {
        printf("Playlist is already empty.\n");
        return;
    }

    // Stop any playing audio
    if (pl->isPlaying) {
        stopAudio();
    }

    PlaylistSong *temp = pl->head;
    PlaylistSong *next;
    
    // Break the circular link
    pl->head->prev->next = NULL;
    
    while (temp) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    
    pl->head = NULL;
    pl->current = NULL;
    pl->isPlaying = 0;
    
    printf("Playlist cleared.\n");
}

void removeSongFromPlaylist(Playlist *pl, int songNumber) {
    if (!pl->head) {
        printf("Playlist is empty.\n");
        return;
    }

    PlaylistSong *temp = pl->head;
    int count = 1;
    
    // Find the song at the given position
    do {
        if (count == songNumber) {
            break;
        }
        temp = temp->next;
        count++;
    } while (temp != pl->head);
    
    if (count != songNumber) {
        printf("Invalid song number.\n");
        return;
    }
    
    char songTitle[100];
    sprintf(songTitle, "%s by %s", temp->song->title, temp->song->artist);
    
    // If only one song in playlist
    if (temp->next == temp) {
        // Stop if this song is playing
        if (pl->isPlaying) {
            stopAudio();
        }
        
        free(temp);
        pl->head = NULL;
        pl->current = NULL;
        pl->isPlaying = 0;
        printf("Song '%s' removed from playlist.\n", songTitle);
        printf("Playlist is now empty.\n");
        return;
    }
    
    // Update links
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    
    // If removing the head
    if (temp == pl->head) {
        pl->head = temp->next;
    }
    
    // If removing the current song
    if (temp == pl->current) {
        // Stop if playing
        if (pl->isPlaying) {
            stopAudio();
        }
        
        pl->current = temp->next;
        pl->isPlaying = 0;
        printf("Current song removed. Moved to next song.\n");
    }
    
    free(temp);
    printf("Song '%s' removed from playlist.\n", songTitle);
}