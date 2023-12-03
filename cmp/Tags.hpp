#pragma once
struct Tags
{
	static const int OBJECT 	   = 0b1;
	static const int PLAYER 	   = 0b10;
	static const int WALL 		   = 0b100;
	static const int COLLISIONABLE = 0b1000;
	static const int PICKABLE 	   = 0b10000;
	static const int PLANT		   = 0b100000;
	static const int MOVABLE 	   = 0b1000000;
	static const int APPLE		   = 0b10000000;
};