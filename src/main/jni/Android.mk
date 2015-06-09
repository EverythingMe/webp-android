######## Build webp ########

LOCAL_PATH := $(call my-dir)
ORIG_LOCAL_PATH := $(LOCAL_PATH)
include $(CLEAR_VARS)
WEBP_FILES := \
    src/dec/alpha.c \
    src/dec/buffer.c \
    src/dec/frame.c \
    src/dec/idec.c \
    src/dec/io.c \
    src/dec/layer.c \
    src/dec/quant.c \
    src/dec/tree.c \
    src/dec/vp8.c \
    src/dec/vp8l.c \
    src/dec/webp.c \
    src/dsp/cpu.c \
    src/dsp/dec.c \
    src/dsp/dec_sse2.c \
    src/dsp/lossless.c \
    src/dsp/upsampling.c \
    src/dsp/upsampling_sse2.c \
    src/dsp/yuv.c \
    src/utils/bit_reader.c \
    src/utils/bit_writer.c \
    src/utils/color_cache.c \
    src/utils/filters.c \
    src/utils/huffman.c \
    src/utils/huffman_encode.c \
    src/utils/quant_levels.c \
    src/utils/quant_levels_dec.c \
    src/utils/rescaler.c \
    src/utils/thread.c \
    src/utils/utils.c \

LOCAL_MODULE    := webp_evme
LOCAL_SRC_FILES := webp.c

LOCAL_CFLAGS := -Wall -DANDROID -DHAVE_MALLOC_H -DHAVE_PTHREAD \
                -DWEBP_USE_THREAD \
                -finline-functions -frename-registers -ffast-math \
                -s -fomit-frame-pointer -Isrc/webp -Os -fno-exceptions -fno-rtti \
                -fvisibility=hidden

LOCAL_C_INCLUDES += $(LOCAL_PATH)/src $(LOCAL_PATH)/libwebp/src

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
  # Setting LOCAL_ARM_NEON will enable -mfpu=neon which may cause illegal
  # instructions to be generated for armv7a code. Instead target the neon code
  # specifically.
  WEBP_FILES += src/dsp/dec_neon.c.neon
  WEBP_FILES += src/dsp/upsampling_neon.c.neon
endif

LOCAL_SRC_FILES += $(WEBP_FILES:%=libwebp/%)
LOCAL_SRC_FILES += swig_utils.c
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := cpufeatures


include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)
