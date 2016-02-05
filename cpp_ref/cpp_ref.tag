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
    <includes id="as_8hpp" name="as.hpp" local="yes" imported="no">alib/strings/as.hpp</includes>
    <includes id="ns__aworx_8hpp" name="ns_aworx.hpp" local="yes" imported="no">alib/core/ns_aworx.hpp</includes>
    <includes id="namespace_8hpp" name="namespace.hpp" local="yes" imported="no">alib/strings/namespace.hpp</includes>
    <class kind="class">aworx::lib::ALIB</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
    <namespace>aworx::lib::threads</namespace>
  </compound>
  <compound kind="file">
    <name>alox.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>alox_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="alox__symbols_8hpp" name="alox_symbols.hpp" local="yes" imported="no">internals/alox_symbols.hpp</includes>
    <includes id="alox__macros_8hpp" name="alox_macros.hpp" local="yes" imported="no">internals/alox_macros.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">log.hpp</includes>
    <includes id="lox_8hpp" name="lox.hpp" local="yes" imported="no">lox.hpp</includes>
    <class kind="class">aworx::lox::ESC</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ALOX_API</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga2cde43a12bd2be40baa4896e409d642c</anchor>
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
      <name>Log_AddDebugLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaa891e8485ea970f574971c6afd851218</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_AddLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga518bf5331afc5bd2e6d79a9f290ae8b6</anchor>
      <arglist>(...)</arglist>
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
      <name>Log_GetMarker</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga85abcf294a9046897fc2924513e7947f</anchor>
      <arglist>(marker, scope)</arglist>
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
      <name>Log_Line</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gae6d6d078cd4c5ed6c6726d0cbdbbc4aa</anchor>
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
      <name>LOG_POSTFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gad662b4dbce165eccc829278f9a1d5477</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_PREFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gaae1d11681b36518afb9413f4194b18a6</anchor>
      <arglist></arglist>
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
      <name>LOG_REL_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gab014491c0aaaceaa1ef1a7d679a8d3e0</anchor>
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
      <name>Log_RemoveLoggers</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad3a71e0a643a1c19f8875e586f95b92e</anchor>
      <arglist>(...)</arglist>
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
      <name>Log_SetLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga8fb5f633199382936bfc67e45c1737af</anchor>
      <arglist>(disabled, filter)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetMarker</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaecd826ea5803a068bca503e075f5d878</anchor>
      <arglist>(marker, scope)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetStartTime</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga519416f7b52968906c24d3c57f4ce39f</anchor>
      <arglist>(time, filter)</arglist>
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
      <name>Lox_AddLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gac3806ad5dcf0f48b170f79069369f380</anchor>
      <arglist>(...)</arglist>
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
      <name>Lox_GetMarker</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaac5f1d37b8f195a7d387d4bf59f9b7c0</anchor>
      <arglist>(marker, scope)</arglist>
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
      <name>Lox_Line</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga97a2c77a1cef79dc8dd295153ea2347e</anchor>
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
      <name>LOX_POSTFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gad7b0252385be7787e0e08c7ea0582ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_PREFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga48644d682557d34b6a07bea1b13bb848</anchor>
      <arglist></arglist>
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
      <name>Lox_RemoveLoggers</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaa493b652d1b9a0d3bca8662603f5e199</anchor>
      <arglist>(filter)</arglist>
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
      <name>Lox_SetLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gae6103e5556647a551bb2d78afb60522d</anchor>
      <arglist>(enable, filter)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetMarker</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gacea507bfcbffd40425f919f17a36fb9f</anchor>
      <arglist>(marker, scope)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetStartTime</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga4ce0c3ef52fd3806ee4e99f8c44e8179</anchor>
      <arglist>(time, filter)</arglist>
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
  </compound>
  <compound kind="file">
    <name>as.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>as_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::AS</class>
    <class kind="struct">aworx::lib::strings::ToASDefined</class>
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
    <member kind="function">
      <type>TReturn</type>
      <name>ToAS</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a86b0b5fb454f1fb24e37f31c51159cea</anchor>
      <arglist>(const TString)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>asalloc.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>asalloc_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASAlloc</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; ASAlloc &gt;</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
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
    <name>asliteral.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>asliteral_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASLiteral</class>
    <class kind="struct">aworx::lib::strings::TMPLiteral</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>asprealloc.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>asprealloc_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASPreAlloc</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; ASPreAlloc&lt; TCapacity &gt; &gt;</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>assubstring.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>assubstring_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASSubstring</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>asterminatable.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>asterminatable_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASTerminatable</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable</class>
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
  </compound>
  <compound kind="file">
    <name>callerinfo.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>callerinfo_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="ticks_8hpp" name="ticks.hpp" local="yes" imported="no">alib/time/ticks.hpp</includes>
    <includes id="thread_8hpp" name="thread.hpp" local="yes" imported="no">thread.hpp</includes>
    <class kind="class">aworx::lox::core::CallerInfo</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
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
    <member kind="variable">
      <type>const char</type>
      <name>PathSeparator</name>
      <anchorfile>namespaceaworx_1_1lib_1_1system.html</anchorfile>
      <anchor>a081742a3398152ceb8694674ffd21c37</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>domain.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>domain_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <class kind="class">aworx::lox::core::Domain</class>
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
    <includes id="configuration_8hpp" name="configuration.hpp" local="yes" imported="no">alib/config/configuration.hpp</includes>
    <class kind="class">aworx::lib::config::IniFile</class>
    <class kind="class">aworx::lib::config::IniFile::Section</class>
    <class kind="class">aworx::lib::config::IniFile::Variable</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::config</namespace>
    <namespace>aworx::lib::strings</namespace>
  </compound>
  <compound kind="file">
    <name>log.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>log_8hpp</filename>
    <class kind="class">aworx::lox::ALoxReportWriter</class>
    <class kind="class">aworx::lox::Log</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
  </compound>
  <compound kind="file">
    <name>logger.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/core/</path>
    <filename>logger_8hpp</filename>
    <includes id="alox_8hpp" name="alox.hpp" local="yes" imported="no">alox/alox.hpp</includes>
    <includes id="callerinfo_8hpp" name="callerinfo.hpp" local="yes" imported="no">callerinfo.hpp</includes>
    <includes id="domain_8hpp" name="domain.hpp" local="yes" imported="no">domain.hpp</includes>
    <class kind="class">aworx::lox::core::Logger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
  </compound>
  <compound kind="file">
    <name>lox.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alox/</path>
    <filename>lox_8hpp</filename>
    <includes id="threadlock_8hpp" name="threadlock.hpp" local="yes" imported="no">alib/threads/threadlock.hpp</includes>
    <includes id="callerinfo_8hpp" name="callerinfo.hpp" local="yes" imported="no">alox/core/callerinfo.hpp</includes>
    <includes id="domain_8hpp" name="domain.hpp" local="yes" imported="no">alox/core/domain.hpp</includes>
    <class kind="class">aworx::lox::Lox</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
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
      <name>ALIB_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga325630a2911ce8e6b188bb5e7ab7f38a</anchor>
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
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1526353c5a75ab50925d64b13cf2ea4b</anchor>
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
      <name>ALIB_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga9760e218b8f31dab354ea3fd9668db73</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaba07586b518480b52466e018bfa34c98</anchor>
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
      <name>ALIB_ASSERT_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac9a7ce9ac002073d26b3abf5797e9d86</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga12732c26cd94f68b87b8d8a31bb079c9</anchor>
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
      <name>ALIB_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga325630a2911ce8e6b188bb5e7ab7f38a</anchor>
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
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1526353c5a75ab50925d64b13cf2ea4b</anchor>
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
      <name>ALIB_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga9760e218b8f31dab354ea3fd9668db73</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaba07586b518480b52466e018bfa34c98</anchor>
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
      <name>ALIB_ASSERT_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac9a7ce9ac002073d26b3abf5797e9d86</anchor>
      <arglist>(cond, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ASSERT_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga12732c26cd94f68b87b8d8a31bb079c9</anchor>
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
  </compound>
  <compound kind="file">
    <name>namespace.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>namespace_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="asterminatable_8hpp" name="asterminatable.hpp" local="yes" imported="no">alib/strings/asterminatable.hpp</includes>
    <includes id="asliteral_8hpp" name="asliteral.hpp" local="yes" imported="no">alib/strings/asliteral.hpp</includes>
    <includes id="asalloc_8hpp" name="asalloc.hpp" local="yes" imported="no">alib/strings/asalloc.hpp</includes>
    <includes id="asprealloc_8hpp" name="asprealloc.hpp" local="yes" imported="no">alib/strings/asprealloc.hpp</includes>
    <includes id="applyto_8hpp" name="applyto.hpp" local="yes" imported="no">alib/strings/applyto.hpp</includes>
    <includes id="applyformat_8hpp" name="applyformat.hpp" local="yes" imported="no">alib/strings/applyformat.hpp</includes>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="variable" static="yes">
      <type>static constexpr ASLiteral&lt; 4 &gt;</type>
      <name>DefaultWhitespaces</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a883f1244d6fd8d7f4615d647fa388d04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr ASLiteral&lt; 1 &gt;</type>
      <name>NewLine</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9976902761097963bf1c3d15a704dd9a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ns_aworx.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/core/</path>
    <filename>ns__aworx_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <class kind="class">aworx::lib::strings::ASLiteral</class>
    <class kind="class">aworx::lib::strings::ASPreAlloc</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <member kind="typedef">
      <type>aworx::lib::strings::ASAlloc</type>
      <name>AString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5878d649ed3cc544cbd74721f95da495</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::AS</type>
      <name>String</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a1b602fe268f8de37e14430b7e646cd0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 128 &gt;</type>
      <name>String128</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abb9edf26ef4b9c245c5a95bb13f41dcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 16 &gt;</type>
      <name>String16</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acbea83160c272e842de487ed7aa0caab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 1024 &gt;</type>
      <name>String1K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acd9946aad9d9041ea509a3bced22e283</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 256 &gt;</type>
      <name>String256</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a81ae91cb74396a4fc28abd35ed7ff052</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 2048 &gt;</type>
      <name>String2K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af3dee8b08186b18ae10ef7bb0a41e650</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 32 &gt;</type>
      <name>String32</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8a557200d216efbde6004a5eea849b86</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 4096 &gt;</type>
      <name>String4K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab35934f523d9f334a8310ea3384d3d67</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 512 &gt;</type>
      <name>String512</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afc3e452a4a1195b67d5a8121fd9ea8ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 64 &gt;</type>
      <name>String64</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad16dfdce0f76423f90dcf6821f8b4a7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 8 &gt;</type>
      <name>String8</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a639c84da3f1fd25fe67d734809c35992</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASLiteral&lt; TLength &gt;</type>
      <name>StringLiteral</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a25a9748ddb0997bcedc38913800a9352</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASSubstring</type>
      <name>Substring</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a020f593b093787650587801352ccddd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASTerminatable</type>
      <name>TString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a2de28a17dc8f201aaa9a8bfa637500a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr String</type>
      <name>EmptyString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae8312c2e2a7a26985be3500c40599b61</anchor>
      <arglist>(&quot;&quot;, 0)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr String</type>
      <name>NullString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a6d6180d70c719442ba8b7a120689b9ce</anchor>
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
    <name>process.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/system/</path>
    <filename>process_8hpp</filename>
    <class kind="class">aworx::lib::system::ProcessInfo</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::system</namespace>
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
    <class kind="struct">aworx::lib::strings::ToASDefined&lt; const std::string &amp; &gt;</class>
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
      <type>const char *</type>
      <name>ToAS&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af2f5751974e1cdb68c13d3a8ac337b7b</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToAS&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad176816568c03b4c43b5bbfb814ca7f5</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7b3324b379ed34963410530fde2392e5</anchor>
      <arglist>(const AS &amp;as, std::string &amp;target, int regionStart, int regionLength=CString::MaxLen, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a70ca8b6e2ef4a9264c6c5f2755a43b07</anchor>
      <arglist>(const AS &amp;as, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af8e87f4ad5a228fdc94f04d405b281d8</anchor>
      <arglist>(const AS &amp;as)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a82a39be3112d82041508726a9dfad939</anchor>
      <arglist>(const AS &amp;as, std::string &amp;target, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
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
    <class kind="class">aworx::lox::core::textlogger::TextLogger</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
    <namespace>aworx::lox</namespace>
    <namespace>aworx::lox::core</namespace>
    <namespace>aworx::lox::core::textlogger</namespace>
  </compound>
  <compound kind="file">
    <name>thread.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/threads/</path>
    <filename>thread_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="asprealloc_8hpp" name="asprealloc.hpp" local="yes" imported="no">alib/strings/asprealloc.hpp</includes>
    <class kind="class">aworx::lib::threads::Runnable</class>
    <class kind="class">aworx::lib::threads::Thread</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::threads</namespace>
  </compound>
  <compound kind="file">
    <name>threadlock.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/threads/</path>
    <filename>threadlock_8hpp</filename>
    <includes id="alib_8hpp" name="alib.hpp" local="yes" imported="no">alib/alib.hpp</includes>
    <includes id="ownable_8hpp" name="ownable.hpp" local="yes" imported="no">alib/core/ownable.hpp</includes>
    <includes id="thread_8hpp" name="thread.hpp" local="yes" imported="no">thread.hpp</includes>
    <class kind="class">aworx::lib::threads::ThreadLock</class>
    <class kind="class">aworx::lib::threads::ThreadLockNR</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::threads</namespace>
  </compound>
  <compound kind="file">
    <name>ticks.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/time/</path>
    <filename>ticks_8hpp</filename>
    <includes id="assubstring_8hpp" name="assubstring.hpp" local="yes" imported="no">alib/strings/assubstring.hpp</includes>
    <class kind="class">aworx::lib::time::Ticks</class>
    <class kind="class">aworx::lib::time::TicksCalendarTime</class>
    <class kind="class">aworx::lib::time::TickSpan</class>
    <class kind="class">aworx::lib::time::TickWatch</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::time</namespace>
  </compound>
  <compound kind="file">
    <name>tokenizer.hpp</name>
    <path>/home/a/mnt/dev/A-Worx/ALox/src.cpp/alib/strings/</path>
    <filename>tokenizer_8hpp</filename>
    <includes id="assubstring_8hpp" name="assubstring.hpp" local="yes" imported="no">alib/strings/assubstring.hpp</includes>
    <class kind="class">aworx::lib::strings::Tokenizer</class>
    <namespace>aworx</namespace>
    <namespace>aworx::lib</namespace>
    <namespace>aworx::lib::strings</namespace>
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
      <type>static ALIB_API config::Configuration *</type>
      <name>Config</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a25de5cc112c10bba144bdd9d8d94b947</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API strings::AS</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classaworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a22148968a71666eb82718ab25d688adc</anchor>
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
    <name>aworx::lox::ALoxReportWriter</name>
    <filename>classaworx_1_1lox_1_1ALoxReportWriter.html</filename>
    <base>aworx::lib::ReportWriter</base>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ALoxReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a4b218cdb1f7e96e6cd3a851cca5f7c76</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Report</name>
      <anchorfile>classaworx_1_1lox_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a3ad9ad01d27945bd76295c63aa1f5457</anchor>
      <arglist>(const lib::Report::Message &amp;report)</arglist>
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
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a228ea55d3746ca88b1d2a8ff7a21db89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a3f90971fd506a7580d1e6a793b499b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a0b2519b873ae00d399a93a15287a3f4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 11 &gt;</type>
      <name>ANSI_BG_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa3abc0b726f85a364f822ef69fd2b708</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad1c457983ab837465edeeeae5570547a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4a9dbb44c99da33ff395eaf2189b2538</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4e21c418f58344c838bc684bc246df5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 11 &gt;</type>
      <name>ANSI_BG_LIGHT_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a64cb6a513058e627f3b2fd666cb43265</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a8cb95631c68faa8a320cb49d008a2717</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae5ae4580cc025f86c36c5e5348fd39b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a8d7d338fb11abdef4e4ba49f9d0e4a0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_LIGHT_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a3bdb0b456b85ffcf30d0d6ec14cb2145</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_LIGHT_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a900b1b7b627c765bdc3d8a5c6b729faa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ac61bddff15e41911f8a8975f17372a5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a18bb2d7b3569d5cab7e4d0ce469fcfda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>afb6e0a58a346c020c73d278816906ed8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_BG_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a48a55414be11b6bc9a61759ca36f9ccf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BG_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af56fd74ff93347b63cede3f70854faee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>adef3f7db058d0f8d1e51173ee3db06b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a62455f6a7eff9b0b7a8076a89791de6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 4 &gt;</type>
      <name>ANSI_BOLD</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a58d11cabdad7f79c70514bbee06f4c0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4f2d70b463cb45d22ab722d33037deff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 11 &gt;</type>
      <name>ANSI_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae94c1892d40b66679e7cf2accd37cbca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a65337713adf9ecf01a5c6d815428a223</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 4 &gt;</type>
      <name>ANSI_ITALICS</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab079336ce2b3ae0a8d6475e7f322ce11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab1957cfdacd73ceaea1c41c1571a16fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a70548855f970ad80c7fe347759d8edab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 11 &gt;</type>
      <name>ANSI_LIGHT_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa830905b6d622a7937d8f702855fdca2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a21ba33fdb33ec4a4de01a993ac82dbd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa83811feca16a7e27043c0ca3c689665</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4d505b745a16639d98880a199333b065</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_LIGHT_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae87517e5a7e11aad6ccedf1978d050e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_LIGHT_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae241b706dbc782f3797bd7b1ac656229</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad5563da237bf3ebaf08c8eabbdb0b884</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_RED</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa2e4b9a44d88fc20c5ece29ca7fbf08d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 4 &gt;</type>
      <name>ANSI_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a0bdf17a2b3d992dfa541b5a209b28bda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_STD_COL</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a68da27811f5429fd786eb526f54b7334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 4 &gt;</type>
      <name>ANSI_STD_STYLE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a8c3ca9ba1ef8b9a9b84e715a52bdc38c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 10 &gt;</type>
      <name>ANSI_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a99e7e0110f0f236d99ee79ce88627846</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 5 &gt;</type>
      <name>ANSI_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a59a88918be599b1cfeb36e9569d3b3df</anchor>
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
      <type>lib::strings::AS</type>
      <name>MsgPostfix</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aee2520fb19bd6ae2691a7dfcd7553acb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::strings::AS</type>
      <name>MsgPrefixError</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa60a6b63f1d879b616876c23686bfb30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::strings::AS</type>
      <name>MsgPrefixInfo</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a0ec0479f805ff3795e3e623fd89f4d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::strings::AS</type>
      <name>MsgPrefixVerbose</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a68902a4d4d4d29707e6c3b6bec8c573a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>lib::strings::AS</type>
      <name>MsgPrefixWarning</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a9ab2c6df9b3cd0cbd82ae35f57c93f8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>AnsiLogger</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aee038aeffe892d57b517d5d7173e5394</anchor>
      <arglist>(std::basic_ostream&lt; char &gt; *oStream, const String &amp;name=nullptr)</arglist>
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
      <name>doTextLog</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad15a0a8b8b8d232f97d9c0d9c28cea41</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, AString &amp;msg, int indent, core::CallerInfo *caller, int lineNumber)</arglist>
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
    <name>aworx::lib::strings::AS</name>
    <filename>classaworx_1_1lib_1_1strings_1_1AS.html</filename>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a5402671442b4da5648a08d10c7890252</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaa5b055c4215aaf5f0304fcafd38a487</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af2b51b9c35197a1fbfe6852e23b3d6e1</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aea2111582ae33626faa088ed5231c47a</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a5d5ce30daece7ec96d0b70ccc5d46002</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a6e891964a37680c01e21dedac6ffe670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a055d87b78f69c9d039b7e12ead7aa6b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaaf24e0ec4b4b51df542cd654230c3da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaef62c8761ddd1b95824fc57b1b277b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a484ba322b1d13f2e2c90066db81179ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaf9706f704337ae92062d7b68c8f33ea</anchor>
      <arglist>(int idx) const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa43766377944d0423a71478f1bbd61e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a78fb764265a5d096e56717a52754396d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af159245e9c28589bfa834b70e09a4b66</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ae9deb6d6fe080bd5a2609f82aefd2f5e</anchor>
      <arglist>(const AS &amp;needle, int pos, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a52c449ac2963a7e4d81fbfb524c242fb</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>abd78491bfb59955d08b84ec1592e059f</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a7d7b7811de40ddd94cdcb7db38ad6ef3</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a92ca8478c9d6e6b869c45606b2271616</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ae54e9b486041d6d7a4270f5e9ce94897</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength, int regionStart, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa8fbc18f968d64405a07b7683f963e63</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa0a55fc3dc13bd853fb456a3a28bdf53</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af8e62ebb3e88a81a5a87bae6d2af4ece</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ad3ba009196aa25cb1190328e7571780f</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a4903bdaa9803322caddc87c623646a90</anchor>
      <arglist>(char needle) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ab62c5abf6381ef65c72b97183fd64c8d</anchor>
      <arglist>(char needle, int regionStart) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a8ea4959c28189d614a7c883dae3787f5</anchor>
      <arglist>(char needle, int regionStart, int regionLength) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a6ff7c059a19d1003e1d150ab86d784f8</anchor>
      <arglist>(char needle, int startIndex=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a7b9b46e0de678476c2d8f4e280d9384b</anchor>
      <arglist>(const AS &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a03154d535fddb6d5bc5f6ffa9d1a578b</anchor>
      <arglist>(const AS &amp;needles, enums::Inclusion inclusion, int startIdx=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a666987a9d5ca0f77ced109391935931e</anchor>
      <arglist>(const AS &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ToWString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a73cfa0a1eb5f3c47cb633967c8b22333</anchor>
      <arglist>(wchar_t *dest, int destCapacity, int regionStart=0, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>afe13e5000dc11709e5da14d928f838b7</anchor>
      <arglist>(int &amp;regionStart, int &amp;regionLength) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>adae84acc92cd77a04f6aaf533643a33a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a9f59b34b1f25fe00023291b678246bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>vbuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ab060ffba71bd8a3d7067a38950b39a82</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a5402671442b4da5648a08d10c7890252</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaa5b055c4215aaf5f0304fcafd38a487</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af2b51b9c35197a1fbfe6852e23b3d6e1</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>AS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aea2111582ae33626faa088ed5231c47a</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>Buffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a5d5ce30daece7ec96d0b70ccc5d46002</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a6e891964a37680c01e21dedac6ffe670</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a055d87b78f69c9d039b7e12ead7aa6b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaaf24e0ec4b4b51df542cd654230c3da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaef62c8761ddd1b95824fc57b1b277b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a484ba322b1d13f2e2c90066db81179ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aaf9706f704337ae92062d7b68c8f33ea</anchor>
      <arglist>(int idx) const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa43766377944d0423a71478f1bbd61e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a78fb764265a5d096e56717a52754396d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af159245e9c28589bfa834b70e09a4b66</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ae9deb6d6fe080bd5a2609f82aefd2f5e</anchor>
      <arglist>(const AS &amp;needle, int pos, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a52c449ac2963a7e4d81fbfb524c242fb</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>abd78491bfb59955d08b84ec1592e059f</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a7d7b7811de40ddd94cdcb7db38ad6ef3</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a92ca8478c9d6e6b869c45606b2271616</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ae54e9b486041d6d7a4270f5e9ce94897</anchor>
      <arglist>(const AS &amp;needle, enums::Case sensitivity, int cmpRegionStart, int cmpRegionLength, int regionStart, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa8fbc18f968d64405a07b7683f963e63</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>aa0a55fc3dc13bd853fb456a3a28bdf53</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>af8e62ebb3e88a81a5a87bae6d2af4ece</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ad3ba009196aa25cb1190328e7571780f</anchor>
      <arglist>(const AS &amp;op) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a4903bdaa9803322caddc87c623646a90</anchor>
      <arglist>(char needle) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>ab62c5abf6381ef65c72b97183fd64c8d</anchor>
      <arglist>(char needle, int regionStart) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a8ea4959c28189d614a7c883dae3787f5</anchor>
      <arglist>(char needle, int regionStart, int regionLength) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a6ff7c059a19d1003e1d150ab86d784f8</anchor>
      <arglist>(char needle, int startIndex=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a7b9b46e0de678476c2d8f4e280d9384b</anchor>
      <arglist>(const AS &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a03154d535fddb6d5bc5f6ffa9d1a578b</anchor>
      <arglist>(const AS &amp;needles, enums::Inclusion inclusion, int startIdx=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAS</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a666987a9d5ca0f77ced109391935931e</anchor>
      <arglist>(const AS &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>ToWString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>a73cfa0a1eb5f3c47cb633967c8b22333</anchor>
      <arglist>(wchar_t *dest, int destCapacity, int regionStart=0, int regionLength=CString::MaxLen) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1AS.html</anchorfile>
      <anchor>afe13e5000dc11709e5da14d928f838b7</anchor>
      <arglist>(int &amp;regionStart, int &amp;regionLength) const </arglist>
    </member>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AS">CPP_STRINGS_AS_NULLSTATE</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1AS">CPP_STRINGS_AS_NC</docanchor>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ASAlloc</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a97b1b72fb6f255c9a081a871b80538d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7f5c06e907b7e0fca24144cb70bd5e69</anchor>
      <arglist>(int initialCapacity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a1e818b2fcc6331ba33670995afa7be58</anchor>
      <arglist>(const ASAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ae055bad54b390d44b6dfc55fa13ecb87</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aaef92d763ea45deca330c3d42588e0cb</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a792ffc4271041166863ca59b37870638</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aa0373d9928777ea07116cd3a746aab28</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a549cf66b555bccba8ae2cc368f8d9c46</anchor>
      <arglist>(const ASAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aa568cfea22455c8476509646e87ee157</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a0c8474e9c19a45b535f1b460aac3847b</anchor>
      <arglist>(char *extBuffer, int extBufferSize, int extLength=0, enums::Responsibility responsibility=enums::Responsibility::KeepWithSender)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GrowBufferAtLeastBy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a3fc410cc4cccd79e66c2f7491bce4bd3</anchor>
      <arglist>(int minimumGrowth)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad07c7e740f0be42afb0c1eda25361864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasInternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a799c4f153843f7dbba7fe16cf9bfc457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>VBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a39184b93936d495a501cbea28e12495e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ab2cf143ab3c019c18b6ada0ea87a6370</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a8068d1bbfd60c6cb178bdc0b2084ab9b</anchor>
      <arglist>(int op)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a222ec65ddfcb63da6f777a0a10f97dea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7d1b2ede295754fcb3ea39e2681a6de6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>InsertAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7b300128fd0109d7ed1512027695b03b</anchor>
      <arglist>(const AS &amp;src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>InsertChars</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afac5206bb2d94e4ddf323c94e3b1ae6b</anchor>
      <arglist>(char c, int qty, int pos=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a39fd9f532675b3fc95bac49859e1304d</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ReplaceRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4c676ecc472793b6c162b55d583007ae</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Delete</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a56823a21c21992ad292b6fa55396307a</anchor>
      <arglist>(int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>DeleteStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ac58f5b2c1fa78ad64e98ece237fb2d01</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>DeleteEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a206da490c31262327e08d08dab328dca</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ASAlloc &amp;</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ab802b141f81d833ebdfcc2491f0ad736</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ASAlloc &amp;</type>
      <name>TrimAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a987b1b4d5170a61db5ebf9fcfcd29284</anchor>
      <arglist>(int index, const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a47c97dc2b945ad9bd6b8f74321a5b51c</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ae7690c97ce6d3329a1eb4e546a46d36f</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Append</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>abd6181d468b63542ae6dcf794263dda7</anchor>
      <arglist>(const char *src, int srcLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4dbe5fba1e5c5ed69d12d57b3eb49ef7</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aefd4424048be8d9fce5bef95d3d0eb37</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad9033b6f935b840edb855ecba2ec3579</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ac2a249cf12c2fb2697e4cb53d04a7f28</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>NewLine</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad4ce5f1548943a9fc77769e7161998b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a9ffcb95f7e39cfd53c51257d0a14357e</anchor>
      <arglist>(const ASTerminatable &amp;needle, const AS &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a826d66b9ce28523efb39eb57babfbd38</anchor>
      <arglist>(const ASTerminatable &amp;needle, const AS &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ToUpper</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aca6738fe7f8559076ce9a939515cf865</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ToLower</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afaa6e9f80da8f54ffa1e29858785a703</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>debugLastAllocRequest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7ebc042256408173ee3c3904906a0e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>debugBufferWithMagicBytePadding</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aa155a96ba168342ab2ae8067d96e373e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>adbe66a087ac3fd4a5b0566f64ca2d12b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ReplaceExternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ae6e756e6f5ccc142f9fc3ceb6ba18cf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_dbgCheck</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a8747c38ac0ef9f863ede544d51ff6721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>constexpr</type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a15ffb1c90b1e88776456b0518f2459e2</anchor>
      <arglist>(char *extBuffer, int extBufferSize)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a97b1b72fb6f255c9a081a871b80538d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7f5c06e907b7e0fca24144cb70bd5e69</anchor>
      <arglist>(int initialCapacity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a1e818b2fcc6331ba33670995afa7be58</anchor>
      <arglist>(const ASAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ae055bad54b390d44b6dfc55fa13ecb87</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aaef92d763ea45deca330c3d42588e0cb</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a792ffc4271041166863ca59b37870638</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ASAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aa0373d9928777ea07116cd3a746aab28</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a549cf66b555bccba8ae2cc368f8d9c46</anchor>
      <arglist>(const ASAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aa568cfea22455c8476509646e87ee157</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API void</type>
      <name>SetBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a0c8474e9c19a45b535f1b460aac3847b</anchor>
      <arglist>(char *extBuffer, int extBufferSize, int extLength=0, enums::Responsibility responsibility=enums::Responsibility::KeepWithSender)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GrowBufferAtLeastBy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a3fc410cc4cccd79e66c2f7491bce4bd3</anchor>
      <arglist>(int minimumGrowth)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad07c7e740f0be42afb0c1eda25361864</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasInternalBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a799c4f153843f7dbba7fe16cf9bfc457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>VBuffer</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a39184b93936d495a501cbea28e12495e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ab2cf143ab3c019c18b6ada0ea87a6370</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a8068d1bbfd60c6cb178bdc0b2084ab9b</anchor>
      <arglist>(int op)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a222ec65ddfcb63da6f777a0a10f97dea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7d1b2ede295754fcb3ea39e2681a6de6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>InsertAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a7b300128fd0109d7ed1512027695b03b</anchor>
      <arglist>(const AS &amp;src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>InsertChars</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afac5206bb2d94e4ddf323c94e3b1ae6b</anchor>
      <arglist>(char c, int qty, int pos=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a39fd9f532675b3fc95bac49859e1304d</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ReplaceRegion</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4c676ecc472793b6c162b55d583007ae</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Delete</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a56823a21c21992ad292b6fa55396307a</anchor>
      <arglist>(int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>DeleteStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ac58f5b2c1fa78ad64e98ece237fb2d01</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>DeleteEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a206da490c31262327e08d08dab328dca</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ASAlloc &amp;</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ab802b141f81d833ebdfcc2491f0ad736</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ASAlloc &amp;</type>
      <name>TrimAt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a987b1b4d5170a61db5ebf9fcfcd29284</anchor>
      <arglist>(int index, const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a47c97dc2b945ad9bd6b8f74321a5b51c</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ae7690c97ce6d3329a1eb4e546a46d36f</anchor>
      <arglist>(const ASTerminatable &amp;trimChars=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>Append</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>abd6181d468b63542ae6dcf794263dda7</anchor>
      <arglist>(const char *src, int srcLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Apply</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a4dbe5fba1e5c5ed69d12d57b3eb49ef7</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aefd4424048be8d9fce5bef95d3d0eb37</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>_</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad9033b6f935b840edb855ecba2ec3579</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ac2a249cf12c2fb2697e4cb53d04a7f28</anchor>
      <arglist>(const T &amp;op)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>NewLine</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>ad4ce5f1548943a9fc77769e7161998b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a9ffcb95f7e39cfd53c51257d0a14357e</anchor>
      <arglist>(const ASTerminatable &amp;needle, const AS &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>a826d66b9ce28523efb39eb57babfbd38</anchor>
      <arglist>(const ASTerminatable &amp;needle, const AS &amp;replacement, int startIdx=0, int maxReplacements=CString::MaxLen, enums::Case sensitivity=enums::Case::Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ToUpper</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>aca6738fe7f8559076ce9a939515cf865</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASAlloc &amp;</type>
      <name>ToLower</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASAlloc.html</anchorfile>
      <anchor>afaa6e9f80da8f54ffa1e29858785a703</anchor>
      <arglist>(int regionStart=0, int regionLength=CString::MaxLen)</arglist>
    </member>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1ASAlloc">alib_namespace_strings_astring_move</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1ASAlloc">alib_namespace_strings_astring_write_access</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1ASAlloc">alib_namespace_strings_astring_nullable</docanchor>
    <docanchor file="classaworx_1_1lib_1_1strings_1_1ASAlloc">alib_namespace_strings_astring_application_vs_interface</docanchor>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ASLiteral</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <templarg>TLength</templarg>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASLiteral&lt; 10 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASLiteral&lt; 11 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASLiteral&lt; 3 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASLiteral&lt; 4 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASLiteral&lt; 5 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</filename>
    <base>aworx::lib::strings::ASTerminatable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>abe54b80eca850835aac62649d48de03c</anchor>
      <arglist>(char *dest, const char *src)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASLiteral</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a42714b027a5bd6dcea974bfa400babbb</anchor>
      <arglist>(const char(&amp;src)[TLength+1])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Copy</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASLiteral.html</anchorfile>
      <anchor>a9d3a01b96278e25b770eabce9295bdf9</anchor>
      <arglist>(char *dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ASPreAlloc</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</filename>
    <templarg>TCapacity</templarg>
    <base>aworx::lib::strings::ASAlloc</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>acdf29f7b25332d4e9616e0ed9ceab40f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>abe4fbd5272d2c7daa4aebd2eec92ab6e</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>afeb557df77f0ba041e5a1d0a14f0e97e</anchor>
      <arglist>(ASPreAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a56f001ca865972bac28c3d92e307a3b3</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a24629b026f42e1f7381df01cc9461e3d</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>ad70f1ea6f2bda34e66ad1edd536ad9d3</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASPreAlloc&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a54182d58dc2f7b29779d9441a07df3c7</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASPreAlloc&lt; 16 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</filename>
    <base>aworx::lib::strings::ASAlloc</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>acdf29f7b25332d4e9616e0ed9ceab40f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>abe4fbd5272d2c7daa4aebd2eec92ab6e</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>afeb557df77f0ba041e5a1d0a14f0e97e</anchor>
      <arglist>(ASPreAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a56f001ca865972bac28c3d92e307a3b3</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a24629b026f42e1f7381df01cc9461e3d</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>ad70f1ea6f2bda34e66ad1edd536ad9d3</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASPreAlloc&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a54182d58dc2f7b29779d9441a07df3c7</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASPreAlloc&lt; 256 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</filename>
    <base>aworx::lib::strings::ASAlloc</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>acdf29f7b25332d4e9616e0ed9ceab40f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>abe4fbd5272d2c7daa4aebd2eec92ab6e</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>afeb557df77f0ba041e5a1d0a14f0e97e</anchor>
      <arglist>(ASPreAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a56f001ca865972bac28c3d92e307a3b3</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a24629b026f42e1f7381df01cc9461e3d</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>ad70f1ea6f2bda34e66ad1edd536ad9d3</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASPreAlloc&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a54182d58dc2f7b29779d9441a07df3c7</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASPreAlloc&lt; 32 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</filename>
    <base>aworx::lib::strings::ASAlloc</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>acdf29f7b25332d4e9616e0ed9ceab40f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>abe4fbd5272d2c7daa4aebd2eec92ab6e</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>afeb557df77f0ba041e5a1d0a14f0e97e</anchor>
      <arglist>(ASPreAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a56f001ca865972bac28c3d92e307a3b3</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a24629b026f42e1f7381df01cc9461e3d</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>ad70f1ea6f2bda34e66ad1edd536ad9d3</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASPreAlloc&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a54182d58dc2f7b29779d9441a07df3c7</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ASPreAlloc&lt; 64 &gt;</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</filename>
    <base>aworx::lib::strings::ASAlloc</base>
    <member kind="function">
      <type>constexpr</type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>acdf29f7b25332d4e9616e0ed9ceab40f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>abe4fbd5272d2c7daa4aebd2eec92ab6e</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>afeb557df77f0ba041e5a1d0a14f0e97e</anchor>
      <arglist>(ASPreAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a56f001ca865972bac28c3d92e307a3b3</anchor>
      <arglist>(ASAlloc &amp;&amp;move) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a24629b026f42e1f7381df01cc9461e3d</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASPreAlloc</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>ad70f1ea6f2bda34e66ad1edd536ad9d3</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASPreAlloc&lt; TCapacity &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a54182d58dc2f7b29779d9441a07df3c7</anchor>
      <arglist>(const ASPreAlloc &amp;copy)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>preAllocBuf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASPreAlloc.html</anchorfile>
      <anchor>a8b9dbb4b7dcd6efcb8275318c285f811</anchor>
      <arglist>[TCapacity]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ASSubstring</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</filename>
    <base>aworx::lib::strings::AS</base>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a3a05680adff595b52de0cba6de885d17</anchor>
      <arglist>(const AS &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aeac7a062b5d87f2497595e06c95e27a6</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a7539a7f4305a50fd17cb17ac57719b19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>af38ff4b91142835d3767c7835d4163cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a40b61c916665860d338a376a98da7040</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aab582852f5c993337387022aa4dbff32</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a254cb22cc3955f3f5895ad3c287e3573</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aaf59accd324c73fe307fbf81e1c35242</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aefbbdae5be3973db831fc14f049902da</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a15088f26d020c580ed62e3b842e9f7fb</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a94a31afdd787fddb34efd2bf97601987</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a1269e3abe8d95272e9e9c3e0aa7f7905</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a52e8d95769240c639d29ee1bdbfa0a0d</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a6091a0b056bb7a1e9ae80c04f2a3d417</anchor>
      <arglist>(const AS &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a91914ee3ff39f6b2d2196243a78d3172</anchor>
      <arglist>(const AS &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a56e71c29f72b9ec95c60a4b47eb45711</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a3f589b8c9f5e4a6deb6f29804f210e12</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a6f37923c216a4c3c7c6d4cf9c989e97a</anchor>
      <arglist>(int32_t &amp;result, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>ad08cf5147354b5a18ab1de0b33520cac</anchor>
      <arglist>(int64_t &amp;result, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>adae22145224d9c573e1ffe0db732e2c7</anchor>
      <arglist>(double &amp;result, strings::NumberFormat *numberFormat=nullptr, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Split</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a9ba2f83672cd35b574cba0788a923f36</anchor>
      <arglist>(int position, Substring &amp;target, int separatorWidth=0)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a3a05680adff595b52de0cba6de885d17</anchor>
      <arglist>(const AS &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aeac7a062b5d87f2497595e06c95e27a6</anchor>
      <arglist>(const AS &amp;src, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>SetNull</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a7539a7f4305a50fd17cb17ac57719b19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>Clear</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>af38ff4b91142835d3767c7835d4163cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a0c14574ea5ef859e15b51f288c40f5da</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a40b61c916665860d338a376a98da7040</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aab582852f5c993337387022aa4dbff32</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Trim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a254cb22cc3955f3f5895ad3c287e3573</anchor>
      <arglist>(const ASTerminatable &amp;whiteSpaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aaf59accd324c73fe307fbf81e1c35242</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>aefbbdae5be3973db831fc14f049902da</anchor>
      <arglist>(enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a15088f26d020c580ed62e3b842e9f7fb</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a94a31afdd787fddb34efd2bf97601987</anchor>
      <arglist>(int regionLength, Substring *target=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a1269e3abe8d95272e9e9c3e0aa7f7905</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a52e8d95769240c639d29ee1bdbfa0a0d</anchor>
      <arglist>(int regionLength, AString &amp;target, int separatorWidth=0, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a6091a0b056bb7a1e9ae80c04f2a3d417</anchor>
      <arglist>(const AS &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a91914ee3ff39f6b2d2196243a78d3172</anchor>
      <arglist>(const AS &amp;consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a56e71c29f72b9ec95c60a4b47eb45711</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a3f589b8c9f5e4a6deb6f29804f210e12</anchor>
      <arglist>(char consumable, enums::Whitespaces trimBeforeConsume=enums::Whitespaces::Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a6f37923c216a4c3c7c6d4cf9c989e97a</anchor>
      <arglist>(int32_t &amp;result, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>ad08cf5147354b5a18ab1de0b33520cac</anchor>
      <arglist>(int64_t &amp;result, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>adae22145224d9c573e1ffe0db732e2c7</anchor>
      <arglist>(double &amp;result, strings::NumberFormat *numberFormat=nullptr, const ASTerminatable &amp;whitespaces=DefaultWhitespaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring &amp;</type>
      <name>Split</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASSubstring.html</anchorfile>
      <anchor>a9ba2f83672cd35b574cba0788a923f36</anchor>
      <arglist>(int position, Substring &amp;target, int separatorWidth=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::ASTerminatable</name>
    <filename>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</filename>
    <base>aworx::lib::strings::AS</base>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Terminate</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a7a1430f618f869550a47b5f078ce6860</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a9d41bf2bd3a1ec7f25f1b6f78252387e</anchor>
      <arglist>(const ASTerminatable &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>aaadf331bd2d7c97de55e27a5b84e6550</anchor>
      <arglist>(const ASTerminatable &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>ab75164b28454722bdf29710c208f0736</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToCString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>af283db5a533654cb8a0fa2e110d4b20f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>ToLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>adc47f802bf6ec7b8c4597f30d9a13a77</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>ToInt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a5d832d40cd653f563ee1ab150dc32bf2</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>ToFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a1309b615228fe47992cf402861185cad</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, strings::NumberFormat *numberFormat=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>debugIsTerminated</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>ac3615a067cb671e6b0cac6dbb26c9f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_dbgCheck</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a8747c38ac0ef9f863ede544d51ff6721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>ASTerminatable</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a192612506aa2768adb24bc6533a1f074</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ASTerminatable</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a1604dfffac2fcb1e478b4125ee8526b0</anchor>
      <arglist>(const T &amp;src)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>constexpr</type>
      <name>ASTerminatable</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>af3039222d341451d8e28d7b7eed03b35</anchor>
      <arglist>(const char *buffer, int contentLength)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>operator[]</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a0b3b9871d2fc6522c1f2aedf67b8b1c2</anchor>
      <arglist>(int op) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Terminate</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a7a1430f618f869550a47b5f078ce6860</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a9d41bf2bd3a1ec7f25f1b6f78252387e</anchor>
      <arglist>(const ASTerminatable &amp;needle, int startIdx=0, enums::Case sensitivity=enums::Case::Sensitive) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>aaadf331bd2d7c97de55e27a5b84e6550</anchor>
      <arglist>(const ASTerminatable &amp;needles, enums::Inclusion inclusion, int startIdx=0) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>ab75164b28454722bdf29710c208f0736</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToCString</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>af283db5a533654cb8a0fa2e110d4b20f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>ToLong</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>adc47f802bf6ec7b8c4597f30d9a13a77</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>ToInt</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a5d832d40cd653f563ee1ab150dc32bf2</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
    <member kind="function">
      <type>ALIB_API double</type>
      <name>ToFloat</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1ASTerminatable.html</anchorfile>
      <anchor>a1309b615228fe47992cf402861185cad</anchor>
      <arglist>(int startIdx=0, int *newIdx=nullptr, strings::NumberFormat *numberFormat=nullptr, const ASTerminatable *whitespaces=nullptr) const </arglist>
    </member>
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
    <name>aworx::lox::core::CallerInfo</name>
    <filename>classaworx_1_1lox_1_1core_1_1CallerInfo.html</filename>
    <member kind="typedef">
      <type>std::map&lt; int, String32 &gt;</type>
      <name>ThreadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a99735dc703a3e0c252ea69a22c1687d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>LineNumber</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>abc72cc909922c33908e48159b106efa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>MethodName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a54e2b41594e56ac5e473240774a85793</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>SourceFileName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a41b14aa6b4e69f96ee0648887a950d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>aworx::lib::time::Ticks</type>
      <name>TimeStamp</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>abce612133a1fd5426e5ac17ae0170ee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>CallerInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ac8a59b2a7246e69fc9400468dcf39f3c</anchor>
      <arglist>(const std::map&lt; int, String32 &gt; &amp;threadDictionary)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ab91dc804181f48b0b445ac1299c36c05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>AcquireAndSet</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a2b0ee3e889c28bcbefb239fe26ec4faa</anchor>
      <arglist>(const TString &amp;source, int lineNumber, const TString &amp;method)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API const aworx::String &amp;</type>
      <name>getThreadNameAndID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a073a52e5c8441631bb198ee3eea5a597</anchor>
      <arglist>(int *id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a94c93747c8daa99d65c2a04c6be0748c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>lazyFlagThreadNameAndID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a92cdf9ddc997d5c1e065702682511453</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>recursionCounter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>aaaa3b2279f13f2258c4db77e7949e123</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const ThreadDictionary &amp;</type>
      <name>threadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ab89d14dc857db74727211f5fcf3c138f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>threadID</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a88110d06c2b8b5584d31b5be3f13af46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>threadName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ab0235bb40987a8310ebd7e8500b96975</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>CallerInfo &amp;</type>
      <name>operator=</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a33aa51e818c9102464c331c763bdb02b</anchor>
      <arglist>(const CallerInfo &amp;op)</arglist>
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
      <type>std::vector&lt; strings::AS &gt;</type>
      <name>TrueValues</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a2f22d43d853eb3c7cae513a002372dc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALIB_API</type>
      <name>Configuration</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a4cc6600e815dce6891f90a80c9791798</anchor>
      <arglist>(enums::Inclusion environment=enums::Inclusion::Include, int argc=0, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALIB_API</type>
      <name>~Configuration</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a09dcd47e8d29f55ef5515d6413d42d16</anchor>
      <arglist>()</arglist>
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
      <name>PrioAndPlugin</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a358c0cf54658aebd8827ac51f402dc4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; PrioAndPlugin &gt;</type>
      <name>plugins</name>
      <anchorfile>classaworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ad6371e09317e11b0cabb24f9adc0290a</anchor>
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
      <name>doLogSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>ac69f7301749f95053732100e17a76fb4</anchor>
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
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>Report</name>
      <anchorfile>classaworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>a4e22fecd02d1d3b1b079178c29c54d90</anchor>
      <arglist>(const Report::Message &amp;report)</arglist>
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
    <member kind="variable" static="yes">
      <type>static TString</type>
      <name>DomainSeparatorChars</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>afbf227c46394352a0762ecc8a5503d89</anchor>
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
      <type>std::vector&lt; Domain * &gt;</type>
      <name>SubDomains</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a45607390dc4f3ea0f79c1ee1a08a777b</anchor>
      <arglist></arglist>
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
      <type>ALOX_API Domain *</type>
      <name>Find</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a81aa542aff07e91462b56a72c2afaede</anchor>
      <arglist>(Substring domainPath, bool *wasCreated=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API Log::DomainLevel</type>
      <name>GetLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a60670380e12310a09a4c36802ba4330c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API bool</type>
      <name>IsActive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a9a7f61a789b52e689f56f0f53ceb449b</anchor>
      <arglist>(Log::Level level)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetLevel</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a24b654c80579e9df23400b6c618f31ed</anchor>
      <arglist>(Log::DomainLevel domainLevel, lib::enums::Propagation propagation=lib::enums::Propagation::ToDescendants)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Log::DomainLevel</type>
      <name>level</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a7dc431275952481e05cbb37a1115fafb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Domain *</type>
      <name>findRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a5fe9c125f72057468ddd766592c08be7</anchor>
      <arglist>(Substring &amp;domainPath, bool *wasCreated=nullptr)</arglist>
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
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a591c0a62a4afe03fd5accee26e649ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a6bd2d030367376b20863d01215c2cf01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a73a7f26c639d550312e047ae416d6aa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a325853f29ab387505994e59d9376a8e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a411f5103413bcca82db8f269080d17cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a787b53262b8939ec34a9011c68be37e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_RED</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a468cb9803ff3822c118ffcb6b68e21e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a371f97707f9e577d213213725ff73293</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a3d71605aad1cb7fed93493182f2e503e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BG_YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>abf8011260cc25ad42e7f6c280c36f69a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BLACK</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aa8a50fad97c27dfc3fead77bd5f84d49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BLUE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ac3cfcc85216df0eee68cdb8d92a6ec0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>BOLD</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a2b923090984551d8c635ca4dfb1b9de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>CYAN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a3ec185162d338c4b9549512b7bf4d490</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>EOMETA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ac4bc405fc7ec1ec27182890373adef87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>FG_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a38657b656a956ed9223ab85b3e00937b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>GRAY</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>abce02f65e33c47f28a6263135b37a44d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>GREEN</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a9d4265677c04fce1d8e8226d4a36365b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>ITALICS</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ac3756a927764ac88ff640c5e594ad58e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>MAGENTA</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ae21ea2db9dd052738bd45708fae2eb1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>RED</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a066674f791cca67278a52c5207d018bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aaf09659f7ae87ae1bb5da7b4bc4e7d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>STYLE_RESET</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>af76abaa902cea3372f5981d2dbb5d306</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>TAB</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a14458bc469a53d8aca7f037c88481aa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>URL_END</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aa0defb57a4d3f5e1d3460d2897c31785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>URL_START</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a4031072e77490d36e39b1adb705cb664</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>WHITE</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ab7e7fd9c108468901218fb49e7246e7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API StringLiteral&lt; 3 &gt;</type>
      <name>YELLOW</name>
      <anchorfile>classaworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>afd8a416942ff072d6ae39bf2b3183144</anchor>
      <arglist></arglist>
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
      <type>const AS &amp;</type>
      <name>contents</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Format_1_1Field.html</anchorfile>
      <anchor>a26d8094f91e9b7c975a330358ce018c1</anchor>
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
      <anchor>abc7b2006960dc53fa75d215f1b9bc9ef</anchor>
      <arglist>(const AS &amp;contents, int width, enums::Alignment alignment=enums::Alignment::Right, char padChar= &apos; &apos;)</arglist>
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
      <anchor>ab48e15d1063142c30ad2e417a4d23e06</anchor>
      <arglist>(strings::ASSubstring &amp;value, AString &amp;target)</arglist>
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
    <name>aworx::lib::strings::IsApplicable&lt; const std::string &amp; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsApplicable_3_01const_01std_1_1string_01_6_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable&lt; ASAlloc &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable_3_01ASAlloc_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::IsTerminatable&lt; ASPreAlloc&lt; TCapacity &gt; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1IsTerminatable_3_01ASPreAlloc_3_01TCapacity_01_4_01_4.html</filename>
    <templarg>TCapacity</templarg>
  </compound>
  <compound kind="class">
    <name>aworx::lox::Log</name>
    <filename>classaworx_1_1lox_1_1Log.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>DomainLevel</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170f</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fa5ef0c737746fae2ca90e66c39333f8f6">Errors</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fac97dda1f78d8fbb5a4f489ab1b51ff4d">WarningsAndErrors</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fa377a1a5cb4724b1fb5993b36459d6570">InfoWarningsAndErrors</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fab1c94ca2fbc3e78fc30069c8d0f01680">All</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fac49484faf79e2388b580e49444d6ac11">Inherit</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5ad4a9fa383ab700c5bdd6f31cf7df0faf">Verbose</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a4059b0251f66a18cb56f544728796875">Info</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a0eaadb4fcb48a0a0ed7bc9868be9fbaa">Warning</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Scope</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6</anchor>
      <arglist></arglist>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6aad9c9150641994c9937a1bce42884a31">SourceFile</enumvalue>
      <enumvalue file="classaworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6a4c3880bb027f159e801041b1021e88e8">Method</enumvalue>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const uint32_t</type>
      <name>ALibCompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ad73d0d3096f8469b1e8ba2f17fe9bb69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API std::pair&lt; const char *, uint32_t &gt;</type>
      <name>CompilationFlagMeanings</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a94e348b81d5b26163c0eb1efc4c0fd69</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const uint32_t</type>
      <name>CompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abbfe1aff131ede76ea8f259b2282b26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const String &amp;</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>addc024f6c6dbb007e99c6becdc4d3649</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALOX_API aworx::lox::core::textlogger::TextLogger *</type>
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
      <type>static ALOX_API Lox *</type>
      <name>lox</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a4bf33caa00cd3346344e5bf2e3b2bc54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static lib::ReportWriter *</type>
      <name>OrigReportWriter</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a0ee0c4383336dd6eec6044a1ca911915</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALOX_API Lox *</type>
      <name>relLox</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a00d43d75f98c8ff6cce6045ebe1557c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Revision</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9c8cddb79a23b8e57370078da95de8ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALIB_API const int</type>
      <name>Version</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8d88b5f159f3cd597cdd92f942340024</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>AddDebugLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af6d116f9dcb6f677378a8f4b58edb94c</anchor>
      <arglist>(Lox *lox, bool replaceDefaultReportWriter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>Init</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aa42e90660a7c751cd1dfd28942375f54</anchor>
      <arglist>(lib::enums::Inclusion environment=lib::enums::Inclusion::Include, int argc=0, void **argv=nullptr, bool wArgs=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>RemoveDebugLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6d4775cac3c6e185f454a5e1fbf9325a</anchor>
      <arglist>(Lox *lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALOX_API void</type>
      <name>TerminationCleanUp</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a2a0bcae1f7341255492ebc90deab5f01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const String</type>
      <name>ToString</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ac6815b6fdee40b577e3a7792f0c57324</anchor>
      <arglist>(DomainLevel level)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const String</type>
      <name>ToString</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a16204b7ac39117faa6738b685073cc1a</anchor>
      <arglist>(Level level)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const String</type>
      <name>ToString</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ae599037403c21665853084b9d88d33e6</anchor>
      <arglist>(Scope scope)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ALIB_API bool</type>
      <name>VerifyCompilationFlags</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6924a062cb4b36d1cffa928296525365</anchor>
      <arglist>(uint32_t flags)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALOX_API Lox</type>
      <name>defaultDbgLox</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af8bae13abcdbf2f4a28f39d9a20368a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALOX_API Lox</type>
      <name>defaultRelLox</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a0bfc5687004f6adc827f13c7592215bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALOX_API bool</type>
      <name>isInitialized</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a1fdc2bf5595c2e64dc06d987769834eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALOX_API void</type>
      <name>checkLibraryVersions</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a2dbf1714a573a9e1d90bd5a68c644917</anchor>
      <arglist>(int alibVersion=ALIB_VERSION_VERYFIER, int aloxVersion=ALIB_VERSION_VERYFIER, uint32_t flagsALib=ALIB_COMPATIBILITY_VERYFIER, uint32_t flagsALox=ALOX_COMPATIBILITY_VERYFIER)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALOX_API bool</type>
      <name>initInternal</name>
      <anchorfile>classaworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aadef22675beaaa96fcf43af0f7350945</anchor>
      <arglist>(lib::enums::Inclusion environment, int argc, void **argv, bool wArgs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::Logger</name>
    <filename>classaworx_1_1lox_1_1core_1_1Logger.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>CntLogs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a644d0a2cf3bb9b3a68b5159b89216f08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsDisabled</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>abada4ef55f947626e50d53b5cb8a31cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>Name</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ab3c68b8a64bf47454f94bde4ebb6de0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Domain</type>
      <name>RootDomain</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a8c3be195312b12e47828c3b647f8add1</anchor>
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
    <member kind="variable">
      <type>String32</type>
      <name>TypeName</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a5a295fb1c491a3a0bc84efbe8ebe28c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~Logger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a0d77f27eb95c246d555904aaf08018eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API bool</type>
      <name>Line</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a87a33ab7f4020fa9b515090948087801</anchor>
      <arglist>(const AString &amp;domain, Log::Level level, const void *msgObject, int msgType, int indent, CallerInfo *caller)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ac449bb9b0f280d33286db8463f48e287</anchor>
      <arglist>(const TString &amp;domain, Log::DomainLevel domainLevel, lib::enums::Propagation propagation=lib::enums::Propagation::ToDescendants)</arglist>
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
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>doLog</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ad424401ee9cc91177dda1c0778790ea5</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, const void *msgObject, int msgType, int indent, CallerInfo *caller)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::Lox</name>
    <filename>classaworx_1_1lox_1_1Lox.html</filename>
    <base>aworx::lib::threads::ThreadLock</base>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ErrIfNoDefaultDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aaaef02f6a1dff7969d2fa1e39a7b9755</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>InternalDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9bccc0d3300ad844c867a263e6e3e8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TString</type>
      <name>NullDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1b898840bc3c6004def2f687caa4acb9</anchor>
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
      <type></type>
      <name>Lox</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>adeecd070b47db04dfac1b186f99a95d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API</type>
      <name>~Lox</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8df22829cdb5cad1db7f72bb0b068d5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>affeac79a4a864890b2e1862d388bfad3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AcquireAndSetCI</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a56aa4e48e2328746639c63a9b9af2fb9</anchor>
      <arglist>(const TString &amp;file, int line, const TString &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>AddLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>abd300988900048304b481573883406d8</anchor>
      <arglist>(core::Logger *logger)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3499398cbeb8d1a26f5eea3399514111</anchor>
      <arglist>(bool cond, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a25747e65a604090e40b91fccea0023d0</anchor>
      <arglist>(bool cond, const TString &amp;domain, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4ede60be7decfe6038d3a7e24798967d</anchor>
      <arglist>(bool cond, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aea4c583aaf831207900eed3bba5b4d6e</anchor>
      <arglist>(bool cond, const TString &amp;domain, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3dab1b8384cf49f26424e34436c5b744</anchor>
      <arglist>(const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab5b4330eb329275e5b8a47988ca1dd6f</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a019fa45a1dcc075e3719d74ecb6c55f5</anchor>
      <arglist>(void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afb3563a6edb68e3726b76510179e3853</anchor>
      <arglist>(const TString &amp;domain, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API core::Logger *</type>
      <name>GetLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a829395dc991b4aed5a09ef5aa77e3e12</anchor>
      <arglist>(const String &amp;loggerName)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void *</type>
      <name>GetMarker</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5c0a8913fff2143fb1eb6d2b86098933</anchor>
      <arglist>(Log::Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad52f89dd7d537db1a1bf70eb5b1c9ae0</anchor>
      <arglist>(const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af38603caa1098e01c8fb24237ad6827d</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae5d7977c90da70a522134f43afa647b4</anchor>
      <arglist>(void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a39e67f909bd052a39ceeb0a198f5f2cc</anchor>
      <arglist>(const TString &amp;domain, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Line</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a36309b70ccb095ea31e0a428111a4d2a</anchor>
      <arglist>(bool doLog, const TString &amp;domain, Log::Level level, const void *msgObject, int msgType, int indent=0, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa51041fd6646711c6d13f84d7bc9259f</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, const void *msgObject, int msgType, int indent=0, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aeb594bf91110eb9584dd472d2e15c21a</anchor>
      <arglist>(Log::Level level, const void *msgObject, int msgType, int indent=0, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>LogConfig</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5ecb5f8a2a72316617ea48e6bcf695d4</anchor>
      <arglist>(const String &amp;domain, Log::Level level, const String &amp;headLine, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>MapThreadName</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3911541857ea84938dede341ceb64ddd</anchor>
      <arglist>(const String &amp;threadName, int id=0)</arglist>
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
      <anchor>a9d6901dfd4853b8287bede398b6d4c86</anchor>
      <arglist>(const core::Logger *logger)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API int</type>
      <name>RemoveLoggers</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a394e92d4075de2a50b6fc0b5658500ac</anchor>
      <arglist>(const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>Reset</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0676d6fc6dd68d7c2c0ca49ab8abe630</anchor>
      <arglist>(const TString &amp;domain, Log::Scope scope=Log::Scope::None)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1812ac9849649157cf391d03e4af86cb</anchor>
      <arglist>(const TString &amp;domain, Log::DomainLevel domainLevel, const String &amp;loggerFilter=nullptr, lib::enums::Propagation propagation=lib::enums::Propagation::ToDescendants)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4cf6388b847550f8b6b318b55efa35ee</anchor>
      <arglist>(const TString &amp;domain, Log::Scope scope, Log::DomainLevel domainLevel, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8546fd2c39a9ee72596df9a57cd82083</anchor>
      <arglist>(const TString &amp;domain, Log::DomainLevel domainLevel, Log::Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetLogger</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af59433acecdc611018aad891528e1efa</anchor>
      <arglist>(lib::enums::Switch newState, const String &amp;loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetMarker</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a848fdd8b93afc2b2c89d526d4d128e3e</anchor>
      <arglist>(void *marker, Log::Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae31d4b72ea1bc7513fd341b6dc99053f</anchor>
      <arglist>(lib::time::Ticks startTime=lib::time::Ticks(0), const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac47e41fa26b09d46e609ad195632b6a4</anchor>
      <arglist>(time_t startTime, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>ALOX_API void</type>
      <name>SetStartTime</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afc65c39a68e3170106a30e13b4006c98</anchor>
      <arglist>(LPFILETIME startTime, const String &amp;loggerFilter=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af6093dbce9dbbeffcf76362b4abacac8</anchor>
      <arglist>(const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a19d5d602e061c3bffafbe24730ed277c</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7de4de50bb74004025ca67dc8ad0bcd4</anchor>
      <arglist>(void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a40ea941f26bcba6258584ccde996411f</anchor>
      <arglist>(const TString &amp;domain, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab00a8f8c882ff229ed5ff26ab1f5633d</anchor>
      <arglist>(const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af5b1f5ef4329394a8f3d25d701ca2fe3</anchor>
      <arglist>(const TString &amp;domain, const TString &amp;msg, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac9945acd645dbaa0d59128d3c8b4fb94</anchor>
      <arglist>(void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae7e139392e7c429aff8f1045e302792d</anchor>
      <arglist>(const TString &amp;domain, void *msgObject, int msgType, int indent=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::CallerInfo</type>
      <name>callerInfo</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3f03380b7450165d47b292ccd8ad86ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; AString, AString &gt;</type>
      <name>defaultDomains</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1d0d0993e720ea4eaadcc4e1debd8f7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; core::Logger * &gt;</type>
      <name>loggers</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8af08b7d47cdaedadac30275031331eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; AString, void * &gt;</type>
      <name>markers</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a95a2ae400c6a2ca0bbb66ac4dcec4020</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>resDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa704b680934869c92c288cb9a23034f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>core::CallerInfo::ThreadDictionary</type>
      <name>threadDictionary</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6840265f2a87f2c836f0661ab90fb188</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static ALOX_API bool</type>
      <name>simpleWildcardFilter</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7f1ea36a1e2ce90d2ced8b3e5fa71084</anchor>
      <arglist>(core::Logger *logger, const String &amp;loggerFilter)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>evaluateResultDomain</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4b3ab93a52d93d663c9898504ff53c90</anchor>
      <arglist>(const TString &amp;domain)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>internalLog</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2788f89cf43423ca779ccfb931574e96</anchor>
      <arglist>(Log::Level level, const TString &amp;msg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ALOX_API void</type>
      <name>logConfigDomainRecursive</name>
      <anchorfile>classaworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a69162739e7506f8e9e806bf52fa4672b</anchor>
      <arglist>(core::Domain &amp;domain, int indent, AString &amp;domPath, AString &amp;buffer)</arglist>
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
      <name>doLogSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a463c7df444456b599a8175d2d5d82daa</anchor>
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
      <type>const strings::ASTerminatable &amp;</type>
      <name>Contents</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a682e2846570b93b1f639f13132b30b10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const strings::ASTerminatable &amp;</type>
      <name>File</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>ae3b802a523b8040532b4e65a62458ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const strings::ASTerminatable &amp;</type>
      <name>Func</name>
      <anchorfile>classaworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a14bbc45cd50e31a0457a9c9fe0c9c073</anchor>
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
      <anchor>a45d7aa667871938158938affcb95f5b5</anchor>
      <arglist>(ALIB_DBG_SRC_INFO_PARAMS_DECL int type, const strings::ASTerminatable &amp;msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::MetaInfo</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>ConsumableSourcePathPrefix</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a33397151e3c9c32997688cd29a3cd0c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>DateFormat</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a04c5093c5a5f5e30994ca8b0b84853a0</anchor>
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
      <type>String16</type>
      <name>LogLevelError</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a2764435fbb01166f974b5a15e1e8409c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>LogLevelInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a3c2f6953954b286c890698b87394d177</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>LogLevelVerbose</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ae770e910a7f77ad48c0a39f18a02d708</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>LogLevelWarning</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a9a924d9d08be43ed1289117bf4983b79</anchor>
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
      <type>String32</type>
      <name>NoMethodInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a12513f8c0773fab55c23cc8546af56b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String32</type>
      <name>NoSourceFileInfo</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>aa2d945d4b31dd484ece4cc687acf8831</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffDays</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>aa3f98d2aa27c33f8dc7c3cf4c6b1a0d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffHours</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a20d1d3b476a6aafeeb5e87fbfacc5e52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffMicros</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a661a09a8e1eb17581bc67aff1f132d56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffMillis</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ad78fde89caeb4ccbe776b1d351d52413</anchor>
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
      <type>String16</type>
      <name>TimeDiffMins</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a6781ce4c72ba2117380b0ee0b803e4bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffNanos</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a64f81ff97c47cac44c8c03890bdf62b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffNone</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a1e70c1adc386d8704fd62c4978a0a3d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeDiffSecs</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a12c8df15357e02da8b11708cb294cfd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeElapsedDays</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a41d26c37bd02bb24b9428af4896aa074</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>TimeOfDayFormat</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a84bddee7b379ee961f0d8dc745401985</anchor>
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
      <anchor>a5848a385a93b4c1ff902525337babcc2</anchor>
      <arglist>(TextLogger &amp;logger, AString &amp;buffer, const TString &amp;domain, Log::Level level, CallerInfo *caller)</arglist>
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
      <anchor>a6afaa48005f63c597d47b2125022cd23</anchor>
      <arglist>(TextLogger &amp;logger, const TString &amp;domain, Log::Level level, CallerInfo *caller, AString &amp;buffer, Substring &amp;variable)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>writeTimeDiff</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a3e51ddb2d0d6ce33302bf0d16b1328fb</anchor>
      <arglist>(AString &amp;buffer, int_fast64_t diffNanos)</arglist>
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
      <type>ASTerminatable</type>
      <name>DecimalExponentSeparator</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a7d522765b039da87634a1ff4c05edca0</anchor>
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
      <type>ASTerminatable</type>
      <name>DecimalPointCharacters</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a79ad4feac81e7c3f18e72411402bce6f</anchor>
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
      <anchor>adc58da979de8d98200f0aca32cade7fe</anchor>
      <arglist>(const AS &amp;src, int &amp;idx)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int64_t</type>
      <name>StringToInteger</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>aab6dcba8a338af34f962ab45b9beaa65</anchor>
      <arglist>(const AS &amp;src, int &amp;idx)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lox::core::textlogger::ObjectConverter</name>
    <filename>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</filename>
    <member kind="variable">
      <type>String64</type>
      <name>FmtNullObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>af8fbc61a0701e45601ee9355a2d6675a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String64</type>
      <name>FmtUnknownObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a132ed009c6e3362a54e052134a602cfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>ALOX_API</type>
      <name>ObjectConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a16313a6b5202d6d886b0e5a34e995a8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ObjectConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a6e913a253720dcb333b6205b4272709d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual ALOX_API bool</type>
      <name>ConvertObject</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a248a310704a1deac3710b03bc5b1712d</anchor>
      <arglist>(const void *o, int typeInfo, AString &amp;result)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>aworx::lib::Ownable</name>
    <filename>classaworx_1_1lib_1_1Ownable.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Acquire</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a72e29e3a91bbf0ab80b0b19bc7975a39</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Release</name>
      <anchorfile>classaworx_1_1lib_1_1Ownable.html</anchorfile>
      <anchor>a4dc7ecb0d192d6cccc9287daaf0eca0f</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::Owner</name>
    <filename>structaworx_1_1lib_1_1Owner.html</filename>
    <member kind="function">
      <type></type>
      <name>Owner</name>
      <anchorfile>structaworx_1_1lib_1_1Owner.html</anchorfile>
      <anchor>a59da7b021af5b8c1ce7e456a6d1c72a1</anchor>
      <arglist>(Ownable &amp;ownable)</arglist>
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
      <anchor>ab982d0ee3cc6faeacdc8f538f63efb87</anchor>
      <arglist>(const String &amp;name, const String &amp;typeName)</arglist>
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
      <name>doLogSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a1eb6db533f3cc421bb2a9a2f9d8751a6</anchor>
      <arglist>(const AString &amp;buffer, int start, int length)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>doTextLog</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>ad15a0a8b8b8d232f97d9c0d9c28cea41</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, AString &amp;msg, int indent, core::CallerInfo *caller, int lineNumber)</arglist>
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
    <member kind="variable">
      <type>bool</type>
      <name>HaltOnError</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>aaa5d96026d2a9009538182741b707aed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>HaltOnWarning</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a57c82f739172de9fc0058f43d6e3f3ed</anchor>
      <arglist></arglist>
    </member>
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
      <anchor>abc1a2b7127e4881f7d5ad8956bdcdc10</anchor>
      <arglist>(ALIB_DBG_SRC_INFO_PARAMS_DECL int type, const strings::ASTerminatable &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API ReportWriter *</type>
      <name>ReplaceReportWriter</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a346c5c5d8273ac95ee3e62194753f9ea</anchor>
      <arglist>(ReportWriter *newReportWriter, bool deletePrevious)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ALIB_API Report</type>
      <name>defaultReport</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a9088fab9d3df935215bb0bb30f7b2250</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>threads::ThreadLockNR *</type>
      <name>lock</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ae93c7c02e0fcf8f15616b0b49bed5194</anchor>
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
      <type>ReportWriter *</type>
      <name>reportWriter</name>
      <anchorfile>classaworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a9b5969adbe225a7b5fe8bda46c619cd3</anchor>
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
      <name>doLogSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>ac69f7301749f95053732100e17a76fb4</anchor>
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
      <type>String16</type>
      <name>FmtIndentString</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a62494b942e4f6e70bf8f80fa1a3a5223</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String256</type>
      <name>FmtMultiLineMsgHeadline</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ab0cf10ab98ce4ece873b70d4577ca035</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>FmtMultiLinePostfix</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ae4e90041230421832bff40fe3ff57d25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String16</type>
      <name>FmtMultiLinePrefix</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a6a0f47a82a9e2018d42acdc864eaeb76</anchor>
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
      <type>String16</type>
      <name>MultiLineDelimiterRepl</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a1c310c98162c46f37a1935c70f8edb70</anchor>
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
      <type>textlogger::ObjectConverter *</type>
      <name>ObjectConverter</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>adbae482a1c395e38d1c0abf4dd8d6660</anchor>
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
      <type>virtual ALOX_API void</type>
      <name>ClearReplacements</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a17d8436509bfd6902d02a1a7628c9708</anchor>
      <arglist>()</arglist>
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
    <member kind="function" protection="protected">
      <type>ALOX_API</type>
      <name>TextLogger</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a95e205d20b58c467d54116f7124f7cc2</anchor>
      <arglist>(const String &amp;name, const String &amp;typeName)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual ALOX_API void</type>
      <name>doLog</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a3ce020f3020679efc65d083b34bb7123</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, const void *msgObject, int msgType, int indent, CallerInfo *caller)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>doTextLog</name>
      <anchorfile>classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a734a84c01a944814d8da5285962e9d50</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, AString &amp;msg, int indent, core::CallerInfo *caller, int lineNumber)=0</arglist>
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
      <anchor>ab91dc804181f48b0b445ac1299c36c05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ALIB_API int</type>
      <name>IsAcquired</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a6713972787725f6b42d7fe94ea32624c</anchor>
      <arglist>(Thread *thread=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>enums::Safeness</type>
      <name>Mode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a6f6f0840b4d4e758e93644c2fd389896</anchor>
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
      <name>SetMode</name>
      <anchorfile>classaworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a7ba75d036f96e4ea3d2b451677bdeba5</anchor>
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
      <anchor>affeac79a4a864890b2e1862d388bfad3</anchor>
      <arglist>()</arglist>
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
      <anchor>a8b1a3d7efe592bf648dfbd0cb42df127</anchor>
      <arglist>(const Ticks &amp;olderTime)</arglist>
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
  <compound kind="struct">
    <name>aworx::lib::strings::ToASDefined</name>
    <filename>structaworx_1_1lib_1_1strings_1_1ToASDefined.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>aworx::lib::strings::ToASDefined&lt; const std::string &amp; &gt;</name>
    <filename>structaworx_1_1lib_1_1strings_1_1ToASDefined_3_01const_01std_1_1string_01_6_01_4.html</filename>
  </compound>
  <compound kind="class">
    <name>aworx::lib::strings::Tokenizer</name>
    <filename>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</filename>
    <member kind="variable">
      <type>ASSubstring</type>
      <name>Actual</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>af12981021000f5c7c10a4f9566191f4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ASSubstring</type>
      <name>Rest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a110a475ccae8a2ff41a9c985c6fd02f6</anchor>
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
      <anchor>a8e0b4e86c2ce04a29c48aab6a9f77c8e</anchor>
      <arglist>(const AS &amp;src, char delim)</arglist>
    </member>
    <member kind="function">
      <type>ASSubstring &amp;</type>
      <name>GetRest</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a201c3ca43bbcfa71f05f2f16e74250c0</anchor>
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
      <type>ALIB_API ASSubstring &amp;</type>
      <name>Next</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>aec29e9f7fa2c7d5d832674393be39cbb</anchor>
      <arglist>(enums::Whitespaces trimming=enums::Whitespaces::Trim, char newDelim= &apos;\0&apos;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a0db72e60497efe368680315f3a14af54</anchor>
      <arglist>(const AS &amp;src, char delim)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>delim</name>
      <anchorfile>classaworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ab56c67e0ed9605b4078e2135f791c4ed</anchor>
      <arglist></arglist>
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
      <anchor>a887f6daaa639283cba0d5d5eb6ce5aba</anchor>
      <arglist>(int minSize=128)</arglist>
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
      <name>doLogSubstring</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1VStudioLogger.html</anchorfile>
      <anchor>ac69f7301749f95053732100e17a76fb4</anchor>
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
      <name>doTextLog</name>
      <anchorfile>classaworx_1_1lox_1_1loggers_1_1WindowsConsoleLogger.html</anchorfile>
      <anchor>ad15a0a8b8b8d232f97d9c0d9c28cea41</anchor>
      <arglist>(const TString &amp;domain, Log::Level level, AString &amp;msg, int indent, core::CallerInfo *caller, int lineNumber)</arglist>
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
      <type>aworx::lib::strings::ASAlloc</type>
      <name>AString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a5878d649ed3cc544cbd74721f95da495</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::AS</type>
      <name>String</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a1b602fe268f8de37e14430b7e646cd0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 128 &gt;</type>
      <name>String128</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>abb9edf26ef4b9c245c5a95bb13f41dcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 16 &gt;</type>
      <name>String16</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acbea83160c272e842de487ed7aa0caab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 1024 &gt;</type>
      <name>String1K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>acd9946aad9d9041ea509a3bced22e283</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 256 &gt;</type>
      <name>String256</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a81ae91cb74396a4fc28abd35ed7ff052</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 2048 &gt;</type>
      <name>String2K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>af3dee8b08186b18ae10ef7bb0a41e650</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 32 &gt;</type>
      <name>String32</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a8a557200d216efbde6004a5eea849b86</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 4096 &gt;</type>
      <name>String4K</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ab35934f523d9f334a8310ea3384d3d67</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 512 &gt;</type>
      <name>String512</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>afc3e452a4a1195b67d5a8121fd9ea8ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 64 &gt;</type>
      <name>String64</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ad16dfdce0f76423f90dcf6821f8b4a7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASPreAlloc&lt; 8 &gt;</type>
      <name>String8</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a639c84da3f1fd25fe67d734809c35992</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASLiteral&lt; TLength &gt;</type>
      <name>StringLiteral</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a25a9748ddb0997bcedc38913800a9352</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASSubstring</type>
      <name>Substring</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a020f593b093787650587801352ccddd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aworx::lib::strings::ASTerminatable</type>
      <name>TString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a2de28a17dc8f201aaa9a8bfa637500a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr String</type>
      <name>NullString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>a6d6180d70c719442ba8b7a120689b9ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr String</type>
      <name>EmptyString</name>
      <anchorfile>namespaceaworx.html</anchorfile>
      <anchor>ae8312c2e2a7a26985be3500c40599b61</anchor>
      <arglist>(&quot;&quot;, 0)</arglist>
    </member>
    <docanchor file="namespaceaworx">CPP_AWORX_NS_SHORTCUTS</docanchor>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib</name>
    <filename>namespaceaworx_1_1lib.html</filename>
    <namespace>aworx::lib::config</namespace>
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
  <compound kind="namespace">
    <name>aworx::lib::strings</name>
    <filename>namespaceaworx_1_1lib_1_1strings.html</filename>
    <class kind="class">aworx::lib::strings::AS</class>
    <class kind="class">aworx::lib::strings::ASAlloc</class>
    <class kind="class">aworx::lib::strings::ASLiteral</class>
    <class kind="class">aworx::lib::strings::ASPreAlloc</class>
    <class kind="class">aworx::lib::strings::ASSubstring</class>
    <class kind="class">aworx::lib::strings::ASTerminatable</class>
    <class kind="class">aworx::lib::strings::CString</class>
    <class kind="class">aworx::lib::strings::Format</class>
    <class kind="struct">aworx::lib::strings::IsApplicable</class>
    <class kind="struct">aworx::lib::strings::IsApplicable&lt; const std::string &amp; &gt;</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; ASAlloc &gt;</class>
    <class kind="struct">aworx::lib::strings::IsTerminatable&lt; ASPreAlloc&lt; TCapacity &gt; &gt;</class>
    <class kind="class">aworx::lib::strings::NumberFormat</class>
    <class kind="class">aworx::lib::strings::ReadLineFromIStream</class>
    <class kind="struct">aworx::lib::strings::TMPLiteral</class>
    <class kind="struct">aworx::lib::strings::ToASDefined</class>
    <class kind="struct">aworx::lib::strings::ToASDefined&lt; const std::string &amp; &gt;</class>
    <class kind="class">aworx::lib::strings::Tokenizer</class>
    <member kind="variable" static="yes">
      <type>static constexpr ASLiteral&lt; 4 &gt;</type>
      <name>DefaultWhitespaces</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a883f1244d6fd8d7f4615d647fa388d04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr ASLiteral&lt; 1 &gt;</type>
      <name>NewLine</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a9976902761097963bf1c3d15a704dd9a</anchor>
      <arglist></arglist>
    </member>
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
      <anchor>aa8fb47b820e77796083d2c3eb13d56b2</anchor>
      <arglist>(AString &amp;target, const T src)</arglist>
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
      <type>ALIB_API int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a17dfe1060a698974265db6b780c709fa</anchor>
      <arglist>(AString &amp;target, const Format::Tab &amp;tab)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ApplyTo</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a99617b411c1009b148f37391abf0d789</anchor>
      <arglist>(AString &amp;target, enums::Case &amp;value)</arglist>
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
      <anchor>a9fad3de9eb89a67a1bc095c3fd5ffc56</anchor>
      <arglist>(AString &amp;target, enums::Alignment &amp;value)</arglist>
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
      <anchor>a829332713d7be0bbde5b1862e1ec837b</anchor>
      <arglist>(AString &amp;target, enums::Inclusion &amp;value)</arglist>
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
      <anchor>a380a2e715c58148cf81b7e31c4ef1bd9</anchor>
      <arglist>(AString &amp;target, enums::CurrentData &amp;value)</arglist>
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
      <anchor>af43cf0906d4f7d8f1b6ed6dd6454d361</anchor>
      <arglist>(AString &amp;target, enums::Safeness &amp;value)</arglist>
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
      <anchor>ad795b43f0a24b4c0e6147e223e051546</anchor>
      <arglist>(AString &amp;target, enums::Responsibility &amp;value)</arglist>
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
      <anchor>a0dcce3ad139fe6f9c313fdfe9be5fed2</anchor>
      <arglist>(AString &amp;target, enums::Timezone &amp;value)</arglist>
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
      <anchor>a3b71964dfcfc46db8bfe4369a60b48c3</anchor>
      <arglist>(AString &amp;target, enums::LockMode &amp;value)</arglist>
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
      <anchor>a59c043f8dd398835f7266e1bb2c630bf</anchor>
      <arglist>(AString &amp;target, enums::Whitespaces &amp;value)</arglist>
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
      <anchor>abe6407ebad387df4da89aeed389e712e</anchor>
      <arglist>(AString &amp;target, enums::Create &amp;value)</arglist>
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
      <anchor>a58b0f925b58b64d308bc299f3fe25281</anchor>
      <arglist>(AString &amp;target, enums::Propagation &amp;value)</arglist>
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
      <type>TReturn</type>
      <name>ToAS</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a86b0b5fb454f1fb24e37f31c51159cea</anchor>
      <arglist>(const TString)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>ToAS&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af2f5751974e1cdb68c13d3a8ac337b7b</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToAS&lt; const std::string &amp; &gt;</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>ad176816568c03b4c43b5bbfb814ca7f5</anchor>
      <arglist>(const std::string &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a7b3324b379ed34963410530fde2392e5</anchor>
      <arglist>(const AS &amp;as, std::string &amp;target, int regionStart, int regionLength=CString::MaxLen, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a70ca8b6e2ef4a9264c6c5f2755a43b07</anchor>
      <arglist>(const AS &amp;as, int regionStart, int regionLength=CString::MaxLen)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>af8e87f4ad5a228fdc94f04d405b281d8</anchor>
      <arglist>(const AS &amp;as)</arglist>
    </member>
    <member kind="function">
      <type>std::string &amp;</type>
      <name>ToStdString</name>
      <anchorfile>namespaceaworx_1_1lib_1_1strings.html</anchorfile>
      <anchor>a82a39be3112d82041508726a9dfad939</anchor>
      <arglist>(const AS &amp;as, std::string &amp;target, enums::CurrentData targetData=enums::CurrentData::Clear)</arglist>
    </member>
    <docanchor file="namespaceaworx_1_1lib_1_1strings">alib_namespace_strings_nullable</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings">alib_namespace_strings_class_overview_astring_construction</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Introduction">alib_namespace_strings_intro</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Classes overview">alib_namespace_strings_class_overview</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class AS">alib_namespace_strings_class_overview_as</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class ASTerminatable">alib_namespace_strings_class_overview_asterminatable</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class ASAlloc">alib_namespace_strings_class_overview_astring</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class ASPreAlloc">alib_namespace_strings_class_overview_asprealoc</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class ASSubstring">alib_namespace_strings_class_overview_substring</docanchor>
    <docanchor file="namespaceaworx_1_1lib_1_1strings" title="Class ASLiteral">alib_namespace_strings_class_overview_asliteral</docanchor>
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
    <member kind="variable">
      <type>const char</type>
      <name>PathSeparator</name>
      <anchorfile>namespaceaworx_1_1lib_1_1system.html</anchorfile>
      <anchor>a081742a3398152ceb8694674ffd21c37</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>aworx::lib::threads</name>
    <filename>namespaceaworx_1_1lib_1_1threads.html</filename>
    <class kind="class">aworx::lib::threads::Runnable</class>
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
    <class kind="class">aworx::lox::ALoxReportWriter</class>
    <class kind="class">aworx::lox::ESC</class>
    <class kind="class">aworx::lox::Log</class>
    <class kind="class">aworx::lox::Lox</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox::core</name>
    <filename>namespaceaworx_1_1lox_1_1core.html</filename>
    <namespace>aworx::lox::core::textlogger</namespace>
    <class kind="class">aworx::lox::core::CallerInfo</class>
    <class kind="class">aworx::lox::core::Domain</class>
    <class kind="class">aworx::lox::core::Logger</class>
  </compound>
  <compound kind="namespace">
    <name>aworx::lox::core::textlogger</name>
    <filename>namespaceaworx_1_1lox_1_1core_1_1textlogger.html</filename>
    <class kind="class">aworx::lox::core::textlogger::AutoSizes</class>
    <class kind="class">aworx::lox::core::textlogger::MetaInfo</class>
    <class kind="class">aworx::lox::core::textlogger::ObjectConverter</class>
    <class kind="class">aworx::lox::core::textlogger::PlainTextLogger</class>
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
      <name>ALIB_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga325630a2911ce8e6b188bb5e7ab7f38a</anchor>
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
      <name>ALIB_IDENTIFIER</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaeee83bac121e3fd5d1b452269a5853f3</anchor>
      <arglist>(prefix)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_DBG_SRC_INFO_PARAMS_DECL</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga1526353c5a75ab50925d64b13cf2ea4b</anchor>
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
      <name>ALIB_ERROR</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gabdd5780e186ebbd62960d7ca9673dff1</anchor>
      <arglist>(msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIB_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga9760e218b8f31dab354ea3fd9668db73</anchor>
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
      <name>ALIB_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gaba07586b518480b52466e018bfa34c98</anchor>
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
      <name>ALIB_ASSERT_ERROR_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>gac9a7ce9ac002073d26b3abf5797e9d86</anchor>
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
      <name>ALIB_ASSERT_WARNING_AS</name>
      <anchorfile>group__GrpALibMacros.html</anchorfile>
      <anchor>ga12732c26cd94f68b87b8d8a31bb079c9</anchor>
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
  </compound>
  <compound kind="group">
    <name>GrpALibCompilerSymbols</name>
    <title>ALib Compilation Symbols</title>
    <filename>group__GrpALibCompilerSymbols.html</filename>
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
      <name>LOG_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga71f7449b6ad8bbd0ba22f897d7338a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_POSTFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gad662b4dbce165eccc829278f9a1d5477</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_PREFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gaae1d11681b36518afb9413f4194b18a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_REL_LOX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gab014491c0aaaceaa1ef1a7d679a8d3e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_POSTFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>gad7b0252385be7787e0e08c7ea0582ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOX_PREFIX</name>
      <anchorfile>group__GrpALoxMacrosLowLevel.html</anchorfile>
      <anchor>ga48644d682557d34b6a07bea1b13bb848</anchor>
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
      <name>Log_AddLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga518bf5331afc5bd2e6d79a9f290ae8b6</anchor>
      <arglist>(...)</arglist>
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
      <name>Log_GetMarker</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga85abcf294a9046897fc2924513e7947f</anchor>
      <arglist>(marker, scope)</arglist>
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
      <name>Log_Line</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gae6d6d078cd4c5ed6c6726d0cbdbbc4aa</anchor>
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
      <name>Log_RemoveLoggers</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gad3a71e0a643a1c19f8875e586f95b92e</anchor>
      <arglist>(...)</arglist>
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
      <name>Log_SetLogger</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga8fb5f633199382936bfc67e45c1737af</anchor>
      <arglist>(disabled, filter)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetMarker</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>gaecd826ea5803a068bca503e075f5d878</anchor>
      <arglist>(marker, scope)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Log_SetStartTime</name>
      <anchorfile>group__GrpMacrosDebugLog.html</anchorfile>
      <anchor>ga519416f7b52968906c24d3c57f4ce39f</anchor>
      <arglist>(time, filter)</arglist>
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
      <name>Lox_AddLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gac3806ad5dcf0f48b170f79069369f380</anchor>
      <arglist>(...)</arglist>
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
      <name>Lox_GetMarker</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaac5f1d37b8f195a7d387d4bf59f9b7c0</anchor>
      <arglist>(marker, scope)</arglist>
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
      <name>Lox_Line</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga97a2c77a1cef79dc8dd295153ea2347e</anchor>
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
      <name>Lox_RemoveLoggers</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gaa493b652d1b9a0d3bca8662603f5e199</anchor>
      <arglist>(filter)</arglist>
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
      <name>Lox_SetLogger</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gae6103e5556647a551bb2d78afb60522d</anchor>
      <arglist>(enable, filter)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetMarker</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>gacea507bfcbffd40425f919f17a36fb9f</anchor>
      <arglist>(marker, scope)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Lox_SetStartTime</name>
      <anchorfile>group__GrpMacrosReleaseLog.html</anchorfile>
      <anchor>ga4ce0c3ef52fd3806ee4e99f8c44e8179</anchor>
      <arglist>(time, filter)</arglist>
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
    <docanchor file="cpptutorial" title="2. Adding ALox to a Project">tutcpp_adding_ALox</docanchor>
    <docanchor file="cpptutorial" title="2.1 Create a tutorial project or equip your current project with ALox">tutcpp_createproject</docanchor>
    <docanchor file="cpptutorial" title="2.2. Create an instance of class &quot;Logger&quot;">tutcpp_ha1</docanchor>
    <docanchor file="cpptutorial" title="2.3. Add code to create and set a &quot;Log Domain&quot;">tutcpp_ha_3</docanchor>
    <docanchor file="cpptutorial" title="2.4. Add log code">tutcpp_ha_4</docanchor>
    <docanchor file="cpptutorial" title="2.5. Run your application within your IDE">tutcpp_ha_5</docanchor>
    <docanchor file="cpptutorial" title="2.6. Build a release version">tutcpp_ha_6</docanchor>
    <docanchor file="cpptutorial" title="3. Log levels and log domains">tutcpp_llld</docanchor>
    <docanchor file="cpptutorial" title="3.1. Log code with different log levels">tutcpp_llld_1</docanchor>
    <docanchor file="cpptutorial" title="3.2. Default domains">tutcpp_llld_2</docanchor>
    <docanchor file="cpptutorial" title="3.3. Where to place ALox log code">tutcpp_llld_3</docanchor>
    <docanchor file="cpptutorial" title="4. Some more Details">tutcpp_more</docanchor>
    <docanchor file="cpptutorial" title="4.1 Stop reading here?">tutcpp_more_1</docanchor>
    <docanchor file="cpptutorial" title="4.2 Using StringNN to create your log messages">tutcpp_more_astring</docanchor>
    <docanchor file="cpptutorial" title="4.3 Conditional logging">tutcpp_more_conditional</docanchor>
    <docanchor file="cpptutorial" title="4.4 LogTools: Log complex things easily">tutcpp_more_logtools</docanchor>
    <docanchor file="cpptutorial" title="4.5 Directing log output to distinct loggers">tutcpp_more_seplog</docanchor>
    <docanchor file="cpptutorial" title="4.6 ALox configuration and internal log messages">tutcpp_more_config</docanchor>
    <docanchor file="cpptutorial" title="4.7 Indentation">tutcpp_more_indentation</docanchor>
    <docanchor file="cpptutorial" title="Further reading">tutcpp_end</docanchor>
  </compound>
</tagfile>
