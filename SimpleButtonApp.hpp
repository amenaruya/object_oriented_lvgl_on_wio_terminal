#ifndef __SIMPLE_BUTTON_APP_HPP__
#define __SIMPLE_BUTTON_APP_HPP__

#include "LvglArduinoAbstractLayer.hpp"

class App final: public LAAL<App> {
private:
    /* 画面設定 */
    void        __mFDisplaySetup();

    /* Reading encoder callback */
    static bool __mFbReadEncoder(
        lv_indev_drv_t*     pInputDeviceDriver,
        lv_indev_data_t*    pInputDevicesData
    );
    /* デバイス設定 */
    void        __mFDeviceSetup();

    /* button1 */
    lv_obj_t*   __mpObjectButton1;
    /* label1 */
    lv_obj_t*   __mpObjectLabel1;
    /* button2 */
    lv_obj_t*   __mpObjectButton2;
    /* label2 */
    lv_obj_t*   __mpObjectLabel2;
    /* button配置 */
    void        __mFButtonsSetup();

    /* group */
    lv_group_t* __mpGroup;
    /* group設定 */
    void        __mFGroupSetup();

    /* 画面構成 */
    void        __mFContentsSetup();

    /* constructor */
    App();
    /* destructor */
    virtual ~App();

public:
    /* 初期化 */
    static App* mFpLaalInitialize(TFT_eSPI* pTft);
};

#endif // __SIMPLE_BUTTON_APP_HPP__
