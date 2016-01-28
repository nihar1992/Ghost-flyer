################################
# Carnegie Mellon University
# 24-780 Engineering Computation
# Final Project
################################

This is an OpenGL based game called the Ghost flyer.
Aim is to navigate a plane around a 3D terrain and shoot down targets using missiles.
Beware! Once you are in the shooting range of the target they'll try to put you down using their own missiles. Dodge them and destroy the targets to win the game.

This game was developed as a part of the final project of the course 24-780 Engineering Computation by a team of CMU students Nihar Sawant, Prasanna R N, Aishwarya Pawar, Divish Ajmani, Aswin Narashiman and Daniel Shafir.


*********
Features
*********
Multiple plane designs - Fly the plane you like!
Game screens - Beautiful loading, start game menu and ending screens
Music - Background music as well as separate music while firing missiles
Mini-map - At the bottom left corner of the screen that shows locations of all the remaining targets
Motion sensored flight - Possible to fly the plane with your hands but will require the leap motion drivers to do so


***********
Main files
***********
Integrate.cpp - Main function
camera.h, camera_function.cpp - Control the camera movements
collision.h, collision_functions.cpp - Uses 3D spheres to detect collisions between plane missile-target, target missile-plane
plane.{h, cpp} - Reads geometry data from an stl files to draw a 3D plane using OpenGL, same functions are used to draw the missile
target.{h, cpp} - Draws the targets and target missiles
terrain.{h, cpp} - Draws terrain

*****************
Playing the game
*****************
Compile and run the the Integrate.cpp file to run the game
Use arrow keys to navigate through the plane selection menu
Use arrow keys to fly the plane and spacebar to shoot missiles