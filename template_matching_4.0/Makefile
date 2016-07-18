all:
	g++ -ggdb `pkg-config --cflags --libs opencv` get_location_and_rotation.cpp annotation.cpp main.cpp get_multi_location_and_rotation.cpp find_object.cpp -o template_matching
	time ./template_matching ../Data/engine_parts/1_model.png ../Data/engine_parts/1_image_23.png
	

