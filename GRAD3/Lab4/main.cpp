#include <QApplication>

#include "util/UI.h"
#include "test.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UI ui(argc, argv, app);

    if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        run_test();
        return 0;
    }

    ui.run();

    return 0;
}