LOCAL_PATH:=$(call my-dir)

# host renderer process ###########################
$(call emugl-begin-host-executable,emulator_renderer)
$(call emugl-import,libOpenglRender)
LOCAL_SRC_FILES := main.cpp
LOCAL_CFLAGS    += -O0 -g

ifeq ($(HOST_OS),linux)
LOCAL_LDLIBS += -lX11
endif

$(call emugl-end-module)

