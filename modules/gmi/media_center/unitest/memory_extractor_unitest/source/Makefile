# Set the platform that we are working on, defualt is 'simulator'
GMI_PLATFORM           ?= simulator

# Set name of this module
GMI_MODULE_NAME         = $(notdir $(shell cd .. && pwd))

# Set top dir of the compile system
GMI_TOPDIR             ?= $(word 1, $(subst modules, ,$(shell pwd)))

# Set if it will show the compile command line
GMI_MAKE_VERBOSE       ?= @

# Export these variables
export GMI_PLATFORM
export GMI_TOPDIR
export GMI_MAKE_VERBOSE

# Include module.mk
include $(GMI_TOPDIR)/build/module.mk

# Set type of this module, value is in ['executable', 'shared_lib', 'static_lib']
GMI_MODULE_TYPE         = executable

# Set the target name of this module
GMI_MODULE_TARGET_NAME  = $(GMI_MODULE_NAME)

# Set the source code files to compile
GMI_MODULE_SRCS         = $(wildcard *.cpp)

# Set compile flags	
GMI_CFLAGS              = -Wall -O3
#GMI_CFLAGS             = -Wall -g -pg

# Set link flags
GMI_LFLAGS              =
#GMI_LFLAGS             = -g -pg

# Set related modules
GMI_RELATED_MODULES     = pthread osal

# Set header file path for this module
GMI_MODULE_INCLUDE_DIR  = ./

# Set other header file path
GMI_INCLUDE_DIR         = ./

# Include rules.mk
include $(GMI_TOPDIR)/build/rules.mk

