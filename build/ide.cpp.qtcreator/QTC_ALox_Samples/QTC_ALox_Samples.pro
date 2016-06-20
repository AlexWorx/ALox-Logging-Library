# #################################################################################################
#  QMake 'pro' file - ALox Samples
#
#  (c) 2016 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
# #################################################################################################

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


#-- optional compilation symbols (ALib/ALox features).
#-- uncomment to set (the opposite value is their default, therefore commenting the lines switches them)
# DEFINES+= ALIB_DEBUG_GLIB_ON
# DEFINES+= ALIB_AVOID_ANALYZER_WARNINGS_ON
# DEFINES+= ALIB_DEBUG_STRINGS_ON
# DEFINES+= ALIB_FEAT_THREADS_OFF     # disabling this does not work with gtest projects
# DEFINES+= ALOX_DBG_LOG_OFF
# DEFINES+= ALOX_DBG_LOG_CI_OFF
# DEFINES+= ALOX_REL_LOG_OFF
DEFINES+= ALOX_REL_LOG_CI_ON



ALIB_BASE_DIR= ../../../../src.cpp
DEPENDPATH += $$ALIB_BASE_DIR/alox.samples

INCLUDEPATH+= $$ALIB_BASE_DIR

SOURCES+=   ../../../../src.cpp/alox.samples/ALoxSamples.cpp


unix:!macx: LIBS += -L$$PWD/../../_builds_/ide.cpp.qtcreator/QTC_ALox_SLib-Desktop-Debug/ -lQTC_ALox_SLib
DEPENDPATH+=          $$PWD/../../_builds_/ide.cpp.qtcreator/QTC_ALox_SLib-Desktop-Debug
