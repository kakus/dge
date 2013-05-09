TEMPLATE = subdirs

SUBDIRS += \
    src \
    # test

OTHER_FILES += box2d.pri

scripts.path = $$OUT_PWD/src
scripts.files = scripts

INSTALLS += scripts
