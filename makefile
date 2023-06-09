All:shared
	g++ -o main main.cpp -lgui -lkeyboard -lbutton -L $(shell pwd)  `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` 

shared:object
	g++ -shared -fPIC -o libgui.so gui.o
	g++ -shared -fPIC -o libkeyboard.so keyboard.o 
	g++ -shared -fPIC -o libbutton.so buttons.o -lkeyboard -L $(shell pwd)

object:
	g++ -c -fPIC -o gui.o gui.cpp `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` 
	g++ -c -fPIC -o keyboard.o keyboard.cpp `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` 
	g++ -c -fPIC -o buttons.o buttons.cpp `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` 

remove:
	rm -rf gui.o
	rm -rf keyboard.o
	rm -rf buttons.o
	rm -rf libgui.so
	rm -rf libkeyboard.so
	rm -rf libbutton.so
	rm -rf main
