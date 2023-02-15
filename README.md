# R-Type

The goal of the R-Type project is to aims to recreate an online multiplayer copy of the [R-Type](https://fr.wikipedia.org/wiki/R-Type) (1987) game. We had to implement a multi-threaded server and a graphical client in [SFML](https://www.sfml-dev.org/).

We choosed to use an [ECS architecture](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) for our engine. The R-Type architecture is a classic client-server game architecture. A client connects to the server by using the R-Type UDP protocol. When connected, the client has the choice between creating a lobby or joining an existing lobby. Multiple clients can connect to the server at the same time. Then, a lobby's creator client can launch a new game. The server can run several games at the same time.

Team's Member : Baptiste ALLEX - Johann SAKO - Nicolas MOREAU - Jules CIBIENS - Remy NOULIN - Mohamed Aziz CHERIFF - Yoann EL ASMAR

***

# Table of Contents

- [**R-Type**](#rtype)
- [**Mandatories tasks**](#mandatories-tasks)
- [**Installation**](#installation)
  - [**Linux**](#linux)
  - [**Windows**](#windows)
- [**Launching**](#launching)
- [**Game Usage**](#game-usage)
- [**Projects Documentation**](#projects-documentation)
    - [**Game Engine's UML**](#game-engine-uml)
    - [**Server Protocol**](#server-protocol)
- [**Organisation**](#organisation)
    - [**Git Hub repository**](#git-hub-repository)
    - [**Jira**](#jira)
    - [**Discord server**](#discord-server)

# Mandatories tasks

- [X] Package manager: VCPKG
- [X] Graphical library: SFML
- [X] Building tool: CMake
- [ ] Cross Platform: Windows & Linux

# Installation
> For the installation we've made two different installer script that you can find below.

#### **Linux :**
```
sudo ./install.sh
```
#### **Windows :**
```
./install.bat
```

# Launching
>Due to the multiplayer possibility you must open two terminal to play on our version of the R-Type 

**In a Terminal :**
```
./r-type_server [PORT]
```

**In a seconde Terminal :**
```
./r-type_client
```

# Game Usage

Input           | Direction    
----------------|--------------
Arrow Up        | Top          
Arrow Down      | Down         
Arrow Left      | Left         
Arrow Right     | Right        
Space           | Shoot        
Space (Holding) | Charged Shoot

# Project's Documentation
>To give the opportunity to everyone to understand how our project is working we've write as much precise documentation as we can so that an junior developper can understand our code and how the project is working.

#### **Game Engine's UML :**

![UML](http://image.noelshack.com/fichiers/2023/07/1/1676296070-uml.png)

#### **Server's Protocol :**

# Organisation
>To achieve our goal on this project the organisation was the key of success here so we've try used different tools to stay organize to fullfill our goal.

#### **Git Hub's repository**

#### **Jira**
>scrum master method used.

#### **Discord's server**
