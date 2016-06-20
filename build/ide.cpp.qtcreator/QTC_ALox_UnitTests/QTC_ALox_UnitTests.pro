# #################################################################################################
#  QMake 'pro' file - ALox Samples
#
#  (c) 2016 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
# #################################################################################################

TEMPLATE=       app
CONFIG+=        console c++11
CONFIG-=        app_bundle
QT-=            gui

DEFINES+=       ALIB_GTEST_ON
DEFINES+=       ALOX_UNITTESTS_QMAKE_BUILD


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


ALIB_BASE_DIR=  ../../../../src.cpp
DEPENDPATH +=   $$ALIB_BASE_DIR/alox.unittests
DEPENDPATH +=   $$ALIB_BASE_DIR/alib/system/

INCLUDEPATH+=   $$ALIB_BASE_DIR


SOURCES+=   ../../../../src.cpp/alib.unittests/aworx_unittests.cpp                          \
            ../../../../src.cpp/alib.unittests/aworx_unittests.hpp                          \
            ../../../../src.cpp/alib.unittests/ut_alib_compatiblity_qt.cpp                  \
            ../../../../src.cpp/alib.unittests/ut_alib_config.cpp                           \
            ../../../../src.cpp/alib.unittests/ut_alib_strings_astring.cpp                  \
            ../../../../src.cpp/alib.unittests/ut_alib_strings_basic.cpp                    \
            ../../../../src.cpp/alib.unittests/ut_alib_strings_numberformat.cpp             \
            ../../../../src.cpp/alib.unittests/ut_alib_strings_substring.cpp                \
            ../../../../src.cpp/alib.unittests/ut_alib_strings_tokenizer.cpp                \
            ../../../../src.cpp/alib.unittests/ut_alib_system.cpp                           \
            ../../../../src.cpp/alib.unittests/ut_alib_threads.cpp                          \
            ../../../../src.cpp/alib.unittests/ut_alib_time.cpp                             \
            ../../../../src.cpp/alib.unittests/docsamples/DOX_ALIB_APPLYTO.cpp              \
            ../../../../src.cpp/alib.unittests/docsamples/DOX_ALIB_ASTRING.cpp              \
            ../../../../src.cpp/alib.unittests/docsamples/DOX_ALIB_STRINGS.cpp              \
            ../../../../src.cpp/alib.unittests/docsamples/DOX_ALIB_TOAS.cpp                 \
            ../../../../src.cpp/alib.unittests/docsamples/DOX_ALIB_TOKENIZER.cpp            \
                                                                                            \
                                                                                            \
            ../../../../src.cpp/alox.unittests/gtest_main.cpp                               \
            ../../../../src.cpp/alox.unittests/ut_alox_log_domains.cpp                      \
            ../../../../src.cpp/alox.unittests/ut_alox_logger.cpp                           \
            ../../../../src.cpp/alox.unittests/ut_alox_log_rel.cpp                          \
            ../../../../src.cpp/alox.unittests/ut_alox_log_scopes.cpp                       \
            ../../../../src.cpp/alox.unittests/ut_alox_log_scopes_helper.cpp                \
            ../../../../src.cpp/alox.unittests/ut_alox_log_scopes_helper_sub2.cpp           \
            ../../../../src.cpp/alox.unittests/ut_alox_log_scopes.hpp                       \
            ../../../../src.cpp/alox.unittests/ut_alox_lox.cpp                              \
            ../../../../src.cpp/alox.unittests/ut_dox_manual.cpp                            \
            ../../../../src.cpp/alox.unittests/ut_dox_tutorial.cpp                          \
            ../../../../src.cpp/alox.unittests/ut_dox_tutorial_minimum.cpp                  \


unix:!macx: LIBS+= -L$$PWD/../../_builds_/ide.cpp.qtcreator/QTC_ALox_SLib-Desktop-Debug/ -lQTC_ALox_SLib
DEPENDPATH+=         $$PWD/../../_builds_/ide.cpp.qtcreator/QTC_ALox_SLib-Desktop-Debug


unix:!macx: LIBS += -lgtest
