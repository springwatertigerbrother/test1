LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/ballGamescene.cpp \
                   ../../Classes/BallSprite.cpp \
                   ../../Classes/BuyLifeLayer.cpp \
                   ../../Classes/ControllerLayer.cpp \
                   ../../Classes/DataBase64.cpp \
                   ../../Classes/DataHome.cpp \
                   ../../Classes/DataManager.cpp \
                   ../../Classes/DataUpdateLayer.cpp \
                   ../../Classes/GameCenterScene.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/MUtils.cpp \
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
