
# COL106 LONG ASSIGNMENT - 2
# SocialNet Simulator
=================================

This README explains how to build and run the `main.cpp` SocialNet simulator in this folder
and documents the supported commands, expected behaviour, known limitations and quick tests.

## Requirements
------------
- A C++11-capable compiler (g++ or clang++). The code only uses language/library features available in
	C++11 and later; compiling with C++11 or newer is recommended.

## Build
-----
Compile `main.cpp` with C++17. Example (macOS / Linux):

```sh
bash run.sh
```

## Run
---
Run the produced `socialnet` binary and enter commands on stdin.



## Supported Commands (Syntax)
---------------------------
All usernames and post contents are treated case-insensitively by the program.

- **ADD_USER \<username\>**
	- Adds a new user (no friends, no posts). Username must be non-empty.
	- Example: ADD_USER alice

- **ADD_FRIEND \<username1\> \<username2\>**
	- Creates a bi-directional friendship. If already friends, the command is ignored with a message.
	- Example: ADD_FRIEND alice bob

- **LIST_FRIENDS \<username\>**
	- Prints an alphabetically sorted list of the user's friends (space separated) followed by a newline.
	- Example: LIST_FRIENDS alice

- **SUGGEST_FRIENDS \<username\> \<N\>**
	- Recommends up to N users who are "friends of a friend" but not already friends.
	- Ranked by number of mutual friends (descending). Ties broken by username (alphabetical).
	- If N is 0 the command prints nothing.
	- Example: SUGGEST_FRIENDS alice 3

- **DEGREES_OF_SEPARATION \<username1\> \<username2\>**
	- Prints the length of the shortest friendship path between two users, or -1 if none exists.
	- Example: DEGREES_OF_SEPARATION alice dave

- **ADD_POST \<username\> \"<post content\>"**
	- Adds a post for the user with the provided content (enclosed in double quotes).
	- Example: ADD_POST alice "Hello world"

- **OUTPUT_POSTS \<username\> \<N\>**
	- Prints the most recent N posts from the user in reverse chronological order (newest first).
	- If N == -1, all posts are printed. If there are fewer than N posts, prints all available.
	- Example: OUTPUT_POSTS alice 5


