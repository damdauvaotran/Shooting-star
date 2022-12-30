build:
	g++ -o Source Source.cpp Bullet.cpp Character.cpp Enemies.cpp Enemy.cpp EnemyBullet.cpp GlobalResource.cpp TextureAPI.cpp Timer.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer