#pragma once

/* 
	This provides a common language for renderer parts and scene to talk about objects and their details

	I'm not too happy about the clutter, but it'll stay until I can figure out a better way for
	handling all the render data
*/

enum class ObjectPreset { ERROR = 0, Sun, BasicCube, BasicSphere, ColorSphere, SandPlanet, EarthlikePlanet };

enum class MeshPreset { ERROR = 0, Sun, BasicCube, BasicSphere, TexturedCube, TexturedPlanet, Skybox};
enum class MaterialPreset { ERROR = 0, Sun, Sand };
enum class ShaderPreset { ERROR = 0, Sun, SingleColor, VertexColor, PositionColor, VertexUV, Textured, Skybox };
enum class TexturePreset { ERROR = 0, Sun, Sand, Earthlike };
enum class SkyboxPreset { ERROR = 0, DefaultSpace };

enum class UniformBlock { SCENE_MATRICES, SUNLIGHT };