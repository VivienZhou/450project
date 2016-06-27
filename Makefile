all:
	g++ -ggdb `pkg-config --cflags --libs opencv` openCV/main.cpp openCV/corner.cpp openCV/putative_match.cpp -o tempExe
	