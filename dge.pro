TEMPLATE = subdirs

SUBDIRS += \
    src \
    # test

OTHER_FILES += box2d.pri \
    tools/tool1.js

scripts.path = $$OUT_PWD/src
scripts.files = scripts
scripts.files = tools

INSTALLS += scripts
