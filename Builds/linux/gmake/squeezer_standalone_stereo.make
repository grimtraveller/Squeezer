# GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_x32
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),debug_x32)
  RESCOMP = windres
  TARGETDIR = ../../../bin
  TARGET = $(TARGETDIR)/squeezer_stereo_debug
  OBJDIR = ../../../bin/intermediate_linux/standalone_stereo_debug/x32
  DEFINES += -DLINUX=1 -D_DEBUG=1 -DDEBUG=1 -DJUCE_CHECK_MEMORY_LEAKS=1 -DSQUEEZER_STEREO=1 -DJucePlugin_Build_LV2=0 -DJucePlugin_Build_Standalone=1 -DJucePlugin_Build_VST=0 -DJUCE_ALSA=1 -DJUCE_JACK=1 -DJUCE_ASIO=0 -DJUCE_WASAPI=0 -DJUCE_DIRECTSOUND=0
  INCLUDES += -I../../../JuceLibraryCode -I../../../libraries/juce/modules -I../../../Source/common -I../../../libraries -I/usr/include -I/usr/include/freetype2
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -g -Wall -Wextra -fno-inline -ggdb
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -g -Wall -Wextra -std=c++11 -fno-inline -ggdb
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -ldl -lfreetype -lpthread -lrt -lX11 -lXext -lasound
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib32 -m32 -Wl,--no-undefined
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_x64)
  RESCOMP = windres
  TARGETDIR = ../../../bin
  TARGET = $(TARGETDIR)/squeezer_stereo_debug_x64
  OBJDIR = ../../../bin/intermediate_linux/standalone_stereo_debug/x64
  DEFINES += -DLINUX=1 -D_DEBUG=1 -DDEBUG=1 -DJUCE_CHECK_MEMORY_LEAKS=1 -DSQUEEZER_STEREO=1 -DJucePlugin_Build_LV2=0 -DJucePlugin_Build_Standalone=1 -DJucePlugin_Build_VST=0 -DJUCE_ALSA=1 -DJUCE_JACK=1 -DJUCE_ASIO=0 -DJUCE_WASAPI=0 -DJUCE_DIRECTSOUND=0
  INCLUDES += -I../../../JuceLibraryCode -I../../../libraries/juce/modules -I../../../Source/common -I../../../libraries -I/usr/include -I/usr/include/freetype2
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g -Wall -Wextra -fno-inline -ggdb
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -Wall -Wextra -std=c++11 -fno-inline -ggdb
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -ldl -lfreetype -lpthread -lrt -lX11 -lXext -lasound
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -Wl,--no-undefined
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_x32)
  RESCOMP = windres
  TARGETDIR = ../../../bin
  TARGET = $(TARGETDIR)/squeezer_stereo
  OBJDIR = ../../../bin/intermediate_linux/standalone_stereo_release/x32
  DEFINES += -DLINUX=1 -DNDEBUG=1 -DJUCE_CHECK_MEMORY_LEAKS=0 -DSQUEEZER_STEREO=1 -DJucePlugin_Build_LV2=0 -DJucePlugin_Build_Standalone=1 -DJucePlugin_Build_VST=0 -DJUCE_ALSA=1 -DJUCE_JACK=1 -DJUCE_ASIO=0 -DJUCE_WASAPI=0 -DJUCE_DIRECTSOUND=0
  INCLUDES += -I../../../JuceLibraryCode -I../../../libraries/juce/modules -I../../../Source/common -I../../../libraries -I/usr/include -I/usr/include/freetype2
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -fomit-frame-pointer -O3 -Wall -Wextra -fvisibility=hidden -pipe
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -fomit-frame-pointer -O3 -Wall -Wextra -std=c++11 -fvisibility=hidden -pipe
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -ldl -lfreetype -lpthread -lrt -lX11 -lXext -lasound
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib32 -m32 -s -Wl,--no-undefined
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_x64)
  RESCOMP = windres
  TARGETDIR = ../../../bin
  TARGET = $(TARGETDIR)/squeezer_stereo_x64
  OBJDIR = ../../../bin/intermediate_linux/standalone_stereo_release/x64
  DEFINES += -DLINUX=1 -DNDEBUG=1 -DJUCE_CHECK_MEMORY_LEAKS=0 -DSQUEEZER_STEREO=1 -DJucePlugin_Build_LV2=0 -DJucePlugin_Build_Standalone=1 -DJucePlugin_Build_VST=0 -DJUCE_ALSA=1 -DJUCE_JACK=1 -DJUCE_ASIO=0 -DJUCE_WASAPI=0 -DJUCE_DIRECTSOUND=0
  INCLUDES += -I../../../JuceLibraryCode -I../../../libraries/juce/modules -I../../../Source/common -I../../../libraries -I/usr/include -I/usr/include/freetype2
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -fomit-frame-pointer -O3 -Wall -Wextra -fvisibility=hidden -pipe
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -fomit-frame-pointer -O3 -Wall -Wextra -std=c++11 -fvisibility=hidden -pipe
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -ldl -lfreetype -lpthread -lrt -lX11 -lXext -lasound
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -s -Wl,--no-undefined
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/juce_audio_basics.o \
	$(OBJDIR)/juce_audio_devices.o \
	$(OBJDIR)/juce_audio_formats.o \
	$(OBJDIR)/juce_audio_plugin_client_utils.o \
	$(OBJDIR)/juce_audio_processors.o \
	$(OBJDIR)/juce_audio_utils.o \
	$(OBJDIR)/juce_core.o \
	$(OBJDIR)/juce_cryptography.o \
	$(OBJDIR)/juce_data_structures.o \
	$(OBJDIR)/juce_events.o \
	$(OBJDIR)/juce_graphics.o \
	$(OBJDIR)/juce_gui_basics.o \
	$(OBJDIR)/juce_gui_extra.o \
	$(OBJDIR)/juce_video.o \
	$(OBJDIR)/frut_audio.o \
	$(OBJDIR)/frut_math.o \
	$(OBJDIR)/frut_parameter.o \
	$(OBJDIR)/frut_skin.o \
	$(OBJDIR)/frut_widget.o \
	$(OBJDIR)/compressor.o \
	$(OBJDIR)/filter_chebyshev.o \
	$(OBJDIR)/filter_chebyshev_stage.o \
	$(OBJDIR)/gain_stage_fet.o \
	$(OBJDIR)/gain_stage_optical.o \
	$(OBJDIR)/meter_bar_gain_reduction.o \
	$(OBJDIR)/meter_bar_level.o \
	$(OBJDIR)/plugin_editor.o \
	$(OBJDIR)/plugin_parameters.o \
	$(OBJDIR)/plugin_processor.o \
	$(OBJDIR)/side_chain.o \
	$(OBJDIR)/skin.o \
	$(OBJDIR)/standalone_application.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking squeezer_standalone_stereo
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning squeezer_standalone_stereo
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH)
$(GCH): $(PCH)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
endif

