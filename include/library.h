#ifndef LIBRARY_H
#define LIBRARY_H

#include "structs.h"

void createAlbumMenu();
void listAlbums();
void viewAlbumMenu();
void deleteAlbumMenu();
void addAlbumToPlaylistMenu();
Album* findAlbumById(int id);
int getNextAlbumId();

#endif