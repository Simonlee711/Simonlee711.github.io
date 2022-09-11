---
title: "Where's My Bread"
permalink: /projects/fmb/
layout: single 
classes: wide
excerpt: "A video game created by Simon Lee"
header:
  overlay_image: /images/projects/sky.png
  caption: "Where's my bread"
date: 2022-09-12
sidebar:
  nav: "docs2"
feature_row_left1:
  - url: "https://github.com/Simonlee711/Basic_Game"
    btn_label: "Code"
    btn_class: "btn--primary"
---
<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 

</p>

# Keywords

Pygame, Game Dev, Physics Engine, Artifical Intellegence

<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 

</p>

# Premise

{% include figure image_path="images/title.png" alt="this is a placeholder image" caption="Where's my bread official logo" %}

Welcome to the 2D platformer created entirely by me titled **Where's My Bread**. The game has two goals to be awarded the maximum points. One of the objectives of the game is to collect as many pieces of bread that are scattered around Paris, France. The second objective is to reach the end goal flag as fast as you can. In a way if you think of *Super Mario Bros* it is the same concept entirely except the two features of the game have been split up. The backstory of this game is that we have a baker whose bread was stolen and was therefore scattered around the city of Paris. Because there has yet to be a release of version 2.0.0 +, we have not met all the characters that could have possibly been in the realm of *Where's My Bread*. Future releases will come as I find free time for myself.

# Design

The longest part of the game development came from the art itself. Having to hand draw everything from the players, to the enemies, even to the backdrop of Paris and the Eiffel Tower took nearly two and a half weeks of work. I used the [Aesprite](https://www.aseprite.org/) software to draw everything. Truth is the character design is widely inspired and has the same dimensions from one of my favorite vide games, Madelin from [*Celeste*](https://store.steampowered.com/app/504230/Celeste/). 

<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" />
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" />  

</p>

# Physics Engine

Creating a video game make you question a lot about what we take for granted. In the context of games, that is all of physics from the amount of time we can jump once we hit the floor, to understanding what exactly is a "floor"? One of the best aspects of creating this game was being able to customize how high a player could jump or how fast gravity brought them to the floor. I will share within the ```player``` class how movement worked in my game.

{% highlight Python linenos %}

def move(self, moving_left, moving_right):
        '''
        tracking movement, sees if movement keys have been activated
        
        :param moving_left - checks to see if moving left key has been activated
        :param moving_right - checks to see if moving right key has been activated
        '''
        # reset movement variables
        screen_scroll = 0
        dx = 0
        dy = 0

        # assign movements variables if moving left and right
        if moving_left:
            dx = -self.speed
            self.flip = True
            self.direction = -1
        if moving_right:
            dx = self.speed
            self.flip = False
            self.direction = 1
        
        #jumping movement
        if self.jump == True and self.in_air == False:
            self.vel_y = -9
            self.jump = False
            self.in_air = True
        
        # apply gravity
        self.vel_y += GRAVITY
        if self.vel_y > 10:
            self.vel_y
        dy += self.vel_y

        #check for collision
        for tile in world.obstacle_list:
            # check collision in the left and right direction
            if tile [1].colliderect(self.rect.x + dx, self.rect.y, self.width, self.height):
                dx = 0
                # if ai has hit wall make it turn around
                if self.char_type == 'enemy2':
                    self.health += 1000
                    self.direction *=-1
                    self.move_counter = 0
            #check for collision in the y direction
            if tile [1].colliderect(self.rect.x, self.rect.y + dy, self.width, self.height):
                # check if below the ground, i.e jumping
                if self.vel_y < 0:
                    self.vel_y = 0
                    dy = tile[1].bottom - self.rect.top
                # check if above the ground, i.e falling
                elif self.vel_y >= 0:
                    self.vel_y = 0
                    self.in_air = False
                    dy = tile[1].top - self.rect.bottom

        # check for collision with water
        if pygame.sprite.spritecollide(self, water_group, False):
            self.health = 0

        # check for collision with exit
        time_complete = False
        if pygame.sprite.spritecollide(self, exit_group, False):
            time_complete = True
        
        # check if fallen off the map
        if self.rect.bottom > SCREEN_HEIGHT:
            self.health = 0

        #check if going off the edges of the screen
        if self.char_type == 'player1':
            if self.rect.left + dx < 0 or self.rect.right + dx > SCREEN_WIDTH:
                dx = 0

        # update rectangle (hitbox's) position
        self.rect.x += dx
        self.rect.y += dy 

        #update scroll based on player position
        if self.char_type == 'player1':
            if (self.rect.right > SCREEN_WIDTH - SCROLL_THRESH and bg_scroll < (world.level_length * TILE_SIZE) - SCREEN_WIDTH)\
				or (self.rect.left < SCROLL_THRESH and bg_scroll > abs(dx)):
                self.rect.x -= dx
                screen_scroll = -dx
        
        return screen_scroll, time_complete

{% endhighlight %}

In the above code segment just in the movement section alone, I had to engineer how movement worked, how gravity worked, the height of jumping, checking collision between immobile objects (floors, walls), checking for collision with water/cars (instant death), how the game would react if I fell off the screen, as well as have a continuous scrolling feature since that looked real since the background is not fixed. 

<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 

</p>

# Enemy Artificial Intellegence


When it came to the AI of the enemies, I installed cool down timers as a way of when to change directions while pacing back and forth. This was to ensure that the enemies never fall off the screen. There were also hidden hit boxes which would trigger the enemy to stop movement and launch an attack. The following Python function displays some the features implemented into the AI that made the game so much fun.

{% highlight Python linenos %}
    def ai(self):
        '''
        computer controlled mafia men
        feat1: move left and move right
        feat2: idle around randomly
        feat3: shoot if within range of vision box
        '''
        # checks if ai should be active 
        if self.alive and player.alive:
            if self.idling == False and random.randint(1, 200) == 1:
                self.idling = True
                self.idling_counter = 500
            #check if ai is near the player
            if self.vision.colliderect(player.rect):
                #stop running and face the player
                self.shoot()
            # pacing back and forth
            else:
                if self.idling == False:
                    if self.direction == 1:
                        ai_moving_right = True
                    if self.direction == -1:
                        ai_moving_right = False
                    ai_moving_left = not ai_moving_right
                    self.move(ai_moving_left, ai_moving_right)
                    self.move_counter += 1
                    # update ai vision as the enemy moves
                    self.vision.center = (self.rect.centerx + 50 * self.direction, self.rect.centery)
                    
                    #pygame.draw.rect(screen, RED, self.vision, 1) # draw vision rectangle

                    if self.move_counter > TILE_SIZE:
                        self.direction *= -1
                        self.move_counter *= -1
                else:
                    self.idling -= 1
                    if self.idling_counter <= 0:
                        self.idling = False
        #scroll
        self.rect.x += screen_scroll
{% endhighlight %}

<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 

</p>

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

<p float="left">
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets//splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 
  <img src="/images/projects/1.png" width="37" />
  <img src="/assets/splash2/3.png" width="80" /> 

</p>

# How to play game

make sure you have pygame package installed
```
pip install pygame==1.9.6
```

Then run command

```
python3 paris.py
```

{% include figure image_path="images/projects/tower.png" alt="this is a placeholder image" caption="Au Revoir" %}
