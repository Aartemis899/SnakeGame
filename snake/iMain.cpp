#include "iGraphics.h"
#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
// parameters

#define Time 30
#define easy 80
#define medium 50
#define hard 50
char* game_mode = "classic";
const int col = 60, row = 50, unit = 10;
int Difficulty = hard, tick_tock = Time;
char score[100] = "SCORE: 0";
char tz_time[100];
int Theme = 3;
char f_score[100];
bool Over = true;








//*****************************************game code***************************************************************************

//*****************************************game code***************************************************************************

//*****************************************game code***************************************************************************












//class names

class gamebox;
class Snake;
class Fruit;
class Maze;


//gamebox class 

class gamebox {
protected:
	double r, g, b;
public:
	gamebox(){}
	gamebox(double R, double G, double B){
		this->set_color(R, G, B);
	}
	void set_color(double red, double green, double blue){
		r = red;
		g = green;
		b = blue;
	}
	double getR() { return r; }
	double getG() { return g; }
	double getB() { return b; }

	template <class T>
	bool Match(T& t){
		if (r == t.getR() && g == t.getG() && b == t.getB()) return true;
		else return false;
	}

};


//snake class 


#define horizontal 1
#define vartical 0

class Snake : public gamebox {

	int initial_length;
	int headX = 1, headY = 0, tailX = 1, tailY = 0;
	queue <pair<int, int>> station, dump;
	pair<int, int> head, tail;
	bool Working;
public:
	int axis = 1;
	Snake(int length, double R, double G, double B){
		initial_length = length;
		this->set_color(R, G, B);
	}
	Snake(){}
	void headXY(int, int);
	void tailXY(int, int);
	pair<int, int>  getHead() { return head; }
	pair<int, int>  getTail() { return tail; }
	void workStatus(bool x) { Working = x; }
	bool working() { return Working; }
	void stopAdd(pair<int, int> x) { station.push(x); }
	void dumpAdd(pair<int, int> x) { dump.push(x); }
	void stationClear();
	void dumpClear();
	void makeSnake(gamebox obj[][100], pair<int, int> ht);
	void move(gamebox game[][100], gamebox background, Fruit& frut, Maze maze);
	void horizontalSnake(int x, int y, gamebox game[][100]);
	friend void gameChange();
};

const int Up[] = { 0, 1, 0, 1 };
const int Right[] = { 1, 0, 1, 0 };
const int Left[] = { -1, 0, -1, 0 };
const int Down[] = { 0, -1, 0, -1 };






//fruit class
class Fruit : public gamebox{
	pair<int, int> fruit;

public:
	Fruit(double R, double G, double B){
		this->set_color(R, G, B);
	}
	Fruit(){}
	int fruitX, fruitY;
	friend class Snake;
	void make_fruit(Snake snake, Maze maze, gamebox game[][100]);
};





//maze class

class Maze : public gamebox{
public:
	Maze(double R, double G, double B){
		this->set_color(R, G, B);
	}
	Maze() {}
	void boxMaze(int x, int y, int height, int width, gamebox game[][100]);
	void filledMaze(int x, int y, int height, int width, gamebox game[][100]);
	void unMaze(pair<int, int> start, pair<int, int> end, gamebox game[][100], gamebox background);

};





//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Game Mode::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

class GameMode {
	char* mode;
public:
	GameMode(char *x = "welcome"){
		mode = x;
	}
	void setMode(char* x){
		mode = x;
	}
	char* getmode(){
		return mode;
	}
};

GameMode mode;
#define Mode mode.getmode()
#define setMode(x) mode.setMode(x)



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Welcome Page::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

class Welcome {
	char*  welcome_text;
	char* bg;
	bool check;
public:

	Welcome(){};
	Welcome(char* img, bool x = true, char* y = "Press Space to Continue"){
		bg = img;
		check = x;
		welcome_text = y;
	}
	void welcomePage(int x, int y);
	friend void  welcomeBlink();

	void set_welcome(bool x, char* y){
		check = x;
		welcome_text = y;
	}

};

void Welcome::welcomePage(int x, int y){
	iShowBMP(0, 0, bg);
	iSetColor(0,0,0);
	iText(x, y, welcome_text, GLUT_BITMAP_TIMES_ROMAN_24);

}
Welcome welcome("images//retro.bmp");


