# #################################################################################################
#  QMake 'pro' file - ALox Samples
#
#  (c) 2016 A-Worx GmbH, Germany
#  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
# #################################################################################################

QT       -= core gui

TARGET = QTC_ALox_SLib
TEMPLATE = lib

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


ALIB_BASE_DIR=
DEPENDPATH+=  ../../../../src.cpp
INCLUDEPATH+= ../../../../src.cpp

#### ALib sources ###########################################################
SOURCES += ../../../../src.cpp/alib/alib.cpp                                \
           ../../../../src.cpp/alib/alib/debug.cpp                          \
           ../../../../src.cpp/alib/lang/enums.cpp                          \
           ../../../../src.cpp/alib/lang/memoryblocks.cpp                   \
           ../../../../src.cpp/alib/lang/report.cpp                         \
           ../../../../src.cpp/alib/lang/rtti.cpp                           \
           ../../../../src.cpp/alib/lang/singleton.cpp                      \
           ../../../../src.cpp/alib/boxing/boxing.cpp                       \
           ../../../../src.cpp/alib/boxing/ftypes.cpp                       \
           ../../../../src.cpp/alib/time/calendartime.cpp                   \
           ../../../../src.cpp/alib/time/ticks.cpp                          \
           ../../../../src.cpp/alib/time/tickspan.cpp                       \
           ../../../../src.cpp/alib/threads/smartlock.cpp                   \
           ../../../../src.cpp/alib/threads/thread.cpp                      \
           ../../../../src.cpp/alib/threads/threadlock.cpp                  \
           ../../../../src.cpp/alib/system/directory.cpp                    \
           ../../../../src.cpp/alib/system/environment.cpp                  \
           ../../../../src.cpp/alib/system/process.cpp                      \
           ../../../../src.cpp/alib/strings/applyformat.cpp                 \
           ../../../../src.cpp/alib/strings/astring.cpp                     \
           ../../../../src.cpp/alib/strings/autosizes.cpp                   \
           ../../../../src.cpp/alib/strings/cstring.cpp                     \
           ../../../../src.cpp/alib/strings/formatter.cpp                   \
           ../../../../src.cpp/alib/strings/formatterjavastyle.cpp          \
           ../../../../src.cpp/alib/strings/formatterpythonstyle.cpp        \
           ../../../../src.cpp/alib/strings/formatterstdimpl.cpp            \
           ../../../../src.cpp/alib/strings/numberformat.cpp                \
           ../../../../src.cpp/alib/strings/spaces.cpp                      \
           ../../../../src.cpp/alib/strings/string.cpp                      \
           ../../../../src.cpp/alib/strings/stringboxing.cpp                \
           ../../../../src.cpp/alib/strings/substring.cpp                   \
           ../../../../src.cpp/alib/strings/tokenizer.cpp                   \
           ../../../../src.cpp/alib/strings/tstring.cpp                     \
           ../../../../src.cpp/alib/config/configuration.cpp                \
           ../../../../src.cpp/alib/config/variable.cpp                     \
           ../../../../src.cpp/alib/config/plugins.cpp                      \
           ../../../../src.cpp/alib/config/inmemoryplugin.cpp               \
           ../../../../src.cpp/alib/config/inifile.cpp                      \
           ../../../../src.cpp/alib/compatibility/std_iostream.cpp          \
                                                                            \
#### ALox sources ###########################################################
           ../../../../src.cpp/alox/alox.cpp                                \
           ../../../../src.cpp/alox/aloxtypesandenums.cpp                   \
           ../../../../src.cpp/alox/log.cpp                                 \
           ../../../../src.cpp/alox/lox.cpp                                 \
           ../../../../src.cpp/alox/lox_getstate.cpp                        \
           ../../../../src.cpp/alox/core/domain.cpp                         \
           ../../../../src.cpp/alox/core/scopedump.cpp                      \
           ../../../../src.cpp/alox/core/scopeinfo.cpp                      \
           ../../../../src.cpp/alox/core/scopestore.cpp                     \
           ../../../../src.cpp/alox/core/textlogger/textlogger.cpp          \
           ../../../../src.cpp/alox/core/textlogger/plaintextlogger.cpp     \
           ../../../../src.cpp/alox/loggers/ansilogger.cpp                  \
           ../../../../src.cpp/alox/loggers/consolelogger.cpp               \
           ../../../../src.cpp/alox/loggers/textfilelogger.cpp              \
           ../../../../src.cpp/alox/loggers/vstudiologger.cpp               \
           ../../../../src.cpp/alox/loggers/windowsconsolelogger.cpp        \


