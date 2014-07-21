LOCAL_PATH := $(call my-dir)

l1_common := CPU_COMMONS
l1_cpuh := CPUH
l1_cpul := CPUL
l1_cpul_l1 := $(l1_cpul)/LTE_L1
l1_cpul_rio := $(l1_cpul_l1)/builds/rio

l1_includes :=
l1_includes += $(LOCAL_PATH)/$(l1_common)/externals
l1_includes += $(LOCAL_PATH)/$(l1_common)/includes
l1_includes += $(LOCAL_PATH)/$(l1_cpul_l1)/externals
l1_includes += $(LOCAL_PATH)/$(l1_cpul_l1)/includes
l1_includes += $(LOCAL_PATH)/$(l1_cpul_rio)/includes
l1_includes += $(LOCAL_PATH)/kernel-headers/usr/include/brcm

l1_cflags_mips32 := -O3 -g -D_GNU_SOURCE -Wall -Wshadow -Wcast-qual -Wno-long-long -march=mips32 -mtune=mips32 -mips32
l1_cflags_mips32r2 := -O3 -g -Wall -Wshadow -Wcast-qual -Wno-long-long -march=mips32r2 -mtune=mips32r2 -mips32r2

###################### libprc_commons ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libprc_commons

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_common)/src/*.c))
#$(warning LOCAL_SRC_FILES == $(LOCAL_SRC_FILES))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)
LOCAL_CFLAGS += -fno-strict-aliasing

include $(BUILD_STATIC_LIBRARY)

###################### libprcl1 ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libprcl1

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/commons/misc/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/tracer/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/comms/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/shell/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/pse/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/l1b/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/l1c/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/l1d/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul_l1)/fle_sim/*.c))

LOCAL_SRC_FILES := $(filter-out $(l1_cpul_l1)/l1d/prc_l1d_dci_api.c,$(LOCAL_SRC_FILES))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)

include $(BUILD_STATIC_LIBRARY)

###################### libprcl1_ns ######################
include $(CLEAR_VARS)

LOCAL_PREBUILT_LIBS := libprcl1_ns:$(l1_cpul_rio)/libprcl1_ns.a

#LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/include

include $(BUILD_MULTI_PREBUILT)

###################### prc_lte ######################
include $(CLEAR_VARS)

LOCAL_MODULE := prc_lte

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul)/LTE_PSE_start/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### prc_flush_traces ######################
include $(CLEAR_VARS)

LOCAL_MODULE := prc_flush_traces

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul)/flush_traces/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### prc_maintenance ######################
include $(CLEAR_VARS)

LOCAL_MODULE := prc_maintenance

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul)/MaintenanceTest/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### fle_load ######################
include $(CLEAR_VARS)

LOCAL_MODULE := fle_load

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpul)/FLE_load/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### prc_perview_proxy ######################
include $(CLEAR_VARS)

LOCAL_MODULE := prc_perview_proxy

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpuh)/perview_proxy/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32r2)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### prc_1pps ######################
include $(CLEAR_VARS)

LOCAL_MODULE := prc_1pps

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpuh)/1pps/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32r2)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)

###################### cpuh_init ######################
include $(CLEAR_VARS)

LOCAL_MODULE := cpuh_init

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(l1_cpuh)/cpuh_init/*.c))

LOCAL_C_INCLUDES += $(l1_includes)

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(l1_cflags_mips32r2)

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

include $(BUILD_EXECUTABLE)
