# Makefile

# Directories
MYPROJECT_DIR := $(LVGL_DIR)/myproject
IMAGES_DIR := $(MYPROJECT_DIR)/images

# Source files
CSRCS += $(MYPROJECT_DIR)/screens.c

# Compiler flags
CFLAGS += -I$(MYPROJECT_DIR) -I$(IMAGES_DIR)

# Dependency paths
DEPPATH += --dep-path $(MYPROJECT_DIR)
DEPPATH += --dep-path $(IMAGES_DIR)

# VPATH (search paths for source files)
VPATH += $(MYPROJECT_DIR)
VPATH += $(IMAGES_DIR)
