all:
	g++ -ggdb `pkg-config --cflags --libs opencv` openCV/main.cpp openCV/corner.cpp openCV/putative_match.cpp -o tempExe
	

slidingWindow:
	g++ -ggdb `pkg-config --cflags --libs opencv` openCV/sliding_window.cpp -o sliding_window
	./sliding_window Data/board/1_model.png Data/board/1_image_2.png