void welcomeBlink(){
	if (welcome.check) welcome.set_welcome(false, "Press Space to Continue");
	else welcome.set_welcome(true, "");
}




//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::game page class::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

class game_page {
	char* bg;

public:
	game_page(char* Bg){
		bg = Bg;
	}
	void game_page::show();

};


void game_page::show(){
	iShowBMP(0, 0, bg);

}





//***************object declarations*****************
gamebox game[100][100];
gamebox background(40, 40, 40);
Fruit fruit(0, 0, 225);
Snake snake(10, 0, 128, 128);
Maze maze(102, 153, 102);
// ********************


//outside functions of the class


//*****************snake functions*****************


void Snake::headXY(int x, int y){
	headX = x;
	headY = y;
}

void Snake::tailXY(int x, int y){
	tailX = x;
	tailY = y;
}


void Snake::makeSnake(gamebox obj[][100], pair<int, int> ht){
	obj[ht.first][ht.second].set_color(this->r, this->g, this->b);
}


void Snake::move(gamebox game[][100], gamebox background, Fruit& frut, Maze maze){
	makeSnake(game, head);
	head = make_pair(head.first + headY, head.second + headX);
	if (head != frut.fruit){
		game[tail.first][tail.second].set_color(background.getR(), background.getG(), background.getB());

		tail = make_pair(tail.first + tailY, tail.second + tailX);
	}
	else {
		if(game_mode=="classic") tick_tock = 7;
		int n;
		sscanf(score, "%*s%d", &n);
		n += 10;
		sprintf(score, "SCORE: %d", n);
		frut.make_fruit(*this, maze, game);

	}
	if (game_mode == "classic" || game_mode == "time"){
		if (head.second > col) head.second = 1;
		else if (head.second < 1) head.second = col;
		if (tail.second > col) tail.second = 1;
		else if (tail.second < 1) tail.second = col;
		if (head.first > row) head.first = 1;
		else  if (head.first < 1) head.first = row;
		if (tail.first > row) tail.first = 1;
		else  if (tail.first < 1) tail.first = row;
	}

	if (game[head.first][head.second].Match(*this) || game[head.first][head.second].Match(maze)){
		if (!Over){
			setMode("gameOver");
			Over = true;
		}
	}

}


void Snake::horizontalSnake(int x, int y, gamebox game[][100]){
	tail = make_pair(y, x);
	head = make_pair(y, x + initial_length - 1);
	for (int i = 1; i <= initial_length; i++){
		makeSnake(game, make_pair(y, x++));
	}

}

void Snake::stationClear(){
	while (!station.empty()) station.pop();
}

void Snake::dumpClear(){
	while (!dump.empty()) dump.pop();
}

//*****************




//*****************fruit class functions *****************



void Fruit::make_fruit(Snake snake, Maze maze, gamebox game[][100]){

	fruitX = rand() % col + 1;
	fruitY = rand() % row + 1;
	while (game[fruitY][fruitX].Match(snake) || game[fruitY][fruitX].Match(maze)){
		fruitX = rand() % col + 1;
		fruitY = rand() % row + 1;
	}
	fruit = make_pair(fruitY, fruitX);
	game[fruitY][fruitX].set_color(this->r, this->g, this->b);
}


//*****************


//*****************Maze class functions*****************

void Maze::boxMaze(int x, int y, int height, int width, gamebox game[][100]) {
	int Y = y, X = x;
	int dx = 1, dy = 0;
	height = y + height - 1;
	width = x + width - 1;
	while (!game[Y][X].Match(*this)){
		game[Y][X].set_color(this->r, this->g, this->b);
		if (X == width && Y == y){
			dy = 1;
			dx = 0;
		}
		else if (Y == height && X == width){
			dy = 0;
			dx = -1;
		}
		else if (X == x && Y == height){
			dy = -1;
			dx = 0;
		}
		Y += dy;
		X += dx;

	}
}

