#include <stdio.h>
#include "cli.h"
#include "../include/load.h"
#include "../include/playlist.h"

int main() {
    // Load master song library (read-only)
    loadMasterSongLibrary();
    
    // Load user's albums
    loadLibrary();
    
    // Initialize playlist
    initPlaylist(&playlist);
    
    // Show welcome screen
    showHomeScreen();
    
    // Start menu-driven interface
    handleMainMenu();
    
    return 0;
}