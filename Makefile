include config.Makefile

export BINDIR

ISODIR=$(CURDIR)/iso
LOGDIR=$(CURDIR)/logs
ifneq ($(BUILD_TYPE),none)
	BINDIR=$(CURDIR)/build.$(TARGET_ARCHITECTURE).$(BUILD_TYPE).$(BUILD_NUMBER)
	ISONAME=$(ISODIR)/build.$(BUILD_NUMBER).$(BUILD_TYPE).iso
	LOGOUT=$(LOGDIR)/build.$(BUILD_NUMBER).$(BUILD_TYPE).txt
endif

.PHONY: clean

debug: build-image
debug-run: debug run

release: build-image
release-run: release run

run: scripts/run-$(TARGET_ARCHITECTURE)-$(EMULATOR).sh
	$(ECHO) RUN
	$(MKDIR) $(LOGDIR)
	@./scripts/run-$(TARGET_ARCHITECTURE)-$(EMULATOR).sh $(ISONAME) $(BUILD_TYPE) $(LOGOUT) $(BINDIR)

clean: $(patsubst %,%-clean,$(MODULES))
	$(ECHO) CLEAN binaries folders
	$(DEL) build.$(TARGET_ARCHITECTURE).debug.0
	$(DEL) build.$(TARGET_ARCHITECTURE).release.0

mrproper: clean
	$(ECHO) CLEAN all binaries folders
	$(DEL) build.*
	$(DEL) $(ISODIR)
	$(DEL) $(LOGDIR)

build-image: $(ISONAME)
$(ISONAME): build scripts/create-grub-iso.sh
	$(ECHO) BUILD disk image
	$(MKDIR) $(ISODIR)
	@./scripts/create-grub-iso.sh $(BINDIR) $(ISONAME)

%-clean: %/Makefile
	$(ECHO) CLEAN $(patsubst %-clean,%,$@)
	@(cd $(patsubst %-clean,%,$@); make clean)

$(BINDIR)/%: %/Makefile
	$(ECHO) BUILD $(patsubst $(BINDIR)/%,%,$@)
	$(MKDIR) $(patsubst %/$(notdir $@),%,$@)
	@(cd $(patsubst $(BINDIR)/%,%,$@); make $(BUILD_TYPE) OUTDIR=$(patsubst %$(notdir $@),%,$@))

build: $(patsubst %,$(BINDIR)/%,$(MODULES))