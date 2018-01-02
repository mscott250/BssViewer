#include "main_window.h"

#include <QApplication>

#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Invalid arguments, no file specified." << std::endl;
		exit(EXIT_FAILURE);
	}

    QApplication application(argc, argv);
    MainWindow main_window;
    main_window.show();
    main_window.LoadFile(argv[1]);

    return application.exec();
}
