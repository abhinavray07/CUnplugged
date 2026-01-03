#ifndef LOAD_H
#define LOAD_H

#include "structs.h"

void saveLibrary();
void loadLibrary();
void loadMasterSongLibrary();
Library* getLibrary();
MasterLibrary* getMasterLibrary();
Song* findSongById(int id);

#endif