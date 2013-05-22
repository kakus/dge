TEMPLATE = subdirs

SUBDIRS += \
    src \
    # test

OTHER_FILES += box2d.pri \
    tools/rectangle.js \
    scripts/cmd_manager.js \
    tools/play_world.js \
    tools/static_rectangle.js \
    tools/select.js

scripts.path = $$OUT_PWD/src
scripts.files = scripts

tools.path = $$OUT_PWD/src
tools.files = tools

INSTALLS += scripts tools
