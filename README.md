# **R-Type**

The goal of the R-Type project is to aims to recreate an online multiplayer copy of the [R-Type](https://fr.wikipedia.org/wiki/R-Type) (1987) game. We had to implement a multi-threaded server and a graphical client in [SFML](https://www.sfml-dev.org/).

We choosed to use an [ECS architecture](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) for our engine. The R-Type architecture is a classic client-server game architecture. A client connects to the server by using the R-Type UDP protocol. When connected, the client has the choice between creating a lobby or joining an existing lobby. Multiple clients can connect to the server at the same time. Then, a lobby's creator client can launch a new game. The server can run several games at the same time.

Team's Member : Baptiste ALLEX - Johann SAKO - Nicolas MOREAU - Jules CIBIEN - Remy NOULIN - Mohamed Aziz CHERIF - Yoann EL ASMAR

***

# **Table of Contents**

- [**R-Type**](#r-type)
- [**Table of Contents**](#table-of-contents)
- [**Mandatories tasks**](#mandatories-tasks)
- [**Installation**](#installation)
  - [**Linux :**](#linux-)
  - [**Windows :**](#windows-)
- [**Launching**](#launching)
- [**Game Usage**](#game-usage)
- [**Project's Documentation**](#projects-documentation)
    - [**Game Engine's UML :**](#game-engines-uml-)
    - [**Server's Protocol :**](#servers-protocol-)
- [**Organisation**](#organisation)
    - [**Git Hub's repository**](#git-hubs-repository)
    - [**Jira**](#jira)
    - [**Discord's server**](#discords-server)

# **Mandatories tasks**

- [X] You must have a package manager: VCPKG
- [X] You must use an graphical library: SFML
- [X] You must setup an building toolchain: CMake
- [X] Your project must be cross platform: Windows & Linux
- [x] You must use an network library: Boost
- [X] You must document your game engine and your server's protocol

[**Return at the table of contents**](#table-of-contents)

# **Installation**
> For the installation we've made two different installer script that you can find below.

## **Linux :**
**Prerequisite list :**
> You should have theses prerequisites installed on your computer to be able to launch our game.
- Git
- Make
> Here is the command you need to launch to install all the dependencies and build the installer.
```
./install.sh
```
> This should generate a rpm or deb package depending on your distribution.
>
> **Debian based :**
> dpkg -i <package_name>.deb
>
> **RPM based :**
> rpm -i <package_name>.rpm

## **Windows :**
**Prerequisite list :**
> You should have theses prerequisites installed on your computer to be able to launch our game.
- Visual Studio 2022
- Winget (you can get it here: https://github.com/microsoft/winget-cli/releases/download/v1.4.10173/Microsoft.DesktopAppInstaller_8wekyb3d8bbwe.msixbundle)
> Here is the command you need to launch to install all the dependencies and build the installer.
```
./install.bat
```
> This should generate a setup executable.
>
> Execute the setup and follow the instructions.
[**Return at the table of contents**](#table-of-contents)
# **Launching**
>Due to the multiplayer possibility you must open two terminal to play on our version of the R-Type 

**In a Terminal :**
```
./r-type_server [PORT]
```

**In a seconde Terminal :**
```
./r-type_client [IP] [PORT]
```
[**Return at the table of contents**](#table-of-contents)
# **Game Usage**

Input           | Direction    
----------------|--------------
Z               | Top          
S               | Down         
Q               | Left         
D               | Right        
Space           | Shoot        
Space (Holding) | Charged Shoot
[**Return at the table of contents**](#table-of-contents)
# **Project's Documentation**
>To give the opportunity to everyone to understand how our project is working we've write as much precise documentation as we can so that an junior developper can understand our code and how the project is working.

### **Game Engine's UML :**

![UML](http://image.noelshack.com/fichiers/2023/07/1/1676296070-uml.png)

### **Server's Protocol :**
[**Return at the table of contents**](#table-of-contents)
# **Organisation**
>To achieve our goal on this project the organisation was the key of success here so we've try used different tools to stay organize to fullfill our goal.

### **Git Hub's repository**

### **Jira**
>scrum master method used.

### **Discord's server**
[**Return at the table of contents**](#table-of-contents)
