include config.Makefile

export BINDIR
export BASEDIR

BASEDIR=$(CURDIR)
BUILDNAME=build.$(BUILD_TYPE).$(TARGET_ARCHITECTURE).$(TARGET_MACHINE)
ISODIR=$(BASEDIR)/images
LOGDIR=$(BASEDIR)/logs
ifneq ($(BUILD_TYPE),none)
	BINDIR=$(BASEDIR)/$(BUILDNAME)
	ISONAME=$(ISODIR)/$(BUILDNAME).img
	LOGOUT=$(LOGDIR)/$(BUILDNAME).txt
endif

.PHONY: clean

debug: build-image
debug-run: debug run

release: build-image
release-run: release run

run: scripts/$(TARGET_ARCHITECTURE)/run-$(EMULATOR).sh
	$(ECHO) RUN
	$(MKDIR) $(LOGDIR)
	@./scripts/$(TARGET_ARCHITECTURE)/run-$(EMULATOR).sh $(ISONAME) $(BUILD_TYPE) $(LOGOUT) $(BINDIR)

clean: $(patsubst %,%-clean,$(MODULES))
	$(ECHO) CLEAN binaries folders
	$(DEL) build.*

mrproper: clean
	$(ECHO) CLEAN all binaries folders
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

%-build: %/Makefile
	$(ECHO) BUILD $(patsubst %-build,%,$@)
	@(cd $(BASEDIR)/$(patsubst %-build,%,$@); make $(BUILD_TYPE) OUTDIR=$(BINDIR)/$(dir $@))

build: $(patsubst %,%-build,$(MODULES))