# Doom-game

This is a game I wrote in C++ designed as a 2D text-based version of the game Doom. A player, represented by an @, can move around and collect items and weapons
while avoiding monsters that chase them and carry out different actions. Levels feature randomly generated mazes and randomly placed enemies and items.
Different monsters feature different movement algorithms or attack patterns. 
Dragons do not move, but have a lot of health.
Snakewomen try to move closer to the player if possible on their turn, but if they can not, they do not move.
Bogeymen move similarly to Snakewomen but at a different range.
Goblins use depth first search to find a path to the player to move in, allowing them to avoid obstacles.

There are also different weapons and items which feature different attack or effects.
Enjoy!