$(OBJDIR)/juce_audio_basics.o: ../../../JuceLibraryCode/juce_audio_basics.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_audio_devices.o: ../../../JuceLibraryCode/juce_audio_devices.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_audio_formats.o: ../../../JuceLibraryCode/juce_audio_formats.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_audio_plugin_client_utils.o: ../../../JuceLibraryCode/juce_audio_plugin_client_utils.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_audio_processors.o: ../../../JuceLibraryCode/juce_audio_processors.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_audio_utils.o: ../../../JuceLibraryCode/juce_audio_utils.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_core.o: ../../../JuceLibraryCode/juce_core.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_cryptography.o: ../../../JuceLibraryCode/juce_cryptography.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_data_structures.o: ../../../JuceLibraryCode/juce_data_structures.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_events.o: ../../../JuceLibraryCode/juce_events.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_graphics.o: ../../../JuceLibraryCode/juce_graphics.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_gui_basics.o: ../../../JuceLibraryCode/juce_gui_basics.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_gui_extra.o: ../../../JuceLibraryCode/juce_gui_extra.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/juce_video.o: ../../../JuceLibraryCode/juce_video.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/frut_audio.o: ../../../Source/common/amalgamated/frut_audio.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/frut_math.o: ../../../Source/common/amalgamated/frut_math.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/frut_parameter.o: ../../../Source/common/amalgamated/frut_parameter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/frut_skin.o: ../../../Source/common/amalgamated/frut_skin.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/frut_widget.o: ../../../Source/common/amalgamated/frut_widget.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/compressor.o: ../../../Source/compressor.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/filter_chebyshev.o: ../../../Source/filter_chebyshev.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/filter_chebyshev_stage.o: ../../../Source/filter_chebyshev_stage.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/gain_stage_fet.o: ../../../Source/gain_stage_fet.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/gain_stage_optical.o: ../../../Source/gain_stage_optical.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/meter_bar_gain_reduction.o: ../../../Source/meter_bar_gain_reduction.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/meter_bar_level.o: ../../../Source/meter_bar_level.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/plugin_editor.o: ../../../Source/plugin_editor.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/plugin_parameters.o: ../../../Source/plugin_parameters.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/plugin_processor.o: ../../../Source/plugin_processor.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/side_chain.o: ../../../Source/side_chain.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/skin.o: ../../../Source/skin.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/standalone_application.o: ../../../Source/standalone_application.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif