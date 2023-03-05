# Game Usage

This documentation explains the ECS and how to use it to implement new part in the game.

## 1. What's an ECS ?

ECS alias ***Entity Component System*** is a software architectural pattern mostly used in video game development for the representation of game world objects. An ECS comprises entities composed from components of data, with systems which operate on entities' components.

ECS follows the principle of composition over inheritance, meaning that every entity is defined not by a type hierarchy, but by the components that are associated with it. Systems act globally over all entities which have the required components.

**Entity**: An entity represents an ```object```. In a game engine context, for example, every coarse game object is represented as an entity. Usually, it only consists of a unique id. Implementations typically use a plain integer for this.

**Component**: A component labels an entity as possessing a particular aspect, and holds the data needed to model that aspect. For example, every game object that can take damage might have a Health component associated with its entity. Implementations typically use ```structs```, ```classes```, or ```associative arrays```.

**System**: A system is a ```process``` which acts on all entities with the desired components. For example, a physics system may query for entities having mass, velocity and position components, and iterate over the results doing physics calculations on the sets of components for each entity.

But an ECS canno't work without a **Core**, he is the heart of the project. He is checking if the game is still playing, he initiates all the systems and call them to process to the game.

## 2. How to use our ECS

This part explains to developers how to use our ECS in a game.

### 2.1 The Systems
To create a system you will need to create a ```systemName.hpp``` file in the following directory ```ecs/systems/```. The Class **NEEDS** to herit of ```ISystem```.

For a working System you will need at least a ```void init()``` function that will allow you to properly init the system ( for example init the SFML window in the SFMLRenderSystem ). A

You will also need a ```void update(std::shared_ptr<IScene> &scene)```, with the current scene given as argument. So you can do anything with to update or use the Components with your System.

And a ```void destroy()``` function that will destroy everything initiated in your system to clear properly when exited.

You can add everything more you need in your System.

### 2.2 The Components

Create a new component is very easy, you will implement it in the scenes where he is needed and the ***Component Manager*** will simplify this step.
But it's gonna be explained in the Scenes Part.

First, create a ```componentName.hpp``` file in the directory ```ecs/components/content/```.

Set your class inside the ```namespace rtype```.
And after is simple, just set every attributes and functions you need in your Component class.

### 2.3 The Scenes

In the directory ```GameScene/``` you will create a ```sceneName.cpp``` and a ```sceneName.hpp``` for your new Scene.

Don't forget to set your class inside the ```namespace rtype``` and the class **NEED** to herit of ```AScene```.

#### 2.3.1 HPP File
We will first focus on the ```sceneName.hpp``` file.

In public, set the following function :
```void update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &previousScene, bool &soundState);```

The ```update``` function will allow you to update your scene by calling Components function or changing Components value.

```const int64_t &time```: The current clock time
```const size_t &windowWidth```: The current window width
```const size_t &windowHeight```: The current window height
```size_t &scene```: The current scene index, you can change the value to change the current scene in the Game System
```size_t &previousScene```: The previous scene index
```bool &soundState```: The current sound state, you can change the value to stop or play sounds.

After in protected set at least the following functions :

    void initSprite();
    void initSound();
    void initText();
    void initMovement();
    void initAction();
    void initAnimation();

This functions will allow you to initiate every requires Components.

You can now add every things you want or need in your scene.

#### 2.3.2 CPP File

In the Constructor, call every Components init functions.

Now I will explain you how to use the init functions to init the Components in the Component Manager.

We will take our ```initSound()``` function as example :

Create a Component Map first with your component :

    ComponentMap<Sound> sound;

After you can initiates all of your instance's Component ( the following example is only for a Sound instance ) :

    Sound music("assets/music.ogg", true, Sound::SoundStatus::PLAY);

For every instance put it in your Component Map, you have two choices :

- The first one is to create an entity by using ```_entityManager.spawnEntity("entity-name")``` and call her id with ```->getId()```.

        sound.put(music, _entityManager.spawnEntity("music")->getId());
- The second one is by using an existing entity with her index like the following example :
- 
        sound.put(music, _entityManager.getEntity("music")[0]->getId());

When you have done initiating your entities, you can register your Component Map :

    _componentManager.registerComponent<Sound>(sound);