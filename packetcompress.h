#ifndef PACKETCOMPRESS_H
#define PACKETCOMPRESS_H

#include <SFML/Graphics.hpp>
class obsField;
class gamePlay;

class PacketCompress {
public:
	gamePlay* game;
	obsField* field;

	sf::Uint8 tmp[100];
	sf::Uint8 bitcount=0;
	sf::Uint8 tmpcount=0;

	//Tempstorage for validation
	sf::Uint8 square[22][10];
	short posX, posY;
	sf::Uint8 grid[4][4];
	short nextpiece, npcol, nprot;

	void compress();
	void extract();
	void addBits(sf::Uint8&, sf::Uint8);
	void getBits(sf::Uint8&, sf::Uint8);
	void clear();
	void copy();
	bool validate();
};

#endif