---
title: "Where's My Bread"
permalink: /projects/fmb/
layout: single 
classes: wide
excerpt: "A video game created by Simon Lee"
header:
  overlay_image: /images/sky.png
  caption: "Where's my bread"
date: 2022-09-12
sidebar:
  nav: "docs2"
feature_row_left1:
  - url: "https://github.com/Simonlee711/Basic_Game"
    btn_label: "Code"
    btn_class: "btn--primary"
---

# Keywords

Pygame, Game Dev, Physics Engine, AI

# Premise

{% include figure image_path="images/title2.png" alt="this is a placeholder image" caption="Where's my bread official logo" %}

Welcome to the 2D platformer created entirely by me titled **Where's My Bread**. The game has two goals to be awarded the maximum points. One of the objectives of the game is to collect as many pieces of bread that are scattered around Paris, France. The second objective is to reach the end goal flag as fast as you can. In a way if you think of *Super Mario Bros* it is the same concept entirely except the two features of the game have been split up. The backstory of this game is that we have a baker whose bread was stolen and was therefore scattered around the city of Paris. Because there has yet to be a release of version 2.0.0 +, we have not met all the characters that could have possibly been in the realm of *Where's My Bread*. Future releases will come as I find free time for myself.

# Design

The longest part of the game development came from the art itself. Having to hand draw everything from the players, to the enemies, even to the backdrop of Paris and the Eiffel Tower took nearly two and a half weeks of work. I used the [Aesprite](https://www.aseprite.org/) software to draw everything. Truth is the character design is widely inspired and has the same dimensions to Madelin from *Celeste*. 

<p float="center">
  <img src="/images/1.png" width="100" />
  <img src="/assets/splash2/3.png" width="100" /> 
</p>




# Physics Engine

# AI

# Code

This was an independent project done in the summer of 2021. Building a game from scratch was one of the longest projects I have embarked on and have wished to make a higher level game real soon on a better game engine

```audio``` - contains music for the game

```buttons``` - contains the 8 bit art buttons files (.png)

```img``` - contains character, enemy, level, background sprites in 8 bit art

```button.py``` - a file to generate buttons within the pygame environment

```highscore.txt``` - a .txt file that saves the highest score

```level1_data.csv``` - the design of the platformer based on numerical arrays

```level_editor_tut.py``` - the platform level editor

```paris.py``` - the main source code for the game

```scores.txt``` - a .txt file that saves the last played score

{% include feature_row id="feature_row_left1" type="left" %}

# How to play game

make sure you have pygame package installed
```
pip install pygame
```

Then run command

```
python3 paris.py
```
