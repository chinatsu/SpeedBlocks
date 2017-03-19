#ifndef GUI_H
#define GUI_H

#include <TGUI/TGUI.hpp>
#include "packetcompress.h"

class optionSet;
class soundBank;
class gamePlay;
class network;
class PacketCompress;
class textures;

class privChat {
public:
	tgui::ChatBox::Ptr chatBox;
	sf::String name;
};

class playRoom {
public:
	sf::String name;
	short currentPlayers;
	short maxPlayers;
	short id;
	tgui::Button::Ptr button;
	tgui::Label::Ptr label;
};

class UI {
public:
	UI(sf::RenderWindow&, sf::Font&, sf::Font&, optionSet&, soundBank&, gamePlay&, network&, textures&);

	tgui::Font typewriter;
	tgui::Font printFont2;
	sf::Font* printFont;

	tgui::Gui gui;
	tgui::Theme::Ptr themeTG;
	tgui::Theme::Ptr themeBB;

	std::vector<privChat> privChats;
	std::list<playRoom> playRooms;

	optionSet* options;
	soundBank* sounds;
	gamePlay* game;
	network* net;
	textures* textureBase;

	sf::RenderWindow* window;

	bool training;
	bool playonline;
	bool quit;
	bool setkey;
	bool adjPieces;
	bool updPieces;
	bool chatFocused;
	bool inroom;
	bool startgame;
	bool startcount;
	bool disconnect;
	bool away;

	sf::Keyboard::Key* key;
	tgui::Button::Ptr button;

	sf::Texture texture[7];
	sf::Sprite piece[7];

	sf::Uint16 linesSent, garbageCleared, linesBlocked;

	sf::Uint16 clientVersion;


	void setKey(tgui::Button::Ptr butt, sf::Keyboard::Key& skey);
	void putKey(sf::Event& event);
	void changeName(const sf::String& name);
	void initSprites();
	void Options();
	void mainMenu();
	void playOnline();
	void rotPiece(short i);
	void colPiece(short i);
	void otabSelect(std::string tab);
	void vidSlide(short i);
	void fsChecked(bool i);
	void applyVideo();
	void sndChecked(bool i);
	void volSlide(short i, short vol);
	void setBool(bool& var);
	void igtabSelect(const std::string& tab);
	void chattabSelect(const std::string& tab);
	void opTabSelect(const std::string& tab);

	void addRoom(const sf::String& name, short curr, short max, short id);
	void removeRoom(const sf::String& name);
	void removeAllRooms();
	void setRoomPos();
	void roomScrolled(int i);
	void joinRoom(sf::Uint16);

	void Chat();
	void Score();

	void privMsg(const sf::String& name, const sf::String& msg);
	void roomMsg(const sf::String& name, const sf::String& msg);
	void lobbyMsg(const sf::String& name, const sf::String& msg);
	void sendMsg(const sf::String& to, const sf::String& msg);
	void chatFocus(bool i);

	void clearScoreBox();
	void printScoreBox(sf::String&&, sf::Uint16, sf::Uint8, sf::Uint16, sf::Uint8, sf::Uint16, sf::Uint16, sf::Uint16, sf::Uint16);
	void appendLine(sf::String& line, sf::String append, short to);

	void ausY();
	void ausN();

	void quickMsg(const sf::String& msg);

	void changeServerAdd(sf::String);

	bool login(const sf::String&, const sf::String&, sf::Uint8);
	void closeLogin();
};

void SFKeyToString(unsigned int keycode, char *keyStr);
sf::Color pColor(short i);

class obsField;

class GameFieldDrawer: public UI {
public:
	GameFieldDrawer(sf::RenderWindow& rwindow, sf::Font& font1, sf::Font& font2, optionSet& opt, soundBank& soundy, gamePlay& gamey, network& net, textures& tex) : UI(rwindow,font1,font2,opt,soundy,gamey,net,tex) { scaleup=0; compressor.game=game; gamedata=sf::seconds(0); gamedatacount=0; myId=0; }
	
	std::list<obsField> fields;

	sf::Clock sclock;
	obsField* scaleup;

	float currentR;

	PacketCompress compressor;
	sf::Time gamedata;
	sf::Uint8 gamedatacount;
	sf::Uint16 myId;

	void addField(obsField& field);
	void removeField(sf::Uint16 id);
	void updateField(obsField& field);
	void calFieldPos();

	void removeAllFields();
	void leaveRoom();

	void resetOppFields();

	void drawOppField(obsField& field);
	void drawFields();

	void handleEvent(sf::Event event);
	void handlePacket();

	void sendGameData();
	void sendGameOver();
	void sendGameWinner();

	void goAway();
	void unAway();

	sf::String getName(sf::Uint16);
};

#endif