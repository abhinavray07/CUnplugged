# C-Unplugged 🎵

A feature-rich CLI-based music player built in C with album management, playlist controls, and cross-platform audio playback support.

## Overview

C-Unplugged is a terminal-based music player that allows users to organize songs into albums, create playlists, and control playback—all from the command line. The project demonstrates proficiency in data structures, file I/O, memory management, and cross-platform development.

## Features

### Core Functionality
- **Album Management**: Create, delete, and view albums with custom song collections
- **Master Song Library**: Centralized repository of all available songs
- **Playlist System**: Add albums to a dynamic playlist with seamless navigation
- **Audio Playback**: Play songs through the system's default media player
- **Playback Controls**: Play, pause, next, previous song functionality
- **Persistent Storage**: User libraries and playlists are saved between sessions
- **Command Logging**: Track all user actions for debugging and analytics

### Technical Highlights
- **Circular Doubly-Linked List**: Efficient playlist navigation in both directions
- **Modular Architecture**: Clean separation of concerns across multiple files
- **Cross-Platform Support**: Works on Windows, Linux, and macOS
- **Dynamic Memory Management**: Proper allocation and deallocation to prevent memory leaks
- **File Persistence**: User data saved in text-based format for easy debugging

## Project Structure

```
CUnplugged/
├── data/
│   ├── songs.txt          # Master song library (edit to add your songs)
│   ├── library.txt        # User's albums (auto-generated)
│   └── log.txt            # Command history (auto-generated)
├── include/               # Header files
│   ├── cli.h
│   ├── library.h
│   ├── load.h
│   ├── playlist.h
│   ├── song.h
│   └── structs.h
├── music/                 # Place your MP3 files here
├── src/                   # Source files
│   ├── main.c            # Entry point
│   ├── cli.c             # User interface and menu handling
│   ├── library.c         # Album management operations
│   ├── song.c            # Song operations
│   ├── playlist.c        # Playlist management and playback
│   └── load.c            # Data persistence
├── Makefile
├── .gitignore
└── README.md
```

## Data Structures

### Song
Represents individual songs with metadata:
- ID, title, artist, duration, filepath
- Linked list structure for album organization

### Album
Groups related songs:
- Unique ID and name
- Head pointer to song linked list
- Support for multiple albums

### Playlist
Circular doubly-linked list enabling:
- Seamless forward/backward navigation
- Current song tracking
- Play state management

## Setup & Usage

### Prerequisites
- GCC compiler
- Audio player installed:
  - **Windows**: Default Media Player
  - **Linux**: mpg123 or VLC (`sudo apt-get install mpg123`)
  - **macOS**: afplay (built-in)

### Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/YOUR_USERNAME/C-Unplugged.git
   cd C-Unplugged
   ```

2. **Add your music files**
   - Place MP3 files in the `music/` folder
   - Update `data/songs.txt` with your songs in this format:
     ```
     1|Song Title|Artist Name|00:03:45|music/Song_Title_Artist.mp3
     ```

3. **Compile the program**
   ```bash
   # Using Makefile (recommended):
   make
   
   # Or manually:
   gcc src/main.c src/cli.c src/library.c src/song.c src/playlist.c src/load.c -o CUnplugged
   ```

4. **Run the program**
   ```bash
   ./CUnplugged          # Linux/Mac
   CUnplugged.exe        # Windows
   ```

### Sample Workflow
1. View all available songs from the master library
2. Create albums and add songs to them
3. Build a playlist by adding albums
4. Use playback controls to enjoy your music

## Key Learnings

This project was a significant learning experience that involved:

- **Self-taught concepts**: Learned file persistence, modular programming, and advanced data structures during development
- **Data Structures**: Implemented circular doubly-linked lists for efficient playlist traversal
- **Memory Management**: Practiced dynamic allocation with malloc/free to prevent memory leaks
- **Cross-platform Development**: Handled OS-specific system calls for audio playback
- **File I/O**: Designed text-based storage format for data persistence
- **Modular Design**: Organized code into logical modules with clear interfaces

## Challenges Overcome

1. **Playlist Implementation**: Designing a circular doubly-linked list that supports seamless looping
2. **Audio Playback**: Integrating with different OS-specific media players
3. **Data Persistence**: Creating a robust save/load system that maintains data integrity
4. **Modular Architecture**: Structuring code for maintainability and scalability

## Future Enhancements

- Shuffle and repeat modes
- Search functionality for songs and albums
- Volume control integration
- Support for different audio formats
- GUI implementation using ncurses

## Technologies Used

- **Language**: C
- **Concepts**: Data Structures (Linked Lists), File I/O, Dynamic Memory Allocation
- **Tools**: GCC, Make, Git

## Course Context

Developed as a semester project for **Computer Programming** course at IIIT Hyderabad, demonstrating practical application of:
- Pointers and dynamic memory management
- Structures and linked data structures  
- File operations and persistence
- Modular programming with header files
- Cross-platform system programming

---

**Author**: B.Tech ECE Student @ IIIT Hyderabad  
**Course**: Computer Programming (Semester 1, 2024)  
**Institution**: International Institute of Information Technology, Hyderabad