The Guns is my earliest C++ project. Built as a monolithic CodeBlocks project. While scalability prefers breaking it down into smaller functions and classes, this is a demonstrates core logic, game loop implementation, and raw problem-solving skills.

========================================================================

NO AI CODE GENERATION WAS USED IN THESE PROJECTS WHATSOEVER

NO ALGORITHMS WERE COPIED OR REVERSE ENGINEERED

ALL DONE IN BARE C++ EXCEPT DISPLAYING SPRITES AND MANAGING WINDOWS. SFML WAS USED

THE CODE IS EXTREMELY DIRTY. ONE FILE, HALF OF THE CODE IS ITEM INITIALIZATION, AND A HALF OF THE REST IS COMMENTED OUT CODE I SAVED JUST IN CASE, AND THE VARIABLES ALL SHARE DIFFERENT NAMING STILE. I LEFT IT INTENTIONALLY TO SHOW THE CHAOTIC DEVELOPMENT PROCESS AND COMPENSATE FOR THE LACK OF PREVIOUS VERSIONS, SINCE MY VERSION CONTROL WAS LITERALLY SAVING EACH VERSION AS DISTINCT FOLDERS AND GITHUB ACTS AS A STORAGE. CHECK main.cpp

========================================================================

THE GUNS:

- ENGINE/COLLISION PHYSICS: a 2d collision calculating algorithm. The map is a 2d matrix, each number representing an "atom". Each frame a hitbox moves: the game state passes two parameters of respective velocities and two parameters of width and height. If abs(vX) > abs(vY), both are divided by x and vice versa. In this example the loop runs x times and checks if the hitbox can be moved 1 by x and y/x by y. If moving the hitbox causes it to overlap a solid atom, the velocity by the respective coordinate is set to 0.

- GAME STATES: the main loop has an if statement. if game_state == GAME, it calculates physics. if game_state == ARMORY, it displays the opened menu and lets you pick weapons and equipment.

- HITSCAN: Basically the same, but for one frame for 1x1 hitbox. The speed is set the way for its rotation to match gun rotation and for the ray to travel a set max distance. It also checks for any entities in the way, dealing damage to the first one it encounters. Ray is drawn by scaling a colored pixel by the distance in pixels.

- PROJECTILES: same, except it is not affected by gravity (in case of entities it adds GRAVITY to y speed), has a hitbox, and deals splash damage upon collision with anything. Splash damage is calculated by distance to the nearest atom of any entity close enough, same with knockback speed and knockback angle.

- ANIMATIONS: a class that consists of multiple sprites and has methods to be animated.


- MULTIPLAYER: upon button click a player is prompted to either become a host or a client, in case of the latter to type in the host's IP. You can duel on local networks.


Might not be all the features listed, but those are the main I can remember after a few years of not coding them) That goes for the descendants as well. Enjoy!
