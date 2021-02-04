include config.Makefile

export BINDIR
export BUILDDIR
export BASEDIR

BASEDIR=$(CURDIR)
BUILDSUFFIX=$(BUILD_TYPE).$(TARGET_ARCHITECTURE).$(TARGET_MACHINE)
ISODIR=$(BASEDIR)/images
LOGDIR=$(BASEDIR)/logs
BINDIR=$(BASEDIR)/binaries.$(BUILDSUFFIX)
BUILDDIR=$(BASEDIR)/build.$(BUILDSUFFIX)
ISONAME=$(ISODIR)/$(BUILDNAME).img
LOGOUT=$(LOGDIR)/$(BUILDNAME).txt

.PHONY: clean

debug: build-image
debug-run: debug run

release: build-image
release-run: release run

run: scripts/$(TARGET_ARCHITECTURE)/run-$(EMULATOR).sh
	$(ECHO) RUN
	$(MKDIR) $(LOGDIR)
	@./scripts/$(TARGET_ARCHITECTURE)/run-$(EMULATOR).sh $(ISONAME) $(BUILD_TYPE) $(LOGOUT) $(BINDIR)

clean:
	$(ECHO) CLEAN binaries folders
	$(DEL) binaries.*

mrproper: clean
	$(ECHO) CLEAN all temporary folders
	$(DEL) $(ISODIR)
	$(DEL) $(LOGDIR)
	$(DEL) build.*

build-image: $(ISONAME)
$(ISONAME): build scripts/create-grub-iso.sh
	$(ECHO) BUILD disk image
	$(MKDIR) $(ISODIR)
	@./scripts/create-grub-iso.sh $(BUILDDIR) $(ISONAME)

%-build: %/Makefile
	$(ECHO) BUILD $(patsubst %-build,%,$@)
	@(cd $(BASEDIR)/$(patsubst %-build,%,$@); make $(BUILD_TYPE) OUTDIR=$(BUILDDIR)/$(dir $@))

build: $(patsubst %,%-build,$(MODULES))
