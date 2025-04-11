# Classes and Structs

## 1. Game class
The Game class acts as the central controller of the application. 
It initializes the rendering window based on the specified window type,
handles the main loop, and manages frame timing.

## 2. Window Handler class
Provides a platform-independent interface for managing a game window,
including input polling, buffer swapping, and window state management.

## 3. GLFW Handler class
Manages a window and input using the GLFW library. Handles initialization,
window state, event polling, and buffer swapping via GLFW. Also sets up
static input callbacks to process user interactions.

## 4. GLFW Destroyer struct
This functor ensures proper cleanup of GLFW resources by destroying
the window and terminating the GLFW context when the smart pointer is destroyed.

## 5. Model (To be extended)
Model stores the loaded model's vertices, indices and which shader program to use.

## 6. Renderer (To be extended)
Renderer handles every graphics related data and operations. Renderer loads the models,
make sure that needed shaders are loaded and creates shader programs.
Renderer draws the objects to render.

## 7. Shader
Shader loads the different kind of shaders

## 8. Shader Program
Shader Program creates GPU programs and sets it's uniforms