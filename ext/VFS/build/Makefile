CONFIG ?= ../../../config.default
-include $(CONFIG)


CFLAGS += -I ../../7z
CFLAGS += -I ../../utf8/source
CFLAGS += -I ../include

#CFLAGS += -Wall
#CFLAGS += -W
CFLAGS += -Wpointer-arith
CFLAGS += -Wreturn-type
CFLAGS += -Wunused-label
CFLAGS += -Wunused-variable
CFLAGS += -Wwrite-strings

ifdef _DEBUG
  CFLAGS += -D_DEBUG
endif

ifdef WITH_VFS
CFLAGS += -DWITH_VFS -DVFS_STATIC
endif

CFLAGS += -DHAVE_MEMMOVE

CCFLAGS += $(CFLAGS)
CCFLAGS += -std=gnu99
CCFLAGS += -Werror-implicit-function-declaration
CCFLAGS += -Wimplicit-int
CCFLAGS += -Wmissing-prototypes

CXXFLAGS += $(CFLAGS)

LDFLAGS += -lm

ifdef WITH_ZLIB
LDFLAGS += -lz
endif

SRCS :=

ifdef WITH_VFS
SRCS += ../src/Aspects/vfs_debugging.cpp
SRCS += ../src/Aspects/vfs_logging.cpp
SRCS += ../src/Aspects/vfs_synchronization.cpp

SRCS += ../src/Core/os_functions.cpp
SRCS += ../src/Core/vfs_string.cpp
SRCS += ../src/Core/vfs_debug.cpp
SRCS += ../src/Core/vfs_file_raii.cpp
SRCS += ../src/Core/vfs_init.cpp
SRCS += ../src/Core/vfs_path.cpp
SRCS += ../src/Core/vfs_profile.cpp
SRCS += ../src/Core/vfs_settings.cpp
SRCS += ../src/Core/vfs_types.cpp
SRCS += ../src/Core/vfs_vfile.cpp
SRCS += ../src/Core/vfs_vloc.cpp
SRCS += ../src/Core/vfs.cpp

SRCS += ../src/Core/File/vfs_dir_file.cpp
SRCS += ../src/Core/File/vfs_file.cpp
SRCS += ../src/Core/File/vfs_lib_file.cpp
SRCS += ../src/Core/File/vfs_memory_file.cpp

SRCS += ../src/Core/Interface/vfs_interface_members.cpp

SRCS += ../src/Core/Location/vfs_directory_tree.cpp
SRCS += ../src/Core/Location/vfs_lib_dir.cpp
SRCS += ../src/Core/Location/vfs_uncompressed_lib_base.cpp

SRCS += ../src/Ext/7z/vfs_7z_library.cpp
SRCS += ../src/Ext/7z/vfs_create_7z_library.cpp
SRCS += ../src/Ext/slf/vfs_slf_library.cpp

SRCS += ../src/Tools/vfs_file_logger.cpp
SRCS += ../src/Tools/vfs_hp_timer.cpp
SRCS += ../src/Tools/vfs_log.cpp
SRCS += ../src/Tools/vfs_parser_tools.cpp
SRCS += ../src/Tools/vfs_profiler.cpp
SRCS += ../src/Tools/vfs_property_container.cpp
SRCS += ../src/Tools/vfs_tools.cpp
endif


OBJS = $(filter %.o, $(SRCS:.c=.o) $(SRCS:.cc=.o) $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

.SUFFIXES:
.SUFFIXES: .c .cc .cpp .d .o

Q ?= @

all: vfs 

-include $(DEPS)

AR = ar

ifdef WITH_VFS 
vfs: $(OBJS)
	@echo '===> LD $@'
	$(Q)$(AR) rcs ../../libvfs.a $(OBJS)
else
vfs:
	echo '*** VFS disabled ***'
endif

.c.o:
	@echo '===> CC $<'
	$(Q)$(CC) $(CCFLAGS) -c -MMD -o $@ $<

.cc.o:
	@echo '===> CXX $<'
	$(Q)$(CXX) $(CXXFLAGS) -c -MMD -o $@ $< 

.cpp.o:
	@echo '===> CXX $<'
	$(Q)$(CXX) $(CXXFLAGS) -c -MMD -o $@ $< 

clean distclean:
	@echo '===> CLEAN'
	$(Q)rm -fr $(DEPS) $(OBJS) $(BINARY)

