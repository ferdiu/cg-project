
# Computer Graphics Project

**!!!WARN!!!** this project is still under development **!!!WARN!!!**

## Test instructions

### Cloning

```bash
# clone
git clone https://github.com/ferdiu/cg-project.git

# enter project directory
cd cg-project

# initilize submodules
git submodule init

# ...and update them
git submodule update
```

### Build

```bash
# create and enter build directory
mkdir build
cd build

# configure for build
cmake ..

# build project (can take a while)
cmake --build . # or just `make'
```

of course the last command can be called with `-j $(nproc)` to speed up compilation (with both `cmake` and `make`).

### Execute

Move into the build directory and then exceute:

```bash
./cg-project
```

Enjoy.


## Commands

Commands are really simple:

- Click and drag to tilt the board
- Bring the ball from the start (red plane) to the finish (green plane) to win
- ESC: quit game
- F: toggle full screen


## About the Project

This project can be divided into two main modules: the `Engine` and the `Main`.

The `Engine` wants to be a generale purpose engine to abstract the graphical and physics components. It is clearly inspired to the architecture of Unity with some influences by the Godot Engine.

The `Main` is the _application specific_ logic, in this case reproducing the classic arcade game in which you have to get the ball to the end through a labyrinth full of holes without making it fall.

### Engine

The Engine is started with a call to `Engine::Start(int argc, char **argv, void (*setup)(void))` where the third parameter (`setup`) is a user-defined function which will contain the initialization logics of the game.

This method will take care to initialize, in this order:

1. GLUT library;
2. Time (a moule that handles timings such as `deltaTime` and `fixedDeltaTime`);
3. Physics (currently handled by the third-party library [ReacPhysics3D](https://github.com/DanielChappuis/reactphysics3d));
4. the default `Scene`;
5. user-defined `setup`.

Finally the `glutMainLoop()` function is called.

At this point you can think as two main _routines_ running:

- `Engine::update()` which is called at each frame (by `glutDisplayFunc`)
- `Engine::fixedUpdate()` which is called every sixtieth of a second by default (by `glutTimerFunc`).

##### Engine::update

`Engine::update()` is responsible of calling, in this order:

1. a user-defined function;
2. `Camera` clear and updates (update the ViewMatrix);
3. `Scene` update;
4. `Scene` draw.

The `Scene` class has a field `root` which is an instance of `GameObject` which will take care to call through all the hierarchy of objects, in the appropriate order (from deepest child to the root), all the _event functions_:

1. `awake`: one time only on each object (used for early initializations);
2. `start`: one time only on each object (used for regular initializations);
3. `update`: used to execute game object specific logic at each frame;
4. `draw`: which do the actual rendering of the scene.

Each `GameObject` is composed by `Component`s that contain methods with the same name as above. In fact the only role of the `GameObject` classe is to hold `Component`s caontaining the real logic in them. For instance the `Transform` component is a dervide class which handles the postioning and ModelMatrix generation of each `GameObject`.

##### Engine::fixedUpdate

`Engine::fixedUpdate()` is responsible of calling, in this order:

1. `Scene::physicsUpdatePre` which will call an homonymous function on the `GameObject` hierarchy to sync the _physics transforms_ to the _engine transforms_[1];
2. `Physics::update` which will call an homonymous function on the `GameObject` hierarchy;
3. `Scene::physicsUpdatePre` which will call an homonymous function on the `GameObject` hierarchy to sync the _engine transforms_ to the _physics transforms_;
4. `Scene::fixedUpdate` which will call an homonymous function on the `GameObject` hierarchy.

This routine is called every 0.016 seconds (1/60 s).

[1] A translation between the `Transform` defined by the external physic library and the component `Transform` is needed after and before every physic simulation step!

### Graphics

Important classes for rendering are:

- `Camera` which handles the generation of the _ProjectionMatrix_ and _ViewMatrix_;
- `Shader` which handles the loading and compilation of the shaders;
- `Material` which provides a general way to handle `Shader`s inside `GameObject`s;
- `Vertex` (actually a struct, not a class) which holds the vertex informations;
- `GLMatricesStack` and `GLMatrices` which are used to reimplement the legacy _matrix stack_ of OpenGL;
- `Light` that creates the light (currently just one light at a time is supported by the default vertex shader);
- `Renderer` which initializes the VAO for each drawable object;
- `[Primitive]Renderer` which initializes _vertices_ (in VBO), _normals_ (in VBO), _indices_ and _offsets_ used to draw the primitive with a subsequent call to `glMultiDrawElements` (currently are available only `PlaneRenderer`, `CubeRenderer` and `SphereRenderer`);
- `Screen` handles window/screen ratios, resizes, fullscreen etc.

### Main

There is not really much going on here: there are just a few `cpp` files whose goal is to:
- read a `.map` file to build the `Board` (and realted `Material`s and `Shader`s)
- create the `Ball` (and realted `Material`s and `Shader`s)
- handle user input
- start the `Engine`

The only script that may need attention is `DefaultShader` which is the responsible to update the shader's `Uniform`s and `Attribute`s before each frame is drawn. See the section `Engine.Graphics` for more details on this.

## Known BUGS

At the moment no collision is working but I'm actively working on fixing this ASAP.
