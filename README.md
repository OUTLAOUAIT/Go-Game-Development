# Go-Game-Development

## Objective
The objective of this project is to develop an application that would allow the management of Go games using the C++ language for the code and the Qt library for the interface.
## Game analysis

The game of Go is initiated by the presence of two players using an indefinite number of black and white stones allocated to each respectively to make the game evolve according to imposed rules.

The game table, called the Goban, is a matrix made of 361 (19x19) intersections serving as seats for the stones placed. The main goal is to capture as many opponent stones as possible and to establish a large area on the goban. The game ends with the surrender of a player.

  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/Goban.PNG"/>


## Game rules

### How the game is played ?

Players take turns placing a stone of their color on an unoccupied intersection of the of the goban or they skip their turn.

### Capture of stones

When a player removes the last freedom from an opponent's chain, he captures it by removing the stones from that chain from the goban. In addition, when placing a stone, a player may not build a chain without freedom, unless by this move he captures an opponent's chain.

### Repetition
A player, by placing a stone, must not give the goban a state identical to one to one of those he had already given it.

### Endgame
The game ends when both players pass consecutively. The points are then counted. Each intersection of a player's territory earns him one point, as well as each of his stones still present on the goban.

## Class diagram modeling


  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/class%20diagram.PNG"/>

## Realization

### Mobile App

The emoticon of the Go game on one of our cell phones:

  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/emoticone.PNG"/>


The main menu :

  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/menu.PNG"/>



The rules of the game are laid out in a linear fashion linear and can be consulted thanks to a scroll bar. scroll bar. At the bottom, a icon allowing to go back to the main menu.

  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/rules.PNG"/>

The table of choice of the specificities of the game :

  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/preparation.PNG"/>
The beginning of a game.
  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/Begin.PNG"/>

In the middle of a game :
  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/game.PNG"/>
The capture (box D4) increases the player's score
  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/between.PNG"/>
Message in case of suicide.
  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/suicide.PNG"/>

A message declaring the winner
  <img src="https://github.com/OUTLAOUAIT/Go-Game-Development/blob/main/Images/endgame.PNG"/>