void Maze::filledMaze(int x, int y, int height, int width, gamebox game[][100]){
	height = y + height - 1;
	width = x + width - 1;
	for (int Y = y; Y <= height; Y++){
		for (int X = x; X <= width; X++){
			game[Y][X].set_color(this->getR(), this->getG(), this->getB());
		}
	}
}


void Maze::unMaze(pair<int, int> start, pair<int, int> end, gamebox game[][100], gamebox background){
	if (start.first == end.first){
		for (int x = start.first; x <= end.first; x++){
			for (int y = start.second; y <= end.second; y++){
				game[y][x].set_color(background.getR(), background.getG(), background.getB());
			}
		}
	}
	else {
		for (int y = start.second; y <= end.second; y++){
			for (int x = start.first; x <= end.first; x++){
				game[y][x].set_color(background.getR(), background.getG(), background.getB());

			}
		}
	}
}

//******************



//functions that are not member functions but uses specific objects 

void  gameChange() {

	if (!snake.station.empty() && snake.station.front() == snake.tail){
		snake.tailXY(snake.dump.front().first, snake.dump.front().second);
		snake.station.pop();
		snake.dump.pop();
	}
	snake.move(game, background, fruit, maze);
	snake.workStatus(false);

}


void setBoxColor(){
	for (int i = 1; i <= row; i++){
		for (int j = 1; j <= col; j++){
			game[i][j].set_color(background.getR(), background.getG(), background.getB());
		}
	}
}



void maze1(){
	maze.boxMaze(1, 1, 50, 60, game);
	maze.boxMaze(16, 16, 20, 30, game);
	maze.filledMaze(22, 21, 4, 8, game);
	maze.filledMaze(32, 21, 4, 8, game);
	maze.filledMaze(22, 27, 4, 8, game);
	maze.filledMaze(32, 27, 4, 8, game);
	maze.boxMaze(11, 11, 30, 40, game);
	maze.unMaze(make_pair(29, 11), make_pair(32, 11), game, background);
	maze.unMaze(make_pair(29, 40), make_pair(32, 40), game, background);
	maze.unMaze(make_pair(16, 24), make_pair(16, 27), game, background);
	maze.unMaze(make_pair(45, 24), make_pair(45, 27), game, background);
}

