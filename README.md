# The Guns

The Guns is my earliest C++ project, built using only SFML for window management and sprite rendering. It stands as a "time capsule" of my foundational game development journey. 

To maintain absolute transparency and showcase my raw problem-solving roots, **the source code remains exactly as it was originally written.** 

### 🛠️ Architecture & Authenticity
* **Organic Monolithic Growth:** The entire game is contained within a single file. The first half handles complex item initialization, while the second half contains the core game logic and legacy code blocks retained during development. check main.cpp
* **100% Hand-Coded Logic:** This project was developed entirely from scratch using vanilla C++. No AI generation tools, copied algorithms, or reverse-engineered code were used. 
* **Evolution of Style:** Variable naming conventions vary throughout the file, directly reflecting the experimental, trial-and-error learning process of a self-taught developer.
* **Legacy Version Control:** Before adopting standard Git practices, my version control consisted of manually saving distinct iterations into separate local folders. This repository represents the final milestone.

### 🕹️ Core Features & Systems

* **engine/collision physics:** a 2d collision calculating algorithm. The map is a 2d matrix, each number representing an "atom". Each frame a hitbox moves: the game state passes two parameters of respective velocities and two parameters of width and height. If abs(vX) > abs(vY), both are divided by x and vice versa. In this example the loop runs x times and checks if the hitbox can be moved 1 by x and y/x by y. If moving the hitbox causes it to overlap a solid atom, the velocity by the respective coordinate is set to 0.

* **game states:** the main loop has an if statement. if game_state == GAME, it calculates physics. if game_state == ARMORY, it displays the opened menu and lets you pick weapons and equipment.

* **hitscan & raycasting:** Basically the same, but for one frame for 1x1 hitbox. The speed is set the way for its rotation to match gun rotation and for the ray to travel a set max distance. It also checks for any entities in the way, dealing damage to the first one it encounters. Ray is drawn by scaling a colored pixel by the distance in pixels.

* **projectiles:** same, except it is not affected by gravity (in case of entities it adds GRAVITY to y speed), has a hitbox, and deals splash damage upon collision with anything. Splash damage is calculated by distance to the nearest atom of any entity close enough, same with knockback speed and knockback angle.

* **animations:** a class that consists of multiple sprites and has methods to be animated.

* **multiplayer** upon button click a player is prompted to either become a host or a client, in case of the latter to type in the host's IP. You can duel on local networks.


Might not be all the features listed, but those are the main I can remember after a few years of not coding them) That goes for the descendants as well. Enjoy!
