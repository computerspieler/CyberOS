include $(BASEDIR)/config.Makefile

ifdef LIBDEP
	CCFLAGS+=$(patsubst %,-I$(BASEDIR)/libs/%,$(LIBDEP))
	LIBS+=$(patsubst %,$(BINDIR)/libs/%.a,$(LIBDEP))
	LIBS_TARGET=$(patsubst %,libs/%,$(LIBDEP))
endif

DEPS=$(patsubst %,deps/%.d,$(SRCS))
OBJS=$(patsubst %,objs/%.o,$(SRCS))

.PRECIOUS: $(OBJS) $(DEPS)

objs/%.s.o: %.s
	$(ECHO) AS $(patsubst objs/%,%,$@)
	$(MKDIR) $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

objs/%.c.o: %.c
	$(ECHO) CC $(patsubst objs/%,%,$@)
	$(MKDIR) $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

deps/%.c.d: %.c
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
	@(cd $(BASEDIR)/$@; make $(BUILD_TYPE) OUTDIR=$(BINDIR)/$(dir $@))

debug: build
release: build

clean:
	$(DEL) objs
	$(DEL) deps