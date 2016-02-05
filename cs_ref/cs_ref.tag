<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>cs::aworx::lib::ALIB</name>
    <filename>classcs_1_1aworx_1_1lib_1_1ALIB.html</filename>
    <member kind="variable" static="yes">
      <type>static Configuration</type>
      <name>Config</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a34430993f800b3bc4571bd4b9a6d9184</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>affcf83e8b52935dd94b74c1a47cf7e0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly int</type>
      <name>Revision</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>abee878df7a0627f72de2e62aa99f2969</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly int</type>
      <name>Version</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a811fc76ba0094b56a1ddbe6ac8d78915</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static bool</type>
      <name>WaitForKeyPressOnTermination</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ada43e256e3815ef07e1fa43666e356da</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ASSERT</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a2ea4f7aebadaee20aace5e26a9a3b82d</anchor>
      <arglist>(bool cond, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ASSERT_ERROR</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a461f3c6899e74f132b890f5fc3a4a8da</anchor>
      <arglist>(bool cond, String msg, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ASSERT_WARNING</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ac2584577aa4b713feb87ce5f4bf457ad</anchor>
      <arglist>(bool cond, String msg, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ERROR</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a248c962b2cc43bb5bc22e737edc1d387</anchor>
      <arglist>(String msg, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Init</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>aa35acc025eeb16aa37ee19849a520e73</anchor>
      <arglist>(bool useEnv=true, String[] args=null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SleepMicros</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>ac05c5caf38ac3e7b07c8d7ff38f269d1</anchor>
      <arglist>(long microsecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SleepMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a56b63ce54d6e27bb1d57a4ddbabfaba2</anchor>
      <arglist>(int millisecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SleepNanos</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>aba575f2ec01b01d870fb04cdc7f649ca</anchor>
      <arglist>(long nanosecs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SysInfo_IsWindowsOS</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a74ac9f321b8c9cf1b135013fcff877c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>TerminationCleanUp</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a2ac605af45f218047a229949e46a78cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WARNING</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a9f64661c7f0a50b63aff2cdeb392fb87</anchor>
      <arglist>(String msg, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static bool</type>
      <name>_sysInfo_HasConsoleWindow</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a37da3179172bfa1af08eeb3a044f6959</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static bool</type>
      <name>isInitialized</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a1fdc2bf5595c2e64dc06d987769834eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="property" static="yes">
      <type>static bool</type>
      <name>SysInfo_HasConsoleWindow</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ALIB.html</anchorfile>
      <anchor>a4901ec26e28a08613ef74b8ee2c12e35</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::Log::ALoxReportWriter</name>
    <filename>classcs_1_1aworx_1_1lox_1_1Log_1_1ALoxReportWriter.html</filename>
    <base>cs::aworx::lib::ReportWriter</base>
    <member kind="function">
      <type></type>
      <name>ALoxReportWriter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a0bf141375d34781d9d1aba4cbedf4c3e</anchor>
      <arglist>(Lox lox)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Report</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log_1_1ALoxReportWriter.html</anchorfile>
      <anchor>a6ff64b0b8bf46ac6b46d8bcdba2ec990</anchor>
      <arglist>(Report.Message report)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Lox</type>
      <name>lox</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log_1_1ALoxReportWriter.html</anchorfile>
      <anchor>aff12beb5eb706efdffb65183b87431df</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::AnsiConsoleLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger.html</filename>
    <base>cs::aworx::lox::loggers::AnsiLogger</base>
    <member kind="function">
      <type></type>
      <name>AnsiConsoleLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger.html</anchorfile>
      <anchor>af8b8a58890028fb40a52dad51156fa38</anchor>
      <arglist>(String name=&quot;ANSI_CONSOLE&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::AnsiLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_BLACK</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7cc0671aebf209879c5ff0716e9b8451</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af0982be13af0a1f57414c069aee0eaaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a5021959501b03408b952e6b57685867a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab599839b58dae38d72632f8dfaaf1243</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af0e0f81e38561e850977422e7634b155</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab40fcb792acb33ca904f7406901009f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a1659189fc0fe8786aeff7b21fc475d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>abdcfe68676d690a61c4fec3afc63c006</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a5946cb92976f2f88245a4233ae915069</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4743312172b6ecbe700e0765fe1a6db5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a042eb46d9746cab0f30083c79519d26a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_LIGHT_YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aba820c478508cd67e81194ada0768758</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a828c0d607a427032d8f4fec3ad6c8e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a38d6437c3ea95ce7dda4068a9adfcb9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_STD_COL</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a46cd822631a80d6e99566fd1577c037a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_WHITE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a59723fdea6345e12a370fe019aa54a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BG_YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af29314a70f359433d4f4cab7b1445130</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BLACK</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7da34f9c90bdd068e1a2ebe848c7942d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4a7dd74d9487c1a49cd8d835e267fcbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_BOLD</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aff82d2628ff65b1f70ec6b3a53adda4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aea93620884d427744ae5cbdf469810c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a8ebbe45df21a3dd4b1203baf1a0d9c31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a2940b5b0cce40a95db0b24600342df5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_ITALICS</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a98d58155c75dfe8d838b56282a536ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a427a391b53b12ebd6c0a0430ebefd901</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a6e7042803f8b8f186c902ef554e00ab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a359cd61a04b5f41de9cab408525d6464</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>adb0b881d838e5f7f35f4918aceabfdf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae3c3614d99d88b82f228e7df2852edb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a2ee17f25a43829684ebe58fa9ede04f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_LIGHT_YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a2acf313a40e65c47e03e1b24ac776592</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ac7a212065112a3f6ce1643bff18a0f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>af503efcaf56330ab607a447515713c71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_RESET</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad7bb9f2bbe5d393834b6401a2585b9b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_STD_COL</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>acdf02abe0778516599228cfcb75a2b56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_STD_STYLE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a5e1ad1da54ed83c1ee2aab5058420744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_WHITE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7b93c5a9e56531854e7e2467a5ddc010</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ANSI_YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad0d9406fc1b59c147bf0fd9232cc34e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsBackgroundLight</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ab9537e130d3c02801775f8c1941eb9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>abf0b7aeabf626699ea5547c4c112c1ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixError</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a7576c4768fda16421e817896836e568f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixInfo</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>aa6f1bc914355fe8d17d8ca1a3d642eed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixVerbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>adfbbaceadd0848bac5de58dd675fd735</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MsgPrefixWarning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ad9cc2acc0ffe4f4ab09344dacb4c4396</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AnsiLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>ae65203106b0bdd842018eaa6c9359c2f</anchor>
      <arglist>(System.IO.TextWriter textWriter, String name=null)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String[]</type>
      <name>ansiCols</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a6df381da9b7a53520c7181cc0a4006f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>System.IO.TextWriter</type>
      <name>textWriter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a4ea8940b74eadffd0223cb5e7bb414f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doTextLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a9f4d4817f9f3191f4a2a26c96fea0bdb</anchor>
      <arglist>(AString domain, Log.Level level, AString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1AnsiLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::strings::AString</name>
    <filename>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</filename>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsNullOrEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aed54c5c21ba7b689b292e15d7cee8e62</anchor>
      <arglist>(AString ms)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0b7e6f9a4638528a39ba8d41a9edca55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa96fbd724b1775e840ceaf97495cc280</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab33094f9b33daa0c1eaee59d7cd0c1ff</anchor>
      <arglist>(AString src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa7d2c0afda3514bdc671fef0de4acaf</anchor>
      <arglist>(Substring src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3ff52dbe81c441479c27e22adfdd3e7b</anchor>
      <arglist>(String src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab08786c133bbed8861ea8e27bf27b30b</anchor>
      <arglist>(StringBuilder src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>char[]</type>
      <name>Buffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad69b5cb760dc02917a5493fe8f9f7cb4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBuffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d6db7bdf7da56cb3e4bcb16ac4c1e71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af1117a7a4486cffff104fca73fb83898</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7151fe54de727f18db76d1c6312ba386</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLength</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a61e8aa44b25c72e5a3f07105d2baff7a</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a402459718b62883583048fa0770653b0</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad2cc1673d4ad954556c5356c3ad51550</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a357657ded604ecb97b76251146f7ac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a75f50caafbd16c907e46fda59bf4b93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Clear</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a34dd5d801f01e4f8d9f6a4cb435da6e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a47326ffd04c7a2fb6d4658401b2512b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9e0db843c2f5d22f28c153dc20385403</anchor>
      <arglist>(char[] src, int cStart, int cLength, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab1033a6fbdddb344e54ac24ba802b6c5</anchor>
      <arglist>(AString src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7fac9c74a7251758e9c8514b7f3ebf01</anchor>
      <arglist>(Substring src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4d97282dd0d2fa47b4e4f0d0676578af</anchor>
      <arglist>(String src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac22aae8f5073c1f83f30ba0251a4e70c</anchor>
      <arglist>(StringBuilder src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acbbc168caef79f406da007c8d1e08188</anchor>
      <arglist>(char c, int qty, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a305938f621759fcfdc2c16fe7b936d68</anchor>
      <arglist>(char c, int qty)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9a298293c0a30e45d7d64f7fd647528b</anchor>
      <arglist>(char[] src, int cStart, int cLength, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aee52b371dc419e70c2c55b5e998eb0fc</anchor>
      <arglist>(AString src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8b769c894f2b70cc370aefd2251038fe</anchor>
      <arglist>(Substring src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a081581ca2cd007b38bbc7a8ebcd5998d</anchor>
      <arglist>(String src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceRegion</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2939504840b6463a7527a1f7f92a980d</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Delete</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8c5ba7abc3c9da86dcb72df05a9ac922</anchor>
      <arglist>(int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Delete_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa1274424f9550dc6a2414dd4d305f84a</anchor>
      <arglist>(int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7238bcb904848d3e1f4284fcc8836232</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteStart_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af5da0511b71396a9d3b18874d7fb6127</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae1ae8c002a0f57a53a4383a19cf57c79</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteEnd_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a045a00fdc96920fa93317559907ef600</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad934b523816cf3f74bb0dbaefd1197cb</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa9ae1b024361a71ce89231998fcaa4b1</anchor>
      <arglist>(int index, char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aff2347e771828c74296b87de22a542b6</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af19502362f7106af8a5c4d038a56c236</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>NewLine</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae4d8039a4afab89516c88e089848836f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Tab</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae57517ec09a0139179d941f5552fabba</anchor>
      <arglist>(int tabSize, int minPad=1, char tabChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Field</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a804d1f7748d98951e31c93829aeeb5fe</anchor>
      <arglist>(int size=-1, Alignment alignment=Alignment.Right, char padChar= &apos; &apos;, int fieldStart=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a184aaaa896f10064ceb59e45c4dc8d51</anchor>
      <arglist>(char[] src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae3bf29ece9c0dacbe70d756d17b9edcc</anchor>
      <arglist>(Object src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa742f81a8e2b6eb9161f40f8626315e8</anchor>
      <arglist>(AString src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0ff3d23cb61319d9d8a326e924d936b9</anchor>
      <arglist>(AString src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aca666db427a29a2fd64244d34d5c2761</anchor>
      <arglist>(AString src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7e2f603873c045e66305817610772c47</anchor>
      <arglist>(AString src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d0692c4ffa0b3c6f8ffde46189fc81a</anchor>
      <arglist>(char[] src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6163d21fceda39e0bd43802e014f207d</anchor>
      <arglist>(char[] src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9642e7fd275bd42f1eacd131c704829d</anchor>
      <arglist>(Substring substring)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a085b98f819ffb05bffeb544031b23375</anchor>
      <arglist>(Substring src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aadac4f47942a043c1f64b275f6eac636</anchor>
      <arglist>(String src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab07e8241644cba7f183717506ed54de2</anchor>
      <arglist>(String src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acddcc2fe8055492b99916a477b566c27</anchor>
      <arglist>(String src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a97fc8e543ec07f53144a13de80af4f88</anchor>
      <arglist>(String src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8c764c95308185f20001481b544a8ff4</anchor>
      <arglist>(StringBuilder src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae73a8b5de837ad0f80070f61079290dd</anchor>
      <arglist>(StringBuilder src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa4d472847c31bd2a62c64b614ac1a43f</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7220d9aa28b3517400944674e92d6428</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5f4e2d7695a4d66fd8a72fc6cb3797b7</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4afc3df609059a1555c69e074b5028c6</anchor>
      <arglist>(char[] needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a27cac7c0abadb7a24f046ce1a816a700</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6ff40679dc673975fd4b1dd4769a4307</anchor>
      <arglist>(String needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a932a686a017e3717248e7fa80c416a57</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a686926c3c76635cb4645b0a9880d566b</anchor>
      <arglist>(AString needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0ee3e9954aff24db98c56d3d50d99aa3</anchor>
      <arglist>(Substring needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a32813834f4cf0d0e3b051da9247eed59</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a71a0cf7e81fa462296e99bfdebb45b53</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a87386f44dbf99151417983163a6c1361</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0bfbc6da1e8bb129e7c20f680479ba51</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>add5ca664631c5d4705fea74fb27c18a9</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d9400cda441d2ade3cebb94b509a7eb</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa68c8f722eb155e6928f0f0200df28d2</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad436452904b3ac83a030f124dfbcfdbc</anchor>
      <arglist>(AString compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac6ca57f049175bbd7dd73cbd06614013</anchor>
      <arglist>(String compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2b9408be0269b7395373da4c2ac6d2e5</anchor>
      <arglist>(Substring compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9bf7ddc09f008c221d8ac1087f765eea</anchor>
      <arglist>(Object compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5f322158cd0b38fdbf05493bba2856dc</anchor>
      <arglist>(String needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4fae2cedef047fd8f7d630fd21af4804</anchor>
      <arglist>(AString needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aede947f11ee8436cb4f77dfc332312a0</anchor>
      <arglist>(Substring needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a210d9eefc190af4c05f611c4ae590c41</anchor>
      <arglist>(char needle, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa33750e463f99fd1db87b6c98c0cd1ac</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2efb8093a3367df0c789eee107e85efd</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0e280322252f0eb1098ec1080c3cfb78</anchor>
      <arglist>(String searchStr, String newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab987bd7ef2d6fbfd5440fd4396c8db15</anchor>
      <arglist>(AString searchStr, AString newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abde028ea6bc3dc27c0a71bef3c414060</anchor>
      <arglist>(AString searchStr, AString newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af6207b444c7fcb58b963ae18f99c1df1</anchor>
      <arglist>(String searchStr, String newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ToUpper</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aafbc9a53655d5650eb2bafc26cd48e6a</anchor>
      <arglist>(int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ToLower</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a947c824053769fea9f5f6958dee443c5</anchor>
      <arglist>(int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae3fca7b7d84a04a0d54c41bb8a935fef</anchor>
      <arglist>(int value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a08454d989cb16a2776a244ce3b3e7ce3</anchor>
      <arglist>(uint value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a68ec34daedca87fc78c5abb9ec02df74</anchor>
      <arglist>(long value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acbc981ecffc8a279f4a058226e3abc08</anchor>
      <arglist>(ulong value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4b989b40c6ecf3ebb1ee5da322119dab</anchor>
      <arglist>(double value, NumberFormat numberFormat=null)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a281ea2c92f6f2ea2a6462632839d7a74</anchor>
      <arglist>(int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>StringBuilder</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab22dacb61e02eb73fd322e12d0cdb7d8</anchor>
      <arglist>(StringBuilder result, int regionStart, int regionLength=int.MaxValue, bool appendMode=false)</arglist>
    </member>
    <member kind="function">
      <type>StringBuilder</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a46eae5029a45000196e12faca04c37eb</anchor>
      <arglist>(StringBuilder result, bool appendMode=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToInt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5694778699786787abf34fd4812cdee0</anchor>
      <arglist>(int startIdx, out int newIdx, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToInt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d5d151eb238fb96bd94581830ba5631</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>ToLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a468d33eae148133e263b8a58acd1187d</anchor>
      <arglist>(int startIdx, out int newIdx, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>ToLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abd71b27aa975865c6f1c58565380a0a1</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ToFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a90c2dffbae9f1223fdd7991031ea7c4b</anchor>
      <arglist>(int startIdx, out int newIdx, NumberFormat numberFormat=null, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ToFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aad36ebdc05dcbd80deb12a5dd2fa1604</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>override int</type>
      <name>GetHashCode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a77e1afa2b6dee1ed3640da81d7407b42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char[]</type>
      <name>buffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8317b33b8c004741d95935199d964be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>fieldReference</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3f9db4d35ad598af0040026b2b59afa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>hash</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6656561117ec1ab686401179004f53ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>length</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9f59b34b1f25fe00023291b678246bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>tabReference</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad464d10c2231d8bbfa23f5dcaa15af92</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>resizeRegion</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3b0a3b2f5119f2fccbd5a04fe165a780</anchor>
      <arglist>(int regionStart, int regionLength, int newLength)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0b7e6f9a4638528a39ba8d41a9edca55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa96fbd724b1775e840ceaf97495cc280</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab33094f9b33daa0c1eaee59d7cd0c1ff</anchor>
      <arglist>(AString src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa7d2c0afda3514bdc671fef0de4acaf</anchor>
      <arglist>(Substring src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a3ff52dbe81c441479c27e22adfdd3e7b</anchor>
      <arglist>(String src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab08786c133bbed8861ea8e27bf27b30b</anchor>
      <arglist>(StringBuilder src, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>char[]</type>
      <name>Buffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad69b5cb760dc02917a5493fe8f9f7cb4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBuffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4c82c5367836f6886f1505c803ce4058</anchor>
      <arglist>(int newSize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureRemainingCapacity</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>afa227b35c03708d90f56d9b3280163f1</anchor>
      <arglist>(int spaceNeeded)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Capacity</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d6db7bdf7da56cb3e4bcb16ac4c1e71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af1117a7a4486cffff104fca73fb83898</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7151fe54de727f18db76d1c6312ba386</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SetLength</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a61e8aa44b25c72e5a3f07105d2baff7a</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLength_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a402459718b62883583048fa0770653b0</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad2cc1673d4ad954556c5356c3ad51550</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a357657ded604ecb97b76251146f7ac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a75f50caafbd16c907e46fda59bf4b93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Clear</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a34dd5d801f01e4f8d9f6a4cb435da6e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a47326ffd04c7a2fb6d4658401b2512b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9e0db843c2f5d22f28c153dc20385403</anchor>
      <arglist>(char[] src, int cStart, int cLength, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab1033a6fbdddb344e54ac24ba802b6c5</anchor>
      <arglist>(AString src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7fac9c74a7251758e9c8514b7f3ebf01</anchor>
      <arglist>(Substring src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4d97282dd0d2fa47b4e4f0d0676578af</anchor>
      <arglist>(String src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac22aae8f5073c1f83f30ba0251a4e70c</anchor>
      <arglist>(StringBuilder src, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acbbc168caef79f406da007c8d1e08188</anchor>
      <arglist>(char c, int qty, int pos)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>InsertChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a305938f621759fcfdc2c16fe7b936d68</anchor>
      <arglist>(char c, int qty)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9a298293c0a30e45d7d64f7fd647528b</anchor>
      <arglist>(char[] src, int cStart, int cLength, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aee52b371dc419e70c2c55b5e998eb0fc</anchor>
      <arglist>(AString src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8b769c894f2b70cc370aefd2251038fe</anchor>
      <arglist>(Substring src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a081581ca2cd007b38bbc7a8ebcd5998d</anchor>
      <arglist>(String src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ReplaceRegion</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2939504840b6463a7527a1f7f92a980d</anchor>
      <arglist>(char c, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Delete</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8c5ba7abc3c9da86dcb72df05a9ac922</anchor>
      <arglist>(int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Delete_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa1274424f9550dc6a2414dd4d305f84a</anchor>
      <arglist>(int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7238bcb904848d3e1f4284fcc8836232</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteStart_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af5da0511b71396a9d3b18874d7fb6127</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae1ae8c002a0f57a53a4383a19cf57c79</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>DeleteEnd_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a045a00fdc96920fa93317559907ef600</anchor>
      <arglist>(int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad934b523816cf3f74bb0dbaefd1197cb</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa9ae1b024361a71ce89231998fcaa4b1</anchor>
      <arglist>(int index, char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aff2347e771828c74296b87de22a542b6</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af19502362f7106af8a5c4d038a56c236</anchor>
      <arglist>(char[] trimChars=null)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>NewLine</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae4d8039a4afab89516c88e089848836f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Tab</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae57517ec09a0139179d941f5552fabba</anchor>
      <arglist>(int tabSize, int minPad=1, char tabChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Field</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a804d1f7748d98951e31c93829aeeb5fe</anchor>
      <arglist>(int size=-1, Alignment alignment=Alignment.Right, char padChar= &apos; &apos;, int fieldStart=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a184aaaa896f10064ceb59e45c4dc8d51</anchor>
      <arglist>(char[] src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae3bf29ece9c0dacbe70d756d17b9edcc</anchor>
      <arglist>(Object src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa742f81a8e2b6eb9161f40f8626315e8</anchor>
      <arglist>(AString src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0ff3d23cb61319d9d8a326e924d936b9</anchor>
      <arglist>(AString src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aca666db427a29a2fd64244d34d5c2761</anchor>
      <arglist>(AString src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7e2f603873c045e66305817610772c47</anchor>
      <arglist>(AString src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d0692c4ffa0b3c6f8ffde46189fc81a</anchor>
      <arglist>(char[] src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6163d21fceda39e0bd43802e014f207d</anchor>
      <arglist>(char[] src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9642e7fd275bd42f1eacd131c704829d</anchor>
      <arglist>(Substring substring)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a085b98f819ffb05bffeb544031b23375</anchor>
      <arglist>(Substring src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aadac4f47942a043c1f64b275f6eac636</anchor>
      <arglist>(String src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab07e8241644cba7f183717506ed54de2</anchor>
      <arglist>(String src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acddcc2fe8055492b99916a477b566c27</anchor>
      <arglist>(String src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a97fc8e543ec07f53144a13de80af4f88</anchor>
      <arglist>(String src, int regionStart, int regionLength)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a8c764c95308185f20001481b544a8ff4</anchor>
      <arglist>(StringBuilder src)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae73a8b5de837ad0f80070f61079290dd</anchor>
      <arglist>(StringBuilder src, int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa4d472847c31bd2a62c64b614ac1a43f</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="property">
      <type>char</type>
      <name>this[int idx]</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af3f77d067fd3b14f425975202643bc26</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad39028e22d5dbd8b2521066e3ce92f03</anchor>
      <arglist>(int idx)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a99452e70346059e17eea01d6ca1a4b46</anchor>
      <arglist>(int idx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a08cf22a8aa1ae899b7eaedea534d6f5a</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCharAt_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a76666e0cbaac7196014cd58d7c8f7214</anchor>
      <arglist>(int idx, char c)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>adb51f01f0e8cecab375ed5ab1ed44816</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9f75f09e3de12741b0ea7d1675446a6d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a389ad35a26228ee2a29b13b2fbb30523</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd_NC</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abad35acbf3618a035d7a38fc58b89697</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a7220d9aa28b3517400944674e92d6428</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5f4e2d7695a4d66fd8a72fc6cb3797b7</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4afc3df609059a1555c69e074b5028c6</anchor>
      <arglist>(char[] needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a27cac7c0abadb7a24f046ce1a816a700</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a6ff40679dc673975fd4b1dd4769a4307</anchor>
      <arglist>(String needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a932a686a017e3717248e7fa80c416a57</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a686926c3c76635cb4645b0a9880d566b</anchor>
      <arglist>(AString needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0ee3e9954aff24db98c56d3d50d99aa3</anchor>
      <arglist>(Substring needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a32813834f4cf0d0e3b051da9247eed59</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a71a0cf7e81fa462296e99bfdebb45b53</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a87386f44dbf99151417983163a6c1361</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0bfbc6da1e8bb129e7c20f680479ba51</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>add5ca664631c5d4705fea74fb27c18a9</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d9400cda441d2ade3cebb94b509a7eb</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa68c8f722eb155e6928f0f0200df28d2</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ad436452904b3ac83a030f124dfbcfdbc</anchor>
      <arglist>(AString compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ac6ca57f049175bbd7dd73cbd06614013</anchor>
      <arglist>(String compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2b9408be0269b7395373da4c2ac6d2e5</anchor>
      <arglist>(Substring compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a9bf7ddc09f008c221d8ac1087f765eea</anchor>
      <arglist>(Object compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5f322158cd0b38fdbf05493bba2856dc</anchor>
      <arglist>(String needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4fae2cedef047fd8f7d630fd21af4804</anchor>
      <arglist>(AString needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aede947f11ee8436cb4f77dfc332312a0</anchor>
      <arglist>(Substring needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a210d9eefc190af4c05f611c4ae590c41</anchor>
      <arglist>(char needle, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aa33750e463f99fd1db87b6c98c0cd1ac</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a2efb8093a3367df0c789eee107e85efd</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a0e280322252f0eb1098ec1080c3cfb78</anchor>
      <arglist>(String searchStr, String newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SearchAndReplace</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab987bd7ef2d6fbfd5440fd4396c8db15</anchor>
      <arglist>(AString searchStr, AString newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abde028ea6bc3dc27c0a71bef3c414060</anchor>
      <arglist>(AString searchStr, AString newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>SearchAndReplaceAll</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>af6207b444c7fcb58b963ae18f99c1df1</anchor>
      <arglist>(String searchStr, String newStr, int startIdx=0, int maxReplacements=int.MaxValue, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ToUpper</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aafbc9a53655d5650eb2bafc26cd48e6a</anchor>
      <arglist>(int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>ToLower</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a947c824053769fea9f5f6958dee443c5</anchor>
      <arglist>(int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ae3fca7b7d84a04a0d54c41bb8a935fef</anchor>
      <arglist>(int value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a08454d989cb16a2776a244ce3b3e7ce3</anchor>
      <arglist>(uint value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a68ec34daedca87fc78c5abb9ec02df74</anchor>
      <arglist>(long value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>acbc981ecffc8a279f4a058226e3abc08</anchor>
      <arglist>(ulong value, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>_</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a4b989b40c6ecf3ebb1ee5da322119dab</anchor>
      <arglist>(double value, NumberFormat numberFormat=null)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a281ea2c92f6f2ea2a6462632839d7a74</anchor>
      <arglist>(int regionStart, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>StringBuilder</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>ab22dacb61e02eb73fd322e12d0cdb7d8</anchor>
      <arglist>(StringBuilder result, int regionStart, int regionLength=int.MaxValue, bool appendMode=false)</arglist>
    </member>
    <member kind="function">
      <type>StringBuilder</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a46eae5029a45000196e12faca04c37eb</anchor>
      <arglist>(StringBuilder result, bool appendMode=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToInt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a5694778699786787abf34fd4812cdee0</anchor>
      <arglist>(int startIdx, out int newIdx, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ToInt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a1d5d151eb238fb96bd94581830ba5631</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>ToLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a468d33eae148133e263b8a58acd1187d</anchor>
      <arglist>(int startIdx, out int newIdx, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>ToLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>abd71b27aa975865c6f1c58565380a0a1</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ToFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a90c2dffbae9f1223fdd7991031ea7c4b</anchor>
      <arglist>(int startIdx, out int newIdx, NumberFormat numberFormat=null, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ToFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>aad36ebdc05dcbd80deb12a5dd2fa1604</anchor>
      <arglist>(int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>override int</type>
      <name>GetHashCode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1AString.html</anchorfile>
      <anchor>a77e1afa2b6dee1ed3640da81d7407b42</anchor>
      <arglist>()</arglist>
    </member>
    <docanchor file="classcs_1_1aworx_1_1lib_1_1strings_1_1AString">CS_ASTRING_NC</docanchor>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::textlogger::AutoSizes</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>ActualIndex</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>acf5441aa3a2d1bcc3dfd3519d7579fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Export</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>ad801ae4a456f1a4fc4d3c936ed43d031</anchor>
      <arglist>(AString target)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Import</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a2e27aca652f660887bba8f1b14d8edee</anchor>
      <arglist>(Substring source, CurrentData session=CurrentData.Clear)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Import</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a7187f9c198b724deb8215b9171d74879</anchor>
      <arglist>(AString source, CurrentData session=CurrentData.Clear)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Next</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>aefa2cd1851ed40a5268c3896945a5872</anchor>
      <arglist>(int requestedSize, int extraGrowth)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Start</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a07aaf1227e4d645f15e0a964f54ef291</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>length</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a9f59b34b1f25fe00023291b678246bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int[]</type>
      <name>sessionValues</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a6a37f7be21e831947390945d22439e13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int[]</type>
      <name>values</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a37671896b86a975f51e992392f49ca08</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ensureArraySize</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1AutoSizes.html</anchorfile>
      <anchor>a125985ca23382fd519da03305ef96cb3</anchor>
      <arglist>(int minArraySize)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::CallerInfo</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>LineNumber</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>abc72cc909922c33908e48159b106efa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MethodName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>aa8885cdf3586b80bd9905b60bf9529d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>SourceFileName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a2728e8e0ff2895fccb263584a374f97e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ThreadID</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a762284c02117c5070871b37484d70b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>ThreadName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ac2edbbf8ece484cc8424036fdaadd651</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Ticks</type>
      <name>TimeStamp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a5a79026581184f7e7977b1827a104b24</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a57555728289b3e873ec939e3a20bc084</anchor>
      <arglist>(String callerSourceFileName, int callerLineNumber, String callerMemberName, Dictionary&lt; int, String &gt; threadDictionary)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::CLRDebuggerLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1CLRDebuggerLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="function">
      <type></type>
      <name>CLRDebuggerLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1CLRDebuggerLogger.html</anchorfile>
      <anchor>af2aa49ccec8951f52a1527ebdc06e098</anchor>
      <arglist>(String name=null)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>doLogSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1CLRDebuggerLogger.html</anchorfile>
      <anchor>aa1ae12f7ee4e81a2f8777809f6fc5c0c</anchor>
      <arglist>(AString buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1CLRDebuggerLogger.html</anchorfile>
      <anchor>af50093e59ce5397d1eb1e43998e37620</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1CLRDebuggerLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::ColorConsoleLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable">
      <type>bool</type>
      <name>IsBackgroundLight</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>ab9537e130d3c02801775f8c1941eb9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ConsoleColor</type>
      <name>MsgColorError</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a416902153f9088373986780731b6c9f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ConsoleColor</type>
      <name>MsgColorInfo</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a437aaf846a3ef2dea352c8bafe45f396</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ConsoleColor</type>
      <name>MsgColorVerbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a4327a1fd6973ad9b7d99cc742c9a5a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ConsoleColor</type>
      <name>MsgColorWarning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a3bfc428813fc814d5e48948585e0c50c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ColorConsoleLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a941bcecd1af22c27a2adaef40c4773f6</anchor>
      <arglist>(String name=null)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ConsoleColor[]</type>
      <name>darkColors</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a3b9f5c4204becd292fb8e1212517e824</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ConsoleColor[]</type>
      <name>lightColors</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a40714713a3c01f0a1a1d2b5953b4e404</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doTextLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a9f4d4817f9f3191f4a2a26c96fea0bdb</anchor>
      <arglist>(AString domain, Log.Level level, AString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ColorConsoleLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::CommandLinePlugIn</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</filename>
    <base>cs::aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="function">
      <type></type>
      <name>CommandLinePlugIn</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a125ef16aaf52510e0884c82306db8356</anchor>
      <arglist>(String[] args)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a6690a1cfc0650692d5de948c41724566</anchor>
      <arglist>(Object category, Object name, AString target)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String[]</type>
      <name>args</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1CommandLinePlugIn.html</anchorfile>
      <anchor>a7551501f7caf9b087ab3da98fbed0ce9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::Configuration</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</filename>
    <class kind="class">cs::aworx::lib::config::Configuration::PrioAndPlugin</class>
    <member kind="variable">
      <type>CommandLinePlugIn</type>
      <name>CmdLineCP</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>aeab3fc98a76ae513a4527528bd9ed304</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EnvironmentPlugIn</type>
      <name>EnvCP</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ac23bef185f6fad19b5a07cef057ccc23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>NumberFormat</type>
      <name>NumberFormat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a20358334d7d6268d5c50b650ebf3e4b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; AString &gt;</type>
      <name>TrueValues</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a12369eaf915d9637d932edb3268d2e55</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Configuration</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ac6f755b1f8e1c7532b3ebfd4f19b7c0c</anchor>
      <arglist>(bool useEnv=true, String[] args=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a2ccbf58795003a2373c5a4dd9c90b3c5</anchor>
      <arglist>(Object category, Object name, AString target)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a7f0305f62e5f91943705ea0ab805917e</anchor>
      <arglist>(Object category, Object name, ref int target, AString temp=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a59e4d55061a2795dad8b2a7d16c8962f</anchor>
      <arglist>(Object category, Object name, ref double target, AString temp=null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InsertPlugin</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a9ccc2a92ad3cf97fb6cbcb0b7109bb57</anchor>
      <arglist>(ConfigurationPlugIn plugin, int priority)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsTrue</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>af8e63074fffc396723b753ddc73ddc86</anchor>
      <arglist>(Object category, Object name, ref int pluginPriority, AString temp=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsTrue</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a6629a76663a353272a1a12f547241d5e</anchor>
      <arglist>(Object category, Object name, AString temp=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RemovePlugin</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ab822760a99ecb38fba7f95c4d2fb700d</anchor>
      <arglist>(ConfigurationPlugIn plugin)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>aadf37512b39dfac1dbf02e6eaaeb5109</anchor>
      <arglist>(Object category, Object name, Object value, Object comments=null, char delim= &apos;,&apos;)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a0c397f690196e6b466e7b48d2aeedb59</anchor>
      <arglist>(Object category, Object name, int value, Object comments=null, AString temp=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>a535866e620a6b43cdaa8fec1feae289b</anchor>
      <arglist>(Object category, Object name, double value, Object comments=null, AString temp=null)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>List&lt; PrioAndPlugin &gt;</type>
      <name>plugins</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration.html</anchorfile>
      <anchor>ac90f5ae6de5fd6744c3bbc5bd6b86d1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::ConfigurationPlugIn</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</filename>
    <member kind="variable">
      <type>Configuration</type>
      <name>Parent</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a85e6c010b38e463045b2393172d3fd31</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>abstract bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a6449cd4a5a29ee459473fbeb22d41d94</anchor>
      <arglist>(Object category, Object name, AString target)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a111788d68fdb2a2a63f9e01e2e0a6452</anchor>
      <arglist>(Object category, Object name, ref int target, AString temp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a2c406851632e37437e58a556ae7cd24e</anchor>
      <arglist>(Object category, Object name, ref double target, AString temp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a8d55af698304815ffd2f2487e300f48d</anchor>
      <arglist>(Object category, Object name, Object value, Object comments, char delim)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a651369ef2d11e3b48c2b010f7b131dbe</anchor>
      <arglist>(Object category, Object name, int value, Object comments, AString temp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>ac98e9ab0a7ccf071d841ff5d6377ee7c</anchor>
      <arglist>(Object category, Object name, double value, Object comments, AString temp)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ConfigurationPlugIn</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1ConfigurationPlugIn.html</anchorfile>
      <anchor>a7be57a5ed92198b336f33405511cc5d4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::ConsoleLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="function">
      <type></type>
      <name>ConsoleLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>acbda79ab3af8a8f70b52ab830e57ab30</anchor>
      <arglist>(String name=null)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>doLogSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>aa1ae12f7ee4e81a2f8777809f6fc5c0c</anchor>
      <arglist>(AString buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>af50093e59ce5397d1eb1e43998e37620</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::ConsoleReportWriter</name>
    <filename>classcs_1_1aworx_1_1lib_1_1ConsoleReportWriter.html</filename>
    <base>cs::aworx::lib::ReportWriter</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Report</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1ConsoleReportWriter.html</anchorfile>
      <anchor>a0ec00af869093da2883b97884ba49b04</anchor>
      <arglist>(Report.Message report)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::strings::CString</name>
    <filename>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</filename>
    <member kind="variable" static="yes">
      <type>static readonly char[]</type>
      <name>DefaultWhitespaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a38121f199788b412de1151c43774a980</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>NewLineChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a8f912677346490ebb297caaee610721f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly char[]</type>
      <name>NullBuffer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>abb7e666c78a39f2ab7934d340b99b091</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>AdjustRegion</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>ab4cfad14918dbb445e67519f3ac9e9d0</anchor>
      <arglist>(int referenceLength, ref int regionStart, ref int regionLength)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a6cc424b278c7b64653cc9e5058d92fb1</anchor>
      <arglist>(String needle, int needleStart, int needleLength, char[] haystack, int haystackStart, int haystackLength, Case sensitivity)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>afd096e4b7e0b7d8244964e4b2716fac0</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, char[] haystack, int haystackStart, int haystackLength, Case sensitivity)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a5d6f94d831646774ce3049291cc6920a</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, char[] haystack, int haystackPos, int haystackLimit, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a590068643fbdfc5f011e8175913959f4</anchor>
      <arglist>(String needle, char[] haystack, int haystackPos, int haystackLimit, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a9d5377eb1699436657c331bf537db8b9</anchor>
      <arglist>(char[] haystack, char needle, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>IndexOfAnyInRegion</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>aed70803d54ddc16853b244863892964b</anchor>
      <arglist>(char[] haystack, int regionStart, int regionLength, char[] needles, Inclusion inclusion)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>IndexOfString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a7e3f4ee05fe4110b731fe6c42ff42e0b</anchor>
      <arglist>(String needle, char[] haystack, int haystackStart, int haystackLength, Case sensitivity)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>IndexOfString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>af7ee8127a7fe3b72b6acd245efa61069</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, char[] haystack, int haystackStart, int haystackLength, Case sensitivity)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1CString.html</anchorfile>
      <anchor>a19fe6558aa402d3cb0284c6ac4ed7294</anchor>
      <arglist>(char[] haystack, int regionStart, int regionLength, char[] needles, Inclusion inclusion)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::Domain</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</filename>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>DomainSeparatorChars</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>afb75ecb5fef3bcf61597efd190ca0114</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Name</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a0de551a5eb98c9fa084c954655523d7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Domain</type>
      <name>Parent</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a8dc3c25005f0e2de28d10fb5d12b97cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; Domain &gt;</type>
      <name>SubDomains</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a2d2032ef55cc34830125ac40dcec1afb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Domain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a637c01c7001a9eb7a5734fe7bc00a03f</anchor>
      <arglist>(Domain parent, AString name)</arglist>
    </member>
    <member kind="function">
      <type>Domain</type>
      <name>Find</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>aec4b8a62a68d36086748848daaa311fb</anchor>
      <arglist>(AString domainPath, ref bool wasCreated)</arglist>
    </member>
    <member kind="function">
      <type>Log.DomainLevel</type>
      <name>GetLevel</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a6b35d5ba376191a0aa5b9ed52b8f05e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsActive</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a729bb906d248e54d997101d8faf8e1c0</anchor>
      <arglist>(Log.Level level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLevel</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a5180f23126f59ef4c5d8510cd7734c6c</anchor>
      <arglist>(Log.DomainLevel domainLevel, Propagation propagation=Propagation.ToDescendants)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Log.DomainLevel</type>
      <name>level</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>a1a9f7325c08dd31ecae733ac275a3791</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Domain</type>
      <name>findRecursive</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Domain.html</anchorfile>
      <anchor>aaff461fc11e5cfa90c7a349137bc7574</anchor>
      <arglist>(AString domainPath, int dpStartIdx, ref bool wasCreated)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::tools::json::DynamicJSONDeserializer</name>
    <filename>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer.html</filename>
    <class kind="class">cs::aworx::lox::tools::json::DynamicJSONDeserializer::DynamicJsonObject</class>
    <member kind="function" static="yes">
      <type>static IDictionary&lt; string, object &gt;</type>
      <name>FromString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer.html</anchorfile>
      <anchor>ae8ed5a6a4f77379a35ea093f0cdf50d5</anchor>
      <arglist>(String json)</arglist>
    </member>
    <member kind="function">
      <type>override object</type>
      <name>Deserialize</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer.html</anchorfile>
      <anchor>a01092d5e0484947c002d470453cbf4b5</anchor>
      <arglist>(IDictionary&lt; string, object &gt; dictionary, Type type, JavaScriptSerializer serializer)</arglist>
    </member>
    <member kind="function">
      <type>override IDictionary&lt; string, object &gt;</type>
      <name>Serialize</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer.html</anchorfile>
      <anchor>a115cd59bd1cbe0bfeba59015090b8fa2</anchor>
      <arglist>(object obj, JavaScriptSerializer serializer)</arglist>
    </member>
    <member kind="property">
      <type>override IEnumerable&lt; Type &gt;</type>
      <name>SupportedTypes</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer.html</anchorfile>
      <anchor>aa7fc96d53ba9a1823678b99be1580b0d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::tools::json::DynamicJSONDeserializer::DynamicJsonObject</name>
    <filename>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</filename>
    <member kind="function">
      <type></type>
      <name>DynamicJsonObject</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</anchorfile>
      <anchor>a68418c7d2b2e5800b79deccdf8a1324a</anchor>
      <arglist>(IDictionary&lt; string, object &gt; dictionary)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>TryGetIndex</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</anchorfile>
      <anchor>af90b4bbff5fc599e84ae7b91c6991cf8</anchor>
      <arglist>(GetIndexBinder binder, object[] indexes, out object result)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>TryGetMember</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</anchorfile>
      <anchor>ae76343f2ab1f658ec5ec5a9850b91709</anchor>
      <arglist>(GetMemberBinder binder, out object result)</arglist>
    </member>
    <member kind="variable" protection="package">
      <type>readonly IDictionary&lt; string, object &gt;</type>
      <name>Dictionary</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</anchorfile>
      <anchor>a0ecddbd2f0dd3f9e45aea60eb4e4fe53</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static object</type>
      <name>WrapResultObject</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1json_1_1DynamicJSONDeserializer_1_1DynamicJsonObject.html</anchorfile>
      <anchor>a0806c1b8bc7eff97057211334c0edd81</anchor>
      <arglist>(object result)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::EnvironmentPlugIn</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</filename>
    <base>cs::aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="function">
      <type></type>
      <name>EnvironmentPlugIn</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</anchorfile>
      <anchor>acbd5e02cd0e7d1fb1263beb7d734fc40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1EnvironmentPlugIn.html</anchorfile>
      <anchor>a6690a1cfc0650692d5de948c41724566</anchor>
      <arglist>(Object category, Object name, AString target)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::ESC</name>
    <filename>classcs_1_1aworx_1_1lox_1_1ESC.html</filename>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_BLACK</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ad9f97de8fc4bcd75284217f1f6a08a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a4fcb8a63c23e04d6e0cc62b8ecb768d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aadc6a2490dd073d14a1e4c6a89a2fd00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a5880784c4b76758c370e2e185843b293</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aeb4ee4a8fa304f618d371bf3cb9f2cfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ae060bbe66b4b4f7d862864c129da46c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a5a7b9bb740d3d57bef2eb0ed7fc43244</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_RESET</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a23cb0fc00083aca1cb08c85b63bb072f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_WHITE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a530f160d98731a247fb64399147d6f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BG_YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a5543908493d3a333e5045d18d8805952</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BLACK</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aad038c9271b9cacb5fc354d9e0c790a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BLUE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a482bba397389d91be57d6e0605f9f162</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>BOLD</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a79517c1ad930e5746fa9b41936adbea6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>CYAN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ae0400fcaf5cf17323f855100b495c9a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>EOMETA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aaa3cac6fdfbe405add0216065cf9f659</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>FG_RESET</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a4d090538b91aeb913f57329509da9116</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>GRAY</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a7837e248ca81fa3afe0c6666548951be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>GREEN</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a9a11c8b2f6c2a96cd7d137d87a1377af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>ITALICS</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a105ee932ad6e094242e289ebb81d4aba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>MAGENTA</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>aabdeecbbe0dc98a98b3a3b1a4fa7a29b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>RED</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a55a99e116c2e2b406217dad47346837d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>RESET</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a2f5a180debe509ca8b281b8334abb6d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>STYLE_RESET</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a4a1438f79ce6e1bc6285eef4c8eaab75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>TAB</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ae78c8c51f9622d0bd398efb1f4c46a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>URL_END</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ae6c49bf947cc01705f08d5996bcfed7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>URL_START</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>ab67c85a196edb1097933824e1d9e6185</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>WHITE</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a9856bdd07ec8a5877eeeeaa4bbb9f814</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>YELLOW</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1ESC.html</anchorfile>
      <anchor>a5003f05d1e4e22ea4d388aec7caa2147</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::IniFile</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</filename>
    <base>cs::aworx::lib::config::ConfigurationPlugIn</base>
    <member kind="enumeration">
      <type></type>
      <name>Status</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a67a0db04d321a74b7e7fcfd3f1a3f70b</anchor>
      <arglist></arglist>
      <enumvalue file="classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70bae0aa021e21dddbd6d8cecec71e9cf564">OK</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70bae9843112228a2d7dd433c3525dce578c">ERROR_OPENING_FILE</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html" anchor="a67a0db04d321a74b7e7fcfd3f1a3f70ba75d3e6ea3c658980029d41d69944b163">ERROR_WRITING_FILE</enumvalue>
    </member>
    <class kind="class">cs::aworx::lib::config::IniFile::Section</class>
    <class kind="class">cs::aworx::lib::config::IniFile::Variable</class>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>DefaultFileExtension</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a2eaa2333f2f0f3ee2b95eb569798ec80</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>AutoSave</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a297ce080be0d2d8b0f5245def3fd1b79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>DefaultCommentPrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a4476ecda6d3ab51725c78ffc7da2ecda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; String &gt;</type>
      <name>EscapeSequences</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>ae78db2be8b8bb16919846bf36e308ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>FileComments</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a83074eb05e084e3cc5d0f9f3bb78f01b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>FileName</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a8bea19241a8e12acb6725e40dd6f2d74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Status</type>
      <name>LastStatus</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a828873beba46715ac28b88ef1de88ae4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; int &gt;</type>
      <name>LinesWithReadErrors</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a7b1f8eca9e66b6d4df78aa76531b3bc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; Section &gt;</type>
      <name>Sections</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a807ad28f27cb71f0929ecb47e6d49f4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IniFile</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a49c1c7a8b07bd2963386683a03bc7705</anchor>
      <arglist>(String filePathAndName=null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a6690a1cfc0650692d5de948c41724566</anchor>
      <arglist>(Object category, Object name, AString target)</arglist>
    </member>
    <member kind="function">
      <type>IniFile.Status</type>
      <name>ReadFile</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a5b3a02da196c52ed5cb54cacd4494378</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Save</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a032c5815976e92b8888116328aa04dd5</anchor>
      <arglist>(Object category, Object name, Object value, Object comments=null, char delim= &apos;,&apos;)</arglist>
    </member>
    <member kind="function">
      <type>Section</type>
      <name>SearchOrCreateSection</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a92238c1ec3b8061d0ebbe405ab6cb8ad</anchor>
      <arglist>(Object name, AString comments)</arglist>
    </member>
    <member kind="function">
      <type>Section</type>
      <name>SearchSectionX</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>aecf9e5296fcc796d1cdbda17ab4d55d3</anchor>
      <arglist>(Object name)</arglist>
    </member>
    <member kind="function">
      <type>IniFile.Status</type>
      <name>WriteFile</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a4f2ebdea6ac3af3e35f92934929fbf94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>commentChars</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a389d30df43a408ed82b7c48feb49dc08</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>addEscapeSequences</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a39b2b60ef9b81321769cf0ef697107a0</anchor>
      <arglist>(TextWriter os, Substring value, AString temp)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>removeEscapeSequences</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>aa9dcab43a5fe003feee1626c47c392a6</anchor>
      <arglist>(Substring value, AString target)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>startsWithCommentSymbol</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a7fb0eea2a0deb68b8b63298b20d9429a</anchor>
      <arglist>(Substring subs)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>writeComments</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile.html</anchorfile>
      <anchor>a48e7f4ef21f89311069eb736d64c0455</anchor>
      <arglist>(TextWriter os, AString comments, Tokenizer tok)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::Log</name>
    <filename>classcs_1_1aworx_1_1lox_1_1Log.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>DomainLevel</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170f</anchor>
      <arglist></arglist>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fa5ef0c737746fae2ca90e66c39333f8f6">Errors</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fac97dda1f78d8fbb5a4f489ab1b51ff4d">WarningsAndErrors</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fa377a1a5cb4724b1fb5993b36459d6570">InfoWarningsAndErrors</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fab1c94ca2fbc3e78fc30069c8d0f01680">All</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a10ac165398697ce1d642d739cc3b170fac49484faf79e2388b580e49444d6ac11">Inherit</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5</anchor>
      <arglist></arglist>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5ad4a9fa383ab700c5bdd6f31cf7df0faf">Verbose</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a4059b0251f66a18cb56f544728796875">Info</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a0eaadb4fcb48a0a0ed7bc9868be9fbaa">Warning</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="a221b779e6bb7b8d40677d7642bfefac5a902b0d55fddef6f8d651fe1035b7d4bd">Error</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Scope</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6</anchor>
      <arglist></arglist>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6aad9c9150641994c9937a1bce42884a31">SourceFile</enumvalue>
      <enumvalue file="classcs_1_1aworx_1_1lox_1_1Log.html" anchor="aaecc53892786f2fa11e682f633af84c6a4c3880bb027f159e801041b1021e88e8">Method</enumvalue>
    </member>
    <class kind="class">cs::aworx::lox::Log::ALoxReportWriter</class>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>ConfigCategoryName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>affcf83e8b52935dd94b74c1a47cf7e0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static TextLogger</type>
      <name>DebugLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af31b3dcdf4a0532206bdfca5d37d4068</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ALoxReportWriter</type>
      <name>DebugReportWriter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a0f39e79a47a3330f131a6539a8306fa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static Lox</type>
      <name>LOX</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9291aece8829db000d6508daa16f67fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly int</type>
      <name>Revision</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abee878df7a0627f72de2e62aa99f2969</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly int</type>
      <name>Version</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a811fc76ba0094b56a1ddbe6ac8d78915</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>AddDebugLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a5ffc84c0ede270c1d09b4820eac46241</anchor>
      <arglist>(Lox lox=null, bool replaceDefaultReportWriter=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>AddLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8ced556c1d5520ea16168f17554b7228</anchor>
      <arglist>(Logger logger, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aee095ff4374fa0a92674287dc27a08d1</anchor>
      <arglist>(bool trueOrLog, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3d4802c79d9f529479edeab504bbe7fb</anchor>
      <arglist>(bool trueOrLog, String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static AString</type>
      <name>Buf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a853691c84a75e5f8fd4e4ef8879eca0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>BufAbort</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3d64fb6257e17b5bd2a4cfa1cba55892</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaad724a6f491718ebea94e5bdc304eaf</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a4bc5c80a505faceb3cbb2adbcafe3fff</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>afbd8c7a382e995b163bc98a3bdad137e</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Logger</type>
      <name>GetLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a81583fc2028aa1ccb925afaa0d63a224</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMarker</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a4576b25512979ba59a7180486b18874a</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8d4eed10072fbce336d60fd926d7c698</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a02b135237e1930051093b3a930a6bbbb</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ac3b403e887df378d8bdb9c480432e4b4</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Init</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aa35acc025eeb16aa37ee19849a520e73</anchor>
      <arglist>(bool useEnv=true, String[] args=null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af545c26975f606a7ea708d954d1c6db8</anchor>
      <arglist>(bool doLog, String domain, Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a4da83abd593e5558182f7ebe0b9bd789</anchor>
      <arglist>(String domain, Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>adf23b6f4fc2211516fa1bbf5df64e5bc</anchor>
      <arglist>(Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>LogConfig</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ae2f57078a4a860f7e16adfe726d81338</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MapThreadName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a99487aa02122a2ddf46146259faeda1c</anchor>
      <arglist>(String threadName, int id=-1, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>RemoveDebugLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a7b326b485cd7ff059bcc3dff4b7e8476</anchor>
      <arglist>(Lox lox=null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>RemoveLoggers</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a853059201cdf7a94f49da10501e6d013</anchor>
      <arglist>(String loggerFilter=null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Reset</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a77ad624cc83a2a71aa4d5ad991d811d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6904a1c24801f8c6ba1f4e58fdec5963</anchor>
      <arglist>(String domain, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a58e44628f46d3667a044e603e33b6d93</anchor>
      <arglist>(String domain, DomainLevel domainLevel, String loggerFilter=null, Propagation propagation=Propagation.ToDescendants, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a73aba0c91d273872c68765d610d49dc3</anchor>
      <arglist>(String domain, Log.Scope scope, Log.DomainLevel domainLevel, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3ebfff19debaebaf32531d7d6dd26f0f</anchor>
      <arglist>(String domain, Log.Scope scope, Log.DomainLevel domainLevel, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a7a69f021a52ba21a3ff7914a143469c9</anchor>
      <arglist>(cs.aworx.lib.enums.Switch newState, String loggerFilter, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetMarker</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ad302d68c6786a82d3c21eb749fb40015</anchor>
      <arglist>(Object marker, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetStartTime</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a1bd69f9755411a857b06d5cd5bf4be69</anchor>
      <arglist>(DateTime?startTime=null, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ae7cd2d23b5a04d9cc3a073cf3b58121e</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af163509f8d2823e746d0a0ef2eb1cc52</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aef109fd14f5ee0cc93c271dc40c576ea</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WaitForKeyPress</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a242d52f9270da13979e726d0e0100e8c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a1c5a83906517e5233bfde85c6dde7a81</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a2976160bd251c4faad246a99a7bee95e</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9eefa1e047d6b4eb185e8b6dfec21472</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static bool</type>
      <name>isInitialized</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a1fdc2bf5595c2e64dc06d987769834eb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::Logger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</filename>
    <member kind="variable">
      <type>uint</type>
      <name>CntLogs</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a7859d287690c28acd561a307d23679bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsDisabled</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>abada4ef55f947626e50d53b5cb8a31cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>Name</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a934fa09ba291a97f43720640e4d83f25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Domain</type>
      <name>RootDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a8c3be195312b12e47828c3b647f8add1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Ticks</type>
      <name>TimeOfCreation</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a42eaec371b1994c77f5497d4213d1183</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Ticks</type>
      <name>TimeOfLastLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a00e19a7e5a1a93ab45e5895a67e6e2eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TypeName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ab7a1acc8625d9adcdc2c86de8045352f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ac0ac9ab9fa44ffc597b20dd6a044d772</anchor>
      <arglist>(AString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a122416e30207f27bc01d0a38fa89618f</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, Propagation propagation=Propagation.ToDescendants)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a9b5821af98374162ebcbceefc1ec0f40</anchor>
      <arglist>(AString domain, Log.DomainLevel domainLevel, Propagation propagation)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>tmpDomainName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ab3455c59a6cb0194878d7942ff4eb825</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Logger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ad5d85bd2edd6cf4e166d9744f6e97f16</anchor>
      <arglist>(String name, String typeName)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>adf2d4a3039b4c8e4f2f24289af899838</anchor>
      <arglist>(AString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::tools::LogTools</name>
    <filename>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</filename>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtExcNull</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aa8eaf49e43df1021c2d606be3fa2a105</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstArrayPostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a589175368d4447e9e299a6772c2de1d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstArrayPrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aff77a89c541f9f77d08d78b65b9f775b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstCycRefPostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ab09e0f17b2e136eab6dd0b8bebb2900a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstCycRefPrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ad56bd642c748ee1addec1188df481eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIEnumerablePostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ab8b8bddb1a3fa62c73e753171cd49dcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIEnumerablePrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aed0d6d14c822f1c1955ef11ae01fb9fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIndent</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a45adaa09fbb02529d24d98b541412995</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstLineNoPostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a965ccdf58230d74195cceaed3fe40539</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstLineNoPrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a2e36df8103a33a2a906ee197a2dea443</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstNoAccessToValue</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aa4ce00beb85593e9964f9036a2a57933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstNull</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>adb9f89054eac0cbc3a6baf24c662f464</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstRecursionLimit</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a4fae788c8c8cd1749d55f7336eae2abf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstTypePostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>acfe76f019ad1076ce73f8d67f292e228</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstTypePrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a961fca96721ab094e840bd62fd81a30b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>instTypeTabStop</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a1cfe4bbb4fae0ca0db99d3fe768ffa64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>instValueTabStop</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ac586537acea9202be95f5cf793324550</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>afc842a4c97fba750a7459c6a7016a9d9</anchor>
      <arglist>(String domain, Log.Level level, Exception e, String headline=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a66ae777e225caa3a816e9d50fabe159f</anchor>
      <arglist>(Log.Level level, Exception e, String headline=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a45c6bc127d70ac0cf8be2f57fdb0c552</anchor>
      <arglist>(Exception e, String headline=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Instance</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a2fe80db61affa775074be23675d518ba</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion, String headline=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Instance</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>abafcf461fb3cd01cc81c14a8b9573309</anchor>
      <arglist>(Log.Level level, Object o, int maxRecursion, String headline=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ac25c0cc25b178a10ef7441a1bccb2a74</anchor>
      <arglist>(String domain, Log.Level level, XDocument xDocument, String headLine=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a5e344feafc8ffdaef2a654393ac57204</anchor>
      <arglist>(Log.Level level, XDocument xDocument, String headLine, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a7c93d3f5007d74bd4806a97ef33bdb2e</anchor>
      <arglist>(String domain, Log.Level level, XElement xElement, String headLine=null, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>acc389c99e2680bf119bef50f73a51cb3</anchor>
      <arglist>(Log.Level level, XElement xElement, String headLine, int indent=0, Lox lox=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>instLineBeginIdx</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aaa958e582bb109b5cf63121eb10a194a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static uint</type>
      <name>instLineNumber</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a4ef97f200cc58b6c0e22c895ddf7c76b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static Dictionary&lt; Object, UInt32 &gt;</type>
      <name>instObject2LineNumber</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a6e81430abaff658ea6e14fbbf242c1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static AString</type>
      <name>tempBuf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ad8bcff62308a450db0f7e00b6937a67d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static AString</type>
      <name>toolBuf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>accf10243655bbcecc845e197c4350e8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a03b1a235ac32902423d66ee923c94613</anchor>
      <arglist>(Exception e, String headline, int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instBeginLine</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a1a60fd445cafbf21819717c2b817af7f</anchor>
      <arglist>(int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instMain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a670b8642fe3a9f4737c9e398c2050006</anchor>
      <arglist>(Object o, int maxRecursion, String headLine)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instNewLine</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a7f90bc448f889a4afd2a0d051508a8e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instRecursive</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ac03b6467ac0863a99a0b52afa782fe8f</anchor>
      <arglist>(Object inst, int maxRecursion, int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instTabStop</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a7ea8777191d09d2b9e64f2c3384ebaf8</anchor>
      <arglist>(int tabStop)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instTabTypeAndNewLine</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>aa64ceea3ae9af0dc33366784f0dfe0e0</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static bool</type>
      <name>isValueType</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a5f76c7257611240fe4d94d77ef3016f4</anchor>
      <arglist>(Object o, Type type)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>xml</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>a1bf3553c854f8a7d0b938a5eeb7bc79c</anchor>
      <arglist>(XDocument xDocument, String headLine)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>xmlElement</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1tools_1_1LogTools.html</anchorfile>
      <anchor>ab871223d442ff953c52fb281aaf84ea6</anchor>
      <arglist>(XElement xe, String headLine, int indent)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::Lox</name>
    <filename>classcs_1_1aworx_1_1lox_1_1Lox.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ErrIfNoDefaultDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aaaef02f6a1dff7969d2fa1e39a7b9755</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>InternalDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aed8c5ed6af267304f7aae60589a589c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>NullDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a14ff0f6a97bd25b6c22c0a820049fbe8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Dictionary&lt; int, String &gt;</type>
      <name>ThreadDictionary</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9449abe368a2e9a9694a52437b02348b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static TextLogger</type>
      <name>CreateConsoleLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8db44d29b6867559f393ad860a0a1782</anchor>
      <arglist>(String name=null)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lox</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>adeecd070b47db04dfac1b186f99a95d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acf0a999558902558b312a55f0f98e39b</anchor>
      <arglist>(Logger logger, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a70fd049804a5fd33235779bc0c728ad3</anchor>
      <arglist>(bool cond, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a35d0b0e246d2105f24f22daa3efd63a8</anchor>
      <arglist>(bool cond, String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>AString</type>
      <name>Buf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad7d2ebe2750e7e4b2548f73d0380f651</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BufAbort</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3474a54c9a6f9f6db081eddb91c078af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae6a54af27a36df2b4f1ade1c5e3a6b26</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa2ae02b6dceda1a272a87cb1840a4d3b</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa175be4be1461484939e26caef684102</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>Logger</type>
      <name>GetLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a74ba68166dee3359939d25f87e648cbe</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetMarker</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aface0c1255d1c75523c654b095c2dc56</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a861890f074da5b826d5b7802c955874c</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1fec7ffaa01b2634d41465465b3db376</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4806ffdc267673deca9e08b9cf0b8c78</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a92a07a47e1dc6dd3bd09428f02e4f835</anchor>
      <arglist>(bool doLog, String domain, Log.Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a369c3716dd8697a8824fe3992fb39e7f</anchor>
      <arglist>(String domain, Log.Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a43d5b54bca91e52364461f111829a55d</anchor>
      <arglist>(Log.Level level, Object msg, int indent=0, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LogConfig</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a833586c138334739ddad9eede52cb909</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MapThreadName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8f5b159dea287785d7d38be9288ab054</anchor>
      <arglist>(String threadName, int id=-1, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7594d8f630b763d4f83ab48ad926f396</anchor>
      <arglist>(Logger logger)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveLoggers</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af07a94c1e4cf8e5d66b6852e04b08624</anchor>
      <arglist>(String loggerFilter=null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a457f426687e79824eec2895798af1830</anchor>
      <arglist>(String domain, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3685670c11543c975d710c98ca7c7f40</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, String loggerFilter=null, Propagation propagation=Propagation.ToDescendants, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9de8563dce83ffc876cca963f72b519e</anchor>
      <arglist>(String domain, Log.Scope scope, Log.DomainLevel domainLevel, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9bbfaa552fdc5d8fbb42aa4a1d0b3647</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac67b00eb07da08f6423e8157be3ac084</anchor>
      <arglist>(cs.aworx.lib.enums.Switch newState, String loggerFilter, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMarker</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a81953e8bd2915702eccfad989570e156</anchor>
      <arglist>(Object marker, Log.Scope scope, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStartTime</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac4e1e9de43f94c25f2b2eb7be54f7a7a</anchor>
      <arglist>(DateTime?startTime=null, String loggerFilter=null, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aaf5e3df48abc6a754ee07dd993b13d07</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a18706951762c1dcb4ad72ec399a58e0c</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4dbf92fb71a193b0433238cbe3052a11</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a683a6aa22be8c620d60c49267ef94e8a</anchor>
      <arglist>(Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3de656356ad723885a8e345742c3f31e</anchor>
      <arglist>(String msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aad904dcf59b775d6050f63d25dbce9fa</anchor>
      <arglist>(String domain, Object msg, int indent=0, [CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CallerInfo</type>
      <name>caller</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a661374595beb4ef6cdcd0417c8c47f0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Dictionary&lt; AString, AString &gt;</type>
      <name>defaultDomains</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7301773dfbda817921e99637adc6ff30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>logBuf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1c3b59e6dc2850f90df33ae9b4533334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ThreadLock</type>
      <name>logBufLock</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a115a099b1c0c5425cd37ec7b54056d01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>List&lt; Logger &gt;</type>
      <name>loggers</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0078398c1e76599b6e0852ffe2937af9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Dictionary&lt; AString, Object &gt;</type>
      <name>markers</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5eab0b79172487be1b04eebcd4ed5736</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>resDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa704b680934869c92c288cb9a23034f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>tempAS</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5a04010d4c0003b3aba30583b7bf3d48</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>simpleWildcardFilter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a904bdd5c05e9810befbf6cbb43201923</anchor>
      <arglist>(Logger logger, string loggerFilter)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>evaluateResultDomain</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0211ab31ad0b19ced6cf693f7f56e838</anchor>
      <arglist>(String domain)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>internalLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa4cbc7d10fb7a53ae1b3f903512f6f75</anchor>
      <arglist>(Log.Level level, AString msg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>logConfigDomainRecursive</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a6b0703f05803dd21c44fa3ffb1d71e7d</anchor>
      <arglist>(Domain domain, int indent, String domPath, AString buf)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::MemoryLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="variable">
      <type>AString</type>
      <name>MemoryLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>ab885e710ebb2c0ae44ee92604a4d56f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>aa4ef264b516797efa54a9df7a697c09f</anchor>
      <arglist>(String name=null, bool pruneESCSequences=true)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>doLogSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>aa1ae12f7ee4e81a2f8777809f6fc5c0c</anchor>
      <arglist>(AString buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>af50093e59ce5397d1eb1e43998e37620</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::Report::Message</name>
    <filename>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>Contents</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a879ba4d7413f0b6f7fa64331b41eed8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>File</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a64de1063997925283992f28eeac1631a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>Func</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>a39c230199b392ed588e57b8950add07f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Line</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>af5b2cae791582f6f4f975f6b25290977</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Type</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>ae011432eaca3858364b05a111f4011d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Message</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report_1_1Message.html</anchorfile>
      <anchor>add4682ff11d43dee82bd8629625220a7</anchor>
      <arglist>(int type, String msg, String csf=&quot;&quot;, int cln=0, String cmn=&quot;&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::textlogger::MetaInfo</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>ConsumableSourcePathPrefixString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ad5e8a7d9f2c872ab23a2332e6583d908</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>DateFormat</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a73be91892f104afd96a32ab547e2cf45</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Format</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a5f73a9d6a9bfabaa4a33c34831006d07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelError</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a56bad526d2a9b0e8fac8774a8e81079d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelInfo</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a642a10ae2076aa7365fd8ac920ee9ff9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelVerbose</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a3948fa2550cec5c1b96c46eaef7d1110</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelWarning</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a796b4686ca6cd82427e5026fa7a13656</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>LogNumberMinDigits</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a72c44479ec3d128c1208b49e4b8ede08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffDays</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a61ceb433642d627c2e1efce90762bb97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffHours</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a1e9702f3330f62f91a66a8e545f48faa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMicros</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>abcd9e4a9e53693daaa04567886a11deb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a2ee9165164ad264d5880f633007629e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>TimeDiffMinimum</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ac72715ae7c695bbfce1fe76075a2f9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMins</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a1463b65c96abf24881c3c153ac0861bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffNanos</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a45ccfa47c91e7a59015e1475d1b52dc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffNone</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a6cc1e88975de4665e5ddc74e397be057</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffSecs</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a5045aad5b73717f73f7adce9823085cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeElapsedDays</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a37dc29c46601640c35ad51bc72b7042e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeOfDayFormat</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ae3289ae62c777551c12429268fea0988</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Write</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a73a26af0308c9b9dbf0a8882d0a4f9e4</anchor>
      <arglist>(TextLogger logger, AString buffer, AString domain, Log.Level level, CallerInfo caller)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DateTime</type>
      <name>callerDateTime</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a321e35a5312d2e9709fd591b7e5d54a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>dateFormatString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a25d0a90e758eef351048c526b82ce060</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>detectDateFormatChanges</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ab621f55d7a1a3c04988089afeea88208</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>detectTimeOfDayFormatChanges</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ae2eb584a3f8074d9b14f56741ff2b628</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>StringBuilder</type>
      <name>formatSB</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a85c8d54f584a622009048d0536f6160f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>timeOfDayFormatString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>ad20e54054ee94793667818d16868ddcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Tokenizer</type>
      <name>tok</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a8a66329d15c440f4546f72bfe913c4a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>processVariable</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a29295bc9771428483565ee6cb928b31c</anchor>
      <arglist>(TextLogger logger, AString domain, Log.Level level, CallerInfo caller, AString dest, Substring variable)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeTimeDiff</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo.html</anchorfile>
      <anchor>a8e4cc4982f400a8cbb57209fb7ee224a</anchor>
      <arglist>(AString buf, long diffNanos)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::strings::NumberFormat</name>
    <filename>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</filename>
    <member kind="variable" static="yes">
      <type>static NumberFormat</type>
      <name>Global</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a9c9a27c7479023730cc33644fc6c9164</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char[]</type>
      <name>DecimalExponentSeparator</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a44879062808763029bcc791c87304c70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>DecimalPointCharacter</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>ac69a618985c8aa8fdec834264d317b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char[]</type>
      <name>DecimalPointCharacters</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>aea9abe9a8bc153e6435ceb8751fac4bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ForceScientificFormat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>ae4968ebb3e654b4b07f58e13d2786dae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>FractionalDigits</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a6c90dcda5ed7d0ecdbc8ec0aa9c76ac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MinIntegralDigits</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a722a7a5cfeadae332ec66b2c79e9c116</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>WriteExponentPlusSign</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a6c00bcda73309af42240644e7b354a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FloatToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>af2bb503687edf4c1c96cd641fccc1b70</anchor>
      <arglist>(double value, char[] buffer, int idx)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IntegerToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a9b8d615738d22e6555ba805874d0c52e</anchor>
      <arglist>(ulong value, char[] buffer, int idx, int minDigits, int sizeHint)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFromLocale</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a286f8e0f3c8b0faa574522a25fbb0912</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>StringToFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>af4233b66b3f0f763fffc8824e4939ce0</anchor>
      <arglist>(char[] buffer, ref int idx, int maxIdx)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>StringToInteger</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a4183c9a24c1c711ec1d92abba88ce43b</anchor>
      <arglist>(char[] buffer, ref int idx, int maxIdx)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static readonly ulong[]</type>
      <name>pow10_0to19</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1NumberFormat.html</anchorfile>
      <anchor>a5f777949702ffefd46ad2d48ae5a1e48</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::textlogger::ObjectConverter</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>FmtNullObject</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>ac281d117b6e931783195f52f70bfa5b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual AString</type>
      <name>ConvertObject</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>a0ba6332bdc61bc28bdc5c9d0106f12c4</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>buffer</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter.html</anchorfile>
      <anchor>aaf50e38674e1c356539d73525486b1d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::textlogger::PlainTextLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::TextLogger</base>
    <member kind="variable">
      <type>bool</type>
      <name>PruneESCSequences</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a9d44a2f52e37f22c5893a1c174251749</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>PlainTextLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a49d9615d6a1b2c20bd5024dcc4689832</anchor>
      <arglist>(String name, String typeName)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract bool</type>
      <name>doLogSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a514f37d6f2158ad5b26a09b5fdc22b7a</anchor>
      <arglist>(AString buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doTextLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>a9f4d4817f9f3191f4a2a26c96fea0bdb</anchor>
      <arglist>(AString domain, Log.Level level, AString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1PlainTextLogger.html</anchorfile>
      <anchor>ab920342c73a91f78d6674097ee84577b</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::Configuration::PrioAndPlugin</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration_1_1PrioAndPlugin.html</filename>
    <member kind="variable">
      <type>ConfigurationPlugIn</type>
      <name>plugIn</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration_1_1PrioAndPlugin.html</anchorfile>
      <anchor>a9580667a91e1962d6169a8416f0580b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prio</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1Configuration_1_1PrioAndPlugin.html</anchorfile>
      <anchor>a6f8e491cf1d80eb127fe0c10ebbfc659</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::Report</name>
    <filename>classcs_1_1aworx_1_1lib_1_1Report.html</filename>
    <class kind="class">cs::aworx::lib::Report::Message</class>
    <member kind="variable">
      <type>bool</type>
      <name>HaltOnError</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>aaa5d96026d2a9009538182741b707aed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>HaltOnWarning</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a57c82f739172de9fc0058f43d6e3f3ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Report</type>
      <name>GetDefault</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ad49d9009e0885cb55639c77ba3de98f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DoReport</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>acf57520593f877afd6cb6d0e0c8b9e95</anchor>
      <arglist>(int type, String msg, [CallerFilePath] String csf=&quot;&quot;, [CallerLineNumber] int cln=0, [CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>ReportWriter</type>
      <name>ReplaceWriter</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a55ce4c99a4d8d27b766949daea9731be</anchor>
      <arglist>(ReportWriter newWriter)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static Report</type>
      <name>defaultReport</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>a9088fab9d3df935215bb0bb30f7b2250</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>recursionBlocker</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>acb62b28ab9467a03c940908b8f6649d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ReportWriter</type>
      <name>writer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Report.html</anchorfile>
      <anchor>abb89fd434c938300bd1b0e80d98fefc5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>cs::aworx::lib::ReportWriter</name>
    <filename>interfacecs_1_1aworx_1_1lib_1_1ReportWriter.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Report</name>
      <anchorfile>interfacecs_1_1aworx_1_1lib_1_1ReportWriter.html</anchorfile>
      <anchor>a6ff64b0b8bf46ac6b46d8bcdba2ec990</anchor>
      <arglist>(Report.Message report)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::IniFile::Section</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>Comments</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a13a7dbf15cba4c8849fdd8044b185475</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Name</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a0de551a5eb98c9fa084c954655523d7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; Variable &gt;</type>
      <name>Variables</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>ac92596745ac4d7e5a6c6e8300cabfc01</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Section</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>ac6cf4efa287e5aba835abd2e5356178d</anchor>
      <arglist>(Object name)</arglist>
    </member>
    <member kind="function">
      <type>Variable</type>
      <name>Get</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a1c36dedb7a2c8d26c63bfd6102be7f7f</anchor>
      <arglist>(Object name)</arglist>
    </member>
    <member kind="function">
      <type>Variable</type>
      <name>Insert</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Section.html</anchorfile>
      <anchor>a7ea99350bd6274d3175f7c563a3d9ca8</anchor>
      <arglist>(Object name, Object value, AString comments=null)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::strings::Substring</name>
    <filename>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</filename>
    <member kind="variable">
      <type>char[]</type>
      <name>Buf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6a6be65c62f7ad0671d250f11c8564bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>End</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a8fd2246e5257c4d309bf3777e74f54bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Start</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0b2c355629c0c41a383ab8db641304ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f56ec7bc62f19b85e690df023b8f1f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2d45017245fe5b4fa9776b77721017b4</anchor>
      <arglist>(String src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9b25f8ee91fc73b2165aa837899565a7</anchor>
      <arglist>(Substring src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2f7a05046d13e7db893dad84396796e7</anchor>
      <arglist>(AString src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a68c1cb5c95b0c8de6f8c0b578e331a13</anchor>
      <arglist>(char[] cstring, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a31cf0c9c55c6c9b49ec12cfd5f622527</anchor>
      <arglist>(Substring src, int regionStart=0, int regionLength=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ac5cc5a4ff2e7d304dbc16abbc5501ec1</anchor>
      <arglist>(String src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7a2750a6eb7cfa25704d963de8679354</anchor>
      <arglist>(AString src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a484e7cc6bcf9861872586e251170f248</anchor>
      <arglist>(char[] src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad2cc1673d4ad954556c5356c3ad51550</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>af1117a7a4486cffff104fca73fb83898</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7151fe54de727f18db76d1c6312ba386</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a357657ded604ecb97b76251146f7ac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a75f50caafbd16c907e46fda59bf4b93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adb51f01f0e8cecab375ed5ab1ed44816</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>afd6be43525a0cc1c1d4cd054037158e1</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a389ad35a26228ee2a29b13b2fbb30523</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a27570af3fa8ccf61646f1b114e076974</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a735ded8473904152818e8cab24054ef1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6d19ed26db418370ba358f244f446195</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abc61ae90824a932de2b70928446a357f</anchor>
      <arglist>(int regionLength, Substring target=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>afdaf0c83b7a1c6740fd6d2ccb8687538</anchor>
      <arglist>(int regionLength, Substring target=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9e919a3f0222661dcba014fe46287fda</anchor>
      <arglist>(char consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2e9779c64504ac241e80d893b2e0ac4c</anchor>
      <arglist>(char consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>acf2311d5e1f028c132c7608e8aba3049</anchor>
      <arglist>(String consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5be537ec41aadc78a5e95199fd75f96b</anchor>
      <arglist>(AString consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adecaebbb89023563cbb576c8a5ac3e07</anchor>
      <arglist>(Substring consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>acdeb7805f8ff00651cfe9f7f37211f54</anchor>
      <arglist>(String consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2b85d5489d20e058e11640ba867df0ce</anchor>
      <arglist>(AString consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ab281947b532d33eb6fa904199195ab1c</anchor>
      <arglist>(Substring consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1bb71d566b30b6ea1c03cf30384401d0</anchor>
      <arglist>(out int result, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a483c136dde5d3309014cb4ec52f9ffe9</anchor>
      <arglist>(out long result, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a51f8fc04bb7e897f3398120d02985e3f</anchor>
      <arglist>(out double result, NumberFormat numberFormat=null, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a210d9eefc190af4c05f611c4ae590c41</anchor>
      <arglist>(char needle, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f322158cd0b38fdbf05493bba2856dc</anchor>
      <arglist>(String needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a4fae2cedef047fd8f7d630fd21af4804</anchor>
      <arglist>(AString needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aede947f11ee8436cb4f77dfc332312a0</anchor>
      <arglist>(Substring needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa33750e463f99fd1db87b6c98c0cd1ac</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2efb8093a3367df0c789eee107e85efd</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7220d9aa28b3517400944674e92d6428</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f4e2d7695a4d66fd8a72fc6cb3797b7</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a4afc3df609059a1555c69e074b5028c6</anchor>
      <arglist>(char[] needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a27cac7c0abadb7a24f046ce1a816a700</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6ff40679dc673975fd4b1dd4769a4307</anchor>
      <arglist>(String needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a932a686a017e3717248e7fa80c416a57</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a686926c3c76635cb4645b0a9880d566b</anchor>
      <arglist>(AString needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0ee3e9954aff24db98c56d3d50d99aa3</anchor>
      <arglist>(Substring needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa68c8f722eb155e6928f0f0200df28d2</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad436452904b3ac83a030f124dfbcfdbc</anchor>
      <arglist>(AString compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ac6ca57f049175bbd7dd73cbd06614013</anchor>
      <arglist>(String compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2b9408be0269b7395373da4c2ac6d2e5</anchor>
      <arglist>(Substring compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9bf7ddc09f008c221d8ac1087f765eea</anchor>
      <arglist>(Object compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a32813834f4cf0d0e3b051da9247eed59</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a71a0cf7e81fa462296e99bfdebb45b53</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a87386f44dbf99151417983163a6c1361</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0bfbc6da1e8bb129e7c20f680479ba51</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>add5ca664631c5d4705fea74fb27c18a9</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1d9400cda441d2ade3cebb94b509a7eb</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aeb962899e8c3ae888bccf9f18e93ccc6</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a204342f4b8fafb65d3fe794e8d0ed8b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa5a677a0022dd7d16a55d5b8c74bbb9a</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a736bfa9d9917a7ed3ff6e8de7a618c75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a8322a49285d016befc43db279b5c9857</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa1122380634547a5a04737b69180dcab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a98ecf2479f109eb0a26e3df3657b0d42</anchor>
      <arglist>(AString target, bool append=false)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override int</type>
      <name>GetHashCode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a77e1afa2b6dee1ed3640da81d7407b42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>hash</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6656561117ec1ab686401179004f53ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f56ec7bc62f19b85e690df023b8f1f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2d45017245fe5b4fa9776b77721017b4</anchor>
      <arglist>(String src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9b25f8ee91fc73b2165aa837899565a7</anchor>
      <arglist>(Substring src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2f7a05046d13e7db893dad84396796e7</anchor>
      <arglist>(AString src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Substring</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a68c1cb5c95b0c8de6f8c0b578e331a13</anchor>
      <arglist>(char[] cstring, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a31cf0c9c55c6c9b49ec12cfd5f622527</anchor>
      <arglist>(Substring src, int regionStart=0, int regionLength=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ac5cc5a4ff2e7d304dbc16abbc5501ec1</anchor>
      <arglist>(String src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7a2750a6eb7cfa25704d963de8679354</anchor>
      <arglist>(AString src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a484e7cc6bcf9861872586e251170f248</anchor>
      <arglist>(char[] src, int start=0, int length=-1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad2cc1673d4ad954556c5356c3ad51550</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a787c9800970197d19a5452ac456d64f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>af1117a7a4486cffff104fca73fb83898</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotNull</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7151fe54de727f18db76d1c6312ba386</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a357657ded604ecb97b76251146f7ac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsNotEmpty</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a75f50caafbd16c907e46fda59bf4b93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adb51f01f0e8cecab375ed5ab1ed44816</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>afd6be43525a0cc1c1d4cd054037158e1</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a389ad35a26228ee2a29b13b2fbb30523</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>CharAtEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a27570af3fa8ccf61646f1b114e076974</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a735ded8473904152818e8cab24054ef1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6d19ed26db418370ba358f244f446195</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>abc61ae90824a932de2b70928446a357f</anchor>
      <arglist>(int regionLength, Substring target=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>afdaf0c83b7a1c6740fd6d2ccb8687538</anchor>
      <arglist>(int regionLength, Substring target=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9e919a3f0222661dcba014fe46287fda</anchor>
      <arglist>(char consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2e9779c64504ac241e80d893b2e0ac4c</anchor>
      <arglist>(char consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>acf2311d5e1f028c132c7608e8aba3049</anchor>
      <arglist>(String consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5be537ec41aadc78a5e95199fd75f96b</anchor>
      <arglist>(AString consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Consume</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>adecaebbb89023563cbb576c8a5ac3e07</anchor>
      <arglist>(Substring consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>acdeb7805f8ff00651cfe9f7f37211f54</anchor>
      <arglist>(String consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2b85d5489d20e058e11640ba867df0ce</anchor>
      <arglist>(AString consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFromEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ab281947b532d33eb6fa904199195ab1c</anchor>
      <arglist>(Substring consumable, Whitespaces trimBeforeConsume=Whitespaces.Keep)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeInteger</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1bb71d566b30b6ea1c03cf30384401d0</anchor>
      <arglist>(out int result, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeLong</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a483c136dde5d3309014cb4ec52f9ffe9</anchor>
      <arglist>(out long result, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ConsumeFloat</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a51f8fc04bb7e897f3398120d02985e3f</anchor>
      <arglist>(out double result, NumberFormat numberFormat=null, char[] whitespaces=null)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a210d9eefc190af4c05f611c4ae590c41</anchor>
      <arglist>(char needle, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f322158cd0b38fdbf05493bba2856dc</anchor>
      <arglist>(String needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a4fae2cedef047fd8f7d630fd21af4804</anchor>
      <arglist>(AString needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aede947f11ee8436cb4f77dfc332312a0</anchor>
      <arglist>(Substring needle, int startIdx=0, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa33750e463f99fd1db87b6c98c0cd1ac</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>LastIndexOfAny</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2efb8093a3367df0c789eee107e85efd</anchor>
      <arglist>(char[] needles, Inclusion inclusion, int startIdx=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a7220d9aa28b3517400944674e92d6428</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a5f4e2d7695a4d66fd8a72fc6cb3797b7</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a4afc3df609059a1555c69e074b5028c6</anchor>
      <arglist>(char[] needle, Case sensitivity=Case.Sensitive, int needleRegionStart=0, int needleRegionLength=int.MaxValue, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a27cac7c0abadb7a24f046ce1a816a700</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive, int regionStart=0, int regionLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a6ff40679dc673975fd4b1dd4769a4307</anchor>
      <arglist>(String needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a932a686a017e3717248e7fa80c416a57</anchor>
      <arglist>(char[] needle, int needleStart, int needleLength, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a686926c3c76635cb4645b0a9880d566b</anchor>
      <arglist>(AString needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0ee3e9954aff24db98c56d3d50d99aa3</anchor>
      <arglist>(Substring needle, int pos, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa68c8f722eb155e6928f0f0200df28d2</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ad436452904b3ac83a030f124dfbcfdbc</anchor>
      <arglist>(AString compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>ac6ca57f049175bbd7dd73cbd06614013</anchor>
      <arglist>(String compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a2b9408be0269b7395373da4c2ac6d2e5</anchor>
      <arglist>(Substring compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Equals</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a9bf7ddc09f008c221d8ac1087f765eea</anchor>
      <arglist>(Object compareString, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a32813834f4cf0d0e3b051da9247eed59</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a71a0cf7e81fa462296e99bfdebb45b53</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a87386f44dbf99151417983163a6c1361</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a0bfbc6da1e8bb129e7c20f680479ba51</anchor>
      <arglist>(String needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>add5ca664631c5d4705fea74fb27c18a9</anchor>
      <arglist>(AString needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a1d9400cda441d2ade3cebb94b509a7eb</anchor>
      <arglist>(Substring needle, Case sensitivity=Case.Sensitive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aeb962899e8c3ae888bccf9f18e93ccc6</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimStart</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a204342f4b8fafb65d3fe794e8d0ed8b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa5a677a0022dd7d16a55d5b8c74bbb9a</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimEnd</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a736bfa9d9917a7ed3ff6e8de7a618c75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a8322a49285d016befc43db279b5c9857</anchor>
      <arglist>(char[] whiteSpaces)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Trim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>aa1122380634547a5a04737b69180dcab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyTo</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a98ecf2479f109eb0a26e3df3657b0d42</anchor>
      <arglist>(AString target, bool append=false)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override int</type>
      <name>GetHashCode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Substring.html</anchorfile>
      <anchor>a77e1afa2b6dee1ed3640da81d7407b42</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::loggers::TextFileLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</filename>
    <base>cs::aworx::lox::core::textlogger::PlainTextLogger</base>
    <member kind="variable">
      <type>String</type>
      <name>FileName</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a5066dd8adab56e4ea54fe46b9db3bd9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TextFileLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>ac0d1ddf81d8bb003641298fd897cb0f4</anchor>
      <arglist>(String fileName, String loggerName=null)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>currentlyInMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a79360590a52ab99fa5ca7bd3e679fef5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>StreamWriter</type>
      <name>sw</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a6943cae82840a1d0b33fe03557040219</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>closeFile</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>ab2ff17b940ae7aca4827d832ceeaeda4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>doLogSubstring</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>aa1ae12f7ee4e81a2f8777809f6fc5c0c</anchor>
      <arglist>(AString buffer, int start, int length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override bool</type>
      <name>notifyLogOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>af50093e59ce5397d1eb1e43998e37620</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>a2c759cbc13e871d8aef5b9672bfa5671</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>openFile</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1loggers_1_1TextFileLogger.html</anchorfile>
      <anchor>acd0224d6aee829fc45210f977168abb4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lox::core::textlogger::TextLogger</name>
    <filename>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</filename>
    <base>cs::aworx::lox::core::Logger</base>
    <member kind="variable">
      <type>AutoSizes</type>
      <name>AutoSizes</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a411d51414c576719fbf8694e1f19fb87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtIndentString</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a84b11e4ba9304e158d4f091d2c6e9d7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLineMsgHeadline</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ab3423baaf4b67d0e7cfa757203aaf872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLinePostfix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ae0ab1101cb40bf899cb8fb9ef26fb29f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLinePrefix</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a74da3f13d354d7b4b31aa8fefa7e7115</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MetaInfo</type>
      <name>MetaInfo</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>adf1921db321da434a7a254222c174398</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MultiLineDelimiter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>aba58580b1670dbfb1caf21f47d0d53de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MultiLineDelimiterRepl</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a957ed4611b87bdf193ad2c3f848a451c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MultiLineMsgMode</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a95ea94dee572eaac760d028ddcf3cf65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ObjectConverter</type>
      <name>ObjectConverter</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>aaf08965c7f26235af09debd323433507</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearReplacements</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a17d8436509bfd6902d02a1a7628c9708</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetReplacement</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>aebb5b477a190ebcf2174fe854a2978ad</anchor>
      <arglist>(String searched, String replacement)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AString</type>
      <name>logBuf</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a1c3b59e6dc2850f90df33ae9b4533334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>List&lt; String &gt;</type>
      <name>replacements</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ae5f1155ccf5f33d2d3fc3202bb88bf8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>TextLogger</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a77541b983eb0b7a2ee732d849b733783</anchor>
      <arglist>(String name, String typeName)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a3f2a29817947567c9a29c42d196a0599</anchor>
      <arglist>(AString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doTextLog</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>a0d2f1838c6403b062f5e7f481d97c51a</anchor>
      <arglist>(AString domain, Log.Level level, AString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>notifyMultiLineOp</name>
      <anchorfile>classcs_1_1aworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger.html</anchorfile>
      <anchor>ad0a0264620cebe7ba84ca1f8d0b5eb94</anchor>
      <arglist>(Phase phase)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::threads::ThreadLock</name>
    <filename>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>RecursionWarningThreshold</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a2b35011c911bf00d065eba8af27620a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>waitWarningTimeLimitInMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>ae5b12a96be437f82f5da54b813614ba7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ThreadLock</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a3482652a4ec58e6c101a78ecca52676d</anchor>
      <arglist>(LockMode lockMode=LockMode.Recursive, Safeness safeness=Safeness.Safe)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Acquire</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>ab91dc804181f48b0b445ac1299c36c05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IsAcquired</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>ae10bdbe9c2585660ee93c3996d01adf5</anchor>
      <arglist>(Thread thread=null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsUnsafe</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>abf2bccd9812728e715f73c27dac06614</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Release</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a94c93747c8daa99d65c2a04c6be0748c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a42d11494af6c497b55ad6ca5ff31a283</anchor>
      <arglist>(Safeness safeness)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>lockCount</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a7f41e1e3070abd18f7cdfdb9a95b3d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>LockMode</type>
      <name>lockMode</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a22778d029b4af3e865c273d2ad677cb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Object</type>
      <name>mutex</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a4cc9273ae9737bab384e14ef7d4b5c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Thread</type>
      <name>owner</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a194df7b1414f1a1181802f255faff967</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>waitTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1threads_1_1ThreadLock.html</anchorfile>
      <anchor>a5c693612d852a9e000481199e9c24f4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::time::Ticks</name>
    <filename>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</filename>
    <member kind="variable" static="yes">
      <type>static readonly Ticks</type>
      <name>CreationTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ab4e057eeeb0ecf2494933081c666ea43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly long</type>
      <name>InternalFrequency</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ae62f17585d560a30016408f33ace2912</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a1c1ae3d4574882f05f5fa9586e7f1fec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a18820450ce6a2a21df681272634d8692</anchor>
      <arglist>(Ticks copy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ticks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aef9b19bc13c2cf1232cf9af34334351f</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a22a9dbaffec3fa638c13c5ae2e8a3a5b</anchor>
      <arglist>(Ticks other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9773a1eac7cae145f7bc6eec351002a9</anchor>
      <arglist>(long value)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Age</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>afc3ea69a2be2bc54667e14ba3fa8cb83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Age</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a0653eecc5886c1614182009ab1f0411e</anchor>
      <arglist>(Ticks result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromDays</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a161ed9398d1cfa08d4db4ed330d98e66</anchor>
      <arglist>(long days)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromHours</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a7c61485aae63d42e28e02cbb7e548824</anchor>
      <arglist>(long hours)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMicros</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a1ea53a33f84438a1785ee2bca6af3be8</anchor>
      <arglist>(long micros)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a022a14bbe8bd29a52672af28f19977c0</anchor>
      <arglist>(long millis)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromMinutes</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac9abb0aba8d40ab4c30e8404bd097c84</anchor>
      <arglist>(long mins)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromNanos</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a2ca7dc68b5aa84ca5c8cc4423e0ac7f2</anchor>
      <arglist>(long nanos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromSeconds</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a16278993f4c841d6865347c7996dbd0e</anchor>
      <arglist>(long secs)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InDays</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac0ca729bf15ebbd36812ba021e4030f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>DateTime</type>
      <name>InDotNetDateTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a11a40cf306eeacbc141e556a77720a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InDotNetDateTimeTicks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a68c1488e775d89b1f808cedf68e4a3dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InEpochMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a85e459d680dcf74b8daa9dce9cff2559</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>InHertz</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a42e86fa4185895d79e83f1a6439d440a</anchor>
      <arglist>(int nDigitsPrec=-1)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InHours</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>afab45db5919f47215a62e0b082fb123b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InMicros</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>adce5eeaded1ab539742218b5a670e6ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a0637e20889e3ab2b54bd5bfa3b75f1c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InMinutes</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ad967309464305020bb8000bcf505d27e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InNanos</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a4f1e90567353bd484fc252eb4c1f7b57</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>InSeconds</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a00fdbf4ceebb73e680f22f110139753f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>Raw</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a3429aac21c056be13621ca4395005863</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a614cfe7992438ee53cfd9440848c39e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>acb7a9f15371bc4845a75a1f8445526b0</anchor>
      <arglist>(Ticks other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFromDotNetDateTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a0a406c24298e2473e4751b7bb7c3e5b6</anchor>
      <arglist>(DateTime dateTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFromEpochMillis</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a06233899624699b39c51da54e1aff1cb</anchor>
      <arglist>(long epochMillis)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRaw</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a281237e70c41ecdfe31a5606f958b75b</anchor>
      <arglist>(long value)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Since</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a21a035ee27f1d1285dfb841cf5baee33</anchor>
      <arglist>(Ticks olderTime)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Since</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a890e162fd09c78184e455b1cf86c8b12</anchor>
      <arglist>(Ticks olderTime, Ticks result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sub</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ac7271304a608df437b10f55b199d7620</anchor>
      <arglist>(Ticks other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Sub</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ab06385075254ed0028784791e11ec98d</anchor>
      <arglist>(long value)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly double</type>
      <name>convSWToDT</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>ad91e3ebd169964f5636d6d006cd445fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly Stopwatch</type>
      <name>creationTimeStopWatch</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a58d43e7232052f1601bc2914babafb17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly long</type>
      <name>dateTimeTicks19700101</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>a9fece05bed075816cf25a02b44f72b57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>tempTicks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>aa1dd788b63c8e4884ff445d813c1a61c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long</type>
      <name>ticks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1Ticks.html</anchorfile>
      <anchor>af0b811e653c51fb98ab202e920af2afe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::time::TickWatch</name>
    <filename>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</filename>
    <member kind="function">
      <type></type>
      <name>TickWatch</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ae5d46be41414c0e48a9611ce08084a50</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickWatch</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a3cf738e64a14fafa681509173e5fe3ca</anchor>
      <arglist>(TickWatch copy)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetAverage</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ae29a8f1f9e654fdc5c28964f8612086f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetAverage</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a0c306dab7a7ec5014a827facc40369d1</anchor>
      <arglist>(Ticks result)</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetCumulated</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>afa26a288553e5b8e69116f085d320564</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSampleCnt</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a8f2deb29070eb959107e5d9ad3584635</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>GetStartTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>abf86508e29c6aa06ee78ea52cf8d36e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reset</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a372de693ad40b3f42839c8ec6ac845f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ticks</type>
      <name>Sample</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a1552464b5f8a4c192c3679db8a08b6e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStartTime</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>aae02d04b5b8ef03807a1ec27d7d64dfd</anchor>
      <arglist>(Ticks t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Start</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a07aaf1227e4d645f15e0a964f54ef291</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>cntSamples</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>a3203b85b99c75b91922c0147ac0ca04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>sum</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>ac78b14fce693b96514184f5ecb99f5fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>tempTicks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>aa1dd788b63c8e4884ff445d813c1a61c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Ticks</type>
      <name>ticks</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1time_1_1TickWatch.html</anchorfile>
      <anchor>aabd9cf330dbc0de48dee7e2f32be3776</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::strings::Tokenizer</name>
    <filename>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</filename>
    <member kind="variable">
      <type>Substring</type>
      <name>Actual</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a2eefe9530c5f2042ddfa20e26b34328b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Substring</type>
      <name>Rest</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a5c8c6045e5fe301e78496fd5e9c7bfab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char[]</type>
      <name>Whitespaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ab83ff0aa583c8a57cbc00240349185f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a09b5373670bea8a8e4ef7645889bad72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a81d875271cb4b26d1c32cc27db48c838</anchor>
      <arglist>(String str, char delim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a461a11c846c48e6c8e58ae00d0575a6a</anchor>
      <arglist>(AString astring, char delim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a22342f5449d696115f4e4cda6549df8d</anchor>
      <arglist>(Substring substring, char delim)</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>GetRest</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>af8eeb416db1e197515b884b2b06de8a0</anchor>
      <arglist>(Whitespaces trimming=enums.Whitespaces.Trim)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasNext</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a3551d22502a58cdc93b15d14f3fb87c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Substring</type>
      <name>Next</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>acf8cc2c23f55fbdc82dce119ea2ea82c</anchor>
      <arglist>(Whitespaces trimming=enums.Whitespaces.Trim, char newDelim= &apos;\0&apos;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ae8ae7f063fc2007372865907bbeda4f4</anchor>
      <arglist>(String str, char delim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>aee36055cd759f5d6c35dd3623bbd4305</anchor>
      <arglist>(AString astring, char delim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a3bb80d9100ef80c50a3dbb65492073ef</anchor>
      <arglist>(Substring substring, char delim)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>delim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1strings_1_1Tokenizer.html</anchorfile>
      <anchor>ab56c67e0ed9605b4078e2135f791c4ed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::Util</name>
    <filename>classcs_1_1aworx_1_1lib_1_1Util.html</filename>
    <member kind="function" static="yes">
      <type>static AString</type>
      <name>GetSpaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a4d9227d105bfa4362fe3cbee757d76a2</anchor>
      <arglist>(int minSize=128)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WriteSpaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a1a042e7db882962ef542966abe9d0a39</anchor>
      <arglist>(StreamWriter os, int qty)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WriteSpaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>a686102820dbd3dfb49891bbcf06aa74c</anchor>
      <arglist>(TextWriter os, int qty)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static AString</type>
      <name>theSpaces</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1Util.html</anchorfile>
      <anchor>af2abf169487119d618ac7a542e28e5c0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cs::aworx::lib::config::IniFile::Variable</name>
    <filename>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</filename>
    <member kind="variable">
      <type>AString</type>
      <name>Comments</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a13a7dbf15cba4c8849fdd8044b185475</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>Delim</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a68297215ac82977611f5dee2062cc910</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Name</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a0de551a5eb98c9fa084c954655523d7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>AString</type>
      <name>Value</name>
      <anchorfile>classcs_1_1aworx_1_1lib_1_1config_1_1IniFile_1_1Variable.html</anchorfile>
      <anchor>a3af185df6d34594e87ac3b8dac9b6b85</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cs</name>
    <filename>namespacecs.html</filename>
    <namespace>cs::aworx</namespace>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx</name>
    <filename>namespacecs_1_1aworx.html</filename>
    <namespace>cs::aworx::lib</namespace>
    <namespace>cs::aworx::lox</namespace>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib</name>
    <filename>namespacecs_1_1aworx_1_1lib.html</filename>
    <namespace>cs::aworx::lib::config</namespace>
    <namespace>cs::aworx::lib::enums</namespace>
    <namespace>cs::aworx::lib::strings</namespace>
    <namespace>cs::aworx::lib::threads</namespace>
    <namespace>cs::aworx::lib::time</namespace>
    <class kind="class">cs::aworx::lib::ALIB</class>
    <class kind="class">cs::aworx::lib::ConsoleReportWriter</class>
    <class kind="class">cs::aworx::lib::Report</class>
    <class kind="interface">cs::aworx::lib::ReportWriter</class>
    <class kind="class">cs::aworx::lib::Util</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib::config</name>
    <filename>namespacecs_1_1aworx_1_1lib_1_1config.html</filename>
    <class kind="class">cs::aworx::lib::config::CommandLinePlugIn</class>
    <class kind="class">cs::aworx::lib::config::Configuration</class>
    <class kind="class">cs::aworx::lib::config::ConfigurationPlugIn</class>
    <class kind="class">cs::aworx::lib::config::EnvironmentPlugIn</class>
    <class kind="class">cs::aworx::lib::config::IniFile</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib::enums</name>
    <filename>namespacecs_1_1aworx_1_1lib_1_1enums.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Alignment</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>acdfaca60ec19c0265bac2692d7982726</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a945d5e233cf7d6240f6b783b36a374ff">Left</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a92b09c7c48c520c3c55e497875da437c">Right</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="acdfaca60ec19c0265bac2692d7982726a4f1f6016fc9f3f2353c0cc7c67b292bd">Center</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Case</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ab9aab17a5e54a8bae6915bc24db13a17</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17a8f21fcdc233ba4078679ca628453d06b">Sensitive</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ab9aab17a5e54a8bae6915bc24db13a17afd038fc7f319e48f3115d92bf5bdbef9">Ignore</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Create</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a55781bd0c78c4e5d47ce433f4eeeee85</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a6e7b34fa59e1bd229b207892956dc41c">Never</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a55781bd0c78c4e5d47ce433f4eeeee85a44c32ea9ad0b836b68c25fdb717fa4b7">IfNotExistent</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CurrentData</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9345007d67faa05253932092d54d10d4</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a9345007d67faa05253932092d54d10d4adc30bc0c7914db5918da4263fce93ad2">Clear</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Inclusion</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a217539925b78b2eed40ae7817d5bee52</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52af4d72a64acd8929c0cc9ed96a7a336cc">Include</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a217539925b78b2eed40ae7817d5bee52a843f2812f595e7ec7c5036e89fde02d6">Exclude</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>LockMode</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a00fc859257c8f09ff9198dde28121961</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a556c3dd912453ae5cb3095cd5054e6f4">Recursive</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a00fc859257c8f09ff9198dde28121961a67b491789a29d0c717a2b4ebe369a936">SingleLocks</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Phase</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ae1c5184dc404edf057ed537bcfddef84</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a1a06729125544cab7cee73195fc044f0">Begin</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ae1c5184dc404edf057ed537bcfddef84a87557f11575c0ad78e4e28abedc13b6e">End</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Propagation</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>aeae0c2d4659a32ef54bd221d1a3da4e6</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="aeae0c2d4659a32ef54bd221d1a3da4e6aa9857b4deb35c57d5753f94fa00a028e">ToDescendants</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Safeness</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a8c800527afe0a8a6c71ae4cceda6bf9d</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dac6eea0560cd6f377e78dff2c85cc9122">Safe</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a8c800527afe0a8a6c71ae4cceda6bf9dad3d57868b6ff9839eff631d2cc8acbce">Unsafe</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Switch</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>a9f3c28a2cb05bdcc618b542e49bfda3f</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fad15305d7a4e34e02489c74a5ef542f36">Off</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="a9f3c28a2cb05bdcc618b542e49bfda3fa521c36a31c2762741cf0f8890cbe05e3">On</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Whitespaces</name>
      <anchorfile>namespacecs_1_1aworx_1_1lib_1_1enums.html</anchorfile>
      <anchor>ad4a46f9fb632511f6be7c53e05f330f7</anchor>
      <arglist></arglist>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a1fc5884251ca9f20a4fd5f79a458f94f">Trim</enumvalue>
      <enumvalue file="namespacecs_1_1aworx_1_1lib_1_1enums.html" anchor="ad4a46f9fb632511f6be7c53e05f330f7a02bce93bff905887ad2233110bf9c49e">Keep</enumvalue>
    </member>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib::strings</name>
    <filename>namespacecs_1_1aworx_1_1lib_1_1strings.html</filename>
    <class kind="class">cs::aworx::lib::strings::AString</class>
    <class kind="class">cs::aworx::lib::strings::CString</class>
    <class kind="class">cs::aworx::lib::strings::NumberFormat</class>
    <class kind="class">cs::aworx::lib::strings::Substring</class>
    <class kind="class">cs::aworx::lib::strings::Tokenizer</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib::threads</name>
    <filename>namespacecs_1_1aworx_1_1lib_1_1threads.html</filename>
    <class kind="class">cs::aworx::lib::threads::ThreadLock</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lib::time</name>
    <filename>namespacecs_1_1aworx_1_1lib_1_1time.html</filename>
    <class kind="class">cs::aworx::lib::time::Ticks</class>
    <class kind="class">cs::aworx::lib::time::TickWatch</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox</name>
    <filename>namespacecs_1_1aworx_1_1lox.html</filename>
    <namespace>cs::aworx::lox::core</namespace>
    <namespace>cs::aworx::lox::loggers</namespace>
    <namespace>cs::aworx::lox::tools</namespace>
    <class kind="class">cs::aworx::lox::ESC</class>
    <class kind="class">cs::aworx::lox::Log</class>
    <class kind="class">cs::aworx::lox::Lox</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox::core</name>
    <filename>namespacecs_1_1aworx_1_1lox_1_1core.html</filename>
    <namespace>cs::aworx::lox::core::textlogger</namespace>
    <class kind="class">cs::aworx::lox::core::CallerInfo</class>
    <class kind="class">cs::aworx::lox::core::Domain</class>
    <class kind="class">cs::aworx::lox::core::Logger</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox::core::textlogger</name>
    <filename>namespacecs_1_1aworx_1_1lox_1_1core_1_1textlogger.html</filename>
    <class kind="class">cs::aworx::lox::core::textlogger::AutoSizes</class>
    <class kind="class">cs::aworx::lox::core::textlogger::MetaInfo</class>
    <class kind="class">cs::aworx::lox::core::textlogger::ObjectConverter</class>
    <class kind="class">cs::aworx::lox::core::textlogger::PlainTextLogger</class>
    <class kind="class">cs::aworx::lox::core::textlogger::TextLogger</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox::loggers</name>
    <filename>namespacecs_1_1aworx_1_1lox_1_1loggers.html</filename>
    <class kind="class">cs::aworx::lox::loggers::AnsiConsoleLogger</class>
    <class kind="class">cs::aworx::lox::loggers::AnsiLogger</class>
    <class kind="class">cs::aworx::lox::loggers::CLRDebuggerLogger</class>
    <class kind="class">cs::aworx::lox::loggers::ColorConsoleLogger</class>
    <class kind="class">cs::aworx::lox::loggers::ConsoleLogger</class>
    <class kind="class">cs::aworx::lox::loggers::MemoryLogger</class>
    <class kind="class">cs::aworx::lox::loggers::TextFileLogger</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox::tools</name>
    <filename>namespacecs_1_1aworx_1_1lox_1_1tools.html</filename>
    <namespace>cs::aworx::lox::tools::json</namespace>
    <class kind="class">cs::aworx::lox::tools::LogTools</class>
  </compound>
  <compound kind="namespace">
    <name>cs::aworx::lox::tools::json</name>
    <filename>namespacecs_1_1aworx_1_1lox_1_1tools_1_1json.html</filename>
    <class kind="class">cs::aworx::lox::tools::json::DynamicJSONDeserializer</class>
  </compound>
  <compound kind="page">
    <name>csmacros</name>
    <title>Conditional Compilation Symbols</title>
    <filename>csmacros</filename>
    <docanchor file="csmacros" title="Conditional Compilation Symbols">csmacros_conditional_compile_symbols</docanchor>
  </compound>
  <compound kind="page">
    <name>csmainpage</name>
    <title>C# Reference</title>
    <filename>csmainpage</filename>
  </compound>
  <compound kind="page">
    <name>cspruning</name>
    <title>Pruning ALox Code in C# from Release Builts</title>
    <filename>cspruning</filename>
    <docanchor file="cspruning" title="1. What is Pruning?">cssetup_pruning_what_is_pruning</docanchor>
    <docanchor file="cspruning" title="2. How Pruning in ALox for C# works">cssetup_pruning_how</docanchor>
    <docanchor file="cspruning" title="3. Mission accomplished: Perfect Auto Pruning with ALox!">cssetup_pruning_result</docanchor>
  </compound>
  <compound kind="page">
    <name>cssetup</name>
    <title>IDE setup ALox for C#</title>
    <filename>cssetup</filename>
    <docanchor file="cssetup" title="1. Introduction">cssetup_1</docanchor>
    <docanchor file="cssetup" title="2. Download">cssetup_vs_download</docanchor>
    <docanchor file="cssetup" title="3. Set up the Built System">cssetup_setup</docanchor>
    <docanchor file="cssetup" title="3.1. Add existing ALox library project to your solution">cssetup_addproject</docanchor>
    <docanchor file="cssetup" title="3.2. Set build dependency">cssetup_builddependency</docanchor>
    <docanchor file="cssetup" title="3.3. Reference the ALox library from within your project">cssetup_referencealox</docanchor>
    <docanchor file="cssetup" title="3.4. Alternatively: Working with the sources">cssetup_using_sources</docanchor>
    <docanchor file="cssetup" title="4. Conditional Compilation Symbols">cssetup_condcompsym</docanchor>
    <docanchor file="cssetup" title="5. Test your setup">cssetup_testsetup</docanchor>
    <docanchor file="cssetup" title="6. Wrap up">cssetup_wrapup</docanchor>
  </compound>
  <compound kind="page">
    <name>cstutorial</name>
    <title>ALox for C# Tutorial</title>
    <filename>cstutorial</filename>
    <docanchor file="cstutorial" title="1. Hello ALox">tutcs_hello_alox</docanchor>
    <docanchor file="cstutorial" title="2. Adding ALox to a Project">tutcs_adding_ALox</docanchor>
    <docanchor file="cstutorial" title="2.1 Create a tutorial project or equip your current project with ALox">tutcs_createproject</docanchor>
    <docanchor file="cstutorial" title="2.2. Create an instance of class &quot;Logger&quot;">tutcs_ha1</docanchor>
    <docanchor file="cstutorial" title="2.3. Add code to create and set a *log domain*">tutcs_ha_3</docanchor>
    <docanchor file="cstutorial" title="2.4. Add log code">tutcs_ha_4</docanchor>
    <docanchor file="cstutorial" title="2.5. Run your application within your IDE">tutcs_ha_5</docanchor>
    <docanchor file="cstutorial" title="2.6. Build a release version">tutcs_ha_6</docanchor>
    <docanchor file="cstutorial" title="3. Log levels and log domains">tutcs_llld</docanchor>
    <docanchor file="cstutorial" title="3.1. Log code with different log levels">tutcs_llld_1</docanchor>
    <docanchor file="cstutorial" title="3.2. Default domains">tutcs_llld_2</docanchor>
    <docanchor file="cstutorial" title="3.3. Where to place ALox log code">tutcs_llld_3</docanchor>
    <docanchor file="cstutorial" title="4. Some more Details">tutcs_more</docanchor>
    <docanchor file="cstutorial" title="4.1 Stop reading here?">tutcs_more_1</docanchor>
    <docanchor file="cstutorial" title="4.2 Using the log buffer singleton">tutcs_more_logbuf</docanchor>
    <docanchor file="cstutorial" title="4.3 Conditional logging">tutcs_more_conditional</docanchor>
    <docanchor file="cstutorial" title="4.4 LogTools: Log complex things easily">tutcs_more_logtools</docanchor>
    <docanchor file="cstutorial" title="4.4.1 Instance(): Log any object recursively">tutcs_more_logtools_instance</docanchor>
    <docanchor file="cstutorial" title="4.4.2 Exception(): Log an exception recursively (with inner exceptions)">tutcs_more_logtools_exception</docanchor>
    <docanchor file="cstutorial" title="4.4.3 XML(): Log out an XML document or element">tutcs_more_logtools_xml</docanchor>
    <docanchor file="cstutorial" title="4.5 Indentation">tutcs_more_indentation</docanchor>
    <docanchor file="cstutorial" title="4.6 Directing log output to distinct loggers">tutcs_more_seplog</docanchor>
    <docanchor file="cstutorial" title="4.7 ALox configuration and internal log messages">tutcs_more_config</docanchor>
    <docanchor file="cstutorial" title="Further reading">tutcs_end</docanchor>
  </compound>
</tagfile>
