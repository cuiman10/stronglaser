#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T11:27:49
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stronglaserHmiProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += core gui xml svg

TARGET = stronglaser
TEMPLATE = app

SOURCES += \
        main.cpp \
        strongMainWin.cpp \
        base_public_widget.cpp \
        flash_label.cpp \
        alarm_module.cpp \
        system_status_module.cpp \
        axis_position_module.cpp \
        laser_cutting_module.cpp \
        ccd_vision_module.cpp \
        machinning_msg_module.cpp \
        work_station_module.cpp \
        vision_marker_module.cpp \
        import_cuttingfile_module.cpp \
        axis_control_module.cpp \
        process_msg_module.cpp \
        auxiliary_plc_module.cpp \
        dl_dxf.cpp \
        dl_writer_ascii.cpp \
    entitiesdata.cpp \
    coordinate_scaling.cpp \
    cad_edit_module.cpp \
    laser_trajectory_module.cpp \
    hmi_motion_interface_module.cpp

HEADERS += \
        strongMainWin.h \
        base_public_widget.h \
        custom_constant.h \
        flash_label.h \
        alarm_module.h \
        system_status_module.h \
        axis_position_module.h \
        laser_cutting_module.h \
        ccd_vision_module.h \
        machinning_msg_module.h \
        work_station_module.h \
        vision_marker_module.h \
        import_cuttingfile_module.h \
        axis_control_module.h \
        process_msg_module.h \
        auxiliary_plc_module.h \
        dl_attributes.h \
        dl_codes.h \
        dl_creationadapter.h \
        dl_creationinterface.h \
        dl_dxf.h \
        dl_entities.h \
        dl_exception.h \
        dl_extrusion.h \
        dl_writer.h \
        dl_writer_ascii.h \
        entitiesdata.h \
    dl_extrusion_copy.h \
    coordinate_scaling.h \
    cad_edit_module.h \
    laser_trajectory_module.h \
    hmi_motion_interface_module.h


RESOURCES += \
    stronglaser.qrc

DISTFILES +=

