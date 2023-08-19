#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include "myscreen.h"

namespace Ui {
class EditScreen;
}

class EditScreen : public MyScreen
{
    Q_OBJECT

public:
    explicit EditScreen(Dict *dict, QWidget *parent = nullptr);
    ~EditScreen();

private:
    Ui::EditScreen *ui;
};

#endif // EDITSCREEN_H