void playGame(){
	iShowBMP(0, 0, "images//background2.bmp");
	int x, y;
	y = 5 - unit;
	for (int i = 1; i <= row; i++){
		x = 5;
		y += unit;
		for (int j = 1; j <= col; j++){
			iSetColor(game[i][j].getR(), game[i][j].getG(), game[i][j].getB());
			iFilledRectangle(x, y, unit, unit);
			x += unit;
		}

	}
	iSetColor(0, 0, 0);
	iLine(5, 5, 5, 505);
	iSetColor(0, 0, 0);
	iLine(5, 5, 605, 5);
	iSetColor(0, 0, 0);
	iLine(5, 505, 605, 505);
	iSetColor(0, 0, 0);
	iLine(605, 5, 605, 505);
	iSetColor(225, 225, 225);
	iText(80, 560, score, GLUT_BITMAP_TIMES_ROMAN_24);
	if (game_mode != "maze" ){
		if (tick_tock < 10) iSetColor(225, 0, 0);
		else iSetColor(225, 225, 225);
		iText(500, 510, tz_time, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
}

void running_time(){
	if (game_mode == "time" || game_mode =="classic"){
		sprintf(tz_time, "TIME: %d", tick_tock);
		if (tick_tock > 0){ tick_tock--; }

		if (!Over && tick_tock <= 0){
			setMode("gameOver");
			Over = true;
		}

	}
}

void game_setup(){
	sprintf(score, "SCORE: 0");
	switch (Theme){
	case 1:
		background.set_color(80, 220, 100);
		if (game_mode == "maze") 	snake.set_color(249, 166, 2);
		else snake.set_color(40, 40, 40);
		fruit.set_color(225, 0, 0);
		maze.set_color(40, 40, 40);
		break;
	case 2:
		background.set_color(249, 166, 2);
		if (game_mode == "maze") 	snake.set_color(80,20,100);
		else snake.set_color(40, 40, 40);
		fruit.set_color(225, 0, 0);
		maze.set_color(40, 40, 40);
		break;
	case 3:
		background.set_color(46, 139, 87);
		if (game_mode == "maze") 	snake.set_color(249, 166, 2);
		else snake.set_color(40, 40, 40);
		fruit.set_color(225, 0, 0);
		maze.set_color(40, 40, 40);
		break;
	case 4:
		background.set_color(40, 40, 40);
		if (game_mode == "maze") 	snake.set_color(249, 166, 2);
		else snake.set_color(0, 128, 128);
		fruit.set_color(225, 0, 0);
		maze.set_color(0, 128, 128);
		break;
	case 5:
		background.set_color(40, 40, 40);
		if (game_mode == "maze") 	snake.set_color(249, 166, 2);
		else snake.set_color(102, 153, 102);
		fruit.set_color(225, 0, 0);
		maze.set_color(102, 153, 102);
		break;
	}
	setBoxColor();
	if (game_mode == "maze")  	 maze1();
	snake.horizontalSnake(2, 4, game);
	snake.headXY(1, 0);
	snake.tailXY(1, 0);
	snake.workStatus(false);
	snake.axis = horizontal;
	snake.dumpClear();
	snake.stationClear();
	fruit.make_fruit(snake, maze, game);
	if(game_mode=="time") tick_tock = Time;
	else tick_tock =7;
	Over = false;
}









//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Game page objects::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


game_page menu("images//menu.bmp");
game_page playMode("images//playMode.bmp");
game_page option("images//option.bmp");
game_page highScore("images//highScore.bmp");
game_page instruction("images//instruction.bmp");
game_page credits("images//credits.bmp");
game_page difficulty("images//difficulty.bmp");
game_page theme("images//theme.bmp");
game_page gameOver("images//gameOver.bmp");


// mouse control functions

void Menu(int mx , int my){
	if (mx >= 15 && mx <= 177 && my <= 575 && my >= 537){
		setMode("playMode");
	}
	else if (mx >= 15 && mx <= 166 && my <= 522 && my >= 486){
		setMode("option");
	}
	else if (mx >= 15 && mx <= 300 && my <= 472 && my >= 440){
		setMode("highScore");
	}
	else if (mx >= 15 && mx <= 340 && my <= 427 && my >= 393){
		setMode("instruction");
	}
	else if (mx >= 15 && mx <= 236 && my <= 376 && my >= 349){
		setMode("credits");
	}
	else if (mx >= 15 && mx <= 153 && my <= 331 && my >= 293){
		exit(0);
	}

}


void Option(int mx, int my){
	if (mx >= 154 && mx <= 310 && my <= 305 && my >= 283){
		setMode("difficulty");
	}
	else if (mx >= 154 && mx <= 244 && my <= 247 && my >= 225){
		setMode("theme");
	}
	else if (mx >= 224 && mx <= 358 && my <= 484 && my >= 383){
		setMode("menu");
	}
}


void diff(int mx, int my){
	if (mx >= 156 && mx <= 232 && my <= 306 && my >= 276){
		Difficulty = easy;
	}
	else if (mx >= 156 && mx <= 256 && my <= 248 && my >= 221){
		Difficulty = medium;
	}
	else if (mx >= 156 && mx <= 236 && my <= 197 && my >= 169){
		Difficulty = hard;
	}
	else if (mx >= 224 && mx <= 358 && my <= 484 && my >= 383){
		setMode("option");
	}
}

void thim(int mx, int my){
	if (mx >= 144 && mx <= 393 && my <= 310 && my >= 292){
		Theme = 1;
	}
	else if (mx >= 144 && mx <= 377 && my <= 269 && my >= 251){
		Theme = 2;
	}
	else if (mx >= 144 && mx <= 336 && my <= 232 && my >= 214){
		Theme = 3;
	}
	else if (mx >= 144 && mx <= 313 && my <= 196 && my >= 178){
		Theme = 4;
	}
	else if (mx >= 144 && mx <= 315 && my <= 161 && my >= 144){
		Theme = 5;
	}
	else if (mx >= 224 && mx <= 358 && my <= 484 && my >= 383){
		setMode("option");
	}
	cout << Theme;
}

void play(int mx, int my){
	if (mx >= 150 && mx <= 288 && my <= 529 && my >= 499){
		game_mode = "classic";
		game_setup();
		setMode("game");
		
	}
	else if (mx >= 150 && mx <= 237 && my <= 457 && my >= 431){
		game_mode = "maze";
		game_setup();
		setMode("game");
		
	}
	else if (mx >= 150 && mx <= 297 && my <= 389 && my >= 365){
		game_mode = "time";
		game_setup();
		setMode("game");
	
	}
	else if (mx >= 350 && mx <= 458 && my <= 561 && my >= 541){
		setMode("menu");
	}
}

void Credits(int mx, int my){
	if (mx >= 154 && mx <= 310 && my <= 305 && my >= 283){
		setMode("menu");
	}
}


void Instruction(int mx, int my){
	if (mx >= 266 && mx <= 328 && my <= 200 && my >= 183){
		setMode("menu");
	}
}


void over(int mx, int my){
	if (mx >= 389 && mx <= 463 && my <= 266 && my >= 247){
		setMode("menu");
	}
	else if (mx >= 127 && mx <= 318 && my <= 266 && my >= 247){
		setMode("playMode");
	}
}







void iDraw()
{
	
	iClear();
	if (Mode == "welcome")  welcome.welcomePage(190,70);

	else if (Mode == "menu") menu.show();

	else if (Mode == "playMode") playMode.show();

	else if (Mode == "option") option.show();
	
	else if (Mode == "highScore") highScore.show();

	else if (Mode == "instruction") instruction.show();

	else if (Mode == "credits") credits.show();

	else if (Mode == "difficulty") difficulty.show();

	else if (Mode == "theme") theme.show();

	else if (Mode == "game") playGame();

	else if (Mode == "gameOver") {
		sscanf(score, "%*s%s", &f_score);
		gameOver.show();
		iSetColor(46, 139, 87);
		iText(297, 371, f_score,GLUT_BITMAP_TIMES_ROMAN_24);
		
	}
}



/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Mode == "menu")  Menu(mx, my);

		else if (Mode == "playMode") play(mx, my);
		
		else if (Mode == "option") Option(mx, my);
		
		else if (Mode == "difficulty") diff(mx, my);

		else if (Mode == "theme") thim(mx, my);

		else if (Mode == "instruction") Instruction(mx, my);
		
		else if (Mode == "gameOver") over(mx, my);
		

	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == ' ') { if (Mode == "welcome") setMode("menu");};
		
	
	
	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{


	if (!snake.working() && key == GLUT_KEY_UP)
	{


		if (snake.axis != vartical){
			snake.workStatus(true);
			snake.headXY(Up[0], Up[1]);
			snake.stopAdd(snake.getHead());
			snake.dumpAdd(make_pair(Up[2], Up[3]));
			snake.axis = vartical;
		}

	}
	if (!snake.working() && key == GLUT_KEY_LEFT)
	{

		if (snake.axis != horizontal){
			snake.workStatus(true);
			snake.headXY(Left[0], Left[1]);
			snake.stopAdd(snake.getHead());
			snake.dumpAdd(make_pair(Left[2], Left[3]));
			snake.axis = horizontal;
		}

	}
	if (!snake.working() && key == GLUT_KEY_DOWN)
	{

		if (snake.axis != vartical){
			snake.workStatus(true);
			snake.headXY(Down[0], Down[1]);
			snake.stopAdd(snake.getHead());
			snake.dumpAdd(make_pair(Down[2], Down[3]));
			snake.axis = vartical;
		}

	}
	if (!snake.working() && key == GLUT_KEY_RIGHT)
	{

		if (snake.axis != horizontal){
			snake.workStatus(true);
			snake.headXY(Right[0], Right[1]);
			snake.stopAdd(snake.getHead());
			snake.dumpAdd(make_pair(Right[2], Right[3]));
			snake.axis = horizontal;
		}
	}

	if (key == GLUT_KEY_HOME)
	{

	}

}





int main()
{
	
	
	srand((unsigned)time(NULL));

	iSetTimer(100,welcomeBlink);
	iSetTimer(Difficulty, gameChange);
	iSetTimer(1000, running_time);
	iInitialize(610, 600, "Project Title");
	
	///updated see the documentations
	iStart();
	return 0;
}

