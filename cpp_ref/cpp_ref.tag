<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>alib.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/</path>
    <filename>alib_8hpp</filename>
    <includes id="symbols_8hpp" name="symbols.hpp" local="yes" imported="no">alib/core/symbols.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">alib/core/macros.hpp</includes>
    <includes id="enums_8hpp" name="enums.hpp" local="yes" imported="no">alib/core/enums.hpp</includes>
    <includes id="report_8hpp" name="report.hpp" local="yes" imported="no">alib/core/report.hpp</includes>
    <includes id="cstring_8hpp" name="cstring.hpp" local="yes" imported="no">alib/strings/cstring.hpp</includes>
    <includes id="string_8hpp" name="string.hpp" local="yes" imported="no">alib/strings/string.hpp</includes>
    <includes id="tstring_8hpp" name="tstring.hpp" local="yes" imported="no">alib/strings/tstring.hpp</includes>
    <includes id="stringliteral_8hpp" name="stringliteral.hpp" local="yes" imported="no">alib/strings/stringliteral.hpp</includes>
    <includes id="astring_8hpp" name="astring.hpp" local="yes" imported="no">alib/strings/astring.hpp</includes>
    <includes id="preallocatedstring_8hpp" name="preallocatedstring.hpp" local="yes" imported="no">alib/strings/preallocatedstring.hpp</includes>
    <includes id="applyto_8hpp" name="applyto.hpp" local="yes" imported="no">alib/strings/applyto.hpp</includes>
    <includes id="applyformat_8hpp" name="applyformat.hpp" local="yes" imported="no">alib/strings/applyformat.hpp</includes>
    <class kind="class">aworx::lib::ALIB</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
    <namespace>aworx::lib::enums</namespace>
    <namespace>aworx::lib::threads</namespace>
    <member kind="typedef">
      <type>aworx::lib::ALIB</type>
      <name>ALIB</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afc2895fe34753aa1cd88ed8845fbd88b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ReadBoolean</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>adb04d5102fc162a8ac01ef0999b761e4</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Case</type>
      <name>ReadCase</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a3aef0064d7182c495b6a683dd61cb3f4</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Inclusion</type>
      <name>ReadInclusion</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a691ce2d51651ae6a8294e76944d30416</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>alox.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>alox_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="alox__symbols_8hpp" name="alox_symbols.hpp" local="yes" imported="no">internals/alox_symbols.hpp</includes>
    <includes id="alox__macros_8hpp" name="alox_macros.hpp" local="yes" imported="no">internals/alox_macros.hpp</includes>
    <includes id="aloxtypesandenums_8hpp" name="aloxtypesandenums.hpp" local="yes" imported="no">aloxtypesandenums.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">log.hpp</includes>
    <includes id="lox_8hpp" name="lox.hpp" local="yes" imported="no">lox.hpp</includes>
    <class kind="class">aworx::lox::ALox</class>
    <class kind="class">aworx::lox::ALoxReportWriter</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_API</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga2cde43a12bd2be40baa4896e409d642c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::ALox</type>
      <name>ALox</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4d5353279fde6a5d6e5b1c8e776abf66</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>alox_console_loggers.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>alox__console__loggers_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="consolelogger_8hpp" name="consolelogger.hpp" local="yes" imported="no">alox/loggers/consolelogger.hpp</includes>
    <includes id="ansilogger_8hpp" name="ansilogger.hpp" local="yes" imported="no">alox/loggers/ansilogger.hpp</includes>
    <includes id="vstudiologger_8hpp" name="vstudiologger.hpp" local="yes" imported="no">alox/loggers/vstudiologger.hpp</includes>
    <includes id="windowsconsolelogger_8hpp" name="windowsconsolelogger.hpp" local="yes" imported="no">alox/loggers/windowsconsolelogger.hpp</includes>
  </compound>
  <compound kind="file">
    <name>alox_macros.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/internals/</path>
    <filename>alox__macros_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>LOG_ACQUIRE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga105a9f44250c23d6bb37df63aa9d9cbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_AddDebugLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaa891e8485ea970f574971c6afd851218</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Assert</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga2797c2e9f997606c3c786fa68720ac71</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_ClearSourcePathTrimRules</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaff8f037b778ce73b40e0c7a0506a8718</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Entry</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga9ac05a63013c784625c66685ad51aff3</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Error</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga8d8e6df0e755763bd471751235199baf</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_GetLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga07ed02a33090774d44b0a9eba642f362</anchor>
      <arglist>(identifier, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_If</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga7a1af9531448e3c6da1027b193e3b01b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Info</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaed4877ef3a04a6eb1ec1d4fba8305d75</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_LogConfig</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga1bac07b7ec3ca3616c301f171e9e73d9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga71f7449b6ad8bbd0ba22f897d7338a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_MapThreadName</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad01526d3f277fab96faf18695d25cb7e</anchor>
      <arglist>(threadName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Once</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga68c8af8941a64be4f6e075ab31c6c05b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Prune</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga7dbb7427d18d49e2dd87d5f2d2036e0b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_RELEASE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga0d5795316ecfccc7b40b43c01bf62b0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveDebugLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac5d4bbea354fbabbebb7703995c3399d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga4a08a7a5c5e794a34d7d05f4d35689e4</anchor>
      <arglist>(logger)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveThreadDomain</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gafc93873c04ed08e842109543d142fb60</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Retrieve</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga233db1e86b0cf457b550f74b58d69926</anchor>
      <arglist>(data,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetDomain</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac4a4311460b712126253fce7304ac6f4</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetDomainSubstitutionRule</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga619af6c6682bc920e038b0fe006c49be</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetPrefix</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga4186c23d7999be11f0e5017d254a306c</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetSourcePathTrimRule</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac96dec2672c7ae4e722cae3b12eaf3fd</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetStartTime</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga14bcc9217818e50b7fe5028398f11e8d</anchor>
      <arglist>(time, loggerName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetVerbosity</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad5444af82c2a3640a1c456940b8c3b8f</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Store</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga9c1ca580a86c5c6a0653146b0bb9cb38</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Verbose</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga975fbf7e95ed6506992f9714627202d0</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Warning</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaa9822f0eda4cc7e9c3f3e99d6238f2aa</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_ACQUIRE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga9ac629621d8152810e41e19931c990a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Assert</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga4d9961312aab181a28b21724c3809184</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_ClearSourcePathTrimRules</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga1689da460f8040489689b3f45cf1e6b2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Entry</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga3ee12da39c3574baf4fb03f7f323c886</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Error</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga5fa12e4bc99fd2ebed4fe90729f54a03</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_GetLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga8536e68dcdee27e1d3463687d42ee6ed</anchor>
      <arglist>(identifier, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_If</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga31e9c5302ccb2af7285d9e17a46aac2b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Info</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga28233c29442a3ae8996d32b5078537d9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_LogConfig</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga0578fb3bfeb63ea05db9c34bc1a0d07d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga1f170b96d3ead37b7f530134e64bf121</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_MapThreadName</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga089dc860d3f28c5cf30b661f2877462a</anchor>
      <arglist>(threadName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Once</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga03e5f8a0b134f709f130a4f93b2f8ab2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Prune</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga04158d8131eba14e98f93e433b6325d2</anchor>
      <arglist>(releaseLogCode)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_RELEASE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga2ef98e816bdf36da37bb9bddbdfd635f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_RemoveLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga321e65d2004cef126220b042fc95e03b</anchor>
      <arglist>(logger)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_RemoveThreadDomain</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga5af8171356c0b231483221d0b3e534c1</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Retrieve</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga21ac85d6bd6b297b92b707b6362f52df</anchor>
      <arglist>(data,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetDomain</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga7e1bc971e6cd3b071fbc928a7d46fae9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetDomainSubstitutionRule</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gab66ecad871e42c6779e9f2bb62921be3</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetPrefix</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga0f4d320a3b393e1e6eba353f567dec4d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetSourcePathTrimRule</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga26b42492cafe7bc093cd810facddeb6b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetStartTime</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga2c91f19bc972dbacc137e8c4c88ee25c</anchor>
      <arglist>(time, loggerName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetVerbosity</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga58d12e520c215bfc22c8da42777d567b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Store</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaa8e5c76201f2ac838ef643377641f2a6</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Verbose</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gacbfc03392b8a4f79d0bcb46bc2825d31</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Warning</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaf2a9706a6b6c48b69cc10ae1d65d9379</anchor>
      <arglist>(...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>alox_symbols.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/internals/</path>
    <filename>alox__symbols_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga2c6ba32fb7e34be7cee2100578b84a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_CI</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga392381bb9caea53c133ce68c32cee4e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga4d0c70512b17f1dd4fa3556f79dd2689</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aloxtypesandenums.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>aloxtypesandenums_8hpp</filename>
    <class kind="class">aworx::lox::ESC</class>
    <class kind="struct">aworx::lox::LogData</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <member kind="typedef">
      <type>aworx::lox::ESC</type>
      <name>ESC</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a41196e8ca29644376437095a102ad9ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::LogData</type>
      <name>LogData</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a07d961a72c3ccbe33993cdeb56dab52e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Scope</type>
      <name>Scope</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aef58f56e96f194bf0b5f765175f6ebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Verbosity</type>
      <name>Verbosity</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aa10bcb350ba5320cadb5dff6b8e2da6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Scope</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a4cc6684df7b4a92b1dec6fce3264fac8">Global</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a1ee3f312b05c55202500569aadfc8d9b">ThreadOuter</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6aac70412e939d72a9234cdebb1af5867b">Path</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a1351017ac6423911223bc19a8cb7c653">Filename</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a4c3880bb027f159e801041b1021e88e8">Method</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6ae46b159c990fae9e712309bdb4d7b7c4">ThreadInner</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Verbosity</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>abf3be10d03894afb391f3a2935e3b313</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313ad4a9fa383ab700c5bdd6f31cf7df0faf">Verbose</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a4059b0251f66a18cb56f544728796875">Info</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a0eaadb4fcb48a0a0ed7bc9868be9fbaa">Warning</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313ad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
    </member>
    <member kind="function">
      <type>Verbosity</type>
      <name>ReadVerbosity</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>a198631ef025eac410d87373b39c7280f</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>ade21849436cde3af69157368d5e5a27e</anchor>
      <arglist>(Verbosity verbosity, int priority, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>a0883c50f69bfa5d7b121a59ba14d8464</anchor>
      <arglist>(Scope scope, int pathLevel, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>ToStringX</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>abfd92f16f9c0e36069f30ffa03a5d96d</anchor>
      <arglist>(Verbosity verbosity)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ansilogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>ansilogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="textlogger_8hpp" name="textlogger.hpp" local="yes" imported="no">alox/core/textlogger/textlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::AnsiConsoleLogger</class>
    <class kind="class">aworx::lox::loggers::AnsiLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::AnsiConsoleLogger</type>
      <name>AnsiConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a1ea18f3cfd0faa27d99ecc1c9532b445</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::AnsiLogger</type>
      <name>AnsiLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afbcb9cbc8853ce81a9d690e2a8923889</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>applyformat.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>applyformat_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::Format::Double</class>
    <class kind="class">aworx::lib::strings::Format::Field</class>
    <class kind="class">aworx::lib::strings::Format</class>
    <class kind="class">aworx::lib::strings::Format::Int32</class>
    <class kind="class">aworx::lib::strings::Format::Int64</class>
    <class kind="class">aworx::lib::strings::Format::Tab</class>
    <class kind="class">aworx::lib::strings::Format::UInt32</class>
    <class kind="class">aworx::lib::strings::Format::UInt64</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::Format</type>
      <name>Format</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aed5a5fab6b4a0c81a5a231f6d0379d41</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a17dfe1060a698974265db6b780c709fa</anchor>
      <arglist>(AString &amp;target, const Format::Tab &amp;tab)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a5874b01f193017660c4748a8a5fc1fde</anchor>
      <arglist>(AString &amp;target, const Format::Field &amp;field)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ae7cf6b7c301dca2c1b7efd7d9cf3fd1a</anchor>
      <arglist>(AString &amp;target, const Format::Int32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aff08105164bdbc38149bdea8526b0fe1</anchor>
      <arglist>(AString &amp;target, int8_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a4e06f646e714741651dbcc70c18f7277</anchor>
      <arglist>(AString &amp;target, uint8_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aa619192ac17ef191b23c4a62c98c6b0e</anchor>
      <arglist>(AString &amp;target, int16_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a182592417855344b2161faa31b88745e</anchor>
      <arglist>(AString &amp;target, uint16_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3ebd14cfce8c2eda7ed1dcbca395a33c</anchor>
      <arglist>(AString &amp;target, int32_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af234ce05458a46a76cc5a593041895b3</anchor>
      <arglist>(AString &amp;target, const Format::UInt32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aff0544080e363cd67465fc12539c06c1</anchor>
      <arglist>(AString &amp;target, uint32_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a68ce4d16395dd82846afb86689c512df</anchor>
      <arglist>(AString &amp;target, const Format::Int64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0c48317b4a34060b56d3e5c581e509e1</anchor>
      <arglist>(AString &amp;target, int64_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0683fedae1a6920e13588d534152f4da</anchor>
      <arglist>(AString &amp;target, const Format::UInt64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ac2e8c17181156fa7a4a2f3cb94dc15a3</anchor>
      <arglist>(AString &amp;target, uint64_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad9a951e16433abb2461bca80d0c2ad8e</anchor>
      <arglist>(AString &amp;target, const Format::Double &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abc006ddec9bb08e63d7e764a785e715b</anchor>
      <arglist>(AString &amp;target, double &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aef0aaba9060d3dd6bcb3914d2b7cc538</anchor>
      <arglist>(AString &amp;target, float &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>applyto.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>applyto_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="struct">aworx::lib::strings::IsApplicable</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DECLARATION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga7ef8eaf71cad1c7be73ef8e61dc65177</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DEFINITION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga87261d3411f0175bbc3efab49720023f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_INLINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf3673497e1c2e5436ad2b369c135658f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aa8fb47b820e77796083d2c3eb13d56b2</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aaaeb23f90707241659667c910e61bbe9</anchor>
      <arglist>(AString &amp;target, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a51d3c0fe2a4125c45c804c1fb1509b3e</anchor>
      <arglist>(AString &amp;target, const wchar_t *src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af0bcfa090927eb989e55774a396d73fd</anchor>
      <arglist>(AString &amp;target, bool &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a70a7ab6f429b5e5e3361d9758b6807d9</anchor>
      <arglist>(AString &amp;target, enums::Switch &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a99617b411c1009b148f37391abf0d789</anchor>
      <arglist>(AString &amp;target, enums::Case &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9fad3de9eb89a67a1bc095c3fd5ffc56</anchor>
      <arglist>(AString &amp;target, enums::Alignment &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a829332713d7be0bbde5b1862e1ec837b</anchor>
      <arglist>(AString &amp;target, enums::Inclusion &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a380a2e715c58148cf81b7e31c4ef1bd9</anchor>
      <arglist>(AString &amp;target, enums::CurrentData &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af43cf0906d4f7d8f1b6ed6dd6454d361</anchor>
      <arglist>(AString &amp;target, enums::Safeness &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad795b43f0a24b4c0e6147e223e051546</anchor>
      <arglist>(AString &amp;target, enums::Responsibility &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0dcce3ad139fe6f9c313fdfe9be5fed2</anchor>
      <arglist>(AString &amp;target, enums::Timezone &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3b71964dfcfc46db8bfe4369a60b48c3</anchor>
      <arglist>(AString &amp;target, enums::LockMode &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a59c043f8dd398835f7266e1bb2c630bf</anchor>
      <arglist>(AString &amp;target, enums::Whitespaces &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abe6407ebad387df4da89aeed389e712e</anchor>
      <arglist>(AString &amp;target, enums::Create &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a58b0f925b58b64d308bc299f3fe25281</anchor>
      <arglist>(AString &amp;target, enums::Propagation &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo_NC</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abcd4a1d202f1c13b510ec14cd55d3a7a</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DECLARATION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga7ef8eaf71cad1c7be73ef8e61dc65177</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DEFINITION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga87261d3411f0175bbc3efab49720023f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_INLINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf3673497e1c2e5436ad2b369c135658f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>astring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>astring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::AString</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; AString &gt;</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::AString</type>
      <name>AString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a51ace28d988aa0a7ab391f6aaec35f60</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aa8fb47b820e77796083d2c3eb13d56b2</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo_NC</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abcd4a1d202f1c13b510ec14cd55d3a7a</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>configuration.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/config/</path>
    <filename>configuration_8hpp</filename>
    <includes id="threadlock_8hpp" name="threadlock.hpp" local="yes" imported="no">alib/threads/threadlock.hpp</includes>
    <includes id="numberformat_8hpp" name="numberformat.hpp" local="yes" imported="no">alib/strings/numberformat.hpp</includes>
    <includes id="plugins_8hpp" name="plugins.hpp" local="yes" imported="no">alib/config/plugins.hpp</includes>
    <class kind="class">aworx::lib::config::Configuration</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
    <member kind="typedef">
      <type>aworx::lib::config::Configuration</type>
      <name>Configuration</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a9b321d2f72b975b304aa678e20344e7a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>consolelogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>consolelogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="plaintextlogger_8hpp" name="plaintextlogger.hpp" local="yes" imported="no">alox/core/textlogger/plaintextlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::ConsoleLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::ConsoleLogger</type>
      <name>ConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acfbbfc11d98646c37dbf27e3ede11644</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cstring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>cstring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::CString</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>directory.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/system/</path>
    <filename>directory_8hpp</filename>
    <class kind="class">aworx::lib::system::Directory</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::system</namespace>
    <member kind="typedef">
      <type>aworx::lib::system::Directory</type>
      <name>Directory</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae59166dff4149598acd5f636fe6760d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr char</type>
      <name>PathSeparator</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a262e7ce267358080f085b5a3f42e3a67</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>domain.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>domain_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <class kind="class">aworx::lox::core::Domain</class>
    <class kind="struct">aworx::lox::core::Domain::LoggerData</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
  </compound>
  <compound kind="file">
    <name>enums.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>enums_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::enums</namespace>
    <member kind="typedef">
      <type>aworx::lib::enums::Alignment</type>
      <name>Alignment</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a96dde4be24b9217d6bef30b22d7dfd4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Case</type>
      <name>Case</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac497730bb253c7efcfee90f6de02a0ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::ContainerOp</type>
      <name>ContainerOp</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a79b40b1cf65e889763d9ac0858268172</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Create</type>
      <name>Create</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae9b7ef57f8fb67372f77ff485e3087d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::CurrentData</type>
      <name>CurrentData</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8cd9fd65cae399a824854fa2ea3b8bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Inclusion</type>
      <name>Inclusion</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af3771c700d4232fb5b8a10510e088274</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::LockMode</type>
      <name>LockMode</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acae7a6e21dc6155b5f1b7c932fb8aa34</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Phase</type>
      <name>Phase</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac87fae76a49419f75db6b44011acc407</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Propagation</type>
      <name>Propagation</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a6becd7c5957b9924c08b78079a67c5b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Responsibility</type>
      <name>Responsibility</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad8c1565886f17d3b3262d8454ae546de</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Result</type>
      <name>Result</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0bb37c2c22c2eb85510445d1b9d11f19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Safeness</type>
      <name>Safeness</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae44933ed0bc5c2462dce430a034dd6b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Switch</type>
      <name>Switch</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abbc3fd675117881e7c7aebcd1058ad03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Timezone</type>
      <name>Timezone</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5d6766c28e92b7f6ec8f96383455acdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Whitespaces</type>
      <name>Whitespaces</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0c07eb477a798a2088b4619390c54e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Alignment</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>acdfaca60ec19c0265bac2692d7982726</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a945d5e233cf7d6240f6b783b36a374ff">Left</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a92b09c7c48c520c3c55e497875da437c">Right</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a4f1f6016fc9f3f2353c0cc7c67b292bd">Center</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Case</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ab9aab17a5e54a8bae6915bc24db13a17</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17a8f21fcdc233ba4078679ca628453d06b">Sensitive</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17afd038fc7f319e48f3115d92bf5bdbef9">Ignore</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ContainerOp</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>af6d9cc1e6686eca6e60d57d959cf57fb</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fbaa458be0f08b7e4ff3c0f633c100176c0">Insert</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba1063e38cb53d94d386f21227fcd84717">Remove</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fbac55582518cba2c464f29f5bae1c68def">Get</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba1d5c1a7fde77e84c993d6fea61f88c2a">GetCreate</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba686e697538050e4664636337cc3b834f">Create</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Create</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a55781bd0c78c4e5d47ce433f4eeeee85</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a6e7b34fa59e1bd229b207892956dc41c">Never</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a44c32ea9ad0b836b68c25fdb717fa4b7">IfNotExistent</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CurrentData</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9345007d67faa05253932092d54d10d4</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4adc30bc0c7914db5918da4263fce93ad2">Clear</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Inclusion</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a217539925b78b2eed40ae7817d5bee52</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52af4d72a64acd8929c0cc9ed96a7a336cc">Include</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52a843f2812f595e7ec7c5036e89fde02d6">Exclude</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>LockMode</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a00fc859257c8f09ff9198dde28121961</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a556c3dd912453ae5cb3095cd5054e6f4">Recursive</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a67b491789a29d0c717a2b4ebe369a936">SingleLocks</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Phase</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ae1c5184dc404edf057ed537bcfddef84</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a1a06729125544cab7cee73195fc044f0">Begin</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a87557f11575c0ad78e4e28abedc13b6e">End</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Propagation</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>aeae0c2d4659a32ef54bd221d1a3da4e6</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6aa9857b4deb35c57d5753f94fa00a028e">ToDescendants</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Responsibility</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ab5305b978950ba3946cf79a4bccbf7af</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab5305b978950ba3946cf79a4bccbf7afa2540530a938da82bfe62957f4aff599b">KeepWithSender</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab5305b978950ba3946cf79a4bccbf7afa6950810f0d2bba97a6f710c7b965b84e">Transfer</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Result</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a28287671eaf7406afd604bd055ba4066</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066ae0aa021e21dddbd6d8cecec71e9cf564">OK</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066aea1776502570f06ddc0569c079cb9ee2">FileExists</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066a5d0744802b24f44a161d350c25d76c7b">InvalidPath</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Safeness</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a8c800527afe0a8a6c71ae4cceda6bf9d</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dac6eea0560cd6f377e78dff2c85cc9122">Safe</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dad3d57868b6ff9839eff631d2cc8acbce">Unsafe</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Switch</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9f3c28a2cb05bdcc618b542e49bfda3f</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fa521c36a31c2762741cf0f8890cbe05e3">On</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Timezone</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9b1d8f31e178e17a8fef3a9e94bc4b2c</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9b1d8f31e178e17a8fef3a9e94bc4b2ca509820290d57f333403f490dde7316f4">Local</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9b1d8f31e178e17a8fef3a9e94bc4b2ca9234324ddf6b4176b57d803a925b7961">UTC</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Whitespaces</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ad4a46f9fb632511f6be7c53e05f330f7</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a1fc5884251ca9f20a4fd5f79a458f94f">Trim</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
    </member>
  </compound>
  <compound kind="file">
    <name>inifile.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/config/</path>
    <filename>inifile_8hpp</filename>
    <includes id="substring_8hpp" name="substring.hpp" local="yes" imported="no">alib/strings/substring.hpp</includes>
    <includes id="configuration_8hpp" name="configuration.hpp" local="yes" imported="no">alib/config/configuration.hpp</includes>
    <class kind="class">aworx::lib::config::IniFile</class>
    <class kind="class">aworx::lib::config::IniFile::Section</class>
    <class kind="class">aworx::lib::config::IniFile::Variable</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::config::IniFile</type>
      <name>IniFile</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aef31dd55ee6403c15d9ba93325d3333d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>log.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>log_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <class kind="class">aworx::lox::Log</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
    <member kind="typedef">
      <type>aworx::lox::Log</type>
      <name>Log</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5d8a9ca518e5abc7446b6a753e2b7ae6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>logger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>logger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <class kind="struct">aworx::lib::strings::IsApplicable&lt; const lox::core::Logger &amp; &gt;</class>
    <class kind="struct">aworx::lox::core::Logable</class>
    <class kind="class">aworx::lox::core::Logger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <member kind="typedef">
      <type>std::vector&lt; core::Logable * &gt;</type>
      <name>Logables</name>
      <anchorfile>namespaceaworx_1_1lox_1_1core.html</anchorfile>
      <anchor>a89b734aa261b747d9edc7a459bfc9db8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::core::Logger</type>
      <name>Logger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8ec4a1b5f5786befe04b9f08d5417cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo&lt; const lox::core::Logger &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9293db3b9b449a46d07d91e1b8964183</anchor>
      <arglist>(AString &amp;target, const lox::core::Logger &amp;logger)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>lox.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>lox_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="threadlock_8hpp" name="threadlock.hpp" local="yes" imported="no">alib/threads/threadlock.hpp</includes>
    <includes id="scopeinfo_8hpp" name="scopeinfo.hpp" local="yes" imported="no">alox/core/scopeinfo.hpp</includes>
    <includes id="logger_8hpp" name="logger.hpp" local="yes" imported="no">alox/core/logger.hpp</includes>
    <includes id="domain_8hpp" name="domain.hpp" local="yes" imported="no">alox/core/domain.hpp</includes>
    <includes id="scopestore_8hpp" name="scopestore.hpp" local="yes" imported="no">alox/core/scopestore.hpp</includes>
    <class kind="struct">aworx::lox::Lox::DomainSubstitutionRule</class>
    <class kind="class">aworx::lox::Lox</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
    <member kind="typedef">
      <type>aworx::lox::Lox</type>
      <name>Lox</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abf1258bbd9cf9772a1559f4ceb37fde4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>macros.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>macros_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGIFY</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3f61373916523c0c97327c83b2d6132e</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_CONCAT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf5375d121ff32a60c641c7e3a4b7810e</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_API</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga74fe706f3101d8e1e21555f772da2849</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab1836c6de18fd089b123e40e22472f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac17f8e410ff33bbb690c0608d12ba5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga8460b7062323107819d75e7001451cc4</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabd7b7f6d6244265e96a13ea98bee76b9</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabdd5780e186ebbd62960d7ca9673dff1</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaecdb7875b059e8d10edc15ff30f22b54</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga259ac181b20784b8dfa4cd72c191da4c</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga6d09217171c3a303e6b91eba62833193</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gafeaac7eedb1d9a90091356b6c68934cb</anchor>
      <arglist>(cond)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga458a325506658361be4a4f8cf2c1d50e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf6ee54a2e2b00632832c094c3683075e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1d9b0a700c59c2e87bc2935d6a434db9</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3cafe9da29ad24d8d8a7997556dde3be</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaa7e7955d3374820a4b3a2a65488c6aca</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_NOT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac3c19147e6144f75f38dc598e8ffd3e7</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_GREATER_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab2d2c9ba9eab04d9b95b78340c582a21</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_LESS_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab9a9f80902169489b72c156e4317419e</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac506942a02a0be3af76a71116e8ce645</anchor>
      <arglist>(identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaea25b327ef9d2c90aad05f5bef07bd97</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga30e363647f8ea56f0af8e834768548bc</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabfca7dd3cf5d8186e47c2bcf11343679</anchor>
      <arglist>(libdecl,identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DEFINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga671251ff77d829ce136055ef6a415ca1</anchor>
      <arglist>(className, identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga0627077cd7f96033d848dc29f2875a5d</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga5558b6404fddb317efd26bf8a9665f40</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga352937357f43d7f9e249427f7f47556a</anchor>
      <arglist>(msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaec0ad3f2704be43a1dfa4101f700821c</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF_NOT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga532a206ad57a4b4f4b1a1e110e8b0cd6</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_CODE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gad2c895310139b3c6988218f2d71896ee</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OWN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga428418e97842561b5fa5118c120954a9</anchor>
      <arglist>(ownable)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGIFY</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3f61373916523c0c97327c83b2d6132e</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_CONCAT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf5375d121ff32a60c641c7e3a4b7810e</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_API</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga74fe706f3101d8e1e21555f772da2849</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab1836c6de18fd089b123e40e22472f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac17f8e410ff33bbb690c0608d12ba5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga8460b7062323107819d75e7001451cc4</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabd7b7f6d6244265e96a13ea98bee76b9</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabdd5780e186ebbd62960d7ca9673dff1</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaecdb7875b059e8d10edc15ff30f22b54</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga259ac181b20784b8dfa4cd72c191da4c</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga6d09217171c3a303e6b91eba62833193</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gafeaac7eedb1d9a90091356b6c68934cb</anchor>
      <arglist>(cond)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga458a325506658361be4a4f8cf2c1d50e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf6ee54a2e2b00632832c094c3683075e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1d9b0a700c59c2e87bc2935d6a434db9</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3cafe9da29ad24d8d8a7997556dde3be</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaa7e7955d3374820a4b3a2a65488c6aca</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_NOT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac3c19147e6144f75f38dc598e8ffd3e7</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_GREATER_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab2d2c9ba9eab04d9b95b78340c582a21</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_LESS_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab9a9f80902169489b72c156e4317419e</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac506942a02a0be3af76a71116e8ce645</anchor>
      <arglist>(identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaea25b327ef9d2c90aad05f5bef07bd97</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga30e363647f8ea56f0af8e834768548bc</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabfca7dd3cf5d8186e47c2bcf11343679</anchor>
      <arglist>(libdecl,identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DEFINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga671251ff77d829ce136055ef6a415ca1</anchor>
      <arglist>(className, identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga0627077cd7f96033d848dc29f2875a5d</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga5558b6404fddb317efd26bf8a9665f40</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga352937357f43d7f9e249427f7f47556a</anchor>
      <arglist>(msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaec0ad3f2704be43a1dfa4101f700821c</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF_NOT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga532a206ad57a4b4f4b1a1e110e8b0cd6</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_CODE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gad2c895310139b3c6988218f2d71896ee</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OWN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga428418e97842561b5fa5118c120954a9</anchor>
      <arglist>(ownable)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>memorylogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>memorylogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="plaintextlogger_8hpp" name="plaintextlogger.hpp" local="yes" imported="no">alox/core/textlogger/plaintextlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::MemoryLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::MemoryLogger</type>
      <name>MemoryLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aff4e02a238ba03a98be3dd17d783f336</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>numberformat.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>numberformat_8hpp</filename>
    <class kind="class">aworx::lib::strings::NumberFormat</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::NumberFormat</type>
      <name>NumberFormat</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4105ad142b7282bab44c0f051d36e350</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ownable.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>ownable_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::Ownable</class>
    <class kind="struct">aworx::lib::Owner</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
  </compound>
  <compound kind="file">
    <name>pathmap.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/containers/</path>
    <filename>pathmap_8hpp</filename>
    <includes id="substring_8hpp" name="substring.hpp" local="yes" imported="no">alib/strings/substring.hpp</includes>
    <class kind="class">aworx::lib::containers::PathMap::Iterator</class>
    <class kind="struct">aworx::lib::containers::PathMap::Iterator::NodeAndChild</class>
    <class kind="class">aworx::lib::containers::PathMap</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::containers</namespace>
    <member kind="typedef">
      <type>aworx::lib::containers::PathMap&lt; StoreT &gt;</type>
      <name>PathMap</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a40dd35c549af4dcf094f486d3f2dca1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>PathMap&lt; StoreT &gt;::Iterator</type>
      <name>begin</name>
      <anchorfile>namespaceaworx_1_1lib_1_1containers.html</anchorfile>
      <anchor>a3c9cd89161562d9d1c346f6f82666108</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; &amp;pathMap)</arglist>
    </member>
    <member kind="function">
      <type>PathMap&lt; StoreT &gt;::Iterator</type>
      <name>end</name>
      <anchorfile>namespaceaworx_1_1lib_1_1containers.html</anchorfile>
      <anchor>a493642c7093a3913fb626ebd25eb4c7d</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; &amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>plaintextlogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/textlogger/</path>
    <filename>plaintextlogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="textlogger_8hpp" name="textlogger.hpp" local="yes" imported="no">alox/core/textlogger/textlogger.hpp</includes>
    <class kind="class">aworx::lox::core::textlogger::PlainTextLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
  </compound>
  <compound kind="file">
    <name>plugins.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/config/</path>
    <filename>plugins_8hpp</filename>
    <class kind="class">aworx::lib::config::CommandLinePlugIn</class>
    <class kind="class">aworx::lib::config::ConfigurationPlugIn</class>
    <class kind="class">aworx::lib::config::EnvironmentPlugIn</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
  </compound>
  <compound kind="file">
    <name>preallocatedstring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>preallocatedstring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; PreallocatedString&lt; TCapacity &gt; &gt;</class>
    <class kind="class">aworx::lib::strings::PreallocatedString</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; TCapacity &gt;</type>
      <name>PAString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a10e9458c58956ec05a324232fc1cc9e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 128 &gt;</type>
      <name>String128</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a2841f1443c3b2f3d6066d5774cf69dbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 16 &gt;</type>
      <name>String16</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a148a217c34a72b4360462205858b8f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 1024 &gt;</type>
      <name>String1K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a82395a8f3fac47787ebe8749679a2796</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 256 &gt;</type>
      <name>String256</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a152f787b6dac47dd3f94ae5ebf1ece53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 2048 &gt;</type>
      <name>String2K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a76f69ad445caecfbf03351c884637b09</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 32 &gt;</type>
      <name>String32</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a221752691fb92bcd592c045d6c368289</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 4096 &gt;</type>
      <name>String4K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a772f06f37ace5e2b2eb8cafc0c859c44</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 512 &gt;</type>
      <name>String512</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af634b7550d8a316ce3cf3fb6f9e86079</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 64 &gt;</type>
      <name>String64</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac2fdc487456a994238ba4284b3859c41</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 8 &gt;</type>
      <name>String8</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab35696c2e8d79567a528a4b6da788eb3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>process.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/system/</path>
    <filename>process_8hpp</filename>
    <class kind="class">aworx::lib::system::ProcessInfo</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::system</namespace>
    <member kind="typedef">
      <type>aworx::lib::system::ProcessInfo</type>
      <name>ProcessInfo</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8644368b56cf61a16e37300584a1d4e2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>report.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>report_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::ConsoleReportWriter</class>
    <class kind="class">aworx::lib::Report::Message</class>
    <class kind="class">aworx::lib::Report</class>
    <class kind="class">aworx::lib::ReportWriter</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lib::threads</namespace>
  </compound>
  <compound kind="file">
    <name>scopedump.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>scopedump_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="scopestore_8hpp" name="scopestore.hpp" local="yes" imported="no">scopestore.hpp</includes>
    <class kind="class">aworx::lox::core::ScopeDump</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
  </compound>
  <compound kind="file">
    <name>scopeinfo.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>scopeinfo_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="ticks_8hpp" name="ticks.hpp" local="yes" imported="no">alib/time/ticks.hpp</includes>
    <includes id="thread_8hpp" name="thread.hpp" local="yes" imported="no">thread.hpp</includes>
    <includes id="directory_8hpp" name="directory.hpp" local="yes" imported="no">alib/system/directory.hpp</includes>
    <class kind="class">aworx::lox::core::ScopeInfo</class>
    <class kind="struct">aworx::lox::core::ScopeInfo::SourceFile</class>
    <class kind="struct">aworx::lox::core::ScopeInfo::SourcePathTrimRule</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
  </compound>
  <compound kind="file">
    <name>scopestore.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>scopestore_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <class kind="class">aworx::lib::containers::PathMap</class>
    <class kind="class">aworx::lox::core::ScopeStore</class>
    <class kind="class">aworx::lox::core::ScopeStoreType</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::containers</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
  </compound>
  <compound kind="file">
    <name>std_iostream.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/compatibility/</path>
    <filename>std__iostream_8hpp</filename>
    <class kind="class">aworx::lib::strings::ReadLineFromIStream</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a26459c1c77708cf6f56a2419734d9978</anchor>
      <arglist>(AString &amp;target, const ReadLineFromIStream &amp;param)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7c480abd39fa10f40a8af566cf1f4dda</anchor>
      <arglist>(std::ostream &amp;stream, const String &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream *</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9a3fcc93b836b62a2ebbca22d3732520</anchor>
      <arglist>(std::ostream *stream, const String &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a357b7d2e804cb32ac765641afa415eee</anchor>
      <arglist>(std::istream &amp;stream, AString &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::istream *</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3b4a073d715b00201505dc87ffdcb73e</anchor>
      <arglist>(std::istream *stream, AString &amp;string)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>std_string.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/compatibility/</path>
    <filename>std__string_8hpp</filename>
    <class kind="struct">aworx::lib::strings::IsApplicable&lt; const std::string &amp; &gt;</class>
    <class kind="struct">aworx::lib::strings::ToStringDefined&lt; const std::string &amp; &gt;</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a46d2b8074d6fd76918018ca6704e7cfc</anchor>
      <arglist>(AString &amp;target, const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo_NC&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ac8de1e5cfd3f85418261ced125aed661</anchor>
      <arglist>(AString &amp;target, const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>acee8df0c9711c319807b3661f1046dfd</anchor>
      <arglist>(const String &amp;as, std::string &amp;target, int regionStart, int regionLength=CString::MaxLen, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a69456b076a8fce4982a9d3790796d424</anchor>
      <arglist>(const String &amp;as, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a039f938c7e403c09e0271e4f353123bf</anchor>
      <arglist>(const String &amp;as)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a8f1c5a17c57b3b54f2f46e58bef50487</anchor>
      <arglist>(const String &amp;as, std::string &amp;target, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToString&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a8d85e610e17c69e9ece8b558735519e0</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToString&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ae0fc15801fea6b54738ca715ed192cf0</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>string.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>string_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::String</class>
    <class kind="struct">aworx::lib::strings::ToStringDefined</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRING_DBG_CHK</name>
      <anchorfile>group__GrpALibStringsMacros.html</anchorfile>
      <anchor>gae7492253da37c76b118d446494f1f632</anchor>
      <arglist>(instance)</arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::String</type>
      <name>String</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad13481d84c6e592a41d07c64f747c95d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>TReturn</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7cfd45024bf9222b42febac98fdcc146</anchor>
      <arglist>(const TString)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr lib::strings::String</type>
      <name>EmptyString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a3372961a8fb9d30455267babb4e6c26c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr lib::strings::String</type>
      <name>NullString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab1ed6dcfbe4628dccefbdb5633b1bf01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>stringliteral.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>stringliteral_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::StringLiteral</class>
    <class kind="struct">aworx::lib::strings::TMPLiteral</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::StringLiteral&lt; TLength &gt;</type>
      <name>SLiteral</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af631a26bf70ad6d6143973fadf779747</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr lib::strings::StringLiteral&lt; 4 &gt;</type>
      <name>DefaultWhitespaces</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5feaaf6a8fb11e8ebbb0013ec9f27b01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr lib::strings::StringLiteral&lt; 1 &gt;</type>
      <name>NewLine</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aca82326cfe712c18f9adb9f560a28553</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>strings_namespace_documentation.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>strings__namespace__documentation_8hpp</filename>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>substring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>substring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::Substring</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>lib::strings::Substring</type>
      <name>Substring</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aade494154da29084f1e59cfa2f83a23b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>symbols.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>symbols_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>gac56d0d10d022f28ce6bacdc612b4a743</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_STRINGS</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>gae0e4a87e11482df5ecd72f6a2a648f05</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ECLIPSE_CDT</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga957b686ba8c86c9c305e6cbc6d1dcac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_FEAT_THREADS</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga1b908cb4e15b716440551455e0a5f138</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_GTEST</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga671a29c6b98b59e9db6149643dd2eb25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_QTCREATOR</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga8f48ad22225f9bc74fce02ae8013e3bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_VSTUDIO</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga54d417a77a33dc7266c3ed03e5b7e6f0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>system.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/system/</path>
    <filename>system_8hpp</filename>
    <class kind="class">aworx::lib::system::System</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::system</namespace>
    <member kind="typedef">
      <type>aworx::lib::system::System</type>
      <name>System</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aea0af9d6b00ede1a16d0af24fdaeebe0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>textfilelogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>textfilelogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="plaintextlogger_8hpp" name="plaintextlogger.hpp" local="yes" imported="no">alox/core/textlogger/plaintextlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::TextFileLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::TextFileLogger</type>
      <name>TextFileLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae64ac3b33c7c180e92559a869977fda0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>textlogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/textlogger/</path>
    <filename>textlogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="logger_8hpp" name="logger.hpp" local="yes" imported="no">alox/core/logger.hpp</includes>
    <class kind="class">aworx::lox::core::textlogger::AutoSizes</class>
    <class kind="class">aworx::lox::core::textlogger::MetaInfo</class>
    <class kind="class">aworx::lox::core::textlogger::ObjectConverter</class>
    <class kind="class">aworx::lox::core::textlogger::StringConverter</class>
    <class kind="class">aworx::lox::core::textlogger::TextLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
    <member kind="typedef">
      <type>aworx::lox::core::textlogger::TextLogger</type>
      <name>TextLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8d1a5942495395f77e31bb5d451c332b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>thread.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/threads/</path>
    <filename>thread_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::threads::Runnable</class>
    <class kind="class">aworx::lib::threads::Thread</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::threads</namespace>
    <member kind="typedef">
      <type>aworx::lib::threads::Runnable</type>
      <name>Runnable</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af259362a7fa123eef74daaf4036e02a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::Thread</type>
      <name>Thread</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a42fe02133ffe8b203c4aa204d2114d49</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::ThreadLockNR</type>
      <name>ThreadLockNR</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a414cfa465381a22be7bf0bdc5728c1a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>threadlock.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/threads/</path>
    <filename>threadlock_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="ownable_8hpp" name="ownable.hpp" local="yes" imported="no">alib/core/ownable.hpp</includes>
    <includes id="thread_8hpp" name="thread.hpp" local="yes" imported="no">thread.hpp</includes>
    <class kind="class">aworx::lib::threads::SmartLock</class>
    <class kind="class">aworx::lib::threads::ThreadLock</class>
    <class kind="class">aworx::lib::threads::ThreadLockNR</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::threads</namespace>
    <member kind="typedef">
      <type>aworx::lib::threads::SmartLock</type>
      <name>SmartLock</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aee1cd004a3010e8ee798517d96c1ffca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::ThreadLock</type>
      <name>ThreadLock</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad941b2cb61bade9aa2478dd063154d33</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ticks.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/time/</path>
    <filename>ticks_8hpp</filename>
    <includes id="substring_8hpp" name="substring.hpp" local="yes" imported="no">alib/strings/substring.hpp</includes>
    <class kind="class">aworx::lib::time::Ticks</class>
    <class kind="class">aworx::lib::time::TicksCalendarTime</class>
    <class kind="class">aworx::lib::time::TickSpan</class>
    <class kind="class">aworx::lib::time::TickWatch</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::time</namespace>
    <member kind="typedef">
      <type>aworx::lib::time::Ticks</type>
      <name>Ticks</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad270463709a4ae7e7098df40e803e458</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TicksCalendarTime</type>
      <name>TicksCalendarTime</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0607ccd659418fa7cb9922b2c4ba5f1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TickSpan</type>
      <name>TickSpan</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a7b85567c52aa0abc2531be7a2a7f887f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TickWatch</type>
      <name>TickWatch</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4d4926218d664dabc231ce5cf0c19afc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tokenizer.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>tokenizer_8hpp</filename>
    <includes id="substring_8hpp" name="substring.hpp" local="yes" imported="no">alib/strings/substring.hpp</includes>
    <class kind="class">aworx::lib::strings::Tokenizer</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::Tokenizer</type>
      <name>Tokenizer</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a605604b4e10ad391819f94254f1727b7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tstring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>tstring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="struct">aworx::lib::strings::IsTerminatable</class>
    <class kind="class">aworx::lib::strings::TString</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRING_DBG_UNTERMINATE</name>
      <anchorfile>group__GrpALibStringsMacros.html</anchorfile>
      <anchor>gacf96023d903e78f3b5d784a799041667</anchor>
      <arglist>(astring, offset)</arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::TString</type>
      <name>TString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af01fde7c67b5f30027a4135222bbde31</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>util.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>util_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::Util</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
  </compound>
  <compound kind="file">
    <name>vstudiologger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>vstudiologger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="plaintextlogger_8hpp" name="plaintextlogger.hpp" local="yes" imported="no">alox/core/textlogger/plaintextlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::VStudioLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::VStudioLogger</type>
      <name>VStudioLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a747899e07def7493ae65c9569a5dc879</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>windowsconsolelogger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/loggers/</path>
    <filename>windowsconsolelogger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="textlogger_8hpp" name="textlogger.hpp" local="yes" imported="no">alox/core/textlogger/textlogger.hpp</includes>
    <class kind="class">aworx::lox::loggers::WindowsConsoleLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <member kind="typedef">
      <type>aworx::lox::loggers::WindowsConsoleLogger</type>
      <name>WindowsConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad427fd161e0ad8bd4c8835c5a643cc3f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::ALIB</name>
    <filename>classaworx_1_1lib_1_1ALIB.html</filename>
    <member kind="variable" static="yes">
      <type>static ALIB_API std::pair&lt; const char *, uint32_t &gt;</type>
      <name>CompilationFlagMeanings</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a075d789701e32425e80a4e766354d005</anchor>
      <arglist>[7]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const uint32_t</type>
      <name>CompilationFlags</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>abbfe1aff131ede76ea8f259b2282b26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API config::Configuration</type>
      <name>Config</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a34430993f800b3bc4571bd4b9a6d9184</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API strings::String</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>affcf83e8b52935dd94b74c1a47cf7e0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API threads::ThreadLockNR</type>
      <name>Lock</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a3a29620087f23e0c8989918e0ff9c9be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Revision</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a9c8cddb79a23b8e57370078da95de8ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API threads::SmartLock</type>
      <name>StdOutputStreamsLock</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>aa44d863f975cf49f3cf879b53f080a07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Version</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a8d88b5f159f3cd597cdd92f942340024</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API bool</type>
      <name>WaitForKeyPressOnTermination</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ada43e256e3815ef07e1fa43666e356da</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API void</type>
      <name>Init</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a368faebfbb1d770d76d5e073266a3deb</anchor>
      <arglist>(enums::Inclusion environment=enums::Inclusion::Include, int argc=0, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsInitialized</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ab2c217951b4362bb6661a1e863105320</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API void</type>
      <name>SleepMicros</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ad450f3684e2b0fbb9e79124eb9e63146</anchor>
      <arglist>(int microsecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API void</type>
      <name>SleepMillis</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a975f9e2b2decf461ca35d96c76d64f87</anchor>
      <arglist>(int millisecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API void</type>
      <name>SleepNanos</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a2597856ee4c535ad62f07982ae9e483b</anchor>
      <arglist>(int nanosecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API void</type>
      <name>TerminationCleanUp</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a2a0bcae1f7341255492ebc90deab5f01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>VerifyCompilationFlags</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a6924a062cb4b36d1cffa928296525365</anchor>
      <arglist>(uint32_t flags)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static bool</type>
      <name>initialized</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>aedeffc7d23da25d52b9a50045189fe2b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::ALox</name>
    <filename>classaworx_1_1lox_1_1ALox.html</filename>
    <member kind="variable" static="yes">
      <type>static ALIB_API const uint32_t</type>
      <name>ALibCompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>ad73d0d3096f8469b1e8ba2f17fe9bb69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API std::pair&lt; const char *, uint32_t &gt;</type>
      <name>CompilationFlagMeanings</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a94e348b81d5b26163c0eb1efc4c0fd69</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const uint32_t</type>
      <name>CompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>abbfe1aff131ede76ea8f259b2282b26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const String &amp;</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>addc024f6c6dbb007e99c6becdc4d3649</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 2 &gt;</type>
      <name>InternalDomains</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a27e1cb674b3172d5696b38af8479755d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Revision</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a9c8cddb79a23b8e57370078da95de8ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Version</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a8d88b5f159f3cd597cdd92f942340024</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API Lox *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a5f7f08079ff9bd8f3bc10ccae36febd0</anchor>
      <arglist>(const TString &amp;name, Create create=Create::Never)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>Init</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>aa42e90660a7c751cd1dfd28942375f54</anchor>
      <arglist>(lib::enums::Inclusion environment=lib::enums::Inclusion::Include, int argc=0, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API Lox *</type>
      <name>Log</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>ae55ef9a26260880cde159c9d7591cb6a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>Register</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>adf95bbd67aec5e9e71e14134b0924fcf</anchor>
      <arglist>(Lox *lox, ContainerOp operation)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>Reset</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>TerminationCleanUp</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a2a0bcae1f7341255492ebc90deab5f01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>VerifyCompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a6924a062cb4b36d1cffa928296525365</anchor>
      <arglist>(uint32_t flags)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALOX_API bool</type>
      <name>isInitialized</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a1fdc2bf5595c2e64dc06d987769834eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API std::vector&lt; Lox * &gt;</type>
      <name>loxes</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a6ca6d3ba00770c0f9f3f510f5f190f25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API Lox *</type>
      <name>theLog</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>aa738c8e1b3262d2afe7463f97d5980e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALOX_API void</type>
      <name>checkLibraryVersions</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a2dbf1714a573a9e1d90bd5a68c644917</anchor>
      <arglist>(int alibVersion=ALIB_VERSION_VERYFIER, int aloxVersion=ALIB_VERSION_VERYFIER, uint32_t flagsALib=ALIB_COMPATIBILITY_VERYFIER, uint32_t flagsALox=ALOX_COMPATIBILITY_VERYFIER)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALOX_API bool</type>
      <name>initInternal</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>a11c523fe94ea435258a293ab80a6afed</anchor>
      <arglist>(Inclusion environment, int argc, void **argv, bool wArgs)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ALox</name>
      <anchorfile>classaworx_1_1lox_1_1ALox.html</anchorfile>
      <anchor>aa6e6d60af89ba00a696f2882251907d9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::ALoxReportWriter</name>
    <filename>classaworx_1_1lox_1_1ALoxReportWriter.html</filename>
    <base>aworx::lib::ReportWriter</base>
    <member kind="function" static="yes">
      <type>static ALOX_API String &amp;</type>
      <name>LogDomain</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a25d1e81288f8b2a044f14e2577bc73cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ALoxReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a4b218cdb1f7e96e6cd3a851cca5f7c76</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>NotifyActivation</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a810c6fafc7e815f40da0a7e1f30e2233</anchor>
      <arglist>(Phase)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Report</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a3ad9ad01d27945bd76295c63aa1f5457</anchor>
      <arglist>(const lib::Report::Message &amp;report)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static String16</type>
      <name>reportDomain</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>add18036b208027dee62ed16031695ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Lox *</type>
      <name>lox</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a337184443073b338364d604916737ba8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::AnsiConsoleLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger.html</filename>
    <base>aworx::lox::loggers::AnsiLogger</base>
    <member kind="function">
      <type>ALOX_API</type>
      <name>AnsiConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger.html</anchorfile>
      <anchor>a4a099618a99a1f332153377f41e747a6</anchor>
      <arglist>(const String &amp;name=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~AnsiConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger.html</anchorfile>
      <anchor>a4c8b0a449e4f27c7f745201dd0a7bdde</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::AnsiLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</filename>
    <base>aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a27e72cbc5b02a1dbcc59459b24fcac93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a78781c97dcd77d8e020d97f45c6ec17d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a55cdb14432692f0f3652ab370f737838</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 11 &gt;</type>
      <name>ANSI_BG_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a6a0101d01ba74803526dfe840f5908ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a730b918b92cd98d292027abe64c204e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a79a4977dd2c4d0c59ecc710e183dfdf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a355036b8fd63b3bc610bb2306e82fd44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 11 &gt;</type>
      <name>ANSI_BG_LIGHT_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>add465a88b8403ce7a9958b5aef88bdec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a5b80a3c04fe8a12fd70bf03ab10ccd24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af730ae0af14b4635f8520b8b38c47c3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a3bb7b29b489ce76c545f44c537de9f11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_LIGHT_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a30242d20b5eeab94340a1fb08aafac6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ac0f817a36a42706066be19b714b18529</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a39a1ec9788d46db67d8070dd8ba5f9c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad8f6edba5f4ea02b34a5ff9f47dbb823</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad347cc384960c5b3a53711db67b461a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a997f0ff7a14095055ca4177f2c7ee24b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a0dd61828101f981ddf40596036491db2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a03bb338f2071710563b5b900776ff97c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af13e42075527c53826a45b701d2f11ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 4 &gt;</type>
      <name>ANSI_BOLD</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a3673001c1ecfade29ebd998fb0a7d34d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab74c43b828d71d6a0bb8f2f638153c38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 11 &gt;</type>
      <name>ANSI_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a451ac488ad5845c1fd7ef00baa7c4804</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a959850ecf9bb6c411bac981f96e856ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 4 &gt;</type>
      <name>ANSI_ITALICS</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a508beb405ebff03bbe2c95f6b1ee3b2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a26d9f5b90c0c759c2f884de2bd3b686d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a8a7ab1c3f0c1801f4753b7688a169fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 11 &gt;</type>
      <name>ANSI_LIGHT_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae011416736a221e44aaffcfef3f3f82c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a38253545c73c267665042f327e8c1d14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a37ab8dbc850a5c7a93377533064a05e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a76e632c9d3072b0787dc39f762570ecd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_LIGHT_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af0def5f87a98d3035be0f9458b51d819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7d398f7c3538d3e90f580b40cb3e98de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a0ddb3aa248250fc2cfc9e11784f2b12a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a08626922493c40a069ef1cc2b0d384a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 4 &gt;</type>
      <name>ANSI_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a58e573cc2e2729e1c8de3f2ef2550f15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad16f181c52a38df089565a239eb26daa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 4 &gt;</type>
      <name>ANSI_STD_STYLE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ac490b3694ac9f9f753bb9dda4fde4f71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 10 &gt;</type>
      <name>ANSI_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7b3c274355061e30b915f2d0d30f16f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 5 &gt;</type>
      <name>ANSI_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a250a3234cb0ca3abaca33bc8651a6477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsBackgroundLight</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab9537e130d3c02801775f8c1941eb9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixError</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7576c4768fda16421e817896836e568f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixInfo</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa6f1bc914355fe8d17d8ca1a3d642eed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixVerbose</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>adfbbaceadd0848bac5de58dd675fd735</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixWarning</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad9cc2acc0ffe4f4ab09344dacb4c4396</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgSuffix</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ac00d21fc9d9b258f5eb5df6681a47c38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String64</type>
      <name>NoMethodInfo</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a2e7b7694fcfdddd12ec0e58161481c25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String64</type>
      <name>NoSourceFileInfo</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a730401280990f16d7aed88c503fe6e04</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>AnsiLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aeac625cc5388399443c5af013b437a4d</anchor>
      <arglist>(std::basic_ostream&lt; char &gt; *oStream, bool usesStdStreams, const String &amp;name=nullptr, const String &amp;typeName=&quot;ANSI&quot;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~AnsiLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad6ebe5d417530b986e219b6a9225459b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::basic_ostream&lt; char &gt; *</type>
      <name>oStream</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a61c72958789f761a5763f20659bd8651</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>logText</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa7e70b90717f0429abf0990e5e12ad9f</anchor>
      <arglist>(core::Domain &amp;domain, Verbosity verbosity, AString &amp;msg, core::ScopeInfo &amp;scope, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aff874730d33416eb95a0650e0df3f39b</anchor>
      <arglist>(lib::enums::Phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::AString</name>
    <filename>classaworx_1_1lib_1_1strings_1_1AString.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a135d849a18470b04a1f4cf761de3a17c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8d15090f040cca48bcb7f1875de0fe3e</anchor>
      <arglist>(int initialCapacity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4f3aebb5fc9bc80c4f569df5d6450025</anchor>
      <arglist>(const AString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aea0679449a7bd77ef8c90909a186b0f8</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aebc985ab1428055a05aee879e173910a</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a572f9132e424efddf6bfa92581db2b36</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab93ea5df790ecc39b4f09e84cbd9805c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab5e4f0275095724f12cb477527d2f33b</anchor>
      <arglist>(const AString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6cfb898b4e0d87d08b6c0b115b690239</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0c8474e9c19a45b535f1b460aac3847b</anchor>
      <arglist>(char *extBuffer, int extBufferSize, int extLength=0, enums::Responsibility responsibility=enums::Responsibility::KeepWithSender)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GrowBufferAtLeastBy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3fc410cc4cccd79e66c2f7491bce4bd3</anchor>
      <arglist>(int minimumGrowth)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad07c7e740f0be42afb0c1eda25361864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasInternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a799c4f153843f7dbba7fe16cf9bfc457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>VBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a39184b93936d495a501cbea28e12495e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab2cf143ab3c019c18b6ada0ea87a6370</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8068d1bbfd60c6cb178bdc0b2084ab9b</anchor>
      <arglist>(int op)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae4d5af65574550e39830297e4496f81b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a05403e545a0fa8171456199085790c1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>InsertAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8b5159f28435000513953d4b28b98c6d</anchor>
      <arglist>(const String &amp;src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>InsertChars</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abf74925ba2fc5109db3c8be01c962e4e</anchor>
      <arglist>(char c, int qty, int pos=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a17e140dfb247b527da7f6e253601e6b3</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ReplaceRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab7e984ef7acfdeb4d63b572c6f2dca70</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Delete</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7d7ec24a8f70ba85b88032b1d853acd0</anchor>
      <arglist>(int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>DeleteStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3919b9c770d283b5df0b09b756081d99</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>DeleteEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c72c80e34049aa4566be4fffe4b9251</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5902ed6d5d02134b98ac686172f34dc9</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>TrimAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a63f255e8769be77d70b70407e388746b</anchor>
      <arglist>(int index, const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4aacb9ead9be86623c688267f76760cf</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abfb73aa66ba9e9ebedecd9de6ee6ed9b</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Append</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a45cb08597c96cf62edb8ece124d8e4fc</anchor>
      <arglist>(const char *src, int srcLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4dbe5fba1e5c5ed69d12d57b3eb49ef7</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a635ad749475cecd00e3ec3603327d78c</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5997f9405428b49e5fd680e62ee41c45</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac243bc3f2d0f61eb45d49f488ddbcb63</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>NewLine</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a949cac7084e10566b50a195b60bff591</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5bf64f32d0163186492461fb2c3e4300</anchor>
      <arglist>(const TString &amp;needle, const String &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ada2d3b01c31c088c8e04676c6e50e78b</anchor>
      <arglist>(const TString needle, const String &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToUpper</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a76441306378ccdc4d560ea2ea417a89b</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToLower</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4d1a7077beb29dd16e84c469e5e01f12</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>debugLastAllocRequest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7ebc042256408173ee3c3904906a0e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>debugBufferWithMagicBytePadding</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa155a96ba168342ab2ae8067d96e373e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>adbe66a087ac3fd4a5b0566f64ca2d12b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ReplaceExternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae6e756e6f5ccc142f9fc3ceb6ba18cf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_dbgCheck</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8747c38ac0ef9f863ede544d51ff6721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>constexpr</type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a56a710a7a5bc7604ce80ae47265f5835</anchor>
      <arglist>(char *extBuffer, int extBufferSize)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a135d849a18470b04a1f4cf761de3a17c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8d15090f040cca48bcb7f1875de0fe3e</anchor>
      <arglist>(int initialCapacity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4f3aebb5fc9bc80c4f569df5d6450025</anchor>
      <arglist>(const AString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aea0679449a7bd77ef8c90909a186b0f8</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aebc985ab1428055a05aee879e173910a</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a572f9132e424efddf6bfa92581db2b36</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab93ea5df790ecc39b4f09e84cbd9805c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab5e4f0275095724f12cb477527d2f33b</anchor>
      <arglist>(const AString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6cfb898b4e0d87d08b6c0b115b690239</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0c8474e9c19a45b535f1b460aac3847b</anchor>
      <arglist>(char *extBuffer, int extBufferSize, int extLength=0, enums::Responsibility responsibility=enums::Responsibility::KeepWithSender)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GrowBufferAtLeastBy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3fc410cc4cccd79e66c2f7491bce4bd3</anchor>
      <arglist>(int minimumGrowth)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad07c7e740f0be42afb0c1eda25361864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasInternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a799c4f153843f7dbba7fe16cf9bfc457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>VBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a39184b93936d495a501cbea28e12495e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab2cf143ab3c019c18b6ada0ea87a6370</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8068d1bbfd60c6cb178bdc0b2084ab9b</anchor>
      <arglist>(int op)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae4d5af65574550e39830297e4496f81b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a05403e545a0fa8171456199085790c1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>InsertAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8b5159f28435000513953d4b28b98c6d</anchor>
      <arglist>(const String &amp;src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>InsertChars</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abf74925ba2fc5109db3c8be01c962e4e</anchor>
      <arglist>(char c, int qty, int pos=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a17e140dfb247b527da7f6e253601e6b3</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ReplaceRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab7e984ef7acfdeb4d63b572c6f2dca70</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Delete</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7d7ec24a8f70ba85b88032b1d853acd0</anchor>
      <arglist>(int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>DeleteStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3919b9c770d283b5df0b09b756081d99</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>DeleteEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c72c80e34049aa4566be4fffe4b9251</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5902ed6d5d02134b98ac686172f34dc9</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>TrimAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a63f255e8769be77d70b70407e388746b</anchor>
      <arglist>(int index, const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4aacb9ead9be86623c688267f76760cf</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abfb73aa66ba9e9ebedecd9de6ee6ed9b</anchor>
      <arglist>(const TString &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>Append</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a45cb08597c96cf62edb8ece124d8e4fc</anchor>
      <arglist>(const char *src, int srcLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4dbe5fba1e5c5ed69d12d57b3eb49ef7</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a635ad749475cecd00e3ec3603327d78c</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5997f9405428b49e5fd680e62ee41c45</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac243bc3f2d0f61eb45d49f488ddbcb63</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>NewLine</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a949cac7084e10566b50a195b60bff591</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5bf64f32d0163186492461fb2c3e4300</anchor>
      <arglist>(const TString &amp;needle, const String &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ada2d3b01c31c088c8e04676c6e50e78b</anchor>
      <arglist>(const TString needle, const String &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToUpper</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a76441306378ccdc4d560ea2ea417a89b</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToLower</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4d1a7077beb29dd16e84c469e5e01f12</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AString">alib_namespace_strings_astring_move</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AString">alib_namespace_strings_astring_write_access</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AString">alib_namespace_strings_astring_nullable</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AString">alib_namespace_strings_astring_applyto</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AString">alib_namespace_strings_astring_application_vs_interface</docanchor>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::AutoSizes</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>ActualIndex</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>acf5441aa3a2d1bcc3dfd3519d7579fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Export</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>aac883c890047d2981a5d7450a10111f9</anchor>
      <arglist>(AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Import</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>afdc01d5f605aa1984884804206b5bf70</anchor>
      <arglist>(const String &amp;source, lib::enums::CurrentData session=lib::enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API int</type>
      <name>Next</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>aefa2cd1851ed40a5268c3896945a5872</anchor>
      <arglist>(int requestedSize, int extraGrowth)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Start</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a07aaf1227e4d645f15e0a964f54ef291</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; int &gt;</type>
      <name>sessionValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>ab984e4481cc3e39628583b38fedc8911</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; int &gt;</type>
      <name>values</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>ad80b3fe86185c92f73dddc2805963dc0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::CommandLinePlugIn</name>
    <filename>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</filename>
    <base>aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="function">
      <type></type>
      <name>CommandLinePlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>ae668464b863651b97396462f7cb5f843</anchor>
      <arglist>(int argc, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CommandLinePlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a8adb5a21052bd527334cdf67115f1d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a4ab8705a2db7095450dbc00919e67dfc</anchor>
      <arglist>(const String &amp;category, const String &amp;name, AString &amp;target)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>argc</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>ad1447518f4372828b8435ae82e48499e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void **</type>
      <name>argv</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a20ad14f3c153549ae4c9e93168bc4977</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>wArgs</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>aa12d3084f7f24b687e9495935fddb6ce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::Configuration</name>
    <filename>classaworx_1_1lib_1_1config_1_1Configuration.html</filename>
    <base>aworx::lib::threads::ThreadLock</base>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>PrioCmdLine</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a1baac67c511294bc3317b956ea196b11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>PrioEnvVars</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>aff7062a012b6acdf15fcfb20ab184975</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>PrioIniFile</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ac0e213817eb829a4d7b3f1960814a781</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>CommandLinePlugIn *</type>
      <name>cmdLineCP</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a8b6414b86e45aeffa6e8a18857614ca6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EnvironmentPlugIn *</type>
      <name>envCP</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a2a30bf55f0ff6dc49518e186c7f2dc41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>strings::NumberFormat</type>
      <name>NumberFormat</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a9bfa3473e5c94dafa94ae1339fe70a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; String &gt;</type>
      <name>TrueValues</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a5848fc835514e61005938ea4c9b9b772</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>Configuration</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a36d123dcc42ef58da853d1eb86f12199</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API</type>
      <name>~Configuration</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a09dcd47e8d29f55ef5515d6413d42d16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>AddStandardPlugIns</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a705c239bb70c153d65d12a2d1a4763ed</anchor>
      <arglist>(enums::Inclusion environment=enums::Inclusion::Include, int argc=0, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a49a4508b4f1b2adfa69472ac63251d70</anchor>
      <arglist>(const String &amp;category, const String &amp;name, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>abb044d9a7fe6ce75eb0b2f598527e298</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int32_t &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a7926b4197266a7f6b97a19f2fa458427</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>InsertPlugin</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ab36ebb23134231a52f92bc04c7ccaf91</anchor>
      <arglist>(ConfigurationPlugIn *plugin, int priority)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>IsTrue</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>aa0da6e72e76dfd9415dedd65569f8d02</anchor>
      <arglist>(const String &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>IsTrue</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a17443adf054241c7688f6bb82f11de70</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int *pluginPriority=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>RemovePlugin</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>abe90d89e1bee0e148609cbe6f1be09a3</anchor>
      <arglist>(ConfigurationPlugIn *plugin)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a54fc8d0635e60448988f6da420f4937b</anchor>
      <arglist>(const String &amp;category, const String &amp;name, const String &amp;value, const String &amp;comments=NullString, char delim= &apos;,&apos;)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a423e203d6722c62b4b5f549a6d873013</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int value, const String &amp;comments=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a29d1e06626b950f1362eede2a7543e64</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double value, const String &amp;comments=nullptr)</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::pair&lt; int, ConfigurationPlugIn * &gt;</type>
      <name>PluginAndPrio</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ae19a925ddfe98cba62d5bea6aeaba2e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; PluginAndPrio &gt;</type>
      <name>plugins</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a3ab0c51547c4c4232d1cc46c3024aef0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::ConfigurationPlugIn</name>
    <filename>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</filename>
    <member kind="variable">
      <type>Configuration *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a82bf1cd3b4adcee833998d1a0642c574</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Configuration</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a30221ddc558692a7b52598b963a74bc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ConfigurationPlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a7be57a5ed92198b336f33405511cc5d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~ConfigurationPlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>acc4f693e1c9d021c6a8ca052bb151863</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a07c28865deadd179a3b671a720287387</anchor>
      <arglist>(const String &amp;category, const String &amp;name, AString &amp;target)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a7769d0a21a18975dab583fca360ed695</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int32_t &amp;target)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>af84adad9c40e4d8507d397b48c68632a</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double &amp;target)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a88428c9e1d24723bb630c1a6b906ea33</anchor>
      <arglist>(const String &amp;category, const String &amp;name, const String &amp;value, const String &amp;comments, char delim)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a8bcdd8dea91d88e7fb3a3c4282422cba</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int value, const String &amp;comments)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>aee1b1c200efc1d49b3bcffcc240a40d6</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double value, const String &amp;comments)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::ConsoleLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</filename>
    <base>aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="function">
      <type></type>
      <name>ConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a125af672dcbe9fbde266699050701770</anchor>
      <arglist>(const String &amp;name=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a804d9d5558b46a55a78a22be5d23778a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>logSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a728330a0b5b726d0bcbb30d1fe0992f5</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>afd61f886ab5fd3838e70919f34224397</anchor>
      <arglist>(lib::enums::Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>aec9a5cf9fd771158d304efda15765384</anchor>
      <arglist>(lib::enums::Phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::ConsoleReportWriter</name>
    <filename>classaworx_1_1lib_1_1ConsoleReportWriter.html</filename>
    <base>aworx::lib::ReportWriter</base>
    <member kind="variable" static="yes">
      <type>static ALIB_API ConsoleReportWriter</type>
      <name>Singleton</name>
      <anchorfile>classaworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>a7814635efff621671f61ae49310a9d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API void</type>
      <name>NotifyActivation</name>
      <anchorfile>classaworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>a060e63e8c473550f7964f35ba21704bc</anchor>
      <arglist>(enums::Phase phase)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API void</type>
      <name>Report</name>
      <anchorfile>classaworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>a4e22fecd02d1d3b1b079178c29c54d90</anchor>
      <arglist>(const Report::Message &amp;report)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ConsoleReportWriter</name>
      <anchorfile>classaworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>aa79313b30414299d171786d881144df7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::CString</name>
    <filename>classaworx_1_1lib_1_1strings_1_1CString.html</filename>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MaxLen</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a702a7d928cd1d34c5aa2f26dd97e199e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a3d3a3aae130c2f0a42728d9ecd0148c7</anchor>
      <arglist>(int referenceLength, int &amp;regionStart, int &amp;regionLength)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>ab974d11810ea818ff2170d45a7b42369</anchor>
      <arglist>(const char *haystack, int haystackLength, const char *needles, int needlesLength, enums::Inclusion inclusion)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a5ddb5d0117e29a7455e0013a0397057e</anchor>
      <arglist>(const char *haystack, int startIdx, const char *needles, int needlesLength, enums::Inclusion inclusion)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API int</type>
      <name>LengthWhenConvertedToWChar</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>ab532d5afe18b9085da60cbfb47bd4bd0</anchor>
      <arglist>(const char *cs, int csLength)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>strncasecmp</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a06e5d82687b5f75828132a6258091abe</anchor>
      <arglist>(const char *cs1, const char *cs2, int cmpLength)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::system::Directory</name>
    <filename>classaworx_1_1lib_1_1system_1_1Directory.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>SpecialFolder</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a12c335c8e07182c17395a8f46f1965f0</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1Directory.html" anchor="a12c335c8e07182c17395a8f46f1965f0afa03eb688ad8aa1db593d33dabd89bad">Root</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1Directory.html" anchor="a12c335c8e07182c17395a8f46f1965f0a222a267cc5778206b253be35ee3ddab5">Current</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1Directory.html" anchor="a12c335c8e07182c17395a8f46f1965f0a8cf04a9734132302f96da8e113e80ce5">Home</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1Directory.html" anchor="a12c335c8e07182c17395a8f46f1965f0a01255de311d629c078914c471e45ec28">HOME_CONFIG</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1Directory.html" anchor="a12c335c8e07182c17395a8f46f1965f0ae55f75a29310d7b60f7ac1d390c8ae42">Module</enumvalue>
    </member>
    <member kind="variable">
      <type>String256</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a7a1498c6111483e7acf3a52bef418c09</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API enums::Result</type>
      <name>Create</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a4705a3d882c8aa61346f6175f1c83a30</anchor>
      <arglist>(const TString &amp;path)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>CurrentDirectory</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a06845a767764e37766027392413e068f</anchor>
      <arglist>(AString &amp;target)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>Exists</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a348d7a37454d70c73f2b7e4106b5389a</anchor>
      <arglist>(const TString &amp;path)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Directory</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>afb2dc4e4a36ed39171b54c55bc38d136</anchor>
      <arglist>(SpecialFolder special)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Directory</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a3d2aef8216e51d8fea90c4f4b4f26959</anchor>
      <arglist>(const String &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>Change</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a27964fd8269b71c00bf2d4dd884c2a97</anchor>
      <arglist>(const String &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Change</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a7368f768fd59c3290b53722fa245c319</anchor>
      <arglist>(SpecialFolder special)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>IsValid</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1Directory.html</anchorfile>
      <anchor>a1865c345633bd315a4095b999bbd2e6d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::Domain</name>
    <filename>classaworx_1_1lox_1_1core_1_1Domain.html</filename>
    <class kind="struct">aworx::lox::core::Domain::LoggerData</class>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; LoggerData &gt;</type>
      <name>Data</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>ae084fa950af8593b424bb0f75fba7a0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String64</type>
      <name>FullPath</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a5249fc60e18f9a0e7e7ffd24a20dbec9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Name</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>ab3c68b8a64bf47454f94bde4ebb6de0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Domain *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a1d350b8d568b2886bda3a5f093adc1bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::pair&lt; Logable, Inclusion &gt; &gt;</type>
      <name>PrefixLogables</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a07cbccb2eb45cd2c64f468b04ef7f397</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Domain * &gt;</type>
      <name>SubDomains</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a45607390dc4f3ea0f79c1ee1a08a777b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr char</type>
      <name>PathSeparator</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a28fc603aa3aaa186e688d30802253538</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>Domain</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a30f0d2a14dee624bd33d7852e9bb8670</anchor>
      <arglist>(Domain *parent, const String &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~Domain</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>aab7e32c77383bf3d384c5c1ab492cd2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>AddLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>af6b2bbb7cabe76ef457594558aac85f8</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CountLoggers</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a99a4aca5fd12818f7a0718ff1bf37c9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API Domain *</type>
      <name>Find</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a39db56c49e652a545a01be2bc1d50a99</anchor>
      <arglist>(Substring domainPath, Case sensitivity, int maxCreate, bool *wasCreated)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCount</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a20db10bae0149b8f99461370b2b3fd48</anchor>
      <arglist>(int loggerNo)</arglist>
    </member>
    <member kind="function">
      <type>core::Logger *</type>
      <name>GetLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a2c5c025862458ad7bd56bff6a0e3ea0c</anchor>
      <arglist>(const String &amp;loggerName)</arglist>
    </member>
    <member kind="function">
      <type>core::Logger *</type>
      <name>GetLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a7a091eb804deb77940227c78f4c36ad7</anchor>
      <arglist>(int no)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLoggerNo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a2657f04b274350d1a8e01747e125ece4</anchor>
      <arglist>(const String &amp;loggerName)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLoggerNo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>aa47720e17d76f442124d5c279b9d0287</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPriority</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a6fd0d5e74c9ce237644735d17cbc7119</anchor>
      <arglist>(int loggerNo)</arglist>
    </member>
    <member kind="function">
      <type>Domain *</type>
      <name>GetRoot</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a3fbb171d3b615727af29167b4cb61c4b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Verbosity</type>
      <name>GetVerbosity</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a19ec6c97f7e17ca51908a7174e43f2bd</anchor>
      <arglist>(int loggerNo)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsActive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a6dc8fbb3427c720adda3ed3a807f9902</anchor>
      <arglist>(int loggerNo, Verbosity statement)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a9aa2e7ebee563c92c3335f9a3b4a574c</anchor>
      <arglist>(int loggerNo)</arglist>
    </member>
    <member kind="function">
      <type>Verbosity</type>
      <name>SetVerbosity</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a72b26b0cca06a87932744d5f625efbfa</anchor>
      <arglist>(int loggerNo, Verbosity verbosity, int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToString</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a40a66924a70652623c5e6bceaff3d62e</anchor>
      <arglist>(AString &amp;target)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addLoggerRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a60a0f660238122080765f3d2e7a2e95d</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Domain *</type>
      <name>findRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a02b8bad45eee615dd7b0fb6e4d863aef</anchor>
      <arglist>(Substring &amp;domainPath, Case sensitivity, int maxCreate, bool *wasCreated)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>removeLoggerRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a1b032fcdfc7306d529107bcd28145b66</anchor>
      <arglist>(int loggerNo)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::Lox::DomainSubstitutionRule</name>
    <filename>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Type</name>
      <anchorfile>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</anchorfile>
      <anchor>a1d1cfd8ffb84e947f82999c682b666a7</anchor>
      <arglist></arglist>
      <enumvalue file="structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html" anchor="a1d1cfd8ffb84e947f82999c682b666a7a1649aed298f99d587e2eb30c1db5946b">Exact</enumvalue>
      <enumvalue file="structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html" anchor="a1d1cfd8ffb84e947f82999c682b666a7a9d1a2cba952f9245c54397bbbf3e8183">StartsWith</enumvalue>
      <enumvalue file="structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html" anchor="a1d1cfd8ffb84e947f82999c682b666a7a213068b7e25d045126e9b1702fae80db">EndsWith</enumvalue>
      <enumvalue file="structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html" anchor="a1d1cfd8ffb84e947f82999c682b666a7a7ba559a2b304b4c6d34d67ed77f80345">Substring</enumvalue>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Replacement</name>
      <anchorfile>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</anchorfile>
      <anchor>aec5095f2fc805732629f1bfc648de05c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Search</name>
      <anchorfile>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</anchorfile>
      <anchor>ac5d8cc07dc3e4eea47354e7b7f6eb8a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Type</type>
      <name>type</name>
      <anchorfile>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</anchorfile>
      <anchor>ab6f4e6d3fde00ce906e46494f60dfe7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DomainSubstitutionRule</name>
      <anchorfile>structaworx_1_1lox_1_1Lox_1_1DomainSubstitutionRule.html</anchorfile>
      <anchor>a79a7b9599dc10cfe2e980f50eb90c53e</anchor>
      <arglist>(const TString &amp;s, const TString &amp;r)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::Double</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1Double.html</filename>
    <member kind="variable">
      <type>NumberFormat *</type>
      <name>nf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Double.html</anchorfile>
      <anchor>afecb8b906f7e79cb68adcdbce823de5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>value</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Double.html</anchorfile>
      <anchor>aee90379adb0307effb138f4871edbc5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Double</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Double.html</anchorfile>
      <anchor>a33cbbfab93231d3ab8f5b7feb3e9b1ce</anchor>
      <arglist>(double value, NumberFormat *nf)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::EnvironmentPlugIn</name>
    <filename>classaworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</filename>
    <base>aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="function">
      <type></type>
      <name>EnvironmentPlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</anchorfile>
      <anchor>acbd5e02cd0e7d1fb1263beb7d734fc40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EnvironmentPlugIn</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</anchorfile>
      <anchor>ab1e9614f71def9d8570c8efdf9f13edb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</anchorfile>
      <anchor>a4ab8705a2db7095450dbc00919e67dfc</anchor>
      <arglist>(const String &amp;category, const String &amp;name, AString &amp;target)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::ESC</name>
    <filename>classaworx_1_1lox_1_1ESC.html</filename>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aa82c6a3b4740dbc8469c438cb508c9fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a32c9da22aa2e2219e6110c71c0862cab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ad3ea7c45421a7fe41bef9fccf446beab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ab06f1181bd398bc4a055f2e1e2505fce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a7d938ef89f27d144e7b95fd249d50ade</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aab3e5266c78e812e7a6c426367dc9071</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_RED</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>afd07c8746625a0194d127cb2249aa0cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a187117a859affcb7261591c26ea6b0d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a48c1e456dcabe4ffd80ec00ab474a0f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BG_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a630181f686ce699e803450426b341d06</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a03fcfa32650e29154ebb6ddfc325f13a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aae0f71c16c24eca46ba82cb778a4511e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>BOLD</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a9f9f2126d9e6edff3218927c04074dcb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>afdf0230e4d8012d7a89df6f3fa266e5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>EOMETA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aebb3b721c38741c6c324f5358f0f881f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>FG_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a54cca82e07ebd6c5b7e91b1b4c5d02d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a381d37bbc1e467b09e401cd87ce6663a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a1453a2687e1c19f8c40d141c1bb89329</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>ITALICS</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a720d5fb808c384fa2d54e4a675b66c6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ad7302f67367bb64d92d430db2b966744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>RED</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aa039ed1389702c723320be5baae61ef9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aea1c3b6709bf24bb5abce06e3061fd7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>STYLE_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a68e36419790bb4e6f1a6aa6148ae1984</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>TAB</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a5f86c0e8a5fe6d0af38c93a5c73724ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>URL_END</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ac4584a5ba5fec38ef5eaf0bb4e59f88a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>URL_START</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a920c1a537a90b3f971ee0d6f17fcdc02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a7e39de6e4f8233bb0dc0a259f6169608</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API SLiteral&lt; 3 &gt;</type>
      <name>YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a929f0d422bc023cdd33e11f92a47bb6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>ReplaceToReadable</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a8bf7915da932619dd2686e9f9f96317d</anchor>
      <arglist>(AString &amp;target, int startIdx)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::Field</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</filename>
    <member kind="variable">
      <type>enums::Alignment</type>
      <name>alignment</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>a2cc66511bdbd482fe68392125b584696</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const String &amp;</type>
      <name>contents</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>ae26b1a80a32917acc6107e4bfc13ed40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>padChar</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>a8fdae00ef4d3c4f8372e573c3afe996c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>width</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>a2474a5474cbff19523a51eb1de01cda4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Field</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>a66aa895a3b1d53cd97ca0073092505db</anchor>
      <arglist>(const String &amp;contents, int width, enums::Alignment alignment=enums::Alignment::Right, char padChar= &apos; &apos;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format.html</filename>
    <class kind="class">aworx::lib::strings::Format::Double</class>
    <class kind="class">aworx::lib::strings::Format::Field</class>
    <class kind="class">aworx::lib::strings::Format::Int32</class>
    <class kind="class">aworx::lib::strings::Format::Int64</class>
    <class kind="class">aworx::lib::strings::Format::Tab</class>
    <class kind="class">aworx::lib::strings::Format::UInt32</class>
    <class kind="class">aworx::lib::strings::Format::UInt64</class>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::IniFile</name>
    <filename>classaworx_1_1lib_1_1config_1_1IniFile.html</filename>
    <base>aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="enumeration">
      <type></type>
      <name>Status</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a67a0db04d321a74b7e7fcfd3f1a3f70b</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70baa60852f204ed8028c1c58808b746d115">Ok</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70bad083aedf850e5989f336e50d1a539d44">ErrorOpeningFile</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70baa3dfa29533b3745c447fff71696df7b0">ErorWritingFile</enumvalue>
    </member>
    <class kind="class">aworx::lib::config::IniFile::Section</class>
    <class kind="class">aworx::lib::config::IniFile::Variable</class>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>DefaultFileExtension</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a2eaa2333f2f0f3ee2b95eb569798ec80</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>AutoSave</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a297ce080be0d2d8b0f5245def3fd1b79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>DefaultCommentPrefix</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a4476ecda6d3ab51725c78ffc7da2ecda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; TString &gt;</type>
      <name>EscapeSequences</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a90c6ad78caa206911f41e45552d63c6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>FileComments</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a83074eb05e084e3cc5d0f9f3bb78f01b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>FileName</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a8bea19241a8e12acb6725e40dd6f2d74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Status</type>
      <name>LastStatus</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a828873beba46715ac28b88ef1de88ae4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>LinesWithReadErrors</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a40fc3347bdd13c78626393bce4f4b7af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Section * &gt;</type>
      <name>Sections</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a4db383e1b52ed42586b8aaf43836c88d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>IniFile</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a941e3deeb4b8a4591a828fc06cfce59b</anchor>
      <arglist>(const String &amp;filePathAndName=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IniFile</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>ae196a3ba5e4598d6823ce0e77bbf75d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a4ab8705a2db7095450dbc00919e67dfc</anchor>
      <arglist>(const String &amp;category, const String &amp;name, AString &amp;target)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>ad4fa10eb1909dec8799f03014e90d721</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int32_t &amp;target)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a1401b913322c506f75e38f7227e8d146</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API IniFile::Status</type>
      <name>ReadFile</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a39a807ecf078c69a8437db857dd0aeaa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>ae35f02909be48392acc4a3632f42f5d0</anchor>
      <arglist>(const String &amp;category, const String &amp;name, const String &amp;value, const String &amp;comments=NullString, char delim= &apos;,&apos;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a41cceca2764c0a9b1db812c7de7dcaa5</anchor>
      <arglist>(const String &amp;category, const String &amp;name, int value, const String &amp;comments=NullString)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Save</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>ab807e01a98358f8446a1b51286ceb581</anchor>
      <arglist>(const String &amp;category, const String &amp;name, double value, const String &amp;comments=NullString)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Section *</type>
      <name>SearchOrCreateSection</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a20f7b65fe669edbac7211be4ea229f5c</anchor>
      <arglist>(const String &amp;name, const String &amp;comments)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Section *</type>
      <name>SearchSection</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a99d17dd20fcdc8919501c21d675f6d40</anchor>
      <arglist>(const String &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API IniFile::Status</type>
      <name>WriteFile</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a73bf37055382606e309f514b0187cf43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API int</type>
      <name>addEscapeSequences</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a6aa99bb2cafe2a344a810a02587c924a</anchor>
      <arglist>(std::ostream &amp;os, const Substring &amp;value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API void</type>
      <name>removeEscapeSequences</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>adb6f2e7ca2ef00452a7d709d4063ea3e</anchor>
      <arglist>(strings::Substring &amp;value, AString &amp;target)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API void</type>
      <name>writeComments</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a8c63931fbc79dff0c0e014d63faa14d9</anchor>
      <arglist>(std::ostream &amp;os, const AString &amp;comments)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::Int32</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1Int32.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>minDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int32.html</anchorfile>
      <anchor>ab6c281111688d6bcd765ff050f741a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int32_t</type>
      <name>value</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int32.html</anchorfile>
      <anchor>a01571c420f280137c16d319178731da5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Int32</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int32.html</anchorfile>
      <anchor>a436b4ffa5fa4c3052fa5d46665075039</anchor>
      <arglist>(int32_t value, int minDigits)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::Int64</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1Int64.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>minDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int64.html</anchorfile>
      <anchor>ab6c281111688d6bcd765ff050f741a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int64_t</type>
      <name>value</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int64.html</anchorfile>
      <anchor>ac072af30c4ffbc834bb4c681f6ecb514</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Int64</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Int64.html</anchorfile>
      <anchor>a7d52ff5092e6e13c15fd6edd579b0ede</anchor>
      <arglist>(int64_t value, int minDigits)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsApplicable</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsApplicable.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsApplicable&lt; const lox::core::Logger &amp; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsApplicable_3_01const_01lox_1_1core_1_1Logger_01_6_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsApplicable&lt; const std::string &amp; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsApplicable_3_01const_01std_1_1string_01_6_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable&lt; AString &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable_3_01AString_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable&lt; PreallocatedString&lt; TCapacity &gt; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable_3_01PreallocatedString_3_01TCapacity_01_4_01_4.html</filename>
    <templarg>TCapacity</templarg>
  </compound>
  <compound kind="class">
    <name>aworx::lib::containers::PathMap::Iterator</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</filename>
    <class kind="struct">aworx::lib::containers::PathMap::Iterator::NodeAndChild</class>
    <member kind="function">
      <type></type>
      <name>Iterator</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a1f703720e1f5d97a0386c2dfe803c763</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Iterator</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a7068350d054e5b6f4375389138dfd1d2</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; &amp;sm)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a8c6df673280990e664cbf787369ef582</anchor>
      <arglist>(const Iterator &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>const PathMap&lt; StoreT &gt; &amp;</type>
      <name>operator*</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a718054a9741bdc52d3dea84cfc84f766</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Iterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>aef12ef33726bc591f569f822c7b5ac41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a9ff2e07df1950f834fee3c2deca0ff78</anchor>
      <arglist>(const typename PathMap&lt; StoreT &gt;::Iterator &amp;other) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::stack&lt; NodeAndChild &gt;</type>
      <name>nodesAndChilds</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator.html</anchorfile>
      <anchor>a2d41004ffc951d19cabd7d5717debd35</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::Log</name>
    <filename>classaworx_1_1lox_1_1Log.html</filename>
    <member kind="variable" static="yes">
      <type>static ALOX_API core::textlogger::TextLogger *</type>
      <name>DebugLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6dab5611a4ba1574d65dfcdcb0f77cd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALoxReportWriter *</type>
      <name>DebugReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3fc6107634a1988540d4f827c3586233</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALOX_API core::textlogger::TextLogger *</type>
      <name>IDELogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a7764bec073718f0cc7c022afbc17b4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>AddALibReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abb8bfbfc93fc3b5b0d8bd9bcac6b7235</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>AddDebugLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a06444d2e7a321e26fe1d4c309cb8ed49</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>RemoveALibReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9bd252035e8769cec5f74ca014b46817</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>RemoveDebugLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6d4775cac3c6e185f454a5e1fbf9325a</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::core::Logable</name>
    <filename>structaworx_1_1lox_1_1core_1_1Logable.html</filename>
    <member kind="variable">
      <type>const void *</type>
      <name>Object</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Logable.html</anchorfile>
      <anchor>aa2a021e8c29b63b3e25531a9f795f50a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Type</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Logable.html</anchorfile>
      <anchor>ae011432eaca3858364b05a111f4011d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Logable</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Logable.html</anchorfile>
      <anchor>a230ce76669619539316f7de7fdbcd02f</anchor>
      <arglist>(int type, const void *object)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Logable.html</anchorfile>
      <anchor>a1bb22a7f33e2cce3c5abc5ced4bf4c06</anchor>
      <arglist>(const Logable &amp;comp)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToString</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Logable.html</anchorfile>
      <anchor>acd0b1256409c89d1b68df9a41825fcea</anchor>
      <arglist>(AString &amp;target)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::LogData</name>
    <filename>structaworx_1_1lox_1_1LogData.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>IntegerValue</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>a65a3775caf9d6718458869ad29c1ab8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>ObjectValue</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>af6e8b41d2b8786b1ce8f27c38f70ab43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>StringValue</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>ae2bc4ad5fb100c1514db295fe5278ebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Type</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>ae011432eaca3858364b05a111f4011d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LogData</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>ab02c224dd1a0fe3c79062f5db7f377a1</anchor>
      <arglist>(const aworx::String &amp;s, int i, void *o=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LogData</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>a7f543b15e40eaffc6e2c9d0512043c4c</anchor>
      <arglist>(const aworx::String &amp;s, void *o=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LogData</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>ad1a67523d8979e36e2fa85d426486507</anchor>
      <arglist>(int i, void *o=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LogData</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>ad81b9241db781fd2d40299166c50340d</anchor>
      <arglist>(void *o=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LogData</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>a939d886d20cf188c46c3082fb068cc46</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API AString &amp;</type>
      <name>ToString</name>
      <anchorfile>structaworx_1_1lox_1_1LogData.html</anchorfile>
      <anchor>a41b1d71f6744e7d3b7e7efb30683471d</anchor>
      <arglist>(AString &amp;target)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::Logger</name>
    <filename>classaworx_1_1lox_1_1core_1_1Logger.html</filename>
    <base>aworx::lib::threads::SmartLock</base>
    <member kind="variable">
      <type>int</type>
      <name>CntLogs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ac0d4236906004de0129b9ff90108fdff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::time::Ticks</type>
      <name>TimeOfCreation</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a23018e698fe55b2e42a8982828188801</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::time::Ticks</type>
      <name>TimeOfLastLog</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a82a500fb8edf826b0c802fce0bee6f67</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Logger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a7a62719474beac5f447b376e0c9d5b44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const TString &amp;</type>
      <name>GetName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a3f67e8769ddaf510b7952b91a4621d08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const TString &amp;</type>
      <name>GetTypeName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>aa3262ab4d70006323c89b20b85d2e4d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>af6b022d80e4b67918067714afb8cab48</anchor>
      <arglist>(Domain &amp;dom, Verbosity verbosity, Logables &amp;logables, ScopeInfo &amp;scope)=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String32</type>
      <name>name</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>abb61b5a8a9b6a9b105bdcadaebd5b1ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String32</type>
      <name>typeName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a7c2cc5873d633c891b5492046ece60fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>_apiInitializer</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>aaa96ca32f5b8d83954f9d77629c1b036</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Logger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>aee3bfe16d6478e9f80bf37786712bfe9</anchor>
      <arglist>(const String &amp;name, const String &amp;typeName)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::core::Domain::LoggerData</name>
    <filename>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>core::Logger *</type>
      <name>Logger</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</anchorfile>
      <anchor>ab0f0a9542542d6c8782e1ad65fdc708b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Verbosity</type>
      <name>LoggerVerbosity</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</anchorfile>
      <anchor>a312c13a4f141e167f5b82a483b9a9edd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Priority</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</anchorfile>
      <anchor>a4450b0bad265ba3bd24e994f70aec802</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LoggerData</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1Domain_1_1LoggerData.html</anchorfile>
      <anchor>a7665b2385a58790b8ef821caeea4f7bf</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::Lox</name>
    <filename>classaworx_1_1lox_1_1Lox.html</filename>
    <base>aworx::lib::threads::ThreadLock</base>
    <class kind="struct">aworx::lox::Lox::DomainSubstitutionRule</class>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>PrioProtected</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aaadcce82539022fab50871afc106a9d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>PrioSource</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a49d9175b17b3c2d376e35c59615a905e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Case</type>
      <name>DomainSensitivity</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac63dd33538dff8703707b14fc6d04d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API core::textlogger::TextLogger *</type>
      <name>CreateConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae92c4ae884c3cd723deb9b5e8d27b6ac</anchor>
      <arglist>(const String &amp;name=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>Lox</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac5a4bc73635c5e608f573170a65c0dc1</anchor>
      <arglist>(const TString &amp;name, bool doRegister=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~Lox</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8df22829cdb5cad1db7f72bb0b068d5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a120c861ade11fa9312affe53dcb39c4e</anchor>
      <arglist>(bool condition, const TString &amp;domain, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac2f172a00bb8f199400ca73a5af89611</anchor>
      <arglist>(bool condition, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af4aa22eabb67650079c44822cae0102f</anchor>
      <arglist>(bool condition, const TString &amp;domain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af6231385bed64a25d113276260fa420c</anchor>
      <arglist>(bool condition, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearSourcePathTrimRules</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a01bb6d07bbecaacf8be4471b16889d63</anchor>
      <arglist>(Inclusion global=Inclusion::Include, bool allowAutoRule=true)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Entry</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6c3cca935f588cd3ce14b9ea8e077a4d</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Entry</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8f6a598272b876b9f4bf8e3cff0a974d</anchor>
      <arglist>(Verbosity verbosity, const void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Entry</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a764d843b292c608d125b17e68480d143</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Entry</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7f16d440005d604207e93de5f5bcae8b</anchor>
      <arglist>(Verbosity verbosity, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7cdf87c0b7a9162f2c748b35f421a218</anchor>
      <arglist>(const TString &amp;domain, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afb10be657f483af50f2dd2e47ca8ac27</anchor>
      <arglist>(void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a99504f65048f664e85268b185682f7ac</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a605156badc9cabaf2391bc99c398bde2</anchor>
      <arglist>(const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API core::Logger *</type>
      <name>GetLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a829395dc991b4aed5a09ef5aa77e3e12</anchor>
      <arglist>(const String &amp;loggerName)</arglist>
    </member>
    <member kind="function">
      <type>const TString</type>
      <name>GetName</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ace2e04c6099b72fe8d100d8736286990</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>If</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab6bd80427375239e9c52f75772162d57</anchor>
      <arglist>(bool condition, const TString &amp;domain, Verbosity verbosity, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>If</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4f78de1a4be801e12d5e69c9d7928f7f</anchor>
      <arglist>(bool condition, Verbosity verbosity, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>If</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a01ecf358ad9640f001f8435b42257ab3</anchor>
      <arglist>(bool condition, const TString &amp;domain, Verbosity verbosity, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>If</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a54d566d5308d5be55c7ce6c8bc685b5d</anchor>
      <arglist>(bool condition, Verbosity verbosity, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a057d793fc722121a883fe4f2bd070135</anchor>
      <arglist>(const TString &amp;domain, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a534f09df615c1685f74ffffc8b2eb209</anchor>
      <arglist>(void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa7971b0e50324b6e0d31195a5d5e4836</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1164ae171b5383d292b71e6bba05b9ec</anchor>
      <arglist>(const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsRegistered</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7232acc9ffe4595630e4abdaf6918ef9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>LogConfig</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ade5edb3b47eee24a0185ac0b7efa8c17</anchor>
      <arglist>(const String &amp;domain, Verbosity verbosity, const String &amp;headLine)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>MapThreadName</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3911541857ea84938dede341ceb64ddd</anchor>
      <arglist>(const String &amp;threadName, int id=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>abe9c3707a734c9442f3913ee9360ab06</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const void *logable, int type, const TString &amp;group, Scope scope=Scope::Global, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a374f4b2b2a5d441c6ea1d5d87c900e5d</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const TString &amp;msg, const TString &amp;group, Scope scope=Scope::Global, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a29b732950cc10545c4c7049562f1247f</anchor>
      <arglist>(Verbosity verbosity, const TString &amp;msg, const TString &amp;group, Scope scope, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3b2a861e3335e72f1ea400d0cf31852a</anchor>
      <arglist>(Verbosity verbosity, const TString &amp;msg, const TString &amp;group, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3fe7e7ccb6629132fc0ac2a390e6727b</anchor>
      <arglist>(Verbosity verbosity, const TString &amp;msg, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1304c179d155be221d4e5d80531a8a44</anchor>
      <arglist>(const TString &amp;msg, const TString &amp;group, Scope scope, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1aa72ece36ea563d1fa192224540f5cd</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const TString &amp;msg, Scope scope=Scope::Global, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad855bd815fb02fc6b3c59bc4a4680cf0</anchor>
      <arglist>(Verbosity verbosity, const TString &amp;msg, Scope scope, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6c81827f29e2f252dad250fbcbcb15ed</anchor>
      <arglist>(const TString &amp;msg, Scope scope, int pathLevel=0, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad8291e14a64c61bcdc55cb4cd5b3ffe1</anchor>
      <arglist>(const TString &amp;msg, int quantity=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a591671dd8ff5a4140e1588071450465a</anchor>
      <arglist>(const TString &amp;msg, const TString &amp;group, int quantity=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a84a1506acc1e04455ebc3bc724265872</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API bool</type>
      <name>RemoveLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab2aa68c613846fce90749385f1c373e1</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API core::Logger *</type>
      <name>RemoveLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa919db1f8e24e600d7f648f52a240487</anchor>
      <arglist>(const String &amp;loggerName)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>RemoveThreadDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a097f3c186dbc0dc2d13188e1c3242230</anchor>
      <arglist>(const TString &amp;scopeDomain, Scope scope, Thread *thread=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Reset</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API LogData *</type>
      <name>Retrieve</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6d6ebd5b956c1a86e602a24bfbe02b94</anchor>
      <arglist>(const TString &amp;key, Scope scope=Scope::Global, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API LogData *</type>
      <name>Retrieve</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae98f464af09413f17915bc73267f33d3</anchor>
      <arglist>(Scope scope=Scope::Global, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8a61a1c73d6a94b505c0baf9e6108bbb</anchor>
      <arglist>(const TString &amp;scopeDomain, Scope scope, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4b9be1d512730ff13756ee388a3e20a3</anchor>
      <arglist>(const TString &amp;scopeDomain, Scope scope, Thread *thread)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetDomainSubstitutionRule</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a57e92057e7a33c93ff16a677df6db52b</anchor>
      <arglist>(const TString &amp;domainPath, const TString &amp;replacement)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7c865720d8a1df7f2df6ee0b130abca9</anchor>
      <arglist>(const void *logable, int type, Scope scope, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a218d51eec9cff785c6df0f91baf965c1</anchor>
      <arglist>(const void *logable, int type, Scope scope, Thread *thread)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3534f0ed8caa9504f58cf1a8fc7ae2d3</anchor>
      <arglist>(const TString &amp;logable, Scope scope, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a26f41fad430c36f0a2518642331115a8</anchor>
      <arglist>(const TString &amp;logable, Scope scope, Thread *thread)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac257a2345d3c5d4223b9861cd32309dd</anchor>
      <arglist>(const void *logable, int type, const TString &amp;domain=nullptr, lib::enums::Inclusion otherPLs=lib::enums::Inclusion::Include)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6da7c7ea4a8b7956e37772963bf885ce</anchor>
      <arglist>(const TString &amp;logable, const TString &amp;domain=nullptr, Inclusion otherPLs=Inclusion::Include)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a81ef55056de37ef21728a427ee665120</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSourcePathTrimRule</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ace0e192fa14eb0d6a522e06e69e5402b</anchor>
      <arglist>(const TString &amp;path, Inclusion includeString=Inclusion::Exclude, int trimOffset=0, Case sensitivity=Case::Ignore, Inclusion global=Inclusion::Include)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1e977d06d962d8afce696058345f94f4</anchor>
      <arglist>(lib::time::Ticks startTime=lib::time::Ticks(0), const String &amp;loggerName=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a717cc8dfcf1a68396ca4bd060eca1c75</anchor>
      <arglist>(time_t startTime, const String &amp;loggerName=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af0daf981d6d3e6bee367e90c2cdd7711</anchor>
      <arglist>(LPFILETIME startTime, const String &amp;loggerName=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetVerbosity</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a31dbb9788d52da7bc7376da0a03a3730</anchor>
      <arglist>(core::Logger *logger, Verbosity verbosity, const TString &amp;domain=TString(&quot;/&quot;), int priority=PrioSource)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetVerbosity</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad7ea38441082c8a2f995c45e8948b0c7</anchor>
      <arglist>(const String &amp;loggerName, Verbosity verbosity, const TString &amp;domain=TString(&quot;/&quot;), int priority=PrioSource)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a03fbc3e701040c7543830e9009b92ae2</anchor>
      <arglist>(LogData *data, const TString &amp;key, Scope scope=Scope::Global, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7e726e7707a926643b25ede72388fcc2</anchor>
      <arglist>(LogData *data, Scope scope=Scope::Global, int pathLevel=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aefc98d380005814de3f5b77cd75782c3</anchor>
      <arglist>(const TString &amp;domain, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af60088d3d1396e844d744c171f3e91b3</anchor>
      <arglist>(void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a536087f02433ec49f75c9f5d7918ddd2</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8a2723a1773a6284b17ca68d0cf05bcf</anchor>
      <arglist>(const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acc935824995fd1701feb05ca9be8029d</anchor>
      <arglist>(const TString &amp;domain, void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>adc0c50c09fe5044dac135fd1b72d1abc</anchor>
      <arglist>(void *logable, int type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afcfd60ee05c9410f38c52569303e29b1</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afd14515586cd059d17cff59eef98be5a</anchor>
      <arglist>(const TString &amp;msg)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::Domain</type>
      <name>domains</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af7a1bb606d5ac72b03aa6cf35988405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; DomainSubstitutionRule &gt;</type>
      <name>domainSubstitutions</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7f3139c0b1ac2de972db69d485a9481e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::Domain</type>
      <name>internalDomains</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa3529fb39b5e80492452d6fb4b669b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>maxDomainPathLength</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a71f136dd9dc7e9d48c33ad54ae5d802f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>maxLoggerNameLength</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a905f7b109e0f5efe1313db829261b824</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const aworx::TString</type>
      <name>noKeyHashKey</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae99685f280a7452b79acca0bdfd6dc7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>oneTimeWarningCircularDS</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1ff634203235e02dab39d057469ec3db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeStore&lt; AString * &gt;</type>
      <name>scopeDomains</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0b8621c72cad2bd075810e7d8641c327</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeInfo</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a39702a71b03e2768266e8bfbef7d6c62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeStore&lt; std::map&lt; AString, LogData * &gt; * &gt;</type>
      <name>scopeLogData</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a031d54d92dd3ebf60e76609c1164133c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeStore&lt; std::map&lt; AString, int &gt; * &gt;</type>
      <name>scopeLogOnce</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4fe9fdff3ef94ccf56c20bba13571e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeStore&lt; core::Logable * &gt;</type>
      <name>scopePrefixes</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8b2fdf701e870e1932cbe2ebe34ea70c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::ScopeInfo::ThreadDictionary</type>
      <name>threadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aaa1e0a8fb5a0deba7ca52242bfa582c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::Logables</type>
      <name>tmpLogables</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a105bef857d9833bf0646546f497e19d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API bool</type>
      <name>checkScopeInformation</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa69a4d8c11d48465bbffe12495842142</anchor>
      <arglist>(Scope scope, int pathLevel, const TString &amp;internalDomain)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>clear</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac8bb3912a3ce86b15842e79d0b421204</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API core::Domain *</type>
      <name>evaluateResultDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9b58060c77090803e3cf92866bd90ce4</anchor>
      <arglist>(const TString &amp;domainPath)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API core::Domain *</type>
      <name>findDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af4d7254610ffa1da2fbcf77ed19251ed</anchor>
      <arglist>(core::Domain &amp;domainSystem, TString domainPath)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>getAllVerbosities</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4054bdb8cd2fe4f7a1bd9b583fde528c</anchor>
      <arglist>(core::Logger *logger, core::Domain *dom, TString *cfgStr, int cfgPriority)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>getVerbosityFromConfig</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a190a949c9c2cc69040e74ef491d257c6</anchor>
      <arglist>(core::Logger *logger, core::Domain *dom, TString *cfgStr, int cfgPriority)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API bool</type>
      <name>isThreadReleatedScope</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a09cea8594a917bd4a8e004acbf452b66</anchor>
      <arglist>(Scope scope)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>log</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>abf4f36065b0fc241ec6610d58a4e267a</anchor>
      <arglist>(core::Domain *dom, Verbosity verbosity, core::Logable &amp;logable, Inclusion prefixes)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>logConfigDomainRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad82cd87b2f33a36a7dd4a750f0d3441f</anchor>
      <arglist>(core::Domain &amp;domain, AString &amp;buffer)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>logInternal</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a921cc772993edd15813cbe3daa4777f4</anchor>
      <arglist>(Verbosity verbosity, const String &amp;subDomain, const TString &amp;msg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>once</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae5fab8772abbb100400889765325221b</anchor>
      <arglist>(const TString &amp;domain, Verbosity verbosity, const void *logable, int type, const TString &amp;group, Scope scope, int pathLevel, int quantity)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API LogData *</type>
      <name>retrieveImpl</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae09231332a3d86620476b3b87006fa82</anchor>
      <arglist>(const TString &amp;key, Scope scope, int pathLevel)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>setDomainImpl</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a34fa0de31f161bd2fe77dc0295c76952</anchor>
      <arglist>(const TString &amp;scopeDomain, Scope scope, int pathLevel, bool removeNTRSD, Thread *thread)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>setPrefixImpl</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a042f2376d21a1d317f632ac4b889e444</anchor>
      <arglist>(const void *logable, int type, Scope scope, int pathLevel, Thread *thread)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>storeImpl</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9c14c75a9aa3b27f5bedefebed8998f0</anchor>
      <arglist>(LogData *data, const TString &amp;key, Scope scope, int pathLevel)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::MemoryLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</filename>
    <base>aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="variable">
      <type>AString</type>
      <name>MemoryLog</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>ab885e710ebb2c0ae44ee92604a4d56f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>UseWCharLengthForTabAdjustments</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a3a7dfded816c72283193efb178b3c0fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a59248830037daf331304554a19a18fa1</anchor>
      <arglist>(const String &amp;name=nullptr, bool pruneESCSequences=true, bool useWCharLengthForTabAdjustments=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MemoryLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a4c1e470f494f74e508a4854c6331e7b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>logSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a32594d5f318dc7d7cdb4aed2ce86a9ac</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>aef9f1f712a57ca9d055a7adb976b6e5f</anchor>
      <arglist>(lib::enums::Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>aec9a5cf9fd771158d304efda15765384</anchor>
      <arglist>(lib::enums::Phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::Report::Message</name>
    <filename>classaworx_1_1lib_1_1Report_1_1Message.html</filename>
    <member kind="variable">
      <type>const strings::TString &amp;</type>
      <name>Contents</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>afa76585979183dca208a5db82709e8af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const strings::TString &amp;</type>
      <name>File</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>ab4336abc4c74ecd888729fd0af580e53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const strings::TString &amp;</type>
      <name>Func</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a2b44f701383104187505a36037238027</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Line</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>af5b2cae791582f6f4f975f6b25290977</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Type</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>ae011432eaca3858364b05a111f4011d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Message</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a8b57d684d8b9eb03bc4683373660211a</anchor>
      <arglist>(int type, const strings::TString &amp;msg, const strings::TString &amp;file, int line, const strings::TString &amp;func)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::MetaInfo</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</filename>
    <member kind="variable">
      <type>TString</type>
      <name>DateFormat</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>af2fb4c3f354b7666adac33e78e4a36a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Format</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a5f73a9d6a9bfabaa4a33c34831006d07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>FormatWarning</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a9b4dcaaa0d0c31151f28626b539b2c78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>LogNumberMinDigits</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a72c44479ec3d128c1208b49e4b8ede08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>NoMethodInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a3feb1a3fdbbde8059ca3007d9a7421d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>NoSourceFileInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>af44d2da6f43116de8557910776f9b1f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffDays</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a7b75d4c8a835d33c6dac1bd7416ed70a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffHours</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a9395ddf39cb846bdf260e116583203cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffMicros</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a8b7385903157de774b3d44906d0f09fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffMillis</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ac3f039b4887207a47f2868449e3b1443</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>TimeDiffMinimum</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ac72715ae7c695bbfce1fe76075a2f9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffMins</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a068b97de0fc963964de79ccb2fde412d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffNanos</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a5466a8a9826616e5082306e7d688ccd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffNone</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a33336f57dcc0d962375b72a082cd16a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeDiffSecs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a41fbed046e377a2f835b2f7e9c93c758</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeElapsedDays</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a090fd75d30917282f140e5fcdde1fe3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>TimeOfDayFormat</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a78d44b9a457f1b8a1e175b3fe7043f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>VerbosityError</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a69535f9bd8c5493447f323c5cf7f7401</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>VerbosityInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a2417488cbf15cf08bf1c373b9aac3222</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>VerbosityVerbose</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a78d18da89faf78000af7767edbd48249</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>VerbosityWarning</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>accf8a9e6cd0f83806e46a5b3998965d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MetaInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a7d8a1047142018ffc32e85ca0bf21df0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API int</type>
      <name>Write</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a037523cdb14e8bae567b8fef2d102009</anchor>
      <arglist>(TextLogger &amp;logger, AString &amp;buffer, core::Domain &amp;domain, Verbosity verbosity, ScopeInfo &amp;scope)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::time::TicksCalendarTime</type>
      <name>callerDateTime</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a594357dd2afccbf86f5b6dfcdda82bbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API int</type>
      <name>processVariable</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>adea560dbe05cd27b8d3313d5bd202817</anchor>
      <arglist>(TextLogger &amp;logger, core::Domain &amp;domain, Verbosity verbosity, ScopeInfo &amp;scope, AString &amp;dest, Substring &amp;variable)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>writeTimeDiff</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a3e51ddb2d0d6ce33302bf0d16b1328fb</anchor>
      <arglist>(AString &amp;buffer, int_fast64_t diffNanos)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::containers::PathMap::Iterator::NodeAndChild</name>
    <filename>structaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator_1_1NodeAndChild.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>childNo</name>
      <anchorfile>structaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator_1_1NodeAndChild.html</anchorfile>
      <anchor>ac10cf46c3127cd5d178f7dafd27307eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const PathMap&lt; StoreT &gt; *</type>
      <name>node</name>
      <anchorfile>structaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator_1_1NodeAndChild.html</anchorfile>
      <anchor>affa9990544a6dc2526546efc06c9d391</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NodeAndChild</name>
      <anchorfile>structaworx_1_1lib_1_1containers_1_1PathMap_1_1Iterator_1_1NodeAndChild.html</anchorfile>
      <anchor>a20a6c2f03983e9a440e87bf1564b4766</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; *node, int childNo)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::NumberFormat</name>
    <filename>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</filename>
    <member kind="variable" static="yes">
      <type>static ALIB_API strings::NumberFormat</type>
      <name>Global</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a9c9a27c7479023730cc33644fc6c9164</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>DecimalExponentSeparator</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a522f4eafcaecbe8d0653d5ca4a33a9b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>DecimalPointCharacter</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>ac69a618985c8aa8fdec834264d317b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>DecimalPointCharacters</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a786b45246188c9d3c25e80fede6de8b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ForceScientificFormat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>ae4968ebb3e654b4b07f58e13d2786dae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>FractionalDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a6c90dcda5ed7d0ecdbc8ec0aa9c76ac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MinIntegralDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a722a7a5cfeadae332ec66b2c79e9c116</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>WriteExponentPlusSign</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a6c00bcda73309af42240644e7b354a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>FloatToString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a50a4acaac277fd7236485b928f5ec1c3</anchor>
      <arglist>(double value, char *buffer, int idx)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>IntegerToString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a2d7340075d3cacbd41d9fc16c968c217</anchor>
      <arglist>(uint_fast64_t value, char *buffer, int idx, int minDigits)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetFromLocale</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a286f8e0f3c8b0faa574522a25fbb0912</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>StringToFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a207b4a145cc239c0724a12de60ba558d</anchor>
      <arglist>(const String &amp;src, int &amp;idx)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>StringToInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a91f18c4d647fe4d49f6e286fa785bc5c</anchor>
      <arglist>(const String &amp;src, int &amp;idx)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::ObjectConverter</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ObjectConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a6e913a253720dcb333b6205b4272709d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>ConvertObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a8420c7f2bc561caf4977bf17ab7d8af6</anchor>
      <arglist>(const Logable &amp;logable, AString &amp;target)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::Ownable</name>
    <filename>classaworx_1_1lib_1_1Ownable.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a07a42f9930e2b2f9b94a3d47d3088532</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a4dc7ecb0d192d6cccc9287daaf0eca0f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>acquirementLineNumber</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a7d085fb917fb26fa76fad94d9296665d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>strings::TString</type>
      <name>acquirementMethodName</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a34743946c0a8598a13feea2b3c7944eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>strings::TString</type>
      <name>acquirementSourcefile</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>ae9f15c83b17c4bab35858650c98c44d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::Owner</name>
    <filename>structaworx_1_1lib_1_1Owner.html</filename>
    <member kind="function">
      <type></type>
      <name>Owner</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a514baed722d3c59c870ad9579f7002ae</anchor>
      <arglist>(Ownable &amp;ownable, const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Owner</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>ac22eca8fa24d998053adc01cde626b52</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ownable &amp;</type>
      <name>ownable</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a33f6a794c5fbaddcd7b726da2492c4d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void *</type>
      <name>operator new</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a5b996753d27ee6aa451e57a8ad036ff2</anchor>
      <arglist>(size_t)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void *</type>
      <name>operator new</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a8b8a5b77612e74d607419f697801f78c</anchor>
      <arglist>(size_t, void *)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void *</type>
      <name>operator new[]</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>af0072d761e6c74c852e9c08861249007</anchor>
      <arglist>(size_t)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void *</type>
      <name>operator new[]</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a712ceeb8f0cad22b42d82c702b750eac</anchor>
      <arglist>(size_t, void *)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Owner &amp;</type>
      <name>operator=</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>abc04222281a5040c88978fc8cc5410f0</anchor>
      <arglist>(const Owner &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::containers::PathMap</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap.html</filename>
    <templarg>StoreT</templarg>
    <class kind="class">aworx::lib::containers::PathMap::Iterator</class>
    <member kind="variable">
      <type>std::vector&lt; PathMap * &gt;</type>
      <name>Childs</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a422c2605154bc2f2293a700bb3a0ad58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PathMap *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ada6ee4f09fb99fb511bcab41e0e56a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>StoreT</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>acc64411e4973d80d6983e983f9ce7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aaccccfd0b10107ddbacf38c91f873caa</anchor>
      <arglist>(PathMap *parent=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a822667eea97b87b37dd5bc7ac2604df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PathMap *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a7046c5973df23b42d51def0cc83ec30a</anchor>
      <arglist>(const TString &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a8f18aa974dae0df745dcb929542c462a</anchor>
      <arglist>(PathMap *node)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>PathMap *</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ae5b636df31556bf9f00d3b88c769cbf1</anchor>
      <arglist>(Substring &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PathMap&lt; aworx::lib::strings::AString * &gt;</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap.html</filename>
    <member kind="variable">
      <type>std::vector&lt; PathMap * &gt;</type>
      <name>Childs</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a422c2605154bc2f2293a700bb3a0ad58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PathMap *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ada6ee4f09fb99fb511bcab41e0e56a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>aworx::lib::strings::AString *</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>acc64411e4973d80d6983e983f9ce7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aaccccfd0b10107ddbacf38c91f873caa</anchor>
      <arglist>(PathMap *parent=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a822667eea97b87b37dd5bc7ac2604df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PathMap *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a7046c5973df23b42d51def0cc83ec30a</anchor>
      <arglist>(const TString &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a8f18aa974dae0df745dcb929542c462a</anchor>
      <arglist>(PathMap *node)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>PathMap *</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ae5b636df31556bf9f00d3b88c769cbf1</anchor>
      <arglist>(Substring &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PathMap&lt; core::aworx::lox::core::Logable * &gt;</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap.html</filename>
    <member kind="variable">
      <type>std::vector&lt; PathMap * &gt;</type>
      <name>Childs</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a422c2605154bc2f2293a700bb3a0ad58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PathMap *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ada6ee4f09fb99fb511bcab41e0e56a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>core::aworx::lox::core::Logable *</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>acc64411e4973d80d6983e983f9ce7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aaccccfd0b10107ddbacf38c91f873caa</anchor>
      <arglist>(PathMap *parent=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a822667eea97b87b37dd5bc7ac2604df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PathMap *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a7046c5973df23b42d51def0cc83ec30a</anchor>
      <arglist>(const TString &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a8f18aa974dae0df745dcb929542c462a</anchor>
      <arglist>(PathMap *node)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>PathMap *</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ae5b636df31556bf9f00d3b88c769cbf1</anchor>
      <arglist>(Substring &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PathMap&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt;</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap.html</filename>
    <member kind="variable">
      <type>std::vector&lt; PathMap * &gt;</type>
      <name>Childs</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a422c2605154bc2f2293a700bb3a0ad58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PathMap *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ada6ee4f09fb99fb511bcab41e0e56a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>acc64411e4973d80d6983e983f9ce7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aaccccfd0b10107ddbacf38c91f873caa</anchor>
      <arglist>(PathMap *parent=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a822667eea97b87b37dd5bc7ac2604df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PathMap *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a7046c5973df23b42d51def0cc83ec30a</anchor>
      <arglist>(const TString &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a8f18aa974dae0df745dcb929542c462a</anchor>
      <arglist>(PathMap *node)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>PathMap *</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ae5b636df31556bf9f00d3b88c769cbf1</anchor>
      <arglist>(Substring &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PathMap&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt;</name>
    <filename>classaworx_1_1lib_1_1containers_1_1PathMap.html</filename>
    <member kind="variable">
      <type>std::vector&lt; PathMap * &gt;</type>
      <name>Childs</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a422c2605154bc2f2293a700bb3a0ad58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PathMap *</type>
      <name>Parent</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ada6ee4f09fb99fb511bcab41e0e56a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>acc64411e4973d80d6983e983f9ce7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aaccccfd0b10107ddbacf38c91f873caa</anchor>
      <arglist>(PathMap *parent=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PathMap</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a822667eea97b87b37dd5bc7ac2604df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PathMap *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a7046c5973df23b42d51def0cc83ec30a</anchor>
      <arglist>(const TString &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>a8f18aa974dae0df745dcb929542c462a</anchor>
      <arglist>(PathMap *node)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>PathMap *</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1containers_1_1PathMap.html</anchorfile>
      <anchor>ae5b636df31556bf9f00d3b88c769cbf1</anchor>
      <arglist>(Substring &amp;key, bool create, const TString &amp;separators)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::PlainTextLogger</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</filename>
    <base>aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable">
      <type>bool</type>
      <name>PruneESCSequences</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a9d44a2f52e37f22c5893a1c174251749</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>PlainTextLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a2f3dfc9db13a16de7292abe4ca45bc82</anchor>
      <arglist>(const String &amp;name, const String &amp;typeName, bool usesStdStreams)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~PlainTextLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a2780280e08368bd1ee9de360d1c07a6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>logSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>aa445d82f16d9fe9da5b080028805447e</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>logText</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>aa7e70b90717f0429abf0990e5e12ad9f</anchor>
      <arglist>(core::Domain &amp;domain, Verbosity verbosity, AString &amp;msg, core::ScopeInfo &amp;scope, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a6cd5422564d767d3a52b271308ee79a2</anchor>
      <arglist>(lib::enums::Phase phase)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::PreallocatedString</name>
    <filename>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</filename>
    <templarg>TCapacity</templarg>
    <base>aworx::lib::strings::AString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ac585a9d67e12366867f16cdf65db1593</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8fcc38ef326fb2c1d64ee7e2fa6df7b8</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a66fcd18865b8c604df35c29578f3f3d7</anchor>
      <arglist>(PreallocatedString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a026da30134930f13e104ee6a552bdc6d</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ad716f6b3fe53cf699bf3a680d89ca3d9</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a5b54d15c29b480c2c654ac5539a4c2e7</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>PreallocatedString&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8d45c282eb1069917c4a0a1a5b76caac</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PreallocatedString&lt; 16 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</filename>
    <base>aworx::lib::strings::AString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ac585a9d67e12366867f16cdf65db1593</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8fcc38ef326fb2c1d64ee7e2fa6df7b8</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a66fcd18865b8c604df35c29578f3f3d7</anchor>
      <arglist>(PreallocatedString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a026da30134930f13e104ee6a552bdc6d</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ad716f6b3fe53cf699bf3a680d89ca3d9</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a5b54d15c29b480c2c654ac5539a4c2e7</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>PreallocatedString&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8d45c282eb1069917c4a0a1a5b76caac</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PreallocatedString&lt; 256 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</filename>
    <base>aworx::lib::strings::AString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ac585a9d67e12366867f16cdf65db1593</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8fcc38ef326fb2c1d64ee7e2fa6df7b8</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a66fcd18865b8c604df35c29578f3f3d7</anchor>
      <arglist>(PreallocatedString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a026da30134930f13e104ee6a552bdc6d</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ad716f6b3fe53cf699bf3a680d89ca3d9</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a5b54d15c29b480c2c654ac5539a4c2e7</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>PreallocatedString&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8d45c282eb1069917c4a0a1a5b76caac</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PreallocatedString&lt; 32 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</filename>
    <base>aworx::lib::strings::AString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ac585a9d67e12366867f16cdf65db1593</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8fcc38ef326fb2c1d64ee7e2fa6df7b8</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a66fcd18865b8c604df35c29578f3f3d7</anchor>
      <arglist>(PreallocatedString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a026da30134930f13e104ee6a552bdc6d</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ad716f6b3fe53cf699bf3a680d89ca3d9</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a5b54d15c29b480c2c654ac5539a4c2e7</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>PreallocatedString&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8d45c282eb1069917c4a0a1a5b76caac</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PreallocatedString&lt; 64 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</filename>
    <base>aworx::lib::strings::AString</base>
    <member kind="function">
      <type>constexpr</type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ac585a9d67e12366867f16cdf65db1593</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8fcc38ef326fb2c1d64ee7e2fa6df7b8</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a66fcd18865b8c604df35c29578f3f3d7</anchor>
      <arglist>(PreallocatedString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a026da30134930f13e104ee6a552bdc6d</anchor>
      <arglist>(AString &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>ad716f6b3fe53cf699bf3a680d89ca3d9</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PreallocatedString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a5b54d15c29b480c2c654ac5539a4c2e7</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>PreallocatedString&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8d45c282eb1069917c4a0a1a5b76caac</anchor>
      <arglist>(const PreallocatedString &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1PreallocatedString.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::system::ProcessInfo</name>
    <filename>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>CmdLine</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a38741324f2f4c6aa56dc430d4388a76c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>ConsoleTitle</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a39dfc3f00493a74b8ab6907dec8c80ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>ExecName</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>ab5fca5813a5614d7a284466c074bcacd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>PID</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>ab3394b1e9c9810e4172bb26364932511</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>PPID</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a2e9f2dde638643f2724049a1c5e559f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Stat</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>aa1d0ce36cf7d7f9338610388ff42fa29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>statPGRP</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a9dd69d834742023497d9c6f3eeaf3f82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>StatState</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>aa313b8c5a87a49b703b0887651b1eef7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const ProcessInfo &amp;</type>
      <name>Current</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a1e9c04463bb57d8ae52cc6f5470ab44b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProcessInfo</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>abd0dc1bed4dd3aa2cb51255d42b77f3b</anchor>
      <arglist>(const String &amp;PID)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>aca957846d7a97dfd4a2d168ff1230a39</anchor>
      <arglist>(const String &amp;PID)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API ProcessInfo</type>
      <name>current</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>afabfc6a52ba3d7842fe4c2b0bdc7cf6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ProcessInfo</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a4219f7fc14fa3ed88a6511e0efc33e90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API bool</type>
      <name>get</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>ac9e6c4357814bf5e9689600968ec16fc</anchor>
      <arglist>(const String &amp;PID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>getStatField</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1ProcessInfo.html</anchorfile>
      <anchor>a98338111ca0a208ada56d8e901e1fdd7</anchor>
      <arglist>(int fieldNo, AString &amp;result)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ReadLineFromIStream</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>BufferSize</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>ae24de3d1938064e4a05dd06bc6b422d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsEOF</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>ade6dbc4e4f8e0b45e0fbe023f5ed8ddd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::istream &amp;</type>
      <name>istream</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>a6727ff65df9fd553e1eca11c56a803c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MaxLineWidth</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>ac84b9d73bc2f084bd6485b1460038408</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>enums::CurrentData</type>
      <name>TargetData</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>ab84e7329548f6b5f9d91a6f3b2be64a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReadLineFromIStream</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ReadLineFromIStream.html</anchorfile>
      <anchor>ada35726be6a9b415e004cba33067b05c</anchor>
      <arglist>(std::istream &amp;istream, enums::CurrentData targetData=enums::CurrentData::Clear, int bufferSize=256, int maxLineWidth=4096)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::Report</name>
    <filename>classaworx_1_1lib_1_1Report.html</filename>
    <class kind="class">aworx::lib::Report::Message</class>
    <member kind="function" static="yes">
      <type>static Report &amp;</type>
      <name>GetDefault</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a1d9ac8f09122b5310b6776784882de6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>DoReport</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a3977916df8d86dcb2c61e95d9b457b38</anchor>
      <arglist>(int type, const lib::strings::TString &amp;msg, const lib::strings::TString &amp;file, int line, const lib::strings::TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ReportWriter *</type>
      <name>PeekWriter</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ac3c72f0916841cb53a007d099a86e4d3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>PopHaltFlags</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ade3d2cc17cc7c56d59b88a15ee247ca0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>PopWriter</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a51cc05fbf386a19049a2e80bd32a0541</anchor>
      <arglist>(ReportWriter *checkWriter)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>PushHaltFlags</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a7983ee7befb74df86990b506dfaaf6a0</anchor>
      <arglist>(bool haltOnErrors, bool haltOnWarnings)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>PushWriter</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a15a55ca31cef913041443efc8a13494f</anchor>
      <arglist>(ReportWriter *newWriter)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API Report *</type>
      <name>defaultReport</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a85731ee839db2fafc226b9a8281167f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::stack&lt; int &gt;</type>
      <name>haltAfterReport</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ae0aa2499cfb7dcf29f7955cde68c79bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>threads::ThreadLock *</type>
      <name>lock</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ad083e81bb83e9548b93f22631c5f0477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>recursionBlocker</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>acb62b28ab9467a03c940908b8f6649d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::stack&lt; ReportWriter * &gt;</type>
      <name>writers</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a46a7dd034e50f98088be4da9bb180524</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::ReportWriter</name>
    <filename>classaworx_1_1lib_1_1ReportWriter.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ReportWriter</name>
      <anchorfile>classaworx_1_1lib_1_1ReportWriter.html</anchorfile>
      <anchor>aacb613601745319beb402a265be497e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>NotifyActivation</name>
      <anchorfile>classaworx_1_1lib_1_1ReportWriter.html</anchorfile>
      <anchor>aff02ec3de8e94bd4d906e89168849ac8</anchor>
      <arglist>(enums::Phase phase)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Report</name>
      <anchorfile>classaworx_1_1lib_1_1ReportWriter.html</anchorfile>
      <anchor>a3a3ec6ba9fc90c059952efc82b021d63</anchor>
      <arglist>(const Report::Message &amp;report)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::threads::Runnable</name>
    <filename>classaworx_1_1lib_1_1threads_1_1Runnable.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Runnable</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Runnable.html</anchorfile>
      <anchor>a93a94435fb3d643aacf328fcc497d9ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Run</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Runnable.html</anchorfile>
      <anchor>adc27ee0d7b66b8795db722f47a615cfe</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::ScopeDump</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeDump.html</filename>
    <member kind="function">
      <type></type>
      <name>ScopeDump</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a62e1dda70b97ff9daa0b12f0e5670b80</anchor>
      <arglist>(ScopeInfo::ThreadDictionary &amp;threadDictionary, const TString noKeyHashKey, AString &amp;target, int maxKeyLength=10)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API int</type>
      <name>writeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a2ac85963ae7b731f047051b4d593b58e</anchor>
      <arglist>(ScopeStore&lt; T &gt; *store, int indentSpaces)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API int</type>
      <name>writeStoreMap</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a0300c0e3bf0ca655848b1737e500a9f9</anchor>
      <arglist>(ScopeStore&lt; T &gt; *store)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>maxKeyLength</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>ace5c16296f35665a0346922cdb706cc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const TString</type>
      <name>noKeyHashKey</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>aa191e3a8df124f0e744972df0322fdda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString &amp;</type>
      <name>target</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a3d93c7a0f172c1aa8064bcb3ad11919a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo::ThreadDictionary &amp;</type>
      <name>threadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>ac9c80619e40a37f61c24b594febf1782</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API AString &amp;</type>
      <name>storeKeyToScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a5a2f983c8c5be78a45fbbeb8c4bde6a4</anchor>
      <arglist>(const lib::containers::PathMap&lt; T &gt; &amp;map)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API AString &amp;</type>
      <name>storeThreadToScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>aa8e35644877b44cceea3c76ef1961b6c</anchor>
      <arglist>(int threadID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API int</type>
      <name>writeStoreMapHelper</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeDump.html</anchorfile>
      <anchor>a9b273d5cd4060583f81ea934d8976d46</anchor>
      <arglist>(std::map&lt; AString, T &gt; &amp;map, const TString &amp;prefix)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::ScopeInfo</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</filename>
    <member kind="typedef">
      <type>std::map&lt; int, String32 &gt;</type>
      <name>ThreadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a99735dc703a3e0c252ea69a22c1687d2</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">aworx::lox::core::ScopeInfo::SourceFile</class>
    <class kind="struct">aworx::lox::core::ScopeInfo::SourcePathTrimRule</class>
    <member kind="variable" static="yes">
      <type>static ALIB_API int</type>
      <name>DefaultCacheSize</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a01d0e5f6ac830884f21e5086d1d91b94</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>ScopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a6af06b1fa6e8772eff948e87947fbb3b</anchor>
      <arglist>(const TString &amp;name, const std::map&lt; int, String32 &gt; &amp;threadDictionary)</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>GetFileName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a28b15d71e257d5eba8fc981ffb1421f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>GetFileNameWithoutExtension</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>acba47760057c72724b081ae6a38465e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>GetFullPath</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ae2c23eee898650cd7880a370e7ce5899</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLineNumber</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ae5c4253d48d562a076016c054d847ccc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const TString &amp;</type>
      <name>GetLoxName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>acda6a047a2327d0ef0819057a0e5c580</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>GetMethod</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a8bdcd510e436ae95bce067beae21b69a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const TString &amp;</type>
      <name>GetOrigFile</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>af4805883509db0aa99eb41e0e75b305d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a6ada61025e16fbfcd69fa53b531eb63a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const aworx::String &amp;</type>
      <name>GetThreadNameAndID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ae0a6b0dbae09af09760197641e5a4025</anchor>
      <arglist>(int *id)</arglist>
    </member>
    <member kind="function">
      <type>const Ticks &amp;</type>
      <name>GetTimeStamp</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aac63d502ad9e3127e63ecc389c36d078</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>GetTrimmedPath</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aa35b14e49f6fa87ff1011fc2f3a4fcc3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aef667a335cd43ee15210ae8f002037dd</anchor>
      <arglist>(const TString &amp;source, int lineNumber, const TString &amp;method, Thread *thread)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetSourcePathTrimRule</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aaccc72216941cd9da1aa1bf22010e313</anchor>
      <arglist>(const TString &amp;path, Inclusion includeString, int trimOffset, Case sensitivity, Inclusion global)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API std::vector&lt; SourcePathTrimRule &gt;</type>
      <name>GlobalSPTRs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a3ff8b25900c8fb4a39086e55a4de2f15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API bool</type>
      <name>GlobalSPTRsReadFromConfig</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a4b4cc9b47565ee962c6488358e236c65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SourceFile *</type>
      <name>actual</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a9e5d069be80c5f7ef34c1aa0abd7e169</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>AutoDetectTrimableSourcePath</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ac69d17599ca644e4c9e9be0f42ca7361</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SourceFile *</type>
      <name>cache</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a0483fbbfacc1e2fedddd3360cf1b7a89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>uint_fast64_t</type>
      <name>cacheRun</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a7777e336e451a64b8311a14136e9a062</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>cacheSize</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a21f5d4e833c67e26ce27afd3d9f23288</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; SourcePathTrimRule &gt;</type>
      <name>LocalSPTRs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a1a109984041e560099b534dd1ab4c10c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String32</type>
      <name>loxName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a17e561c001584e6fc3a4b9445deea701</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>origLine</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aea32b63d1b8fdc55f090b2b8b41b3d6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>TString</type>
      <name>origMethod</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ad28921e2af5d6ded371d6d1b33ade6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Thread *</type>
      <name>thread</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a743989b66f3b52f1eda2a8498a93da0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const ThreadDictionary &amp;</type>
      <name>threadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ab89d14dc857db74727211f5fcf3c138f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>threadName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>ab0235bb40987a8310ebd7e8500b96975</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>timeStamp</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a4e72dac5d168369a754893772395f0d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>getPathSeparator</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>aa6d59afb05181160d621a1e9e8875a40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API void</type>
      <name>trimPath</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>adce30083ede7f1172f4f92c5b627e837</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ScopeInfo &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeInfo.html</anchorfile>
      <anchor>a79aef84c80ea77a4800b7aa7179d1aa3</anchor>
      <arglist>(const ScopeInfo &amp;op)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::ScopeStore</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStore.html</filename>
    <templarg>StoreT</templarg>
    <member kind="variable">
      <type>StoreT</type>
      <name>globalStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad5f544834c72f2e639cda32bfdf4914b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::containers::PathMap&lt; StoreT &gt; *</type>
      <name>languageStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a1251572d8e2460a60f89fd2372e71c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; StoreT &gt; &gt;</type>
      <name>threadInnerStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a344205164cffc3c7c0a6191c9a716b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; StoreT &gt; &gt;</type>
      <name>threadOuterStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aaedb67f0bf7ce679a991c7ee988e1cc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac7a74581c38faf240883a9a395547d5a</anchor>
      <arglist>(ScopeInfo &amp;scopeInfo, bool cfgSingleThreadValue)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9bff9f3eb2193028b398787f43ca19d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a8276b692283d7725759466633f2c8211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>StoreT</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a19b162b0d416fc5be7f1f6a91c718c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitAccess</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a15cc8a2338769a04748e8964f2659b42</anchor>
      <arglist>(Scope scope, int pathLevel, int threadID)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitWalk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5c609208e4e06536121b94f6896fab1e</anchor>
      <arglist>(Scope startScope, StoreT localObject)</arglist>
    </member>
    <member kind="function">
      <type>StoreT</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a4b6e9ae247a950ed1b5d5d82c72b1440</anchor>
      <arglist>(StoreT value)</arglist>
    </member>
    <member kind="function">
      <type>StoreT</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5361906d7ce4b2ca6c3f676c85cf01fd</anchor>
      <arglist>(StoreT value)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API StoreT</type>
      <name>Walk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a262f597e568a196dcb284fb1c859c8d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actPathLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa5ede8468c729de0886d3bc84d31714e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::containers::PathMap&lt; StoreT &gt; *</type>
      <name>actPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a77c6ecbc68ffa22251428b4763a3d3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Scope</type>
      <name>actScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ab420b6d519025a485c6345895ad174ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>afd0f796ebbfae3564416016c197c27b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>cfgSingleThreadValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac8ebbb91a987a22c90eae5a4c72ecbc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyLanguageNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a531fce640b5915cd0496ba8c3c1058db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo &amp;</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aef20e807838c38a874e2952fa989535b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>walking</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa99316a33a7768a6af77f01edda34ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>StoreT</type>
      <name>walkLocalObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a82821b811e042ad4ca39396346cd49e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>walkNextThreadIdx</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9928f44e5399d356c4380ab105e48941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; StoreT &gt; *</type>
      <name>walkThreadValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>abf7b7f408957d23da2c7b6fc692436cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>StoreT</type>
      <name>access</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9d948185e80ad3706923867cfe608317</anchor>
      <arglist>(int cmd, StoreT value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad1305df36b6dfcde87eded99e9e9424b</anchor>
      <arglist>(bool create)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ScopeStore&lt; aworx::lib::strings::AString * &gt;</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStore.html</filename>
    <member kind="variable">
      <type>aworx::lib::strings::AString *</type>
      <name>globalStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad5f544834c72f2e639cda32bfdf4914b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::containers::PathMap&lt; aworx::lib::strings::AString * &gt; *</type>
      <name>languageStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a1251572d8e2460a60f89fd2372e71c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; aworx::lib::strings::AString * &gt; &gt;</type>
      <name>threadInnerStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a344205164cffc3c7c0a6191c9a716b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; aworx::lib::strings::AString * &gt; &gt;</type>
      <name>threadOuterStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aaedb67f0bf7ce679a991c7ee988e1cc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac7a74581c38faf240883a9a395547d5a</anchor>
      <arglist>(ScopeInfo &amp;scopeInfo, bool cfgSingleThreadValue)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9bff9f3eb2193028b398787f43ca19d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a8276b692283d7725759466633f2c8211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>aworx::lib::strings::AString *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a19b162b0d416fc5be7f1f6a91c718c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitAccess</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a15cc8a2338769a04748e8964f2659b42</anchor>
      <arglist>(Scope scope, int pathLevel, int threadID)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitWalk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5c609208e4e06536121b94f6896fab1e</anchor>
      <arglist>(Scope startScope, aworx::lib::strings::AString *localObject)</arglist>
    </member>
    <member kind="function">
      <type>aworx::lib::strings::AString *</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a4b6e9ae247a950ed1b5d5d82c72b1440</anchor>
      <arglist>(aworx::lib::strings::AString *value)</arglist>
    </member>
    <member kind="function">
      <type>aworx::lib::strings::AString *</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5361906d7ce4b2ca6c3f676c85cf01fd</anchor>
      <arglist>(aworx::lib::strings::AString *value)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API aworx::lib::strings::AString *</type>
      <name>Walk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a262f597e568a196dcb284fb1c859c8d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actPathLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa5ede8468c729de0886d3bc84d31714e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::containers::PathMap&lt; aworx::lib::strings::AString * &gt; *</type>
      <name>actPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a77c6ecbc68ffa22251428b4763a3d3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Scope</type>
      <name>actScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ab420b6d519025a485c6345895ad174ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>afd0f796ebbfae3564416016c197c27b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>cfgSingleThreadValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac8ebbb91a987a22c90eae5a4c72ecbc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyLanguageNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a531fce640b5915cd0496ba8c3c1058db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo &amp;</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aef20e807838c38a874e2952fa989535b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>walking</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa99316a33a7768a6af77f01edda34ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>aworx::lib::strings::AString *</type>
      <name>walkLocalObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a82821b811e042ad4ca39396346cd49e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>walkNextThreadIdx</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9928f44e5399d356c4380ab105e48941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; aworx::lib::strings::AString * &gt; *</type>
      <name>walkThreadValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>abf7b7f408957d23da2c7b6fc692436cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>aworx::lib::strings::AString *</type>
      <name>access</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9d948185e80ad3706923867cfe608317</anchor>
      <arglist>(int cmd, aworx::lib::strings::AString *value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad1305df36b6dfcde87eded99e9e9424b</anchor>
      <arglist>(bool create)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ScopeStore&lt; core::aworx::lox::core::Logable * &gt;</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStore.html</filename>
    <member kind="variable">
      <type>core::aworx::lox::core::Logable *</type>
      <name>globalStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad5f544834c72f2e639cda32bfdf4914b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::containers::PathMap&lt; core::aworx::lox::core::Logable * &gt; *</type>
      <name>languageStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a1251572d8e2460a60f89fd2372e71c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; core::aworx::lox::core::Logable * &gt; &gt;</type>
      <name>threadInnerStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a344205164cffc3c7c0a6191c9a716b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; core::aworx::lox::core::Logable * &gt; &gt;</type>
      <name>threadOuterStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aaedb67f0bf7ce679a991c7ee988e1cc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac7a74581c38faf240883a9a395547d5a</anchor>
      <arglist>(ScopeInfo &amp;scopeInfo, bool cfgSingleThreadValue)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9bff9f3eb2193028b398787f43ca19d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a8276b692283d7725759466633f2c8211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>core::aworx::lox::core::Logable *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a19b162b0d416fc5be7f1f6a91c718c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitAccess</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a15cc8a2338769a04748e8964f2659b42</anchor>
      <arglist>(Scope scope, int pathLevel, int threadID)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitWalk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5c609208e4e06536121b94f6896fab1e</anchor>
      <arglist>(Scope startScope, core::aworx::lox::core::Logable *localObject)</arglist>
    </member>
    <member kind="function">
      <type>core::aworx::lox::core::Logable *</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a4b6e9ae247a950ed1b5d5d82c72b1440</anchor>
      <arglist>(core::aworx::lox::core::Logable *value)</arglist>
    </member>
    <member kind="function">
      <type>core::aworx::lox::core::Logable *</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5361906d7ce4b2ca6c3f676c85cf01fd</anchor>
      <arglist>(core::aworx::lox::core::Logable *value)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API core::aworx::lox::core::Logable *</type>
      <name>Walk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a262f597e568a196dcb284fb1c859c8d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actPathLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa5ede8468c729de0886d3bc84d31714e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::containers::PathMap&lt; core::aworx::lox::core::Logable * &gt; *</type>
      <name>actPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a77c6ecbc68ffa22251428b4763a3d3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Scope</type>
      <name>actScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ab420b6d519025a485c6345895ad174ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>afd0f796ebbfae3564416016c197c27b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>cfgSingleThreadValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac8ebbb91a987a22c90eae5a4c72ecbc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyLanguageNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a531fce640b5915cd0496ba8c3c1058db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo &amp;</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aef20e807838c38a874e2952fa989535b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>walking</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa99316a33a7768a6af77f01edda34ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::aworx::lox::core::Logable *</type>
      <name>walkLocalObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a82821b811e042ad4ca39396346cd49e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>walkNextThreadIdx</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9928f44e5399d356c4380ab105e48941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; core::aworx::lox::core::Logable * &gt; *</type>
      <name>walkThreadValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>abf7b7f408957d23da2c7b6fc692436cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>core::aworx::lox::core::Logable *</type>
      <name>access</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9d948185e80ad3706923867cfe608317</anchor>
      <arglist>(int cmd, core::aworx::lox::core::Logable *value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad1305df36b6dfcde87eded99e9e9424b</anchor>
      <arglist>(bool create)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ScopeStore&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt;</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStore.html</filename>
    <member kind="variable">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>globalStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad5f544834c72f2e639cda32bfdf4914b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::containers::PathMap&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt; *</type>
      <name>languageStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a1251572d8e2460a60f89fd2372e71c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt; &gt;</type>
      <name>threadInnerStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a344205164cffc3c7c0a6191c9a716b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt; &gt;</type>
      <name>threadOuterStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aaedb67f0bf7ce679a991c7ee988e1cc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac7a74581c38faf240883a9a395547d5a</anchor>
      <arglist>(ScopeInfo &amp;scopeInfo, bool cfgSingleThreadValue)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9bff9f3eb2193028b398787f43ca19d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a8276b692283d7725759466633f2c8211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a19b162b0d416fc5be7f1f6a91c718c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitAccess</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a15cc8a2338769a04748e8964f2659b42</anchor>
      <arglist>(Scope scope, int pathLevel, int threadID)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitWalk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5c609208e4e06536121b94f6896fab1e</anchor>
      <arglist>(Scope startScope, std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *localObject)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a4b6e9ae247a950ed1b5d5d82c72b1440</anchor>
      <arglist>(std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *value)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5361906d7ce4b2ca6c3f676c85cf01fd</anchor>
      <arglist>(std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *value)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>Walk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a262f597e568a196dcb284fb1c859c8d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actPathLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa5ede8468c729de0886d3bc84d31714e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::containers::PathMap&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt; *</type>
      <name>actPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a77c6ecbc68ffa22251428b4763a3d3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Scope</type>
      <name>actScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ab420b6d519025a485c6345895ad174ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>afd0f796ebbfae3564416016c197c27b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>cfgSingleThreadValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac8ebbb91a987a22c90eae5a4c72ecbc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyLanguageNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a531fce640b5915cd0496ba8c3c1058db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo &amp;</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aef20e807838c38a874e2952fa989535b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>walking</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa99316a33a7768a6af77f01edda34ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>walkLocalObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a82821b811e042ad4ca39396346cd49e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>walkNextThreadIdx</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9928f44e5399d356c4380ab105e48941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; * &gt; *</type>
      <name>walkThreadValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>abf7b7f408957d23da2c7b6fc692436cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *</type>
      <name>access</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9d948185e80ad3706923867cfe608317</anchor>
      <arglist>(int cmd, std::map&lt; aworx::lib::strings::AString, aworx::lox::LogData * &gt; *value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad1305df36b6dfcde87eded99e9e9424b</anchor>
      <arglist>(bool create)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ScopeStore&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt;</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStore.html</filename>
    <member kind="variable">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>globalStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad5f544834c72f2e639cda32bfdf4914b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::containers::PathMap&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt; *</type>
      <name>languageStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a1251572d8e2460a60f89fd2372e71c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt; &gt;</type>
      <name>threadInnerStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a344205164cffc3c7c0a6191c9a716b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; int, std::vector&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt; &gt;</type>
      <name>threadOuterStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aaedb67f0bf7ce679a991c7ee988e1cc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac7a74581c38faf240883a9a395547d5a</anchor>
      <arglist>(ScopeInfo &amp;scopeInfo, bool cfgSingleThreadValue)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>~ScopeStore</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9bff9f3eb2193028b398787f43ca19d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a8276b692283d7725759466633f2c8211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a19b162b0d416fc5be7f1f6a91c718c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitAccess</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a15cc8a2338769a04748e8964f2659b42</anchor>
      <arglist>(Scope scope, int pathLevel, int threadID)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>InitWalk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5c609208e4e06536121b94f6896fab1e</anchor>
      <arglist>(Scope startScope, std::map&lt; aworx::lib::strings::AString, int &gt; *localObject)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>Remove</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a4b6e9ae247a950ed1b5d5d82c72b1440</anchor>
      <arglist>(std::map&lt; aworx::lib::strings::AString, int &gt; *value)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>Store</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a5361906d7ce4b2ca6c3f676c85cf01fd</anchor>
      <arglist>(std::map&lt; aworx::lib::strings::AString, int &gt; *value)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>Walk</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a262f597e568a196dcb284fb1c859c8d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actPathLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa5ede8468c729de0886d3bc84d31714e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>lib::containers::PathMap&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt; *</type>
      <name>actPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a77c6ecbc68ffa22251428b4763a3d3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Scope</type>
      <name>actScope</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ab420b6d519025a485c6345895ad174ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>actThreadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>afd0f796ebbfae3564416016c197c27b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>cfgSingleThreadValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ac8ebbb91a987a22c90eae5a4c72ecbc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyLanguageNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a531fce640b5915cd0496ba8c3c1058db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ScopeInfo &amp;</type>
      <name>scopeInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aef20e807838c38a874e2952fa989535b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>walking</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>aa99316a33a7768a6af77f01edda34ef3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>walkLocalObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a82821b811e042ad4ca39396346cd49e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>walkNextThreadIdx</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9928f44e5399d356c4380ab105e48941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; std::map&lt; aworx::lib::strings::AString, int &gt; * &gt; *</type>
      <name>walkThreadValues</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>abf7b7f408957d23da2c7b6fc692436cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::map&lt; aworx::lib::strings::AString, int &gt; *</type>
      <name>access</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>a9d948185e80ad3706923867cfe608317</anchor>
      <arglist>(int cmd, std::map&lt; aworx::lib::strings::AString, int &gt; *value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>getPathMapNode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStore.html</anchorfile>
      <anchor>ad1305df36b6dfcde87eded99e9e9424b</anchor>
      <arglist>(bool create)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::ScopeStoreType</name>
    <filename>classaworx_1_1lox_1_1core_1_1ScopeStoreType.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static ALOX_API bool</type>
      <name>AreEqual</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStoreType.html</anchorfile>
      <anchor>ad5516ec32df909883ecac628527d7e09</anchor>
      <arglist>(StoreT first, StoreT second)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API bool</type>
      <name>IsNull</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStoreType.html</anchorfile>
      <anchor>ae5573aa455900d85f7191f38710c09f5</anchor>
      <arglist>(StoreT value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API StoreT</type>
      <name>NullValue</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1ScopeStoreType.html</anchorfile>
      <anchor>a6b093555946a852ee96996e03c376c25</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::IniFile::Section</name>
    <filename>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>Comments</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a13a7dbf15cba4c8849fdd8044b185475</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Name</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>ab3c68b8a64bf47454f94bde4ebb6de0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Variable * &gt;</type>
      <name>Variables</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a738ca476f47674d8516d09e15ce172de</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Section</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a51635002e9136e57c782638128864dbc</anchor>
      <arglist>(const String &amp;name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Section</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>ad718550e15dc3c8a9fd66717dd17e5d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Variable *</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>ad6c0495f4adb84887542660894d7aac6</anchor>
      <arglist>(const String &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>Variable *</type>
      <name>Insert</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a295f81c573fa45f08d98e19a72a814a8</anchor>
      <arglist>(const String &amp;name, const String &amp;value, const String &amp;comments=&quot;&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::threads::SmartLock</name>
    <filename>classaworx_1_1lib_1_1threads_1_1SmartLock.html</filename>
    <base>aworx::lib::threads::ThreadLock</base>
    <member kind="function">
      <type></type>
      <name>SmartLock</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>a90c2c49cbc4b52547424991f1665a8cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>a07a42f9930e2b2f9b94a3d47d3088532</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>AddAcquirer</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>ac097a5b90ddc055cbf44b6a87b8cfda6</anchor>
      <arglist>(ThreadLock *newAcquirer)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>CntAcquirers</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>a8d7f3cb41c747cf4c508db08fc60fe9f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>RemoveAcquirer</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>a2f480eaa76919774ba222225c952b874</anchor>
      <arglist>(ThreadLock *acquirer)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; ThreadLock * &gt;</type>
      <name>acquirers</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1SmartLock.html</anchorfile>
      <anchor>a69a7bacc64ce3f8afd6cc837408e532f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::core::ScopeInfo::SourceFile</name>
    <filename>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>fullPath</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>a54ee0033dccba3b71b4df46be20a8ed8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>a9a2326f35466e54c36c070829245c557</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>nameWOExt</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>ae612f42281f92db83f647e7bcb9634c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>origFile</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>a792c2a0b64091058562faaf73b0b5e9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>origFilePathSeparator</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>a92c278f6e653f2ff33c65cd197d61239</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint_fast64_t</type>
      <name>timeStamp</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>ad45eb797111ee6d571af7fffc9fc6d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>trimmedPath</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourceFile.html</anchorfile>
      <anchor>a457ff5532ac38a6fafc282764d6da378</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lox::core::ScopeInfo::SourcePathTrimRule</name>
    <filename>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</filename>
    <member kind="variable">
      <type>Inclusion</type>
      <name>IncludeString</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</anchorfile>
      <anchor>a4dfbe3fa1c6cd975f1a6a3b17dc6ac8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsPrefix</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</anchorfile>
      <anchor>af3bc9a519dad021ce04b07599d610ccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Path</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</anchorfile>
      <anchor>a5e583dd1bf88abfb28487df2f676a6e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Case</type>
      <name>Sensitivity</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</anchorfile>
      <anchor>a48bf193d2228373a7e76ba4e08137017</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>TrimOffset</name>
      <anchorfile>structaworx_1_1lox_1_1core_1_1ScopeInfo_1_1SourcePathTrimRule.html</anchorfile>
      <anchor>a400a3c8a83ee22ccb635bb8a96a1d6ca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::String</name>
    <filename>classaworx_1_1lib_1_1strings_1_1String.html</filename>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>adcffeb665e497d8c0909063e4b5df871</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a863a723eb56ea0b5fab9a838c5f27658</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a79bdef100f3c7887fd120a7a98d8062c</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a2b1f593a0b9b71d210993cea0727b419</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a5d5ce30daece7ec96d0b70ccc5d46002</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6e891964a37680c01e21dedac6ffe670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a055d87b78f69c9d039b7e12ead7aa6b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaaf24e0ec4b4b51df542cd654230c3da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaef62c8761ddd1b95824fc57b1b277b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a484ba322b1d13f2e2c90066db81179ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaf9706f704337ae92062d7b68c8f33ea</anchor>
      <arglist>(int idx) const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa43766377944d0423a71478f1bbd61e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a78fb764265a5d096e56717a52754396d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa30b895dcfaf0574aca843b212ee2602</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a0c6c00e3b4e659d0088973d4219d86b3</anchor>
      <arglist>(const String &amp;needle, int pos, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a874e198025e872dc30012ccdaef4ea71</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a34f943472db189e27586b5ad6df554f4</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa9596ce7ca16857d887ae619a42d231c</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a830c0be0e018f2e52eb311d566e61338</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6e6c71cbde80abfd17075314878964a9</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength, int regionStart, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa87398e168744e30fdae0c9641273ab2</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a8e233e56892e8dde5bbc59d232561895</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a5458d43552b4f83c721cc967f091cc4c</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a9582e8e8e4b37606065566ec88f9626d</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a4903bdaa9803322caddc87c623646a90</anchor>
      <arglist>(char needle) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>ab62c5abf6381ef65c72b97183fd64c8d</anchor>
      <arglist>(char needle, int regionStart) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a8ea4959c28189d614a7c883dae3787f5</anchor>
      <arglist>(char needle, int regionStart, int regionLength) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6ff7c059a19d1003e1d150ab86d784f8</anchor>
      <arglist>(char needle, int startIndex=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>af56c0c63f30160a0e3e44957e3409732</anchor>
      <arglist>(const String &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa7292ca793aceb1572d65a8ee444e97c</anchor>
      <arglist>(const String &amp;needles, enums::Inclusion inclusion, int startIdx=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>adc427de75c146cf8618a397833edaa9a</anchor>
      <arglist>(const String &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ToWString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a73cfa0a1eb5f3c47cb633967c8b22333</anchor>
      <arglist>(wchar_t *dest, int destCapacity, int regionStart=0, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>afe13e5000dc11709e5da14d928f838b7</anchor>
      <arglist>(int &amp;regionStart, int &amp;regionLength) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>adae84acc92cd77a04f6aaf533643a33a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a9f59b34b1f25fe00023291b678246bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>vbuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>ab060ffba71bd8a3d7067a38950b39a82</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>adcffeb665e497d8c0909063e4b5df871</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a863a723eb56ea0b5fab9a838c5f27658</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a79bdef100f3c7887fd120a7a98d8062c</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>String</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a2b1f593a0b9b71d210993cea0727b419</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a5d5ce30daece7ec96d0b70ccc5d46002</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6e891964a37680c01e21dedac6ffe670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a055d87b78f69c9d039b7e12ead7aa6b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaaf24e0ec4b4b51df542cd654230c3da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaef62c8761ddd1b95824fc57b1b277b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a484ba322b1d13f2e2c90066db81179ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aaf9706f704337ae92062d7b68c8f33ea</anchor>
      <arglist>(int idx) const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa43766377944d0423a71478f1bbd61e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a78fb764265a5d096e56717a52754396d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa30b895dcfaf0574aca843b212ee2602</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a0c6c00e3b4e659d0088973d4219d86b3</anchor>
      <arglist>(const String &amp;needle, int pos, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a874e198025e872dc30012ccdaef4ea71</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a34f943472db189e27586b5ad6df554f4</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa9596ce7ca16857d887ae619a42d231c</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a830c0be0e018f2e52eb311d566e61338</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6e6c71cbde80abfd17075314878964a9</anchor>
      <arglist>(const String &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength, int regionStart, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa87398e168744e30fdae0c9641273ab2</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a8e233e56892e8dde5bbc59d232561895</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a5458d43552b4f83c721cc967f091cc4c</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a9582e8e8e4b37606065566ec88f9626d</anchor>
      <arglist>(const String &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a4903bdaa9803322caddc87c623646a90</anchor>
      <arglist>(char needle) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>ab62c5abf6381ef65c72b97183fd64c8d</anchor>
      <arglist>(char needle, int regionStart) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a8ea4959c28189d614a7c883dae3787f5</anchor>
      <arglist>(char needle, int regionStart, int regionLength) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a6ff7c059a19d1003e1d150ab86d784f8</anchor>
      <arglist>(char needle, int startIndex=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>af56c0c63f30160a0e3e44957e3409732</anchor>
      <arglist>(const String &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>aa7292ca793aceb1572d65a8ee444e97c</anchor>
      <arglist>(const String &amp;needles, enums::Inclusion inclusion, int startIdx=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>adc427de75c146cf8618a397833edaa9a</anchor>
      <arglist>(const String &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ToWString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>a73cfa0a1eb5f3c47cb633967c8b22333</anchor>
      <arglist>(wchar_t *dest, int destCapacity, int regionStart=0, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1String.html</anchorfile>
      <anchor>afe13e5000dc11709e5da14d928f838b7</anchor>
      <arglist>(int &amp;regionStart, int &amp;regionLength) const </arglist>
    </member>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1String">CPP_STRINGS_AS_NULLSTATE</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1String">CPP_STRINGS_AS_NC</docanchor>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::StringConverter</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1StringConverter.html</filename>
    <base>aworx::lox::core::textlogger::ObjectConverter</base>
    <member kind="variable">
      <type>TString</type>
      <name>FmtNullObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1StringConverter.html</anchorfile>
      <anchor>a955492342cb1b68eb4c56a036750d036</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>StringConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1StringConverter.html</anchorfile>
      <anchor>a3ac0b7af1e751b339f2ea93813e4120c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~StringConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1StringConverter.html</anchorfile>
      <anchor>a8aa76811d77f8707068ed596468fc849</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API bool</type>
      <name>ConvertObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1StringConverter.html</anchorfile>
      <anchor>ac396326d32429f94105a6b045c0ce42d</anchor>
      <arglist>(const Logable &amp;logable, AString &amp;target)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::StringLiteral</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <templarg>TLength</templarg>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 10 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 11 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 2 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 3 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 4 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>StringLiteral&lt; 5 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</filename>
    <base>aworx::lib::strings::TString</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>StringLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a4b8fba33694e7534bd9ce9f0feae415d</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1StringLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Substring</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Substring.html</filename>
    <base>aworx::lib::strings::String</base>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a78e69b45cdcafe78919ef4394b946473</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abd670ace7a547520a1de51e09af48d16</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a3805c0af8d0d8c718fabbfce10236da3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>af3534dc253659982f8f5f646da7c951c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad35eefd241e9ac52278c696d28671760</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a96cf750c8bd36acaa7510d08c4709567</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7ab157d58b1dcdec6b1962e2ed9580dc</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aaf59accd324c73fe307fbf81e1c35242</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aefbbdae5be3973db831fc14f049902da</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a15088f26d020c580ed62e3b842e9f7fb</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a94a31afdd787fddb34efd2bf97601987</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1269e3abe8d95272e9e9c3e0aa7f7905</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a52e8d95769240c639d29ee1bdbfa0a0d</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1ec4cca1d72e31dff41edbcb584a4138</anchor>
      <arglist>(const String &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adccc3a479bc3abc37a8aef9322baa3c4</anchor>
      <arglist>(const String &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a56e71c29f72b9ec95c60a4b47eb45711</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a3f589b8c9f5e4a6deb6f29804f210e12</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5a68f106a868e841f97fac80c946cee0</anchor>
      <arglist>(int32_t &amp;result, const TString &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ae6fb29c871e36492716451fc3081bad6</anchor>
      <arglist>(int64_t &amp;result, const TString &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abdbc41364a58d285b7f12ab88543aa5f</anchor>
      <arglist>(double &amp;result, NumberFormat *numberFormat=nullptr, const TString whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Split</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9ba2f83672cd35b574cba0788a923f36</anchor>
      <arglist>(int position, Substring &amp;target, int separatorWidth=0)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a78e69b45cdcafe78919ef4394b946473</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abd670ace7a547520a1de51e09af48d16</anchor>
      <arglist>(const String &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a3805c0af8d0d8c718fabbfce10236da3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>af3534dc253659982f8f5f646da7c951c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad35eefd241e9ac52278c696d28671760</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a96cf750c8bd36acaa7510d08c4709567</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7ab157d58b1dcdec6b1962e2ed9580dc</anchor>
      <arglist>(const TString &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aaf59accd324c73fe307fbf81e1c35242</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aefbbdae5be3973db831fc14f049902da</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a15088f26d020c580ed62e3b842e9f7fb</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a94a31afdd787fddb34efd2bf97601987</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1269e3abe8d95272e9e9c3e0aa7f7905</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a52e8d95769240c639d29ee1bdbfa0a0d</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1ec4cca1d72e31dff41edbcb584a4138</anchor>
      <arglist>(const String &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adccc3a479bc3abc37a8aef9322baa3c4</anchor>
      <arglist>(const String &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a56e71c29f72b9ec95c60a4b47eb45711</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a3f589b8c9f5e4a6deb6f29804f210e12</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5a68f106a868e841f97fac80c946cee0</anchor>
      <arglist>(int32_t &amp;result, const TString &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ae6fb29c871e36492716451fc3081bad6</anchor>
      <arglist>(int64_t &amp;result, const TString &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abdbc41364a58d285b7f12ab88543aa5f</anchor>
      <arglist>(double &amp;result, NumberFormat *numberFormat=nullptr, const TString whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Split</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9ba2f83672cd35b574cba0788a923f36</anchor>
      <arglist>(int position, Substring &amp;target, int separatorWidth=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::system::System</name>
    <filename>classaworx_1_1lib_1_1system_1_1System.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>RuntimeEnvironment</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>aeae50cdd350e3deaae33d2900b0a72f2</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2a88183b946cc5f0e8c96b2e66e1c74a7e">Unknown</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2aac3b9401d30402b6f3f9c930e92eba6a">EclipseCDT</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2abd58134b67d16f4a15d1f36d60e2f5b0">QTCreator</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2a9da6f898a198b78810f6ad36fb83064e">VStudio</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2aea89b68c34ce4a63c0f77e17413c6e30">Shell</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2a2310408a63388fe57e3a4177168a8798">Desktop</enumvalue>
      <enumvalue file="classaworx_1_1lib_1_1system_1_1System.html" anchor="aeae50cdd350e3deaae33d2900b0a72f2aeaf6ea57c3dde8d4f04202a0115c613f">MobileDevice</enumvalue>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API String</type>
      <name>DebuggerProcessName</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a1c6688a1a1c7568ff374b4ccd279b041</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const String &amp;</type>
      <name>GetProcessName</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a3efcfee814940f4c1c1ad2a99d5e172a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>GetVariable</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a7bd3327e84e88d8704a95585c57ee7ed</anchor>
      <arglist>(const TString &amp;varName, AString &amp;target, enums::CurrentData targetData=enums::CurrentData::Clear, enums::Case sensitivity=enums::Case::Ignore)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>HasConsoleWindow</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a62821694d315ff9e9b417531bce97ce6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>IsDebuggerPresent</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>ad0e7333ca518b4965afb347b0c072680</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API RuntimeEnvironment</type>
      <name>RTE</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a28b473ab05b45948857c11c98973e6c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static AString</type>
      <name>processName</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>acdefe8c9e0fc3c1abb1655ea13d4f3d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALIB_API void</type>
      <name>getProcessName</name>
      <anchorfile>classaworx_1_1lib_1_1system_1_1System.html</anchorfile>
      <anchor>a14d31f74cb29b4e92cc090905256c8d1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::Tab</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>minPad</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</anchorfile>
      <anchor>a7aceeb3f7d87d0a3d102cf99dea70e3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>reference</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</anchorfile>
      <anchor>aaf215a3c05140d166ae6441c061d0643</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>tabChar</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</anchorfile>
      <anchor>afc97f451934a3418868537a2dd94a096</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>tabSize</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</anchorfile>
      <anchor>a5080752e4b748a0dfaff4512500fcf4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tab</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Tab.html</anchorfile>
      <anchor>a2682d3b6e163caeb520961bf5e0c2ae7</anchor>
      <arglist>(int tabSize, int reference=0, int minPad=1, char tabChar= &apos; &apos;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::TextFileLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</filename>
    <base>aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="variable">
      <type>aworx::AString</type>
      <name>FileName</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a15b92b72838ed16c47a44702bce981c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>hasIoError</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>aef8156626509284bebb701bfd5a93699</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TextFileLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a064b89198d7a4138c32e0964ab620e2f</anchor>
      <arglist>(const aworx::String &amp;fileName, const aworx::String &amp;loggerName=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TextFileLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>accac5141ecc60e6bca547cceb61ef1ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>currentlyInMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a79360590a52ab99fa5ca7bd3e679fef5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::ofstream *</type>
      <name>os</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>abb9ed1102af33c2c129f3deb334ee2ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API void</type>
      <name>closeFile</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>ab2ff17b940ae7aca4827d832ceeaeda4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>logSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a728330a0b5b726d0bcbb30d1fe0992f5</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>afd61f886ab5fd3838e70919f34224397</anchor>
      <arglist>(lib::enums::Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a568c34b5dbea541c187abe97fcfce756</anchor>
      <arglist>(lib::enums::Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALIB_API void</type>
      <name>openFile</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>acd0224d6aee829fc45210f977168abb4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::TextLogger</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</filename>
    <base>aworx::lox::core::Logger</base>
    <member kind="variable">
      <type>textlogger::AutoSizes</type>
      <name>AutoSizes</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>adda71dc824b4e9ff5fda6afb7aed1c44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>FmtMultiLineMsgHeadline</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a53efc9595ad578dfa30d7c3f79441c19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>FmtMultiLinePrefix</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ae7e21aa436fd2966ab2ce5188f3bbca2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>FmtMultiLineSuffix</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a321ad7402c369b0f2249ffa764afc080</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>FmtUnknownObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ab3a2c4f921a956a74a79c8b93fa4bec7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>textlogger::MetaInfo *</type>
      <name>MetaInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a44ec0d8f6ee263114e758dd8d4cd8301</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>MultiLineDelimiter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a4b152755ce9a00713a680ee56a07112b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>MultiLineDelimiterRepl</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a044f3f9d4ad22b7e3b6210f0ead7307c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MultiLineMsgMode</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a95ea94dee572eaac760d028ddcf3cf65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; ObjectConverter * &gt;</type>
      <name>ObjectConverters</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a7db775b96025ee18de0b020f81302633</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~TextLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>aaa18c56d081d6d2bce737e506613fc03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>AddAcquirer</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ac097a5b90ddc055cbf44b6a87b8cfda6</anchor>
      <arglist>(ThreadLock *newAcquirer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>ClearReplacements</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a17d8436509bfd6902d02a1a7628c9708</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>Log</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a16ba334409d5da064ac05df710fb2239</anchor>
      <arglist>(Domain &amp;domain, Verbosity verbosity, Logables &amp;logables, ScopeInfo &amp;scope)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>RemoveAcquirer</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a2f480eaa76919774ba222225c952b874</anchor>
      <arglist>(ThreadLock *acquirer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>SetReplacement</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>adcc3e44d96eefbb58460dc913c54af6a</anchor>
      <arglist>(const String &amp;searched, const String &amp;replacement)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>logBuf</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a1c3b59e6dc2850f90df33ae9b4533334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>msgBuf</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>aca76e783906a4030895a9797a98adb3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; AString &gt;</type>
      <name>replacements</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a07a5ac8fc34beb304cd3389da5378ed0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>stdStreamLockRegistrationCounter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a7e0257392907f8a498262a3d8516f04c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>usesStdStreams</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a521df36fef7aa1dc1979a93cd4db2e83</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API</type>
      <name>TextLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a642acb6c649fc76e765ad8ed4cfbc50d</anchor>
      <arglist>(const String &amp;name, const String &amp;typeName, bool usesStdStreams)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>logText</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ae272f3e7c4827d4ad3cd3e7822bf9aff</anchor>
      <arglist>(core::Domain &amp;domain, Verbosity verbosity, AString &amp;msg, core::ScopeInfo &amp;scope, int lineNumber)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a34888c98e0110b09d5f839643b33b7ca</anchor>
      <arglist>(lib::enums::Phase phase)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::threads::Thread</name>
    <filename>classaworx_1_1lib_1_1threads_1_1Thread.html</filename>
    <base>aworx::lib::threads::Runnable</base>
    <member kind="variable" static="yes">
      <type>static constexpr int</type>
      <name>NullThreadId</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>ab74d46f09db54cfc6e3c0d55baca5bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>_Init_ALib</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a003163fa39a645018d798dc5f78d1489</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>_Terminate_ALib</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>accd9bab0730ee5dd06545352ca0346f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API Thread *</type>
      <name>CurrentThread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>afbdb4b0df9aaf36f3ab6c4965178f0d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>acf5e3cb660c7d17d4602097e0e609f98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>af8a3dd10fdb7b395c3aa577bf427ee65</anchor>
      <arglist>(const String &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a6d3e50558e2d1e2fd5737f53db6af98c</anchor>
      <arglist>(Runnable *target, const String &amp;name=EmptyString)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API</type>
      <name>~Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a87a9c69a69ee4b13cb1ec5772f6d32ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetId</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a7afa9b288457f394b566c93d58820852</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const String &amp;</type>
      <name>GetName</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a3b994abc1d545e8f442b3cffc69f170d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsAlive</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>aed968892a37acc82e42dc5631873763a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Run</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>ae468c1feb28eb3650062bd36b81a4dc4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetName</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a6b96e15f0d3f46e1d07fc90f2d80fe04</anchor>
      <arglist>(const String &amp;newName)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Start</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a07aaf1227e4d645f15e0a964f54ef291</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend void</type>
      <name>_Thread__Start</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>ab0de95445010749d86515d0c065ae384</anchor>
      <arglist>(Thread *t)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static std::mutex</type>
      <name>mutex</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>ac1e5f028d9196e79535292af4d31f555</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>nextSystemThreadId</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a6f75d73b07fa7d51811c670006afddfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>nextThreadId</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>aafbcb206984d160d0e23ceb38921175c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static std::map&lt; std::thread::id, Thread * &gt;</type>
      <name>threadMap</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a20bce847bfb62b236bfd6c9d3edda4d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::thread::id</type>
      <name>c11ID</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a0a145a251b9bfd12952ab051fdd6f6b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::thread *</type>
      <name>c11Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a89f5d379ab6ea494541102c2f4be341c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>id</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a7441ef0865bcb3db9b8064dd7375c1ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>isAliveFlag</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a56a0c2524b8071ee7d9447a62d83ce32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String64</type>
      <name>name</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>ab8753ff0c292faf40f6618a33d16ee9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Runnable *</type>
      <name>runnable</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>af96dc80019779aec1839595c875b104e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Thread</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1Thread.html</anchorfile>
      <anchor>a0200ba496119c9e8c096e380331ac9aa</anchor>
      <arglist>(bool internal)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::threads::ThreadLock</name>
    <filename>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</filename>
    <base>aworx::lib::Ownable</base>
    <member kind="variable">
      <type>int</type>
      <name>RecursionWarningThreshold</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a2b35011c911bf00d065eba8af27620a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>WaitWarningTimeLimitInMillis</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a1a326aeefec583cbccf74ea567257e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>ThreadLock</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a2aa8bcb0a11b134d79fdfa97c2219719</anchor>
      <arglist>(enums::LockMode lockMode=enums::LockMode::Recursive, enums::Safeness safeness=enums::Safeness::Safe)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API</type>
      <name>~ThreadLock</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a62d4d1d8df991fec098bbd8d5f19e34b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a607d6c96bfd21c3530e8a7fab9ca0395</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>DbgCountAcquirements</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>af99e21e2f05c81744d2e6b5b66d14951</anchor>
      <arglist>(Thread *thread=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>enums::LockMode</type>
      <name>GetMode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a92909f85539d41af1752c6654b837922</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>enums::Safeness</type>
      <name>GetSafeness</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a41098f63af0e1f20173013039dfa6956</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a94c93747c8daa99d65c2a04c6be0748c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetSafeness</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a906fc408a38b0d414e232328d82cdb72</anchor>
      <arglist>(enums::Safeness safeness)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>cntAcquirements</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a04735ee43ec4d1676e4e0eb3d6bebd73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>enums::LockMode</type>
      <name>lockMode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a5df502d54adfe465de472847d8dc6588</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::mutex *</type>
      <name>mutex</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a925e97cfc2fb5e3b27bd06f805668a9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::condition_variable *</type>
      <name>mutexNotifier</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a546b08274dd279ace7093f6b6d562beb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Thread *</type>
      <name>owner</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a6d42f8ca4a142dc8f1e48b8329b17be7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::threads::ThreadLockNR</name>
    <filename>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</filename>
    <base>aworx::lib::Ownable</base>
    <member kind="function">
      <type></type>
      <name>ThreadLockNR</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>ab5925d1db9fdc30ccd8e7f713ec94777</anchor>
      <arglist>(enums::Safeness safeness=enums::Safeness::Safe)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ThreadLockNR</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>ad2dd19f8e7eb364c570f32d320c470ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a07a42f9930e2b2f9b94a3d47d3088532</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>enums::Safeness</type>
      <name>Mode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a6f6f0840b4d4e758e93644c2fd389896</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a84a1506acc1e04455ebc3bc724265872</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a7ba75d036f96e4ea3d2b451677bdeba5</anchor>
      <arglist>(enums::Safeness safeness)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>dbgIsAcquired</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a9426fc5fde1af618b0afd97ff21c1b6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::mutex *</type>
      <name>mutex</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLockNR.html</anchorfile>
      <anchor>a925e97cfc2fb5e3b27bd06f805668a9d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::time::Ticks</name>
    <filename>classaworx_1_1lib_1_1time_1_1Ticks.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>_Init_ALib</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a003163fa39a645018d798dc5f78d1489</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>_Terminate_ALib</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>accd9bab0730ee5dd06545352ca0346f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API const Ticks &amp;</type>
      <name>CreationTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aac6aca1e8b6f497d214a46445e04b232</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API int_fast64_t</type>
      <name>InternalFrequency</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>af3517d9cd90fd195ce3c876c0dc1b848</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a1c1ae3d4574882f05f5fa9586e7f1fec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>afeacd76ef9e20fc341e433ba27104741</anchor>
      <arglist>(int_fast64_t ticks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a3a2e922d9d3aecf9ade93859d7c08bef</anchor>
      <arglist>(const Ticks &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a81b5045a48ca7b958fc2be35d3260b3c</anchor>
      <arglist>(const Ticks &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a41b1e94505a539e23c9e1ab3d1a32bc8</anchor>
      <arglist>(int_fast64_t ticks)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Age</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>afc3ea69a2be2bc54667e14ba3fa8cb83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>Format</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aa0befe92a960e53ffbe042855f5d5ec3</anchor>
      <arglist>(const String &amp;format, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromDays</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ade22d8be07ec20cef7e883706db3fe24</anchor>
      <arglist>(int days)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromHours</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a57b52b2e1e8b464a3959fd83575a48af</anchor>
      <arglist>(int hours)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMicros</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a16a825623d5af98d25d329d0b9f56dcf</anchor>
      <arglist>(int_fast64_t micros)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMillis</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac6f86e6b884d65770873fca3c6f7b498</anchor>
      <arglist>(int_fast64_t millis)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMinutes</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac1cc62dbe83f81c070b0307b75ce275a</anchor>
      <arglist>(int mins)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromNanos</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a4564b4390f9f8f71aae6df7109e62486</anchor>
      <arglist>(int_fast64_t nanos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromSeconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a5d07dd8ebb7243db9a95bfe07a18938a</anchor>
      <arglist>(int secs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InDays</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9397bc3e901c7e8e901763a554fdcbc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API time_t</type>
      <name>InEpochSeconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ad96f1b87ddca623ddecf2821280bfcb2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>InFileTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aa21af34c932595e5cc84deab77531bff</anchor>
      <arglist>(LPFILETIME result) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>InFileTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a7fa56186f09974e858424da65f3029a0</anchor>
      <arglist>(ULARGE_INTEGER &amp;result) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>InHertz</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a88db94a7906cff1e3ec57007436cf8b2</anchor>
      <arglist>(int nDigitsPrecision=-1) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InHours</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a2584f400808d42f731209def0908aa93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int_fast64_t</type>
      <name>InMicros</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ad52e8866e8e98cbbde6fe8322fe126e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int_fast64_t</type>
      <name>InMillis</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a7781a8fbfebb3b1fcde30dc08c665245</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InMinutes</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a34b63b0c6af9441239b5de19502ba9e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int_fast64_t</type>
      <name>InNanos</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a57fa6b33e83e04e3f39df8293855ab5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InSeconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a598e222338b0c08ceccb5479a5ac9429</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>InSystemTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a4771f4d4927d9d3928d4e498d03db585</anchor>
      <arglist>(LPSYSTEMTIME result, enums::Timezone timezone=enums::Timezone::Local) const </arglist>
    </member>
    <member kind="function">
      <type>int_fast64_t</type>
      <name>Raw</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a1f296d900086b2d93c452986e21fa123</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a614cfe7992438ee53cfd9440848c39e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a4037be6f5cc14d19b7c5ee5ea4e58c13</anchor>
      <arglist>(const Ticks &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetFromEpochSeconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a53a9f29f45a8cd2b3d2f265e0604e012</anchor>
      <arglist>(time_t epochSeconds)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetFromFileTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac8c2076c8c5cd13103806c80af25e67b</anchor>
      <arglist>(const LPFILETIME fileTime)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetFromFileTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>acb337572671e84adbe312a80f65a2fc6</anchor>
      <arglist>(const ULARGE_INTEGER &amp;fileTime)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetFromSystemTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a13799849de3c9abbe5ed617878481795</anchor>
      <arglist>(const SYSTEMTIME &amp;systemTime, enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRaw</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a64e12c028b0905f2419bf7e488102f06</anchor>
      <arglist>(int_fast64_t value)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Since</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a152d260d4d1411a09d9c14fa4ae2eeb2</anchor>
      <arglist>(const Ticks &amp;olderTime) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sub</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a32d565c619412910f6e8b056a4401f0f</anchor>
      <arglist>(const Ticks &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sub</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a5419f99b5b82a0f3ca26c92466418003</anchor>
      <arglist>(int_fast64_t ticks)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend void</type>
      <name>static_aworx_lib_ticks_destroy</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a4d5586810c41f0d40e6ff25061a2125c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend Ticks *</type>
      <name>static_lib_init_ticks</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aa6776de3a3f4260295adfaba1ccf4146</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API Ticks *</type>
      <name>creationTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac4aaa87e2fbf873c653a97f4a1d49d13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API int_fast64_t</type>
      <name>frequency</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a91344eb48cdbf17a21a6b6b4509894b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API int_fast64_t</type>
      <name>mscResFactor</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9d727de999177c753eff9e3c5427e641</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerDay</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9b8e242cdbf7d71e049c7dc06d96f640</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerFileTimeTick</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aca87bb90119ae16cb9c1cfc5dded3602</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerHour</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a8129640383e6b088061c41884250f3af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerMicrosecond</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9f054d063e3276f4da2ea8a9b32a86b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerMillisecond</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9a325ec045c47b5e1434b82d1d12eb0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerMinute</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a44f0bf5ead88f6db72609ca0bcc2fa8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerNanosecond</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ae5333b92f0d53a1645bc659548235252</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API double</type>
      <name>mscTicksPerSecond</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a786f849b19c17bdff821b14dc0e2d0a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int_fast64_t</type>
      <name>ticks</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a1f13e9e266613429367dc4f500b5f59b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::time::TicksCalendarTime</name>
    <filename>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>Day</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a8f67164de537e3ec2b47e3204ddd3400</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>DayOfWeek</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>ac3213e69636923e6b0b41a0e388f79ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Hour</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a9a7e982c278ab66497180395ad975b4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Millisecond</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>af3cfef93e0bc093468e23c7e8768ce62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Minute</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a361937b5d839c9e24d045e2fb21933ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Month</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a530b376ec91a278ac98531d3ea17f148</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Second</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>af95fdbfb8f07e751f4396ef15bc70b5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Year</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a42e645110404fbf4f10235789577fa32</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TicksCalendarTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>aeaad7380abf5a17bffdafda72230e919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TicksCalendarTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>ab2175a8abca8ec7c2f2cf6e6d0c222bf</anchor>
      <arglist>(const Ticks &amp;ticks, enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TicksCalendarTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a6f30a8bba3f6faf4b6477031eb89f61a</anchor>
      <arglist>(int_fast64_t ticks, enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API AString &amp;</type>
      <name>Format</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a63ea1fdf739ee189059a606854533c99</anchor>
      <arglist>(Substring format, AString &amp;target, lib::enums::CurrentData targetData=lib::enums::CurrentData::Keep)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int_fast64_t</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a7a3fe04b805066e044a29047fb9f3e69</anchor>
      <arglist>(enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>aede0204d6bf28f6b7f2546f0d8c6370d</anchor>
      <arglist>(const Ticks &amp;ticks, enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>ae33c6b69f0f5485e44d28e1dad921427</anchor>
      <arglist>(int_fast64_t ticks, enums::Timezone timezone=enums::Timezone::Local)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>tm_isdst</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TicksCalendarTime.html</anchorfile>
      <anchor>a7d102a87f898878ebf37ebd87504e099</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::time::TickSpan</name>
    <filename>classaworx_1_1lib_1_1time_1_1TickSpan.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>Days</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a5b70bc3780a4da05fec9a52b7e4eb85b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Hours</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a9039ccfcf02dd3340b9fdfa18517f2ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Microseconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a486553d6699abe764277cccc1c48fe69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Milliseconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a3818cea5a28d6856ec80d39a8ce64b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Minutes</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a9f1239b10f2ae7a1187323c5f19d48c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Nanoseconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a07bce61c5d03546046f1cbbd77273a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Seconds</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a3df113560f1b5fdd862befb68ddec3ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickSpan</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>ad636246fac9c30f5d7ccf2d756020585</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickSpan</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a4df0c6745053f035268465f8e281392c</anchor>
      <arglist>(const Ticks &amp;ticks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickSpan</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a53e665f2e34bf5a0a1399330dcb865bb</anchor>
      <arglist>(int_fast64_t ticks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickSpan</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a880df1f180f962d18da5dba4497ca915</anchor>
      <arglist>(const Ticks &amp;first, const Ticks &amp;second)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int_fast64_t</type>
      <name>Get</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a0f695c897e507e52a6223f9c3b23a148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>a3eb34a60738ebd4fd7e0782b8dd3cc25</anchor>
      <arglist>(const Ticks &amp;ticks)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickSpan.html</anchorfile>
      <anchor>ac346611ad25959526c85c8406c30b222</anchor>
      <arglist>(int_fast64_t ticks)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::time::TickWatch</name>
    <filename>classaworx_1_1lib_1_1time_1_1TickWatch.html</filename>
    <member kind="function">
      <type></type>
      <name>TickWatch</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ae5d46be41414c0e48a9611ce08084a50</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickWatch</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a2b1b331cedde52bd637b612c67faa202</anchor>
      <arglist>(const TickWatch &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetAverage</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ae29a8f1f9e654fdc5c28964f8612086f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetCumulated</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>afa26a288553e5b8e69116f085d320564</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSampleCnt</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a8f2deb29070eb959107e5d9ad3584635</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Ticks &amp;</type>
      <name>GetStartTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ac2383605393294fea20913084f176fde</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Ticks</type>
      <name>Sample</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a04ef4fd46aa6e5ae371cb3c70f278e61</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>aad3f9a5a16ca34c75b8db8d065e0c47e</anchor>
      <arglist>(const Ticks startTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Start</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a07aaf1227e4d645f15e0a964f54ef291</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>cntSamples</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a3203b85b99c75b91922c0147ac0ca04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>startTime</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ad4a637681761e440fc76c0c91a3a2737</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>sum</name>
      <anchorfile>classaworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ac78b14fce693b96514184f5ecb99f5fa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::TMPLiteral</name>
    <filename>structaworx_1_1lib_1_1strings_1_1TMPLiteral.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>Buffer</name>
      <anchorfile>structaworx_1_1lib_1_1strings_1_1TMPLiteral.html</anchorfile>
      <anchor>ab5858da312ca4522c5c241ed9153a2e6</anchor>
      <arglist>(void *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Tokenizer</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</filename>
    <member kind="variable">
      <type>Substring</type>
      <name>Actual</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a2eefe9530c5f2042ddfa20e26b34328b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Substring</type>
      <name>Rest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a5c8c6045e5fe301e78496fd5e9c7bfab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>Whitespaces</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ade1a53d31b95db4ed98b03ff74a8b472</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a09b5373670bea8a8e4ef7645889bad72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>aec862d2011e01f63cc367fb40c1e6ade</anchor>
      <arglist>(const String &amp;src, char delim, bool skipEmptyTokens=false)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>GetRest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ad8bca63647be16f18c25123486a41d19</anchor>
      <arglist>(enums::Whitespaces trimming=enums::Whitespaces::Trim)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNext</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a3551d22502a58cdc93b15d14f3fb87c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Substring &amp;</type>
      <name>Next</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a55ffaac69d1ce7232db83470a8390db8</anchor>
      <arglist>(enums::Whitespaces trimming=enums::Whitespaces::Trim, char newDelim= &apos;\0&apos;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a0e0b8ea460fe939a3a6f133e0619042a</anchor>
      <arglist>(const String &amp;src, char delim, bool skipEmptyTokens=false)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>delim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ab56c67e0ed9605b4078e2135f791c4ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>skipEmptyTokens</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a30e566108b40ef50fce0d40509d0413d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::ToStringDefined</name>
    <filename>structaworx_1_1lib_1_1strings_1_1ToStringDefined.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::ToStringDefined&lt; const std::string &amp; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1ToStringDefined_3_01const_01std_1_1string_01_6_01_4.html</filename>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::TString</name>
    <filename>classaworx_1_1lib_1_1strings_1_1TString.html</filename>
    <base>aworx::lib::strings::String</base>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Terminate</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a7a1430f618f869550a47b5f078ce6860</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a57423bbca362af5c912ea619d9a14746</anchor>
      <arglist>(const TString &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a77001b79e815a22ce126e3df14f591b2</anchor>
      <arglist>(const TString &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>ab75164b28454722bdf29710c208f0736</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToCString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>af283db5a533654cb8a0fa2e110d4b20f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>ToLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>af2efe140bd7fe9300fa64c27c7adab08</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>ToInt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a0318c4e2b29a58be56c9f8645184448d</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>ToFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>aefab2dff23cb4a711c8efdd73e85c15e</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, NumberFormat *numberFormat=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>debugIsTerminated</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>ac3615a067cb671e6b0cac6dbb26c9f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_dbgCheck</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a8747c38ac0ef9f863ede544d51ff6721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>TString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>ad751e8adb9aa217a042c45e1c0585285</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>abe0c3a5e03ba9a10bd9b19a22a261499</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>constexpr</type>
      <name>TString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a6d715743a3937ea101a8deda34d993dc</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Terminate</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a7a1430f618f869550a47b5f078ce6860</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a57423bbca362af5c912ea619d9a14746</anchor>
      <arglist>(const TString &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a77001b79e815a22ce126e3df14f591b2</anchor>
      <arglist>(const TString &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>ab75164b28454722bdf29710c208f0736</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToCString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>af283db5a533654cb8a0fa2e110d4b20f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>ToLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>af2efe140bd7fe9300fa64c27c7adab08</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>ToInt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>a0318c4e2b29a58be56c9f8645184448d</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>ToFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1TString.html</anchorfile>
      <anchor>aefab2dff23cb4a711c8efdd73e85c15e</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, NumberFormat *numberFormat=nullptr, const TString *whitespaces=nullptr) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::UInt32</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt32.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>minDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt32.html</anchorfile>
      <anchor>ab6c281111688d6bcd765ff050f741a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>value</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt32.html</anchorfile>
      <anchor>ae7f66047e6e39ba2bb6af8b95f00d1dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UInt32</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt32.html</anchorfile>
      <anchor>a43588a61a7b361b2fc1f563eee1f3979</anchor>
      <arglist>(uint32_t value, int minDigits)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Format::UInt64</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt64.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>minDigits</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt64.html</anchorfile>
      <anchor>ab6c281111688d6bcd765ff050f741a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>value</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt64.html</anchorfile>
      <anchor>a4e630859cc0e2a22bd6acf39a6a8e218</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UInt64</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1UInt64.html</anchorfile>
      <anchor>a8c277fa0e922affef8caced713b9a3c1</anchor>
      <arglist>(uint64_t value, int minDigits)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::Util</name>
    <filename>classaworx_1_1lib_1_1Util.html</filename>
    <member kind="function" static="yes">
      <type>static const aworx::AString &amp;</type>
      <name>GetSpaces</name>
      <anchorfile>classaworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a59010cc79be20c6026095241b52c564f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const aworx::AString &amp;</type>
      <name>GetSpacesUnsafe</name>
      <anchorfile>classaworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a3e3ea965460f027ed5e65b9df82bdeae</anchor>
      <arglist>(int minSize)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WriteSpaces</name>
      <anchorfile>classaworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a45f5d6b6d0a3d2c68d86a11cac8750e8</anchor>
      <arglist>(std::ostream &amp;os, int qty)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static AString</type>
      <name>theSpaces</name>
      <anchorfile>classaworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>af2abf169487119d618ac7a542e28e5c0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::config::IniFile::Variable</name>
    <filename>classaworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>Comments</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a13a7dbf15cba4c8849fdd8044b185475</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>Delim</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a68297215ac82977611f5dee2062cc910</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Name</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>ab3c68b8a64bf47454f94bde4ebb6de0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Value</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>aaadcdd81806203a103169225c3079f43</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::VStudioLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</filename>
    <base>aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="function">
      <type>ALOX_API</type>
      <name>VStudioLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>aeee499182934b2b2708e1647818b62b1</anchor>
      <arglist>(const String &amp;name=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~VStudioLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>a761045927d1191f0c3ba585104751952</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>wchar_t *</type>
      <name>wCharBuffer</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>a91eee64289a4ad8305ad6f78e85090c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>wCharBufferSize</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>a097dc29175f1cb3e0a307177fca6f6f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API int</type>
      <name>logSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>a728330a0b5b726d0bcbb30d1fe0992f5</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALIB_API bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>afd61f886ab5fd3838e70919f34224397</anchor>
      <arglist>(lib::enums::Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>aff874730d33416eb95a0650e0df3f39b</anchor>
      <arglist>(lib::enums::Phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::loggers::WindowsConsoleLogger</name>
    <filename>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</filename>
    <base>aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable">
      <type>UINT</type>
      <name>CodePage</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>ac47fdc0badba5fd9ada1680d8d2b3304</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsBackgroundLight</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>ab9537e130d3c02801775f8c1941eb9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WORD</type>
      <name>MsgColorError</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>a0aa798339706a84a2c9ec39a2054b2bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WORD</type>
      <name>MsgColorInfo</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>a7846dc401b8648308dce0b728732b021</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WORD</type>
      <name>MsgColorVerbose</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>a307806929aea5a432234d48268d2cbb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WORD</type>
      <name>MsgColorWarning</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>ae3d7f3c0dfe898043615a5b18880527d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>WindowsConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>ababff47d22b9b979460f912912011682</anchor>
      <arglist>(const String &amp;name=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~WindowsConsoleLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>a990f689b5da69d74661c6798eda75364</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WORD</type>
      <name>originalConsoleAttributes</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>a149584f1eda778dd1322190ddd5b00de</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>logText</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>aa7e70b90717f0429abf0990e5e12ad9f</anchor>
      <arglist>(core::Domain &amp;domain, Verbosity verbosity, AString &amp;msg, core::ScopeInfo &amp;scope, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>aff874730d33416eb95a0650e0df3f39b</anchor>
      <arglist>(lib::enums::Phase)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx</name>
    <filename>namespaceaworx.html</filename>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lox</namespace>
    <member kind="typedef">
      <type>aworx::lib::ALIB</type>
      <name>ALIB</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afc2895fe34753aa1cd88ed8845fbd88b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Alignment</type>
      <name>Alignment</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a96dde4be24b9217d6bef30b22d7dfd4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::ALox</type>
      <name>ALox</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4d5353279fde6a5d6e5b1c8e776abf66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::AnsiConsoleLogger</type>
      <name>AnsiConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a1ea18f3cfd0faa27d99ecc1c9532b445</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::AnsiLogger</type>
      <name>AnsiLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afbcb9cbc8853ce81a9d690e2a8923889</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::AString</type>
      <name>AString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a51ace28d988aa0a7ab391f6aaec35f60</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Case</type>
      <name>Case</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac497730bb253c7efcfee90f6de02a0ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::config::Configuration</type>
      <name>Configuration</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a9b321d2f72b975b304aa678e20344e7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::ConsoleLogger</type>
      <name>ConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acfbbfc11d98646c37dbf27e3ede11644</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::ContainerOp</type>
      <name>ContainerOp</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a79b40b1cf65e889763d9ac0858268172</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Create</type>
      <name>Create</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae9b7ef57f8fb67372f77ff485e3087d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::CurrentData</type>
      <name>CurrentData</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8cd9fd65cae399a824854fa2ea3b8bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::system::Directory</type>
      <name>Directory</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae59166dff4149598acd5f636fe6760d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::ESC</type>
      <name>ESC</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a41196e8ca29644376437095a102ad9ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::Format</type>
      <name>Format</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aed5a5fab6b4a0c81a5a231f6d0379d41</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Inclusion</type>
      <name>Inclusion</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af3771c700d4232fb5b8a10510e088274</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::config::IniFile</type>
      <name>IniFile</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aef31dd55ee6403c15d9ba93325d3333d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::LockMode</type>
      <name>LockMode</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acae7a6e21dc6155b5f1b7c932fb8aa34</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Log</type>
      <name>Log</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5d8a9ca518e5abc7446b6a753e2b7ae6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::LogData</type>
      <name>LogData</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a07d961a72c3ccbe33993cdeb56dab52e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::core::Logger</type>
      <name>Logger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8ec4a1b5f5786befe04b9f08d5417cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Lox</type>
      <name>Lox</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abf1258bbd9cf9772a1559f4ceb37fde4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::MemoryLogger</type>
      <name>MemoryLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aff4e02a238ba03a98be3dd17d783f336</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::NumberFormat</type>
      <name>NumberFormat</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4105ad142b7282bab44c0f051d36e350</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; TCapacity &gt;</type>
      <name>PAString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a10e9458c58956ec05a324232fc1cc9e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::containers::PathMap&lt; StoreT &gt;</type>
      <name>PathMap</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a40dd35c549af4dcf094f486d3f2dca1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Phase</type>
      <name>Phase</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac87fae76a49419f75db6b44011acc407</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::system::ProcessInfo</type>
      <name>ProcessInfo</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8644368b56cf61a16e37300584a1d4e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Propagation</type>
      <name>Propagation</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a6becd7c5957b9924c08b78079a67c5b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Responsibility</type>
      <name>Responsibility</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad8c1565886f17d3b3262d8454ae546de</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Result</type>
      <name>Result</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0bb37c2c22c2eb85510445d1b9d11f19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::Runnable</type>
      <name>Runnable</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af259362a7fa123eef74daaf4036e02a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Safeness</type>
      <name>Safeness</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae44933ed0bc5c2462dce430a034dd6b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Scope</type>
      <name>Scope</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aef58f56e96f194bf0b5f765175f6ebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::StringLiteral&lt; TLength &gt;</type>
      <name>SLiteral</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af631a26bf70ad6d6143973fadf779747</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::SmartLock</type>
      <name>SmartLock</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aee1cd004a3010e8ee798517d96c1ffca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::String</type>
      <name>String</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad13481d84c6e592a41d07c64f747c95d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 128 &gt;</type>
      <name>String128</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a2841f1443c3b2f3d6066d5774cf69dbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 16 &gt;</type>
      <name>String16</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a148a217c34a72b4360462205858b8f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 1024 &gt;</type>
      <name>String1K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a82395a8f3fac47787ebe8749679a2796</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 256 &gt;</type>
      <name>String256</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a152f787b6dac47dd3f94ae5ebf1ece53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 2048 &gt;</type>
      <name>String2K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a76f69ad445caecfbf03351c884637b09</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 32 &gt;</type>
      <name>String32</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a221752691fb92bcd592c045d6c368289</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 4096 &gt;</type>
      <name>String4K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a772f06f37ace5e2b2eb8cafc0c859c44</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 512 &gt;</type>
      <name>String512</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af634b7550d8a316ce3cf3fb6f9e86079</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 64 &gt;</type>
      <name>String64</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ac2fdc487456a994238ba4284b3859c41</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::PreallocatedString&lt; 8 &gt;</type>
      <name>String8</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab35696c2e8d79567a528a4b6da788eb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>lib::strings::Substring</type>
      <name>Substring</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aade494154da29084f1e59cfa2f83a23b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Switch</type>
      <name>Switch</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abbc3fd675117881e7c7aebcd1058ad03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::system::System</type>
      <name>System</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aea0af9d6b00ede1a16d0af24fdaeebe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::TextFileLogger</type>
      <name>TextFileLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae64ac3b33c7c180e92559a869977fda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::core::textlogger::TextLogger</type>
      <name>TextLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8d1a5942495395f77e31bb5d451c332b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::Thread</type>
      <name>Thread</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a42fe02133ffe8b203c4aa204d2114d49</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::ThreadLock</type>
      <name>ThreadLock</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad941b2cb61bade9aa2478dd063154d33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::threads::ThreadLockNR</type>
      <name>ThreadLockNR</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a414cfa465381a22be7bf0bdc5728c1a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::Ticks</type>
      <name>Ticks</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad270463709a4ae7e7098df40e803e458</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TicksCalendarTime</type>
      <name>TicksCalendarTime</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0607ccd659418fa7cb9922b2c4ba5f1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TickSpan</type>
      <name>TickSpan</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a7b85567c52aa0abc2531be7a2a7f887f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::time::TickWatch</type>
      <name>TickWatch</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a4d4926218d664dabc231ce5cf0c19afc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Timezone</type>
      <name>Timezone</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5d6766c28e92b7f6ec8f96383455acdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::Tokenizer</type>
      <name>Tokenizer</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a605604b4e10ad391819f94254f1727b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::TString</type>
      <name>TString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af01fde7c67b5f30027a4135222bbde31</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::Verbosity</type>
      <name>Verbosity</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aa10bcb350ba5320cadb5dff6b8e2da6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::VStudioLogger</type>
      <name>VStudioLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a747899e07def7493ae65c9569a5dc879</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::enums::Whitespaces</type>
      <name>Whitespaces</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a0c07eb477a798a2088b4619390c54e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lox::loggers::WindowsConsoleLogger</type>
      <name>WindowsConsoleLogger</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad427fd161e0ad8bd4c8835c5a643cc3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr lib::strings::StringLiteral&lt; 4 &gt;</type>
      <name>DefaultWhitespaces</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5feaaf6a8fb11e8ebbb0013ec9f27b01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr lib::strings::String</type>
      <name>EmptyString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a3372961a8fb9d30455267babb4e6c26c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr lib::strings::StringLiteral&lt; 1 &gt;</type>
      <name>NewLine</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>aca82326cfe712c18f9adb9f560a28553</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr lib::strings::String</type>
      <name>NullString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab1ed6dcfbe4628dccefbdb5633b1bf01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr char</type>
      <name>PathSeparator</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a262e7ce267358080f085b5a3f42e3a67</anchor>
      <arglist></arglist>
    </member>
    <docanchor file="namespaceaworx">CPP_AWORX_NS_SHORTCUTS</docanchor>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib</name>
    <filename>namespaceaworx_1_1lib.html</filename>
    <namespace>aworx::lib::config</namespace>
    <namespace>aworx::lib::containers</namespace>
    <namespace>aworx::lib::enums</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lib::system</namespace>
    <namespace>aworx::lib::threads</namespace>
    <namespace>aworx::lib::time</namespace>
    <class kind="class">aworx::lib::ALIB</class>
    <class kind="class">aworx::lib::ConsoleReportWriter</class>
    <class kind="class">aworx::lib::Ownable</class>
    <class kind="struct">aworx::lib::Owner</class>
    <class kind="class">aworx::lib::Report</class>
    <class kind="class">aworx::lib::ReportWriter</class>
    <class kind="class">aworx::lib::Util</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::config</name>
    <filename>namespaceaworx_1_1lib_1_1config.html</filename>
    <class kind="class">aworx::lib::config::CommandLinePlugIn</class>
    <class kind="class">aworx::lib::config::Configuration</class>
    <class kind="class">aworx::lib::config::ConfigurationPlugIn</class>
    <class kind="class">aworx::lib::config::EnvironmentPlugIn</class>
    <class kind="class">aworx::lib::config::IniFile</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::containers</name>
    <filename>namespaceaworx_1_1lib_1_1containers.html</filename>
    <class kind="class">aworx::lib::containers::PathMap</class>
    <member kind="function">
      <type>PathMap&lt; StoreT &gt;::Iterator</type>
      <name>begin</name>
      <anchorfile>namespaceaworx_1_1lib_1_1containers.html</anchorfile>
      <anchor>a3c9cd89161562d9d1c346f6f82666108</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; &amp;pathMap)</arglist>
    </member>
    <member kind="function">
      <type>PathMap&lt; StoreT &gt;::Iterator</type>
      <name>end</name>
      <anchorfile>namespaceaworx_1_1lib_1_1containers.html</anchorfile>
      <anchor>a493642c7093a3913fb626ebd25eb4c7d</anchor>
      <arglist>(const PathMap&lt; StoreT &gt; &amp;)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::enums</name>
    <filename>namespaceaworx_1_1lib_1_1enums.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Alignment</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>acdfaca60ec19c0265bac2692d7982726</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a945d5e233cf7d6240f6b783b36a374ff">Left</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a92b09c7c48c520c3c55e497875da437c">Right</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a4f1f6016fc9f3f2353c0cc7c67b292bd">Center</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Case</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ab9aab17a5e54a8bae6915bc24db13a17</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17a8f21fcdc233ba4078679ca628453d06b">Sensitive</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17afd038fc7f319e48f3115d92bf5bdbef9">Ignore</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ContainerOp</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>af6d9cc1e6686eca6e60d57d959cf57fb</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fbaa458be0f08b7e4ff3c0f633c100176c0">Insert</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba1063e38cb53d94d386f21227fcd84717">Remove</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fbac55582518cba2c464f29f5bae1c68def">Get</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba1d5c1a7fde77e84c993d6fea61f88c2a">GetCreate</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="af6d9cc1e6686eca6e60d57d959cf57fba686e697538050e4664636337cc3b834f">Create</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Create</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a55781bd0c78c4e5d47ce433f4eeeee85</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a6e7b34fa59e1bd229b207892956dc41c">Never</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a44c32ea9ad0b836b68c25fdb717fa4b7">IfNotExistent</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CurrentData</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9345007d67faa05253932092d54d10d4</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4adc30bc0c7914db5918da4263fce93ad2">Clear</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Inclusion</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a217539925b78b2eed40ae7817d5bee52</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52af4d72a64acd8929c0cc9ed96a7a336cc">Include</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52a843f2812f595e7ec7c5036e89fde02d6">Exclude</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>LockMode</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a00fc859257c8f09ff9198dde28121961</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a556c3dd912453ae5cb3095cd5054e6f4">Recursive</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a67b491789a29d0c717a2b4ebe369a936">SingleLocks</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Phase</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ae1c5184dc404edf057ed537bcfddef84</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a1a06729125544cab7cee73195fc044f0">Begin</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a87557f11575c0ad78e4e28abedc13b6e">End</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Propagation</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>aeae0c2d4659a32ef54bd221d1a3da4e6</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6aa9857b4deb35c57d5753f94fa00a028e">ToDescendants</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Responsibility</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ab5305b978950ba3946cf79a4bccbf7af</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab5305b978950ba3946cf79a4bccbf7afa2540530a938da82bfe62957f4aff599b">KeepWithSender</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ab5305b978950ba3946cf79a4bccbf7afa6950810f0d2bba97a6f710c7b965b84e">Transfer</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Result</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a28287671eaf7406afd604bd055ba4066</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066ae0aa021e21dddbd6d8cecec71e9cf564">OK</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066aea1776502570f06ddc0569c079cb9ee2">FileExists</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a28287671eaf7406afd604bd055ba4066a5d0744802b24f44a161d350c25d76c7b">InvalidPath</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Safeness</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a8c800527afe0a8a6c71ae4cceda6bf9d</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dac6eea0560cd6f377e78dff2c85cc9122">Safe</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dad3d57868b6ff9839eff631d2cc8acbce">Unsafe</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Switch</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9f3c28a2cb05bdcc618b542e49bfda3f</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fa521c36a31c2762741cf0f8890cbe05e3">On</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Timezone</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9b1d8f31e178e17a8fef3a9e94bc4b2c</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9b1d8f31e178e17a8fef3a9e94bc4b2ca509820290d57f333403f490dde7316f4">Local</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="a9b1d8f31e178e17a8fef3a9e94bc4b2ca9234324ddf6b4176b57d803a925b7961">UTC</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Whitespaces</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ad4a46f9fb632511f6be7c53e05f330f7</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a1fc5884251ca9f20a4fd5f79a458f94f">Trim</enumvalue>
      <enumvalue file="namespaceaworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ReadBoolean</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>adb04d5102fc162a8ac01ef0999b761e4</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Case</type>
      <name>ReadCase</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a3aef0064d7182c495b6a683dd61cb3f4</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API Inclusion</type>
      <name>ReadInclusion</name>
      <anchorfile>namespaceaworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a691ce2d51651ae6a8294e76944d30416</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::strings</name>
    <filename>namespaceaworx_1_1lib_1_1strings.html</filename>
    <class kind="class">aworx::lib::strings::AString</class>
    <class kind="class">aworx::lib::strings::CString</class>
    <class kind="class">aworx::lib::strings::Format</class>
    <class kind="struct">aworx::lib::strings::IsApplicable</class>
    <class kind="struct">aworx::lib::strings::IsApplicable&lt; const lox::core::Logger &amp; &gt;</class>
    <class kind="struct">aworx::lib::strings::IsApplicable&lt; const std::string &amp; &gt;</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; AString &gt;</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; PreallocatedString&lt; TCapacity &gt; &gt;</class>
    <class kind="class">aworx::lib::strings::NumberFormat</class>
    <class kind="class">aworx::lib::strings::PreallocatedString</class>
    <class kind="class">aworx::lib::strings::ReadLineFromIStream</class>
    <class kind="class">aworx::lib::strings::String</class>
    <class kind="class">aworx::lib::strings::StringLiteral</class>
    <class kind="class">aworx::lib::strings::Substring</class>
    <class kind="struct">aworx::lib::strings::TMPLiteral</class>
    <class kind="class">aworx::lib::strings::Tokenizer</class>
    <class kind="struct">aworx::lib::strings::ToStringDefined</class>
    <class kind="struct">aworx::lib::strings::ToStringDefined&lt; const std::string &amp; &gt;</class>
    <class kind="class">aworx::lib::strings::TString</class>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a40af8c9dcfc80a2b4a9e0d50ce506725</anchor>
      <arglist>(AString &amp;target, const ReadLineFromIStream &amp;cparam)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a259d311e0220dbf28a4eb0dcb26b5b2e</anchor>
      <arglist>(AString &amp;target, const wchar_t *src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a4f19ceb8dc5cb5fb75e0e008fc0b62c9</anchor>
      <arglist>(AString &amp;target, const Format::Tab &amp;tab)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aeefaeb91f4a057ddf48252b58e7f168d</anchor>
      <arglist>(AString &amp;target, const Format::Field &amp;field)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a71883c7c0a41a97d63c3606296a07c80</anchor>
      <arglist>(AString &amp;target, const Format::Int32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a26459c1c77708cf6f56a2419734d9978</anchor>
      <arglist>(AString &amp;target, const ReadLineFromIStream &amp;param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9a404410b1aaf03e4115c05414d6bbf5</anchor>
      <arglist>(AString &amp;target, const Format::UInt32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a07f1969f5176f25927efd6c3b869dd69</anchor>
      <arglist>(AString &amp;target, const Format::Int64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a10cbaebe29c1bc6e2147b1c25d6ba6ac</anchor>
      <arglist>(AString &amp;target, const Format::UInt64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3166349c4945294de1c31b25b77da647</anchor>
      <arglist>(AString &amp;target, const Format::Double &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aa8fb47b820e77796083d2c3eb13d56b2</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aaaeb23f90707241659667c910e61bbe9</anchor>
      <arglist>(AString &amp;target, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a17dfe1060a698974265db6b780c709fa</anchor>
      <arglist>(AString &amp;target, const Format::Tab &amp;tab)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a51d3c0fe2a4125c45c804c1fb1509b3e</anchor>
      <arglist>(AString &amp;target, const wchar_t *src)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a5874b01f193017660c4748a8a5fc1fde</anchor>
      <arglist>(AString &amp;target, const Format::Field &amp;field)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af0bcfa090927eb989e55774a396d73fd</anchor>
      <arglist>(AString &amp;target, bool &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ae7cf6b7c301dca2c1b7efd7d9cf3fd1a</anchor>
      <arglist>(AString &amp;target, const Format::Int32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aff08105164bdbc38149bdea8526b0fe1</anchor>
      <arglist>(AString &amp;target, int8_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a70a7ab6f429b5e5e3361d9758b6807d9</anchor>
      <arglist>(AString &amp;target, enums::Switch &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a4e06f646e714741651dbcc70c18f7277</anchor>
      <arglist>(AString &amp;target, uint8_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a99617b411c1009b148f37391abf0d789</anchor>
      <arglist>(AString &amp;target, enums::Case &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aa619192ac17ef191b23c4a62c98c6b0e</anchor>
      <arglist>(AString &amp;target, int16_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9fad3de9eb89a67a1bc095c3fd5ffc56</anchor>
      <arglist>(AString &amp;target, enums::Alignment &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a182592417855344b2161faa31b88745e</anchor>
      <arglist>(AString &amp;target, uint16_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a829332713d7be0bbde5b1862e1ec837b</anchor>
      <arglist>(AString &amp;target, enums::Inclusion &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3ebd14cfce8c2eda7ed1dcbca395a33c</anchor>
      <arglist>(AString &amp;target, int32_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a380a2e715c58148cf81b7e31c4ef1bd9</anchor>
      <arglist>(AString &amp;target, enums::CurrentData &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af234ce05458a46a76cc5a593041895b3</anchor>
      <arglist>(AString &amp;target, const Format::UInt32 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af43cf0906d4f7d8f1b6ed6dd6454d361</anchor>
      <arglist>(AString &amp;target, enums::Safeness &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aff0544080e363cd67465fc12539c06c1</anchor>
      <arglist>(AString &amp;target, uint32_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad795b43f0a24b4c0e6147e223e051546</anchor>
      <arglist>(AString &amp;target, enums::Responsibility &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a68ce4d16395dd82846afb86689c512df</anchor>
      <arglist>(AString &amp;target, const Format::Int64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0dcce3ad139fe6f9c313fdfe9be5fed2</anchor>
      <arglist>(AString &amp;target, enums::Timezone &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0c48317b4a34060b56d3e5c581e509e1</anchor>
      <arglist>(AString &amp;target, int64_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3b71964dfcfc46db8bfe4369a60b48c3</anchor>
      <arglist>(AString &amp;target, enums::LockMode &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a0683fedae1a6920e13588d534152f4da</anchor>
      <arglist>(AString &amp;target, const Format::UInt64 &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a59c043f8dd398835f7266e1bb2c630bf</anchor>
      <arglist>(AString &amp;target, enums::Whitespaces &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ac2e8c17181156fa7a4a2f3cb94dc15a3</anchor>
      <arglist>(AString &amp;target, uint64_t &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abe6407ebad387df4da89aeed389e712e</anchor>
      <arglist>(AString &amp;target, enums::Create &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad9a951e16433abb2461bca80d0c2ad8e</anchor>
      <arglist>(AString &amp;target, const Format::Double &amp;fmt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a58b0f925b58b64d308bc299f3fe25281</anchor>
      <arglist>(AString &amp;target, enums::Propagation &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abc006ddec9bb08e63d7e764a785e715b</anchor>
      <arglist>(AString &amp;target, double &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>aef0aaba9060d3dd6bcb3914d2b7cc538</anchor>
      <arglist>(AString &amp;target, float &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo&lt; const lox::core::Logger &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9293db3b9b449a46d07d91e1b8964183</anchor>
      <arglist>(AString &amp;target, const lox::core::Logger &amp;logger)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a46d2b8074d6fd76918018ca6704e7cfc</anchor>
      <arglist>(AString &amp;target, const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo_NC</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>abcd4a1d202f1c13b510ec14cd55d3a7a</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo_NC&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ac8de1e5cfd3f85418261ced125aed661</anchor>
      <arglist>(AString &amp;target, const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7c480abd39fa10f40a8af566cf1f4dda</anchor>
      <arglist>(std::ostream &amp;stream, const String &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream *</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9a3fcc93b836b62a2ebbca22d3732520</anchor>
      <arglist>(std::ostream *stream, const String &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a357b7d2e804cb32ac765641afa415eee</anchor>
      <arglist>(std::istream &amp;stream, AString &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::istream *</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a3b4a073d715b00201505dc87ffdcb73e</anchor>
      <arglist>(std::istream *stream, AString &amp;string)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>acee8df0c9711c319807b3661f1046dfd</anchor>
      <arglist>(const String &amp;as, std::string &amp;target, int regionStart, int regionLength=CString::MaxLen, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a69456b076a8fce4982a9d3790796d424</anchor>
      <arglist>(const String &amp;as, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a039f938c7e403c09e0271e4f353123bf</anchor>
      <arglist>(const String &amp;as)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a8f1c5a17c57b3b54f2f46e58bef50487</anchor>
      <arglist>(const String &amp;as, std::string &amp;target, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>TReturn</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7cfd45024bf9222b42febac98fdcc146</anchor>
      <arglist>(const TString)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToString&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a8d85e610e17c69e9ece8b558735519e0</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToString&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ae0fc15801fea6b54738ca715ed192cf0</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <docanchor file="namespaceaworx_1_1lib_1_1strings">alib_namespace_strings_nullable</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings">alib_namespace_strings_class_overview_astring_construction</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Introduction">alib_namespace_strings_intro</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Classes overview">alib_namespace_strings_class_overview</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class String">alib_namespace_strings_class_overview_as</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class TString">alib_namespace_strings_class_overview_asterminatable</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class AString">alib_namespace_strings_class_overview_astring</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class PreallocatedString">alib_namespace_strings_class_overview_asprealoc</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class Substring">alib_namespace_strings_class_overview_substring</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class StringLiteral">alib_namespace_strings_class_overview_asliteral</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="&apos;Non-Checking&apos; Methods of ALib String Classes">alib_namespace_strings_nonchecking</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Compatibility with External Libraries">alib_namespace_strings_compat</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Debugging ALib String Classes">alib_namespace_strings_debugging</docanchor>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::system</name>
    <filename>namespaceaworx_1_1lib_1_1system.html</filename>
    <class kind="class">aworx::lib::system::Directory</class>
    <class kind="class">aworx::lib::system::ProcessInfo</class>
    <class kind="class">aworx::lib::system::System</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::threads</name>
    <filename>namespaceaworx_1_1lib_1_1threads.html</filename>
    <class kind="class">aworx::lib::threads::Runnable</class>
    <class kind="class">aworx::lib::threads::SmartLock</class>
    <class kind="class">aworx::lib::threads::Thread</class>
    <class kind="class">aworx::lib::threads::ThreadLock</class>
    <class kind="class">aworx::lib::threads::ThreadLockNR</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::time</name>
    <filename>namespaceaworx_1_1lib_1_1time.html</filename>
    <class kind="class">aworx::lib::time::Ticks</class>
    <class kind="class">aworx::lib::time::TicksCalendarTime</class>
    <class kind="class">aworx::lib::time::TickSpan</class>
    <class kind="class">aworx::lib::time::TickWatch</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox</name>
    <filename>namespaceaworx_1_1lox.html</filename>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::loggers</namespace>
    <class kind="class">aworx::lox::ALox</class>
    <class kind="class">aworx::lox::ALoxReportWriter</class>
    <class kind="class">aworx::lox::ESC</class>
    <class kind="class">aworx::lox::Log</class>
    <class kind="struct">aworx::lox::LogData</class>
    <class kind="class">aworx::lox::Lox</class>
    <member kind="enumeration">
      <type></type>
      <name>Scope</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a4cc6684df7b4a92b1dec6fce3264fac8">Global</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a1ee3f312b05c55202500569aadfc8d9b">ThreadOuter</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6aac70412e939d72a9234cdebb1af5867b">Path</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a1351017ac6423911223bc19a8cb7c653">Filename</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6a4c3880bb027f159e801041b1021e88e8">Method</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="aaecc53892786f2fa11e682f633af84c6ae46b159c990fae9e712309bdb4d7b7c4">ThreadInner</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Verbosity</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>abf3be10d03894afb391f3a2935e3b313</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313ad4a9fa383ab700c5bdd6f31cf7df0faf">Verbose</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a4059b0251f66a18cb56f544728796875">Info</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a0eaadb4fcb48a0a0ed7bc9868be9fbaa">Warning</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
      <enumvalue file="namespaceaworx_1_1lox.html" anchor="abf3be10d03894afb391f3a2935e3b313ad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
    </member>
    <member kind="function">
      <type>Verbosity</type>
      <name>ReadVerbosity</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>a198631ef025eac410d87373b39c7280f</anchor>
      <arglist>(const String &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>ade21849436cde3af69157368d5e5a27e</anchor>
      <arglist>(Verbosity verbosity, int priority, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>AString &amp;</type>
      <name>ToString</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>a0883c50f69bfa5d7b121a59ba14d8464</anchor>
      <arglist>(Scope scope, int pathLevel, AString &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>const String</type>
      <name>ToStringX</name>
      <anchorfile>namespaceaworx_1_1lox.html</anchorfile>
      <anchor>abfd92f16f9c0e36069f30ffa03a5d96d</anchor>
      <arglist>(Verbosity verbosity)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox::core</name>
    <filename>namespaceaworx_1_1lox_1_1core.html</filename>
    <namespace>aworx::lox::core::textlogger</namespace>
    <class kind="class">aworx::lox::core::Domain</class>
    <class kind="struct">aworx::lox::core::Logable</class>
    <class kind="class">aworx::lox::core::Logger</class>
    <class kind="class">aworx::lox::core::ScopeDump</class>
    <class kind="class">aworx::lox::core::ScopeInfo</class>
    <class kind="class">aworx::lox::core::ScopeStore</class>
    <class kind="class">aworx::lox::core::ScopeStoreType</class>
    <member kind="typedef">
      <type>std::vector&lt; core::Logable * &gt;</type>
      <name>Logables</name>
      <anchorfile>namespaceaworx_1_1lox_1_1core.html</anchorfile>
      <anchor>a89b734aa261b747d9edc7a459bfc9db8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox::core::textlogger</name>
    <filename>namespaceaworx_1_1lox_1_1core_1_1textlogger.html</filename>
    <class kind="class">aworx::lox::core::textlogger::AutoSizes</class>
    <class kind="class">aworx::lox::core::textlogger::MetaInfo</class>
    <class kind="class">aworx::lox::core::textlogger::ObjectConverter</class>
    <class kind="class">aworx::lox::core::textlogger::PlainTextLogger</class>
    <class kind="class">aworx::lox::core::textlogger::StringConverter</class>
    <class kind="class">aworx::lox::core::textlogger::TextLogger</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox::loggers</name>
    <filename>namespaceaworx_1_1lox_1_1loggers.html</filename>
    <class kind="class">aworx::lox::loggers::AnsiConsoleLogger</class>
    <class kind="class">aworx::lox::loggers::AnsiLogger</class>
    <class kind="class">aworx::lox::loggers::ConsoleLogger</class>
    <class kind="class">aworx::lox::loggers::MemoryLogger</class>
    <class kind="class">aworx::lox::loggers::TextFileLogger</class>
    <class kind="class">aworx::lox::loggers::VStudioLogger</class>
    <class kind="class">aworx::lox::loggers::WindowsConsoleLogger</class>
  </compound>
  <compound kind="group">
    <name>GrpALibMacros</name>
    <title>ALib  Macros</title>
    <filename>group__GrpALibMacros.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGIFY</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3f61373916523c0c97327c83b2d6132e</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_CONCAT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf5375d121ff32a60c641c7e3a4b7810e</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_API</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga74fe706f3101d8e1e21555f772da2849</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab1836c6de18fd089b123e40e22472f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac17f8e410ff33bbb690c0608d12ba5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga8460b7062323107819d75e7001451cc4</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_REPORT_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabd7b7f6d6244265e96a13ea98bee76b9</anchor>
      <arglist>(type, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabdd5780e186ebbd62960d7ca9673dff1</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga259ac181b20784b8dfa4cd72c191da4c</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaecdb7875b059e8d10edc15ff30f22b54</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga6d09217171c3a303e6b91eba62833193</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gafeaac7eedb1d9a90091356b6c68934cb</anchor>
      <arglist>(cond)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga458a325506658361be4a4f8cf2c1d50e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_ERROR_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1d9b0a700c59c2e87bc2935d6a434db9</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf6ee54a2e2b00632832c094c3683075e</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING_S512</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga3cafe9da29ad24d8d8a7997556dde3be</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaa7e7955d3374820a4b3a2a65488c6aca</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_NOT_EQUALS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac3c19147e6144f75f38dc598e8ffd3e7</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_GREATER_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab2d2c9ba9eab04d9b95b78340c582a21</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_RESULT_LESS_THAN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gab9a9f80902169489b72c156e4317419e</anchor>
      <arglist>(func, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabfca7dd3cf5d8186e47c2bcf11343679</anchor>
      <arglist>(libdecl,identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DEFINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga671251ff77d829ce136055ef6a415ca1</anchor>
      <arglist>(className, identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga0627077cd7f96033d848dc29f2875a5d</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_TYPE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga5558b6404fddb317efd26bf8a9665f40</anchor>
      <arglist>(className, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac506942a02a0be3af76a71116e8ce645</anchor>
      <arglist>(identifier, default)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_ENABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaea25b327ef9d2c90aad05f5bef07bd97</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_PER_INSTANCE_DISABLE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga30e363647f8ea56f0af8e834768548bc</anchor>
      <arglist>(instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga352937357f43d7f9e249427f7f47556a</anchor>
      <arglist>(msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaec0ad3f2704be43a1dfa4101f700821c</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARN_ONCE_IF_NOT</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga532a206ad57a4b4f4b1a1e110e8b0cd6</anchor>
      <arglist>(cond, msg, instance, identifier)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_CODE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gad2c895310139b3c6988218f2d71896ee</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OWN</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga428418e97842561b5fa5118c120954a9</anchor>
      <arglist>(ownable)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DECLARATION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga7ef8eaf71cad1c7be73ef8e61dc65177</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_DEFINITION</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga87261d3411f0175bbc3efab49720023f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRINGS_APPLYTO_INLINE</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaf3673497e1c2e5436ad2b369c135658f</anchor>
      <arglist>(TYPE, IMPLEMENTATION)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALibCompilerSymbols</name>
    <title>ALib Compilation Symbols</title>
    <filename>group__GrpALibCompilerSymbols.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_AVOID_ANALYZER_WARNINGS_OFF</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga749e93d24d210c48e3b9b31a09727b82</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_AVOID_ANALYZER_WARNINGS_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>gacaa316e613cf0f7bc021130c1b4e2f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_OFF</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga141eac004cc6915d6217ddd591b46b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga3afdbe5a480e0328d115f7b6fb17f5f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_STRINGS_OFF</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>gaffe4a144b888498c743d7b81d983d84b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_STRINGS_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga2992625b88f70b1e01564be4e7eba2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DLL_EXPORTS</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga3495a2abef09ec42f2f17bc642f86cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ECLIPSE_CDT_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>gaf14aacbf978386a12da102ba323469e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_FEAT_THREADS_OFF</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>gac4bd86743dc96603b414fa7e517fdb9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_FEAT_THREADS_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga1bed5257f25120726eb658164c482957</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_GTEST_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>gab3693d8273b2b664d1bc1cccb319ac2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_QTCREATOR_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga18b975ebc3c8f298e32a26b59ff30e7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_VSTUDIO_ON</name>
      <anchorfile>group__GrpALibCompilerSymbols.html</anchorfile>
      <anchor>ga40a577eb60771e76df0ba0f3d8b4d322</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALibCodeSelectorSymbols</name>
    <title>ALib Symbols To Select Code Fragments</title>
    <filename>group__GrpALibCodeSelectorSymbols.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_AVOID_ANALYZER_WARNINGS</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga22453f45d36d0fa8790b74a270f027c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>gac56d0d10d022f28ce6bacdc612b4a743</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DEBUG_STRINGS</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>gae0e4a87e11482df5ecd72f6a2a648f05</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ECLIPSE_CDT</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga957b686ba8c86c9c305e6cbc6d1dcac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_FEAT_THREADS</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga1b908cb4e15b716440551455e0a5f138</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_GTEST</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga671a29c6b98b59e9db6149643dd2eb25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_QTCREATOR</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga8f48ad22225f9bc74fce02ae8013e3bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_VSTUDIO</name>
      <anchorfile>group__GrpALibCodeSelectorSymbols.html</anchorfile>
      <anchor>ga54d417a77a33dc7266c3ed03e5b7e6f0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALoxMacrosLowLevel</name>
    <title>ALox Low level Macros</title>
    <filename>group__GrpALoxMacrosLowLevel.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_API</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga2cde43a12bd2be40baa4896e409d642c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_ACQUIRE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga105a9f44250c23d6bb37df63aa9d9cbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga71f7449b6ad8bbd0ba22f897d7338a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_RELEASE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga0d5795316ecfccc7b40b43c01bf62b0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_ACQUIRE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga9ac629621d8152810e41e19931c990a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga1f170b96d3ead37b7f530134e64bf121</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_RELEASE</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga2ef98e816bdf36da37bb9bddbdfd635f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpMacrosDebugLog</name>
    <title>ALox Macros For Debug Logging</title>
    <filename>group__GrpMacrosDebugLog.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>Log_AddDebugLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaa891e8485ea970f574971c6afd851218</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Assert</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga2797c2e9f997606c3c786fa68720ac71</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_ClearSourcePathTrimRules</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaff8f037b778ce73b40e0c7a0506a8718</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Entry</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga9ac05a63013c784625c66685ad51aff3</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Error</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga8d8e6df0e755763bd471751235199baf</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_GetLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga07ed02a33090774d44b0a9eba642f362</anchor>
      <arglist>(identifier, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_If</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga7a1af9531448e3c6da1027b193e3b01b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Info</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaed4877ef3a04a6eb1ec1d4fba8305d75</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_LogConfig</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga1bac07b7ec3ca3616c301f171e9e73d9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_MapThreadName</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad01526d3f277fab96faf18695d25cb7e</anchor>
      <arglist>(threadName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Once</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga68c8af8941a64be4f6e075ab31c6c05b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Prune</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga7dbb7427d18d49e2dd87d5f2d2036e0b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveDebugLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac5d4bbea354fbabbebb7703995c3399d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga4a08a7a5c5e794a34d7d05f4d35689e4</anchor>
      <arglist>(logger)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_RemoveThreadDomain</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gafc93873c04ed08e842109543d142fb60</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Retrieve</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga233db1e86b0cf457b550f74b58d69926</anchor>
      <arglist>(data,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetDomain</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac4a4311460b712126253fce7304ac6f4</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetDomainSubstitutionRule</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga619af6c6682bc920e038b0fe006c49be</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetPrefix</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga4186c23d7999be11f0e5017d254a306c</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetSourcePathTrimRule</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gac96dec2672c7ae4e722cae3b12eaf3fd</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetStartTime</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga14bcc9217818e50b7fe5028398f11e8d</anchor>
      <arglist>(time, loggerName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetVerbosity</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad5444af82c2a3640a1c456940b8c3b8f</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Store</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga9c1ca580a86c5c6a0653146b0bb9cb38</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Verbose</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga975fbf7e95ed6506992f9714627202d0</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_Warning</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaa9822f0eda4cc7e9c3f3e99d6238f2aa</anchor>
      <arglist>(...)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpMacrosReleaseLog</name>
    <title>ALox Macros For Release Logging</title>
    <filename>group__GrpMacrosReleaseLog.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Assert</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga4d9961312aab181a28b21724c3809184</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_ClearSourcePathTrimRules</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga1689da460f8040489689b3f45cf1e6b2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Entry</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga3ee12da39c3574baf4fb03f7f323c886</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Error</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga5fa12e4bc99fd2ebed4fe90729f54a03</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_GetLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga8536e68dcdee27e1d3463687d42ee6ed</anchor>
      <arglist>(identifier, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_If</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga31e9c5302ccb2af7285d9e17a46aac2b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Info</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga28233c29442a3ae8996d32b5078537d9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_LogConfig</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga0578fb3bfeb63ea05db9c34bc1a0d07d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_MapThreadName</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga089dc860d3f28c5cf30b661f2877462a</anchor>
      <arglist>(threadName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Once</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga03e5f8a0b134f709f130a4f93b2f8ab2</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Prune</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga04158d8131eba14e98f93e433b6325d2</anchor>
      <arglist>(releaseLogCode)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_RemoveLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga321e65d2004cef126220b042fc95e03b</anchor>
      <arglist>(logger)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_RemoveThreadDomain</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga5af8171356c0b231483221d0b3e534c1</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Retrieve</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga21ac85d6bd6b297b92b707b6362f52df</anchor>
      <arglist>(data,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetDomain</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga7e1bc971e6cd3b071fbc928a7d46fae9</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetDomainSubstitutionRule</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gab66ecad871e42c6779e9f2bb62921be3</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetPrefix</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga0f4d320a3b393e1e6eba353f567dec4d</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetSourcePathTrimRule</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga26b42492cafe7bc093cd810facddeb6b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetStartTime</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga2c91f19bc972dbacc137e8c4c88ee25c</anchor>
      <arglist>(time, loggerName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetVerbosity</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga58d12e520c215bfc22c8da42777d567b</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Store</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaa8e5c76201f2ac838ef643377641f2a6</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Verbose</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gacbfc03392b8a4f79d0bcb46bc2825d31</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_Warning</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaf2a9706a6b6c48b69cc10ae1d65d9379</anchor>
      <arglist>(...)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALoxCompilerSymbols</name>
    <title>ALox Compilation Symbols</title>
    <filename>group__GrpALoxCompilerSymbols.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_CI_OFF</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>gabf2ce25e392b218c30b6b0af8280ddf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_CI_ON</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga9920512a7b2c48a248b5cfb1643c7cac</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_OFF</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>gaf2de46ee4b30ee640266f7ac5de25bb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_ON</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga1d6b17b1dc814c44f312baf8d6f56688</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DLL_EXPORTS</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga811a35cc97d3af292de65fb560a0479a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG_CI_OFF</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga9723e112c2b491520922d1fdfef60504</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG_CI_ON</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga85c683ba401d4c9216c96a9a17a9e9a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG_OFF</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>gae77944a12e0a9b9bc2657cb7298d70f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG_ON</name>
      <anchorfile>group__GrpALoxCompilerSymbols.html</anchorfile>
      <anchor>ga56671e8b3fa44f19acb0d9c4c4403682</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALoxCodeSelectorSymbols</name>
    <title>ALox Symbols to Select Code Fragments</title>
    <filename>group__GrpALoxCodeSelectorSymbols.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga2c6ba32fb7e34be7cee2100578b84a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_DBG_LOG_CI</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga392381bb9caea53c133ce68c32cee4e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga4d0c70512b17f1dd4fa3556f79dd2689</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_REL_LOG_CI</name>
      <anchorfile>group__GrpALoxCodeSelectorSymbols.html</anchorfile>
      <anchor>ga4b0e38e300ec824146da5e868f2c6290</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GrpALibStringsMacros</name>
    <title>GrpALibStringsMacros</title>
    <filename>group__GrpALibStringsMacros.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRING_DBG_CHK</name>
      <anchorfile>group__GrpALibStringsMacros.html</anchorfile>
      <anchor>gae7492253da37c76b118d446494f1f632</anchor>
      <arglist>(instance)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_STRING_DBG_UNTERMINATE</name>
      <anchorfile>group__GrpALibStringsMacros.html</anchorfile>
      <anchor>gacf96023d903e78f3b5d784a799041667</anchor>
      <arglist>(astring, offset)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>cppmainpage</name>
    <title>C++ Reference</title>
    <filename>cppmainpage</filename>
  </compound>
  <compound kind="page">
    <name>cppprepro</name>
    <title>ALox and the C++ Preprocessor</title>
    <filename>cppprepro</filename>
    <docanchor file="cppprepro" title="2. Introduction">cppprepro_intro</docanchor>
    <docanchor file="cppprepro" title="2.1. Structure of ALox Preprocessor Usage">cppprepro_intro1</docanchor>
    <docanchor file="cppprepro" title="1.2. Preprocessor symbols introduced by ALib">cppprepro_intro2</docanchor>
    <docanchor file="cppprepro" title="3. Compilation Symbols">cppprepro_compsymbols</docanchor>
    <docanchor file="cppprepro" title="4. Code Selection Symbols">cppprepro_code_selection_symbols</docanchor>
    <docanchor file="cppprepro" title="5. C++ Macros">cppprepro_macros</docanchor>
    <docanchor file="cppprepro" title="5.2. ALox Logging Macros">cppprepro_42</docanchor>
    <docanchor file="cppprepro" title="5.3. ALox Low Level Macros">cppprepro_43</docanchor>
    <docanchor file="cppprepro" title="5.4. ALib Macros">cppprepro_44</docanchor>
  </compound>
  <compound kind="page">
    <name>cppsetup</name>
    <title>IDE/Build system Setup</title>
    <filename>cppsetup</filename>
    <docanchor file="cppsetup" title="1. Introduction">cppsetup_1</docanchor>
    <docanchor file="cppsetup" title="2. Download">cppsetup_download</docanchor>
    <docanchor file="cppsetup" title="3. Set up the Built System">cppsetup_setup</docanchor>
    <docanchor file="cppsetup" title="3.1. Using ALox with CMake">cppsetup_cmake</docanchor>
    <docanchor file="cppsetup" title="3.2. Using ALox with QT Creator">cppsetup_qtcreator</docanchor>
    <docanchor file="cppsetup" title="3.3. Using ALox with Visual Studio">cppsetup_vstudio</docanchor>
    <docanchor file="cppsetup" title="3.3.1 Open provided DLL project">cppsetup_vstudio1</docanchor>
    <docanchor file="cppsetup" title="3.3.2. Set build dependency">cppsetup_vstudio2</docanchor>
    <docanchor file="cppsetup" title="3.3.3. Reference the ALox library from within your project">cppsetup_vstudio3</docanchor>
    <docanchor file="cppsetup" title="3.3.4. Add the ALox include directory to your project">cppsetup_vstudio4</docanchor>
    <docanchor file="cppsetup" title="4. Test your setup">cppsetup_testsetup</docanchor>
    <docanchor file="cppsetup" title="5. Wrap up">cppsetup_wrapup</docanchor>
  </compound>
  <compound kind="page">
    <name>cpptutorial</name>
    <title>ALox for C++ Tutorial</title>
    <filename>cpptutorial</filename>
    <docanchor file="cpptutorial" title="1. Hello ALox">tutcpp_hello_alox</docanchor>
    <docanchor file="cpptutorial" title="2. Class Lox and ALox C++ Macros">tutcpp_adding_ALox</docanchor>
    <docanchor file="cpptutorial" title="3. Create a tutorial project or equip your current project with ALox">tutcpp_createproject</docanchor>
    <docanchor file="cpptutorial" title="4. Class Logger">tutcpp_logger</docanchor>
    <docanchor file="cpptutorial" title="5. Run the Application">tutcpp_run</docanchor>
    <docanchor file="cpptutorial" title="5.1. Run your application within your IDE">tutcpp_run_ide</docanchor>
    <docanchor file="cpptutorial" title="5.2. Build a release version">tutcpp_run_release</docanchor>
    <docanchor file="cpptutorial" title="6. Controlling the &apos;Verbosity&apos;">tutcpp_verbosity</docanchor>
    <docanchor file="cpptutorial" title="7. Log Domains">tutcpp_logdomains</docanchor>
    <docanchor file="cpptutorial" title="8. Hierarchical Log Domains">tutcpp_logdomains_hierarchical</docanchor>
    <docanchor file="cpptutorial" title="9. Scope Domains">tutcpp_scope_domains</docanchor>
    <docanchor file="cpptutorial" title="10. Conditional logging">tutcpp_conditional</docanchor>
    <docanchor file="cpptutorial" title="11. Prefixes">tutcpp_Log_Prefix</docanchor>
    <docanchor file="cpptutorial" title="12. LogTools: Log Complex Data">tutcpp_logtools</docanchor>
    <docanchor file="cpptutorial" title="13 Using aworx::StringNNN for Log Messages">tutcpp_astring</docanchor>
    <docanchor file="cpptutorial" title="14. Name Your Threads">tutcpp_threadnames</docanchor>
    <docanchor file="cpptutorial" title="15. ALox Log Data">tutcpp_logdata</docanchor>
    <docanchor file="cpptutorial" title="16. ALox Configuration Information and Internal Log Messages">tutcpp_config</docanchor>
    <docanchor file="cpptutorial" title="Further Reading">tutcpp_end</docanchor>
  </compound>
</tagfile>
