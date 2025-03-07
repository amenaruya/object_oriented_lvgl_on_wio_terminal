/*
Curiously Recurring Template Pattern

```
template<class T>
class LAAL {};

class App final: public LAAL<App> {};
```

*/

#include <TFT_eSPI.h>
#include <lvgl.h>

#include "SimpleButtonApp.hpp"

/* TFT LCD */
static TFT_eSPI TFT;

/* App */
App* pApp;

void setup() {
    pApp = App::mFpLaalInitialize(&TFT);
    pApp -> mFSetup();
}

void loop() {
    pApp -> mFOperateGraphic();
}
