# Space War

## Game Description

In Space War, two players battle small, maneuvrable spaceships in an enclosed 2D rectangular space fitting entirely on the screen. The spaceships are controlled via four keys: two (up/down) control acceleration along the main axis of the ship; two more (left/right) control the orientation of the ship. The edges of the screen bounce back the ships without damage.

The players can shoot projectile of several types, which disappear after a certain time if they hit nothing. Both spaceships start off with the same amount of hit points (HP), every projectile collision takes some away. When a spaceship reaches 0 HP, the game is over; if the other player has >0 HP at this point, he's awarded a point.

The spaceships and bullets move according to a 2D approximation of Newtonian physics; the player input modify the acceleration, and the velocity is calculated at each timestep from the acceleration; the position in turn is calculated from the velocities. For the purposes of collision detection, spaceships and projectiles are considered perfect circles.

At the center of the playing field there is an optional planet and an optional center of gravity attracting the ships and the bullets. The planet and the gravity can be chosen independently before the game starts, and exist for the entire duration.

The game includes an AI opponent which decides on each update loop what to do. It should operate the spaceship via the same interface the human player has at his disposal: acceleration increase/decrease, turn left/right, shoot any of the weapons if the cooldown allows it.

## Implementation

The implementation consist of a setup work, which needs to be done preferrably by the entire team, before any of the other work can proceed. The rest of the work is divided in four tracks. Tracks A and B should be one programmer each; tracks C and D should be done by third programmer, as track D can only be started when some part of the work on track A is complete.

### Setup

This part needs to be done before separate work can be done on the subsequent parts!

Implement the classes representing the spaceships and the projectiles.
Implement user input that modifies directly the positions of the spaceships.
Implement debug visualization drawing the spaceships and projectiles as circles with the appropriate collision radii.
Implement a way to restart the game.

### Track A: Basic Gameplay

Implement the update loop that calculates forces (gravity and acceleration), velocities and positions. Change the user input to affect acceleration and angle, not directly positions.

Implement the collision detection between spaceships and the planet, in the main update loop. Use static circle vs. circle collision for the new positions of the objects. Implement bouncing off the edges of the screen.

Implement projectiles - launched at the nose of spaceship with its current orientation. Add them to the collision calculations. Add HP to ships, take away HP on collisions. (Ignore collisions from own projectiles.)

Implement support for different weapons, defined by the following parameters:

  * projectile speed
  * number of projectiles
  * spread of projectiles in front of ship, e.g. 30 degrees means from -15 to +15 degrees relative to ship orientation
  * projectile lifetime
  * damage done
  * key to launch for player 1
  * key to launch for player 2
  * cooldown (forced wait before using this or any other weapon again)
 
Read these parameters from a text files every time a new game starts, so ballancing the weapons can be done without recompiling and restarting the executable.

### Track B: Presentation

Draw the ships and projectiles as rotated sprites.

Implement sound effects on appropriate events:

  * projectile fired
  * projectile hits spaceship
  * projectile hits planet
  * spaceship hits spaceship
  * spaceship hits planet
  * spaceship hits screen border
  * spaceship fires its engines
  * spaceship reaches HP 0 and dies

Implement graphics effects on above events, where appropriate - explosions, sparks, etc.

Draw trails after projectiles.

Draw the planet, if present, as an animation.

Draw a cosmic background consisting of static images at different positions and orientations. Read the list of these images from a text file. Add a key to reload them, so backgrounds can be designed by editing the file and instantly seeing the result in the running game, without recompilation/restarting.

Add support for animated objects in the background - sparkling stars, spinning planets.


### Track C: Main Menu

Implement a main menu for starting the game. It consists of a static background, two checkboxes ("Planet" and "Gravity") and three buttons: "One player", "Two players", and "Quit".
The "Two players" button should start the game. When the game is over, display "Player 1 wins", "Player 2 wins" or "Both players died"; wait for a mouse click or key press and return to main menu.

Implement proper button behavior buttons in the main menu : changing the appearance when the mouse is over, and when clicked.

Implement the checkboxes and pass their values to the game.


### Track D: AI

Implement an AI that attempts to approach the player.

Teach the AI to orient itself towards the player and shoot the default weapon.

Teach the AI to avoid the planet.

Teach the AI to use other weapons.

Teach the AI to try to stay behind the player.