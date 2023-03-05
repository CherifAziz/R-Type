# Level system

Our R-Type uses a configuration file to manage the levels. This configuration file represents severals levels. A level represents enemies and their number of appearances.
The file is called level.txt and is located in the "assets" folder.

***

# Table of Contents

- [**Level system**](#level-system)
- [**How to use it**](#how-to-use-it)
    - [**Create an enemy :**](#create-an-enemy)
    - [**Add more enemies :**](#add-more-enemies)
    - [**Create levels :**](#create-levels)

# How to use it

### **Create an enemy :**

To create an enemy, you need to write the type of enemy and its number of appearances, separated by a comma. Make sure to write correctly the type of the enemy and to respect the syntax (TypeOfEnemy,NumberOfApparances). Here is an example :

> basicEnemy,10

### **Add more enemies :**

To add more enemies, you have to go back to the line and do the same thing with anothers enemies. Here is an exemple of a level :

> basicEnemy,10\
mediumEnemy,8\
flyEnemy,5\
vesselEnemy,3

### **Create levels :**

To add more levels, you need to need to separate each level by an empty line :

> basicEnemy,10\
mediumEnemy,8\
flyEnemy,5\
vesselEnemy,3\
\
basicEnemy,10\
mediumEnemy,8\
flyEnemy,5\
vesselEnemy,3\
\
basicEnemy,10\
mediumEnemy,8\
flyEnemy,5\
vesselEnemy,3

###### [**Return at the table of contents**](#table-of-contents)
