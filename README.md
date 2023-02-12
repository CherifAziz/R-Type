# R-Type

The goal of the R-Type project is to aims to recreate an online multiplayer copy of the [R-Type](https://fr.wikipedia.org/wiki/R-Type) (1987) game. We had to implement a multi-threaded server and a graphical client in [SFML](https://www.sfml-dev.org/).

We choosed to use an [ECS architecture](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) for our engine. The R-Type architecture is a classic client-server game architecture. A client connects to the server by using the R-Type UDP protocol. When connected, the client has the choice between creating a lobby or joining an existing lobby. Multiple clients can connect to the server at the same time. Then, a lobby's creator client can launch a new game. The server can run several games at the same time.

Team's Member : Baptiste ALLEX - Johann SAKO - Nicolas MOREAU - Jules CIBIENS - Remy NOULIN - Mohamed Aziz CHERIFF - Yoann EL ASMAR

# Installation
> For the installation we've made two different installer script.

**Linux :**
```
```
**Windows :**
```
```

# Launching

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