#### ALib headers ###########################################################
HEADERS += ../../../../src.cpp/alib/alib.hpp                                \
           ../../../../src.cpp/alib/alib_distribution.hpp                   \
           ../../../../src.cpp/alib/alib/prepro.hpp                         \
           ../../../../src.cpp/alib/alib/debug.hpp                          \
           ../../../../src.cpp/alib/lang/enums.hpp                          \
           ../../../../src.cpp/alib/lang/memoryblocks.hpp                   \
           ../../../../src.cpp/alib/lang/ownable.hpp                        \
           ../../../../src.cpp/alib/lang/report.hpp                         \
           ../../../../src.cpp/alib/lang/rtti.hpp                           \
           ../../../../src.cpp/alib/lang/singleton.hpp                      \
           ../../../../src.cpp/alib/lang/types.hpp                          \
           ../../../../src.cpp/alib/boxing/box.hpp                          \
           ../../../../src.cpp/alib/boxing/boxer.hpp                        \
           ../../../../src.cpp/alib/boxing/boxes.hpp                        \
           ../../../../src.cpp/alib/boxing/boxing.hpp                       \
           ../../../../src.cpp/alib/boxing/interface.hpp                    \
           ../../../../src.cpp/alib/boxing/interface_builtin.hpp            \
           ../../../../src.cpp/alib/boxing/ftypes.hpp                       \
           ../../../../src.cpp/alib/time/calendartime.hpp                   \
           ../../../../src.cpp/alib/time/ticks.hpp                          \
           ../../../../src.cpp/alib/time/tickspan.hpp                       \
           ../../../../src.cpp/alib/time/tickwatch.hpp                      \
           ../../../../src.cpp/alib/threads/smartlock.hpp                   \
           ../../../../src.cpp/alib/threads/thread.hpp                      \
           ../../../../src.cpp/alib/threads/threadlock.hpp                  \
           ../../../../src.cpp/alib/threads/threadlocknr.hpp                \
           ../../../../src.cpp/alib/system/directory.hpp                    \
           ../../../../src.cpp/alib/system/environment.hpp                  \
           ../../../../src.cpp/alib/system/process.hpp                      \
           ../../../../src.cpp/alib/strings/applyformat.hpp                 \
           ../../../../src.cpp/alib/strings/applyto.hpp                     \
           ../../../../src.cpp/alib/strings/autosizes.hpp                   \
           ../../../../src.cpp/alib/strings/astring.hpp                     \
           ../../../../src.cpp/alib/strings/cstring.hpp                     \
           ../../../../src.cpp/alib/strings/formatter.hpp                   \
           ../../../../src.cpp/alib/strings/formatterjavastyle.hpp          \
           ../../../../src.cpp/alib/strings/formatterpythonstyle.hpp        \
           ../../../../src.cpp/alib/strings/formatterstdimpl.hpp            \
           ../../../../src.cpp/alib/strings/numberformat.hpp                \
           ../../../../src.cpp/alib/strings/preallocatedstring.hpp          \
           ../../../../src.cpp/alib/strings/string.hpp                      \
           ../../../../src.cpp/alib/strings/spaces.hpp                      \
           ../../../../src.cpp/alib/strings/string.hpp                      \
           ../../../../src.cpp/alib/strings/stringboxing.hpp                \
           ../../../../src.cpp/alib/strings/stringliteral.hpp               \
           ../../../../src.cpp/alib/strings/stringtuples.hpp                \
           ../../../../src.cpp/alib/strings/stringliteral.hpp               \
           ../../../../src.cpp/alib/strings/substring.hpp                   \
           ../../../../src.cpp/alib/strings/tokenizer.hpp                   \
           ../../../../src.cpp/alib/strings/formatter.hpp                   \
           ../../../../src.cpp/alib/strings/tstring.hpp                     \
           ../../../../src.cpp/alib/config/configuration.hpp                \
           ../../../../src.cpp/alib/config/variable.hpp                     \
           ../../../../src.cpp/alib/config/plugins.hpp                      \
           ../../../../src.cpp/alib/config/inmemoryplugin.hpp               \
           ../../../../src.cpp/alib/config/inifile.hpp                      \
           ../../../../src.cpp/alib/compatibility/std_iostream.hpp          \
           ../../../../src.cpp/alib/compatibility/std_string.hpp            \
           ../../../../src.cpp/alib/compatibility/qt.hpp                    \
                                                                            \
#### ALox sources ###########################################################
           ../../../../src.cpp/alox/alox.hpp                                \
           ../../../../src.cpp/alox/alox_console_loggers.hpp                \
           ../../../../src.cpp/alox/aloxtypesandenums.hpp                   \
           ../../../../src.cpp/alox/log.hpp                                 \
           ../../../../src.cpp/alox/lox.hpp                                 \
           ../../../../src.cpp/alox/internals/alox_macros.hpp               \
           ../../../../src.cpp/alox/internals/alox_symbols.hpp              \
           ../../../../src.cpp/alox/core/logger.hpp                         \
           ../../../../src.cpp/alox/core/domain.hpp                         \
           ../../../../src.cpp/alox/core/scopedump.hpp                      \
           ../../../../src.cpp/alox/core/scopeinfo.hpp                      \
           ../../../../src.cpp/alox/core/scopestore.hpp                     \
           ../../../../src.cpp/alox/core/textlogger/textlogger.hpp          \
           ../../../../src.cpp/alox/core/textlogger/plaintextlogger.hpp     \
           ../../../../src.cpp/alox/loggers/ansilogger.hpp                  \
           ../../../../src.cpp/alox/loggers/consolelogger.hpp               \
           ../../../../src.cpp/alox/loggers/textfilelogger.hpp              \
           ../../../../src.cpp/alox/loggers/vstudiologger.hpp               \
           ../../../../src.cpp/alox/loggers/windowsconsolelogger.hpp        \

#unix
#{
#    target.path = /usr/lib
#    INSTALLS += target
#}
#
