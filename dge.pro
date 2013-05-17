TEMPLATE = subdirs

SUBDIRS += \
    src \
    # test

OTHER_FILES += box2d.pri

scripts.path = $$OUT_PWD/src
scripts.files = scripts

tools.path = $$OUT_PWD/src
tools.files = tools

INSTALLS += scripts tools
