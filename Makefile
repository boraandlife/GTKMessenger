all:
	g++ -o gtk_app main.cpp `pkg-config --cflags --libs gtk+-3.0`
clean:
	rm -rf ./gtk_app
