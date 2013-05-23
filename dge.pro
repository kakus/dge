TEMPLATE = subdirs

SUBDIRS += \
    src \
    # test

OTHER_FILES += box2d.pri \
    tools/play_world.js \
    tools/static_rectangle.js \
    tools/select.js \
    scripts/cmd_manager.js \
    scripts/cmd_mapper.js \
    tools/box.js \
    scripts/keyboard_manager.js

scripts.path = $$OUT_PWD/src
scripts.files = scripts

tools.path = $$OUT_PWD/src
tools.files = tools

INSTALLS += scripts tools
