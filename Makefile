#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := esp32-clock

include $(IDF_PATH)/make/project.mk

COMPONENT_LDFLAGS += -lstdc++
