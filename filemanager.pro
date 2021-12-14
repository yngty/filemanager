TEMPLATE  = subdirs

isEmpty(PREFIX){
    PREFIX = /usr
}

CONFIG += ordered

SUBDIRS  += \
    filemanager-lib \
    plugin \
    filemanager

