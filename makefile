all:
	g++ -g -O0 -std=c++11 -I ./include -L ./lib ./src/*.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx -lBulletCollision -lBulletDynamics -lLinearMath
