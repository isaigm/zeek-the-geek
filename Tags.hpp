#pragma once
struct Tags
{
	static const int OBJECT 	       = 0b1;
	static const int PLAYER 	       = 0b10;
	static const int WALL 		       = 0b100;
	static const int BOMB		       = 0b1000;
	static const int PICKABLE 	       = 0b10000;
	static const int PLANT		       = 0b100000;
	static const int MOVABLE 	       = 0b1000000;
	static const int APPLE		       = 0b10000000;
	static const int CRYSTAL	       = 0b100000000;
	static const int KEY 		       = 0b1000000000;
	static const int DOOR 		       = 0b10000000000;
	static const int REMOVABLE	       = 0b100000000000;
	static const int MUSHROOM	       = 0b1000000000000;
	static const int FLOWER 	   	   = 0b10000000000000;
	static const int CHEST 		   	   = 0b100000000000000;
	static const int POISONED_MUSHROOM = 0b1000000000000000;
	static const int ROTTEN_APPLE      = 0b10000000000000000;
	static const int ATTACKABLE        = 0b100000000000000000;
	static const int MONSTER 		   = 0b1000000000000000000;
	static const int UNKNOW			   = 0b10000000000000000000;

};