# Planetarium

This is my OpenGL Planetarium Project! 

The aim of the project is to put together and experiment with a scene and a renderer without delving too deep into gameplay programming and such that often come with 3D projects. 
The project is constant work in progress and serves as a platform for experimentation and learning.

## Running the Project

For now, only a visual studio 2019 project is included and the app is tested only on Win 10 PC with NVIDIA GPU and mostly run in debug mode. The plan is to include a build system at some point, but for there's plenty to do even without one. 

The project uses GLFW for most of the OS abstaction, so ports to other platforms should be doable at some point and may even work now with little tinkering. 

The external dependencies are included (and hopefully aknowledged accordingly) and the aim is to have project running without any additional library hunting or such. 

## Features

The project is heavily work in progress. The initial target is to get a nicely Phong-shaded solar system running with some planet variation. The camera operates based on solar centered polar coordinate system.

#### From that point on I'd love to have:
 - Particles, dust clouds
 - More options for camera movement
 - Animated texturing
 - Screen space effects
 - Model loading for rockets, satellites and such. NASA has some sweet free-to-use 3D models that could be added.
 - "Skybox" for space background or even for more experimental enviroments. 
 - General visual improvements.  
 - ect ect... 

## External Dependencies

### GLFW 
GLFW is used for window creation and input. It is licensed under the zlib/libpng license. The project's home page is at: https://www.glfw.org/

### STB
Widely used stb_image is used for loading images. It is public domain and available at https://github.com/nothings/stb.

### GLAD
Glad is used for loading OpenGL. It is licenced under MIT License. 

### GLM
GLM is an OpenGL standard-compliant and widely used math library. It is licenced under the MIT License.

### Dear ImGui
Dear ImGui is used for the graphical user interface. It is licenced under the MIT License. 
