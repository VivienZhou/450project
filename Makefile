all:
	g++ -ggdb `pkg-config --cflags --libs opencv` openCV/main.cpp -o tempExe
	