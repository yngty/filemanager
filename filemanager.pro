TEMPLATE  = subdirs

isEmpty(PREFIX){
    PREFIX = /usr
}

CONFIG += ordered

SUBDIRS  += \
    plugin/plugin.pro \
    filemanager/filemanager.pro \
