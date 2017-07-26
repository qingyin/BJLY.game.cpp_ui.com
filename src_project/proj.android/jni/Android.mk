LOCAL_PATH := $(call my-dir)

# --- 引用 libBugly.so ---
include $(CLEAR_VARS)

LOCAL_MODULE := bugly_native_prebuilt
# 可在Application.mk添加APP_ABI := armeabi armeabi-v7a 指定集成对应架构的.so文件
LOCAL_SRC_FILES := prebuilt/$(TARGET_ARCH_ABI)/libBugly.so

include $(PREBUILT_SHARED_LIBRARY)
# --- end ---


include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)


LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
				$(LOCAL_PATH)/../../cocos2d/external/protobuf-2.5.0/src \
				

# 遍历目录及子目录的函数
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
# 遍历Classes目录
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
FILE_LIST := hellocpp/main.cpp
#  从所有文件中提取出所有.cpp和.cc文件
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.cc, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += protobuf_static
LOCAL_WHOLE_STATIC_LIBRARIES += android_support
LOCAL_WHOLE_STATIC_LIBRARIES += bugly_crashreport_cocos_static
# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,external/protobuf-2.5.0)
$(call import-module,android/support)
$(call import-module,external/bugly)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END