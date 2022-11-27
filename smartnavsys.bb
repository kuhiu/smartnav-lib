#
# This file is the smartnavsys recipe.
#

SUMMARY = "Simple smartnavsys application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "	file://main.cpp \
						file://modules/hc-sr04/DistanceSensors.cpp \
						file://modules/hc-sr04/DistanceSensors.hpp \
						file://modules/frame-processor/Detector.cpp \
						file://modules/frame-processor/Detector.hpp \
						file://modules/frame-processor/FrameProcessor.cpp \
						file://modules/frame-processor/FrameProcessor.hpp \
						file://modules/frame-processor/RecognitionResult.hpp \
						file://modules/capture-frame/VirtualImage.cpp \
						file://modules/capture-frame/VirtualImage.hpp \
						file://modules/capture-frame/ColorSpaces.hpp \
						file://modules/capture-frame/CaptureFrame.cpp \
						file://modules/capture-frame/CaptureFrame.hpp \
						file://modules/logger/Logger.cpp \
						file://modules/logger/Logger.hpp \
						file://modules/logger/LogLevels.hpp \
						file://modules/logger/LogStream.cpp \
						file://modules/logger/LogStream.hpp \
           	file://Makefile \
					"

S = "${WORKDIR}"
DEPENDS += "libtensorflowlite" 
DEPENDS += "opencv"

do_compile() {
	     oe_runmake INCLUDE=${S}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 smartnavsys ${D}${bindir}
}
