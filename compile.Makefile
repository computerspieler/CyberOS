include $(BASEDIR)/config.Makefile

ifdef LIBDEP
	CCFLAGS+=$(patsubst %,-I$(BASEDIR)/libs/%,$(LIBDEP))
	LIBS+=$(patsubst %,$(BUILDDIR)/libs/%.a,$(LIBDEP))
	LIBS_TARGET=$(patsubst %,libs/%,$(LIBDEP))
endif

LOCALBINDIR=$(patsubst $(BASEDIR)%,$(BINDIR)%,$(CURDIR))

DEPS=$(patsubst %,$(LOCALBINDIR)/%.d,$(SRCS))
OBJS=$(patsubst %,$(LOCALBINDIR)/%.o,$(SRCS))

.PRECIOUS: $(OBJS) $(DEPS)

$(LOCALBINDIR)/%.s.o: %.s
	$(ECHO) AS $(notdir $@)
	$(MKDIR) $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(LOCALBINDIR)/%.c.o: %.c
	$(ECHO) CC $(notdir $@)
	$(MKDIR) $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

$(LOCALBINDIR)/%.c.d: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst %.c,objs/%.c.o,$<)

-include $(DEPS)

%.bin: $(OBJS) $(LIBS_TARGET)
	$(ECHO) LINK $(notdir $@)
	$(MKDIR) $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.a: $(OBJS) $(LIBS_TARGET)
	$(ECHO) AR $(notdir $@)
	$(MKDIR) $(dir $@)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(LIBS)

libs/%: $(BASEDIR)/libs/%/Makefile
	$(ECHO) BUILD $@
	@(cd $(BASEDIR)/$@; make $(BUILD_TYPE) OUTDIR=$(BUILDDIR)/$(dir $@))

debug: build
release: build

