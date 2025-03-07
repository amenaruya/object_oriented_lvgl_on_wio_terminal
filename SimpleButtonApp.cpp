#include "SimpleButtonApp.hpp"

App* App::mFpLaalInitialize(TFT_eSPI* pTft) {
    /* 未定ならば初期化 */
    if (LAAL<App>::__smpLaalSingleton == nullptr) {
        /* static member variableの初期化 */
        LAAL<App>::__mpTft = pTft;
        /* 子クラスの初期化 */
        LAAL<App>::__smpLaalSingleton = new App();
    }
    /* 既初期化の場合でも既存インスタンスへのポインターが返却される */
    return LAAL<App>::__smpLaalSingleton;
}

App::App() {
    LAAL<App>::__mFNew();
}
App::~App() {}

void App::__mFDisplaySetup() {
    LAAL<App>::__mFDisplaySetup();
}

bool App::__mFbReadEncoder(
    lv_indev_drv_t*  pInputDeviceDriver,
    lv_indev_data_t*        pInputDevicesData
) {
    (void) pInputDeviceDriver;
    if (digitalRead(WIO_5S_PRESS) == LOW) {
        pInputDevicesData -> state = LV_INDEV_STATE_PR;
    } else {
        pInputDevicesData -> state = LV_INDEV_STATE_REL;
    }

    /*
    indev_encoder_proc()に基づく左右の定義
    */
    if (digitalRead(WIO_5S_LEFT) == LOW) {
        pInputDevicesData -> enc_diff = -1;
    } else if (digitalRead(WIO_5S_RIGHT) == LOW) {
        pInputDevicesData -> enc_diff = 1;
    } else {
        pInputDevicesData -> enc_diff = 0;
    }

    /* no data buffered */
    return false;
}

void App::__mFDeviceSetup() {
    /* 入力の設定 */
    lv_indev_drv_init(&(LAAL<App>::__mInputDeviceDriverEncoder));
    (LAAL<App>::__mInputDeviceDriverEncoder).type = LV_INDEV_TYPE_ENCODER;
    (LAAL<App>::__mInputDeviceDriverEncoder).read_cb = App::__mFbReadEncoder;
    LAAL<App>::__mpInputDeviceEncoder = lv_indev_drv_register(&(LAAL<App>::__mInputDeviceDriverEncoder));

    /* enable 5way switch */
    pinMode(WIO_5S_UP, INPUT);
    pinMode(WIO_5S_DOWN, INPUT);
    pinMode(WIO_5S_LEFT, INPUT);
    pinMode(WIO_5S_RIGHT, INPUT);
    pinMode(WIO_5S_PRESS, INPUT);
}

void App::__mFButtonsSetup() {
    this -> __mpObjectButton1 = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_event_cb(this -> __mpObjectButton1, event_handler);
    lv_obj_align(this -> __mpObjectButton1, NULL, LV_ALIGN_CENTER, 0, -40);

    this -> __mpObjectLabel1 = lv_label_create(this -> __mpObjectButton1, NULL);
    lv_label_set_text(this -> __mpObjectLabel1, "Button");

    this -> __mpObjectButton2 = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_event_cb(this -> __mpObjectButton2, event_handler);
    lv_obj_align(this -> __mpObjectButton2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(this -> __mpObjectButton2, true);
    lv_btn_toggle(this -> __mpObjectButton2);
    lv_btn_set_fit2(this -> __mpObjectButton2, LV_FIT_NONE, LV_FIT_TIGHT);

    this -> __mpObjectLabel2 = lv_label_create(this -> __mpObjectButton2, NULL);
    lv_label_set_text(this -> __mpObjectLabel2, "Toggled");
}

void App::__mFGroupSetup() {
    this -> __mpGroup = lv_group_create();
    lv_indev_set_group(LAAL<App>::__mpInputDeviceEncoder, this -> __mpGroup);
    lv_group_add_obj(this -> __mpGroup, this -> __mpObjectButton1);
    lv_group_add_obj(this -> __mpGroup, this -> __mpObjectButton2);
}

void App::__mFContentsSetup() {
    (this -> __mFButtonsSetup)();
    (this -> __mFGroupSetup)();
}
