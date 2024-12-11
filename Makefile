# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Eris_Utility_config = debug
  LeadTheHordes_config = debug

else ifeq ($(config),release)
  Eris_Utility_config = release
  LeadTheHordes_config = release

else ifeq ($(config),dist)
  Eris_Utility_config = dist
  LeadTheHordes_config = dist

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := Eris_Utility LeadTheHordes

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Eris_Utility:
ifneq (,$(Eris_Utility_config))
	@echo "==== Building Eris_Utility ($(Eris_Utility_config)) ===="
	@${MAKE} --no-print-directory -C Eris_Utility -f Makefile config=$(Eris_Utility_config)
endif

LeadTheHordes: Eris_Utility
ifneq (,$(LeadTheHordes_config))
	@echo "==== Building LeadTheHordes ($(LeadTheHordes_config)) ===="
	@${MAKE} --no-print-directory -C LeadTheHordes -f Makefile config=$(LeadTheHordes_config)
endif

clean:
	@${MAKE} --no-print-directory -C Eris_Utility -f Makefile clean
	@${MAKE} --no-print-directory -C LeadTheHordes -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo "  dist"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Eris_Utility"
	@echo "   LeadTheHordes"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"