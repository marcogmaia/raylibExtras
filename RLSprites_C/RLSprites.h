/**********************************************************************************************
*
*   raylibExtras * Utilities and Shared Components for Raylib
*
*   RLSprite * Simple Sprite Managment System for Raylib
*
*   LICENSE: MIT
*
*   Copyright (c) 2020 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#ifndef RLSPRITES_H
#define RLSPRITES_H

#include "raylib.h"
#include "raymath.h"

#define DIRECTION_DEFAULT 0
#define DIRECTION_UP 0
#define DIRECTION_LEFT 1
#define DIRECTION_DOWN 2
#define DIRECTION_RIGHT 3

#define MAX_NAME 512

typedef struct SpriteImage
{
	char ImageSource[MAX_NAME];
	size_t FrameCount;
	Rectangle *Frames;
	Texture Sheet;
	int StartFrame;
}SpriteImage;

typedef void(*SpriteFrameCallback)(void*, int);

typedef struct SpriteFrameCallbackFrame
{
	int Frame;
	SpriteFrameCallback Callback;
}SpriteFrameCallbackFrame;

typedef struct DirectionFrameset
{
	int Direction;
	size_t FrameCount;
	int* Frames;
}DirectionFrameset;

typedef struct SpriteAnimation
{
	char Name[MAX_NAME];
	float FramesPerSecond;
	bool Loop;
		
	size_t DirectionFrameCount;
	DirectionFrameset* DirectionFrames;

	size_t FrameCallbackCount;
	SpriteFrameCallbackFrame* FrameCallbaks;
}SpriteAnimation;

SpriteAnimation CloneAnimation(SpriteAnimation* anim);
void ReverseAnimation(SpriteAnimation* anim);

typedef struct Sprite
{
	size_t ImageCount;
	SpriteImage* Images;

    size_t AnimationCount;
	SpriteAnimation* Animations;
}Sprite;

int AddSpriteImage(Sprite* sprite, Texture tx, int xFrameCount, int yFrameCount, const char* name);
int AddSpriteImageFromFile(Sprite* sprite, const char* imageName, int xFrameCount, int yFrameCount);

int AddSpriteFlipFrames(Sprite* sprite, int startFrame, int endFrame, bool flipHorizontal, bool flipVertical);

SpriteAnimation* FindSpriteAnimation(Sprite* sprite, const char* name);

SpriteAnimation* AddSpriteAnimationFrames(Sprite* sprite, const char* name, int direction, int start, int end);

void SetSpriteAnimationLoop(Sprite* sprite, const char* name, bool loop);
void SetSpriteAnimationSpeed(Sprite* sprite, const char* name, float fps);

void AddSpriteAnimationFrameCallback(Sprite* sprite, const char* name, SpriteFrameCallback callback, int frame);

void FreeSprite(Sprite* sprite);

typedef enum
{
	OriginMinium,
	OriginCenter,
	OriginMaximum
}OriginLocations;

typedef struct SpriteInstanceLayer
{
    Sprite* Image;
    Color Tint;
}SpriteInstanceLayer;

typedef struct SpriteInstance
{
	size_t LayerCount;
	SpriteInstanceLayer* Layers;

	Vector2 Postion;
	int Direction;
	float Rotation;
	float Scale;
	float Speed;

	OriginLocations OriginX;
	OriginLocations OriginY;

	Rectangle LastRectangle;

	SpriteAnimation* CurrentAnimation;

	int CurrentFrame;
	int CurrentDirection;
	int CurrentRealFrame;
	double LastFrameTime;
}SpriteInstance;

SpriteInstance* CreateSpriteInstance(Sprite* sprite, Color tint);
int AddSpriteInstancLayer(SpriteInstance* instance, Sprite* sprite, Color tint);

void SetSpriteInstanceAimation(SpriteInstance* instance, const char* name);

void UpdateSpriteInstance(SpriteInstance* instance);
void RenderSpriteInstance(SpriteInstance* instance);
void UpdateRenderSpriteInstance(SpriteInstance* instance);

void FreeSpriteInstance(SpriteInstance* instance);

#endif //RLSPRITES_H

