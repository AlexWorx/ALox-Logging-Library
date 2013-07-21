<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>tutorial_cs</name>
    <title>ALox for C# Tutorial</title>
    <filename>tutorial_cs</filename>
    <docanchor file="tutorial_cs" title="1. Hello ALox">tutcs_hello_alox</docanchor>
    <docanchor file="tutorial_cs" title="1.1 Create a tutorial project or equip your current project with ALox">tutcs_createproject</docanchor>
    <docanchor file="tutorial_cs" title="1.2. Create an instance of class &quot;ConsoleLogger&quot;">tutcs_ha1</docanchor>
    <docanchor file="tutorial_cs" title="1.3. Add code to create and set a *log domain*">tutcs_ha_3</docanchor>
    <docanchor file="tutorial_cs" title="1.4. Add log code">tutcs_ha_4</docanchor>
    <docanchor file="tutorial_cs" title="1.5. Run your application within visual studio">tutcs_ha_5</docanchor>
    <docanchor file="tutorial_cs" title="1.6. Build Release Version">tutcs_ha_6</docanchor>
    <docanchor file="tutorial_cs" title="2. Log levels and log domains">tutcs_llld</docanchor>
    <docanchor file="tutorial_cs" title="2.1. Log code with different log levels">tutcs_llld_1</docanchor>
    <docanchor file="tutorial_cs" title="2.2. Default domains">tutcs_llld_2</docanchor>
    <docanchor file="tutorial_cs" title="2.3. Where to place ALox log code">tutcs_llld_3</docanchor>
    <docanchor file="tutorial_cs" title="3. Some more Details">tutcs_more</docanchor>
    <docanchor file="tutorial_cs" title="3.1 Stop reading here?">tutcs_more_1</docanchor>
    <docanchor file="tutorial_cs" title="3.2 Conditional logging">tutcs_more_2</docanchor>
    <docanchor file="tutorial_cs" title="3.3 LogTools: Log complex things easily">tutcs_more_3</docanchor>
    <docanchor file="tutorial_cs" title="3.4 Indentation">tutcs_more_4</docanchor>
    <docanchor file="tutorial_cs" title="3.5 Separating domain log levels in different loggers">tutcs_more_5</docanchor>
    <docanchor file="tutorial_cs" title="3.6 ALox configuration and internal log messages">tutcs_more_6</docanchor>
    <docanchor file="tutorial_cs" title="Further reading">tutcs_end</docanchor>
  </compound>
  <compound kind="page">
    <name>setup_projects_vs_cs</name>
    <title>Setup Visual Studio for C# Projects</title>
    <filename>setup_projects_vs_cs</filename>
    <docanchor file="setup_projects_vs_cs" title="1. Setting Up Visual Studio">setup_projects_vs_cs_1</docanchor>
    <docanchor file="setup_projects_vs_cs" title="1.1. Download">setup_projects_vs_cs_1_1</docanchor>
    <docanchor file="setup_projects_vs_cs" title="1.2. Add one of the following projects into your solution">setup_projects_vs_cs_1_2</docanchor>
    <docanchor file="setup_projects_vs_cs" title="1.3 Alternatively: Adding source code to your project">setup_projects_vs_cs_1_3</docanchor>
    <docanchor file="setup_projects_vs_cs" title="1.4 Configure your project properties">setup_projects_vs_cs_1_4</docanchor>
    <docanchor file="setup_projects_vs_cs" title="2. Conditional Compilation Symbols">setup_projects_vs_conditional_compile_symbols</docanchor>
    <docanchor file="setup_projects_vs_cs" title="3. Pruning ALox">setup_projects_vs_cs_pruning</docanchor>
    <docanchor file="setup_projects_vs_cs" title="3.1 What is Pruning?">setup_projects_vs_cs_pruning_1</docanchor>
    <docanchor file="setup_projects_vs_cs" title="3.1 How Pruning in ALox for C# works">setup_projects_vs_cs_pruning_2</docanchor>
    <docanchor file="setup_projects_vs_cs" title="3.1 Mission accomplished: Perfect Auto Pruning with ALox!">setup_projects_vs_cs_pruning_3</docanchor>
  </compound>
  <compound kind="namespace">
    <name>com</name>
    <filename>namespacecom.html</filename>
    <namespace>com::aworx</namespace>
  </compound>
  <compound kind="namespace">
    <name>com::aworx</name>
    <filename>namespacecom_1_1aworx.html</filename>
    <namespace>com::aworx::lox</namespace>
    <namespace>com::aworx::util</namespace>
  </compound>
  <compound kind="namespace">
    <name>com::aworx::lox</name>
    <filename>namespacecom_1_1aworx_1_1lox.html</filename>
    <namespace>com::aworx::lox::core</namespace>
    <namespace>com::aworx::lox::loggers</namespace>
    <class kind="class">com::aworx::lox::Log</class>
    <class kind="class">com::aworx::lox::LogTools</class>
    <class kind="class">com::aworx::lox::Lox</class>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log</name>
    <filename>classcom_1_1aworx_1_1lox_1_1Log.html</filename>
    <class kind="class">com::aworx::lox::Log::ALoxAWXUErrorHandler</class>
    <member kind="enumeration">
      <type></type>
      <name>DomainLevel</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Off</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fad15305d7a4e34e02489c74a5ef542f36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Errors</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fa5ef0c737746fae2ca90e66c39333f8f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>WarningsAndErrors</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fac97dda1f78d8fbb5a4f489ab1b51ff4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>InfoWarningsAndErrors</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fa377a1a5cb4724b1fb5993b36459d6570</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>All</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fab1c94ca2fbc3e78fc30069c8d0f01680</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Inherit</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a10ac165398697ce1d642d739cc3b170fac49484faf79e2388b580e49444d6ac11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5ad4a9fa383ab700c5bdd6f31cf7df0faf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5a4059b0251f66a18cb56f544728796875</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5a0eaadb4fcb48a0a0ed7bc9868be9fbaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a221b779e6bb7b8d40677d7642bfefac5a902b0d55fddef6f8d651fe1035b7d4bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Scope</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>None</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6a6adf97f83acf6453d4a6a4b1070f3754</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SourceFile</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6aad9c9150641994c9937a1bce42884a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>Method</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaecc53892786f2fa11e682f633af84c6a4c3880bb027f159e801041b1021e88e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Logger</type>
      <name>GetLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a81583fc2028aa1ccb925afaa0d63a224</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Reset</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a77ad624cc83a2a71aa4d5ad991d811d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>AddLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a48c449476d1fd8d89894d79a3083c47c</anchor>
      <arglist>(Logger logger, DomainLevel internalDomainLevel=DomainLevel.WarningsAndErrors,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>RemoveLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a853059201cdf7a94f49da10501e6d013</anchor>
      <arglist>(String loggerFilter=null)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetConsumableSourcePathPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8ca190d37d5b67e60b1c1506adc25e7b</anchor>
      <arglist>(String cspp,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>RegDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ad82a9166e7179f88e1c66c76afc32d35</anchor>
      <arglist>(String domain, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aa581535137279580a7e3236132275700</anchor>
      <arglist>(String domain, DomainLevel domainLevel, bool recursive=true, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ab49f2ffa2ac6ff60e03a7042461d894e</anchor>
      <arglist>(bool disabled, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ad0aaaed2c1edfeac7c2005502c48cc2d</anchor>
      <arglist>(DateTime?startTime=null, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>MapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ac412e05b0ef291166764d99bf255e550</anchor>
      <arglist>(String threadName, int id=-1,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a743ee0a0ddfa6e6cdcabb4695a548d81</anchor>
      <arglist>(Object marker, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a1a6524586457c57f00bd4f6fb309512a</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>LogConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ab0a8ad96173757285e9ab5e832d6bee9</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8646e072715a76d18a5a581a7a031ca7</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8275e68d3beb1580971d608f071c95d9</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8ece5802704a024dcea32c5c1308fe59</anchor>
      <arglist>(String msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8bb22c0b2c0703060eb5db8c638a4373</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a4b9e2f35dadea676f0bebe0a80c9f168</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a0b68b2cc760d84b02b5ad96ff45f25ed</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3a18674e47f0eb74c55eb7f8c44508dd</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ac45da91372538ac41ae599081dcdd65b</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aec98b95865d8af15195eed1c3b86f7f7</anchor>
      <arglist>(bool trueOrLog, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a18185a2d919187e0821d2a5dd7b2f92a</anchor>
      <arglist>(bool trueOrLog, String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3e7e792f0cb6840a49f4730c49aa3a4e</anchor>
      <arglist>(bool doLog, String domain, Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a587ecc8edd693a30830a3e22004c5a41</anchor>
      <arglist>(String domain, Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aab174cba345afa40506456c68580bb9c</anchor>
      <arglist>(Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static Lox</type>
      <name>LOX</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9291aece8829db000d6508daa16f67fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log::ALoxAWXUErrorHandler</name>
    <filename>classcom_1_1aworx_1_1lox_1_1Log_1_1ALoxAWXUErrorHandler.html</filename>
    <base>com::aworx::util::AWXUErrorHandler</base>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log_1_1ALoxAWXUErrorHandler.html</anchorfile>
      <anchor>a143121b7aa73c57aed99b0d13b5b80d3</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log_1_1ALoxAWXUErrorHandler.html</anchorfile>
      <anchor>a054c4b2d956d70587cfc45b54d09d1c9</anchor>
      <arglist>(Object msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::LogTools</name>
    <filename>classcom_1_1aworx_1_1lox_1_1LogTools.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a3a172ec6285dc3cdd47f147801dbbc32</anchor>
      <arglist>(String domain, Log.Level level, Exception e, String headline=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a64f87b393288e74399e1be5a18339ab0</anchor>
      <arglist>(Log.Level level, Exception e, String headline=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a53d84203c6717bcc67dd5c2a16d0cd32</anchor>
      <arglist>(Exception e, String headline=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a8c29adc9ba464af7c76dc25fd65f46a1</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion, String headline=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a7d89783dae96a8d7d71d937c2fbe7716</anchor>
      <arglist>(Log.Level level, Object o, int maxRecursion, String headline=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>adad74abbe21748cf5db7fb9811e19327</anchor>
      <arglist>(String domain, Log.Level level, XDocument xDocument, String headLine=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa97d1f2fa1006ac9dd2a7913a8309642</anchor>
      <arglist>(Log.Level level, XDocument xDocument, String headLine, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a0ff47e9ff0259463e827d31a8f6b00ca</anchor>
      <arglist>(String domain, Log.Level level, XElement xElement, String headLine=null, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>XML</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>af33f2251927a308f5252b4fc4fc68a18</anchor>
      <arglist>(Log.Level level, XElement xElement, String headLine, int indent=0, Lox lox=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtExcNull</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa8eaf49e43df1021c2d606be3fa2a105</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstLineNoPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a2e36df8103a33a2a906ee197a2dea443</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstLineNoPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a965ccdf58230d74195cceaed3fe40539</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstNull</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>adb9f89054eac0cbc3a6baf24c662f464</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstRecursionLimit</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a4fae788c8c8cd1749d55f7336eae2abf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstCycRefPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ad56bd642c748ee1addec1188df481eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIEnumerablePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aed0d6d14c822f1c1955ef11ae01fb9fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIEnumerablePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ab8b8bddb1a3fa62c73e753171cd49dcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstArrayPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aff77a89c541f9f77d08d78b65b9f775b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstArrayPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a589175368d4447e9e299a6772c2de1d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstCycRefPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ab09e0f17b2e136eab6dd0b8bebb2900a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstNoAccessToValue</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa4ce00beb85593e9964f9036a2a57933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstTypePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a961fca96721ab094e840bd62fd81a30b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstTypePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>acfe76f019ad1076ce73f8d67f292e228</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>FmtInstIndent</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a45adaa09fbb02529d24d98b541412995</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a03b1a235ac32902423d66ee923c94613</anchor>
      <arglist>(Exception e, String headline, int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instMain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a670b8642fe3a9f4737c9e398c2050006</anchor>
      <arglist>(Object o, int maxRecursion, String headLine)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instRecursive</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac03b6467ac0863a99a0b52afa782fe8f</anchor>
      <arglist>(Object inst, int maxRecursion, int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instNewLine</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a7f90bc448f889a4afd2a0d051508a8e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instBeginLine</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1a60fd445cafbf21819717c2b817af7f</anchor>
      <arglist>(int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instTabStop</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a7ea8777191d09d2b9e64f2c3384ebaf8</anchor>
      <arglist>(int tabStop)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>instTabTypeAndNewLine</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa64ceea3ae9af0dc33366784f0dfe0e0</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>xml</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1bf3553c854f8a7d0b938a5eeb7bc79c</anchor>
      <arglist>(XDocument xDocument, String headLine)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>xmlElement</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ab871223d442ff953c52fb281aaf84ea6</anchor>
      <arglist>(XElement xe, String headLine, int indent)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>instValueTabStop</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac586537acea9202be95f5cf793324550</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>instTypeTabStop</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1cfe4bbb4fae0ca0db99d3fe768ffa64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static MString</type>
      <name>toolBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ab2b7fd952d42f838905b7ce560f1e68e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static uint</type>
      <name>instLineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a4ef97f200cc58b6c0e22c895ddf7c76b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static Dictionary&lt; Object, UInt32 &gt;</type>
      <name>instObject2LineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a6e81430abaff658ea6e14fbbf242c1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>instLineBeginIdx</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aaa958e582bb109b5cf63121eb10a194a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Lox</name>
    <filename>classcom_1_1aworx_1_1lox_1_1Lox.html</filename>
    <member kind="function">
      <type>Logger</type>
      <name>GetLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a74ba68166dee3359939d25f87e648cbe</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a360d4bab0de9498716bfe3328e3aca48</anchor>
      <arglist>(Logger logger, Log.DomainLevel internalDomainLevel=Log.DomainLevel.WarningsAndErrors,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af07a94c1e4cf8e5d66b6852e04b08624</anchor>
      <arglist>(String loggerFilter=null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetConsumableSourcePathPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2f942041d5724873ea6daa9fdd86563f</anchor>
      <arglist>(String cspp,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RegDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a87c7c940b64590f9c757a918cff85eb8</anchor>
      <arglist>(String domain, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1d80a2ac703e5137a8649bb6e51cbb92</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, bool recursive=true, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a86ab9bdfd6b89e7a20ab2508bf00fc9e</anchor>
      <arglist>(bool disabled, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad5a5538441906cd183b14593e4a6525d</anchor>
      <arglist>(DateTime?startTime=null, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a92fa582c87c957cddbd0fd3bd50144d7</anchor>
      <arglist>(String threadName, int id=-1,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acf90c6eb026b11c9f2bc528e78c34832</anchor>
      <arglist>(Object marker, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af64d481903ed65f97ee4e7a8df7892ee</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LogConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1880766f95ae58955e908fe2e54fb321</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8705225063ecca80f30b87035bc11bdd</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a94bc46def19c21f0607b7d43cc2e765f</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4d68c7953af41794595495cefe5daec6</anchor>
      <arglist>(String msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac3322de1c1e20d3b3cc884c9ebe08045</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa329f2e9f7592e041c96a88ba7e93ce7</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4ae89f59de79d1054aa9acd848c7f939</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aa50a0ec4f97b5c06b65c9f70f0edbda2</anchor>
      <arglist>(Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>abb1993ef714a4c7516e813a343ca8eab</anchor>
      <arglist>(String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a33684b7e69af6726dbfaf0105e9a128a</anchor>
      <arglist>(bool trueOrLog, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af2b9896d54cc46e902a105da26176da5</anchor>
      <arglist>(bool trueOrLog, String domain, Object msg, int indent=0,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1412969c1414fbd571289d5265c21139</anchor>
      <arglist>(bool doLog, String domain, Log.Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8b98598ed96bf177d5fb1528fd70baa6</anchor>
      <arglist>(String domain, Log.Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>af35754849cbc87fdf297951d3fb379a3</anchor>
      <arglist>(Log.Level level, Object msgObject, int indent=0, String loggerFilter=null,[CallerFilePath] String csf=&quot;&quot;,[CallerLineNumber] int cln=0,[CallerMemberName] String cmn=&quot;&quot;)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>CntLogCalls</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2c80e5630abe5d5042ddb4b85c0c3562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ThreadLock</type>
      <name>Lock</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae10600cb6914f091adfbbde00bbfdcd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>InternalDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aed8c5ed6af267304f7aae60589a589c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Dictionary&lt; int, String &gt;</type>
      <name>ThreadDictionary</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9449abe368a2e9a9694a52437b02348b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly String</type>
      <name>Version</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1a33f478950a66f73f765da03857e91a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>saveAndSet</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a27b95a1106d1211289720ecf01db9e81</anchor>
      <arglist>(String csf, int cln, String cmn, bool getResDomain, String domain)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>internalLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5f28dc7cc5e8367ae94c0bd9ea180080</anchor>
      <arglist>(Log.Level level, MString msg)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>logConfigDomainRecursive</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a117ffffe6a67d18964e60d277a17d71c</anchor>
      <arglist>(LogDomain domain, int indent, String domPath, MString buf)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>List&lt; Logger &gt;</type>
      <name>loggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0078398c1e76599b6e0852ffe2937af9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Dictionary&lt; MString, MString &gt;</type>
      <name>defaultDomains</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad8161c647b7b5d806611c07ad2357e75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Dictionary&lt; MString, Object &gt;</type>
      <name>markers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afce4382b76f3d1cb8c951f1c6f6c11d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CallerInfo</type>
      <name>caller</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a661374595beb4ef6cdcd0417c8c47f0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>resDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a53cc89ae4402b9385259e06c5fc0a546</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>tempDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab1e2c7dee8db47cd16ca92fb3a7ae904</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>tempMS</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a0d99bb961369853273a8f67384b2c3c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>simpleWildcardFilter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a904bdd5c05e9810befbf6cbb43201923</anchor>
      <arglist>(Logger logger, string loggerFilter)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>com::aworx::lox::core</name>
    <filename>namespacecom_1_1aworx_1_1lox_1_1core.html</filename>
    <class kind="class">com::aworx::lox::core::CallerInfo</class>
    <class kind="class">com::aworx::lox::core::LogDomain</class>
    <class kind="class">com::aworx::lox::core::Logger</class>
    <class kind="class">com::aworx::lox::core::TextLogger</class>
    <class kind="class">com::aworx::lox::core::TextLoggerLineFormatter</class>
    <class kind="class">com::aworx::lox::core::TextLoggerObjectConverter</class>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::CallerInfo</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a57555728289b3e873ec939e3a20bc084</anchor>
      <arglist>(String callerSourceFileName, int callerLineNumber, String callerMemberName, Dictionary&lt; int, String &gt; threadDictionary)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>GetConsumableSourcePathPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>aaa7c961bfb7548a03031f4954cc17893</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MethodName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>aa8885cdf3586b80bd9905b60bf9529d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>SourceFileName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a2728e8e0ff2895fccb263584a374f97e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>LineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>abc72cc909922c33908e48159b106efa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>TimeStamp</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a094cd0d7c1114ab3989a4f3992f36dd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>ThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a826e257cf75401d69ae22837d578d457</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ThreadID</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a762284c02117c5070871b37484d70b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>ConsumableSourcePathPrefixString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ad5e8a7d9f2c872ab23a2332e6583d908</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::LogDomain</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</filename>
    <member kind="function">
      <type></type>
      <name>LogDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a17cbb6fb2ea129b0bd1d08254c3ba0ce</anchor>
      <arglist>(LogDomain parent, MString name)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Log.DomainLevel</type>
      <name>GetLevel</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a6b35d5ba376191a0aa5b9ed52b8f05e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLevel</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a6b11c04355e05570006df5aa449f62db</anchor>
      <arglist>(Log.DomainLevel level, bool recursive)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsActive</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a729bb906d248e54d997101d8faf8e1c0</anchor>
      <arglist>(Log.Level level)</arglist>
    </member>
    <member kind="function">
      <type>LogDomain</type>
      <name>FindOrCreate</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>abaf3a8692758ecaaa7381ad97b1b2cd5</anchor>
      <arglist>(MString domainPath, bool createIfNotExistant)</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>Name</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a3328db10c8e026e2171ea6061e020bc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LogDomain</type>
      <name>Parent</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>adf9d6758ee68e2a2a72dcb13c400bc1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; LogDomain &gt;</type>
      <name>SubDomains</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a376c0d4a4807be43e52cd1ad25a09ace</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>DomainSeparatorChars</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>afb75ecb5fef3bcf61597efd190ca0114</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>LogDomain</type>
      <name>findOrCreateInternal</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a4bdfd1d3df4067bb3896bf0efd60d9d2</anchor>
      <arglist>(MString domainPath, int dpStartIdx, bool createIfNotExistant)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Log.DomainLevel</type>
      <name>level</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a1a9f7325c08dd31ecae733ac275a3791</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::Logger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</filename>
    <member kind="function">
      <type>LogDomain</type>
      <name>CreateDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a5e24dffed44ef22b05a1491799053a31</anchor>
      <arglist>(MString domainPath)</arglist>
    </member>
    <member kind="function">
      <type>LogDomain</type>
      <name>FindDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a8ecd4ffbcef16d4aac7e29db3afa92b3</anchor>
      <arglist>(MString domainPath)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a131d672c77b9abb0fc4a5a3d23e66ccf</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>Name</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a934fa09ba291a97f43720640e4d83f25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint</type>
      <name>CntLogs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a7859d287690c28acd561a307d23679bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>TimeOfCreation</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ae8f7ba7f8c77976fc229f260ba44717b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>TimeOfLastLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a1c081cd8e1cc313de5c7e64d27e975be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>IsDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>abada4ef55f947626e50d53b5cb8a31cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LogDomain</type>
      <name>RootDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a46ee964173efe1f2b01121d11d91f597</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Logger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a42c27444187c8bea77c2b065a2ec183e</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>aae6d2874b82786019b36b4ac8ca9c647</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>tempDomainPath</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>af717d7b13f31ce14d19c3b24707f20f6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</filename>
    <base>com::aworx::lox::core::Logger</base>
    <member kind="variable">
      <type>TextLoggerObjectConverter</type>
      <name>ObjectConverter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a4659dec01dc35beaed57a1d13fb3a60c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TextLoggerLineFormatter</type>
      <name>LineFormatter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>afd6c2389bad25caa4a5b201ef86e4608</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>List&lt; String &gt;</type>
      <name>Replacements</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a26fadf1d9e7165180f210156799fdd22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MultiLineMsgMode</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a95ea94dee572eaac760d028ddcf3cf65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MultiLineDelimiter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aba58580b1670dbfb1caf21f47d0d53de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>MultiLineDelimiterRepl</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a957ed4611b87bdf193ad2c3f848a451c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLineMsgHeadline</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>ab3423baaf4b67d0e7cfa757203aaf872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLinePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a74da3f13d354d7b4b31aa8fefa7e7115</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtMultiLinePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>ae0ab1101cb40bf899cb8fb9ef26fb29f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>TextLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a922bc82585360a89568276c894e3631c</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a1300bd920d9f44ebc751480932ed2585</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>af95411fc4b7545a2f5c660bc51159245</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>logBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aaf37e693e36d895e18bcc1f6037f5d9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLoggerLineFormatter</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>WriteMetaInfo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a35cf27a31e5d5ff36ea1453d6e9657e1</anchor>
      <arglist>(Logger logger, MString buf, MString domain, Log.Level level, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>Format</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>af529892abacd85c83ff6a646962fe28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int[]</type>
      <name>AutoTabs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ac8dabdb1b182d956f350c910643c9ece</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>IndentString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a64f513c6899c4fbfe76e5bbd8d5f73ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelError</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a56bad526d2a9b0e8fac8774a8e81079d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelWarning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a796b4686ca6cd82427e5026fa7a13656</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelInfo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a642a10ae2076aa7365fd8ac920ee9ff9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>LogLevelVerbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a3948fa2550cec5c1b96c46eaef7d1110</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>DateFormat</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a73be91892f104afd96a32ab547e2cf45</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeOfDayFormat</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ae3289ae62c777551c12429268fea0988</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeElapsedDays</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a37dc29c46601640c35ad51bc72b7042e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMicros</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>abcd9e4a9e53693daaa04567886a11deb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMillis</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a2ee9165164ad264d5880f633007629e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffSecs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a5045aad5b73717f73f7adce9823085cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffMins</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a1463b65c96abf24881c3c153ac0861bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffHours</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a1e9702f3330f62f91a66a8e545f48faa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>TimeDiffDays</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a61ceb433642d627c2e1efce90762bb97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>LogNumberMinDigits</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a72c44479ec3d128c1208b49e4b8ede08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>AutoGrowThreadNameLength</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a96f24fc7ddd1a84a0889ef8231511034</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>AutoGrowDomainNameLength</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a0585150ce640c5cc15f70fb566426497</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>processVariable</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a7c695e7e6cc32592b96209dc136446b1</anchor>
      <arglist>(Logger logger, MString domain, Log.Level level, CallerInfo caller, MString buf, char[] formatString, int formatStringIdx)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeTimeDiff</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>acb45f022e4cabaceb8efa4205264b06d</anchor>
      <arglist>(MString buf, long diffMicros)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>StringBuilder</type>
      <name>formatSB</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a85c8d54f584a622009048d0536f6160f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>detectDateFormatChanges</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ab621f55d7a1a3c04988089afeea88208</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>dateFormatString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a25d0a90e758eef351048c526b82ce060</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>detectTimeOfDayFormatChanges</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ae2eb584a3f8074d9b14f56741ff2b628</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>timeOfDayFormatString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ad20e54054ee94793667818d16868ddcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>autoTabNo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a6baac125a9d8081f25ff930d5d90edbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>DateTime</type>
      <name>callerDateTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a321e35a5312d2e9709fd591b7e5d54a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLoggerObjectConverter</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual MString</type>
      <name>ConvertObject</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</anchorfile>
      <anchor>ab8190be4513726c7c2c49276ab2ed3fa</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>FmtNullObject</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</anchorfile>
      <anchor>ac281d117b6e931783195f52f70bfa5b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>buffer</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</anchorfile>
      <anchor>abb05cbb40d212c431ab82b3718ccfa04</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>com::aworx::lox::loggers</name>
    <filename>namespacecom_1_1aworx_1_1lox_1_1loggers.html</filename>
    <class kind="class">com::aworx::lox::loggers::ConsoleLogger</class>
    <class kind="class">com::aworx::lox::loggers::MemoryLogger</class>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::loggers::ConsoleLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</filename>
    <base>com::aworx::lox::core::TextLogger</base>
    <member kind="function">
      <type></type>
      <name>ConsoleLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>ab424eff3af16ee9c77c6a57547d1753d</anchor>
      <arglist>(String name=&quot;CONSOLE&quot;)</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>EnableVSDebugConsole</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>aa8fbde711ff2895904643515cd565a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>EnableAppConsole</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>afebe821fecca4fbd3778cb0227fd9a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>af8da5b301accf1a23758a98b88f222d0</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>consoleBuffer</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a13297cc2c876d3e5667e2c567efbb377</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::loggers::MemoryLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</filename>
    <base>com::aworx::lox::core::TextLogger</base>
    <member kind="function">
      <type></type>
      <name>MemoryLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a7c0c45d25777d6d8897a1144d560cb0e</anchor>
      <arglist>(String name=&quot;MEMORY&quot;)</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>Buffer</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a4c4401d5279509f8e691416e41478f8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>override void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>af8da5b301accf1a23758a98b88f222d0</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>com::aworx::util</name>
    <filename>namespacecom_1_1aworx_1_1util.html</filename>
    <class kind="interface">com::aworx::util::AWXUErrorHandler</class>
    <class kind="class">com::aworx::util::AWXU</class>
    <class kind="class">com::aworx::util::MString</class>
    <class kind="class">com::aworx::util::ThreadLock</class>
    <class kind="class">com::aworx::util::Ticker</class>
    <class kind="struct">com::aworx::util::TickTime</class>
  </compound>
  <compound kind="interface">
    <name>com::aworx::util::AWXUErrorHandler</name>
    <filename>interfacecom_1_1aworx_1_1util_1_1AWXUErrorHandler.html</filename>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>interfacecom_1_1aworx_1_1util_1_1AWXUErrorHandler.html</anchorfile>
      <anchor>a143121b7aa73c57aed99b0d13b5b80d3</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>interfacecom_1_1aworx_1_1util_1_1AWXUErrorHandler.html</anchorfile>
      <anchor>a054c4b2d956d70587cfc45b54d09d1c9</anchor>
      <arglist>(Object msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::AWXU</name>
    <filename>classcom_1_1aworx_1_1util_1_1AWXU.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Sleep</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1AWXU.html</anchorfile>
      <anchor>a3c3079a3bc112d999cfdb967f02875ec</anchor>
      <arglist>(int millisecs)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static AWXUErrorHandler</type>
      <name>errorHandler</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1AWXU.html</anchorfile>
      <anchor>a310f9753e567021a3074e649210d8c18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::MString</name>
    <filename>classcom_1_1aworx_1_1util_1_1MString.html</filename>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a677e5696d36925a2de6542b24769bad3</anchor>
      <arglist>(int size=1024)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ac2c6bb3b70df59497307419594375261</anchor>
      <arglist>(MString ms, int startIdx=0, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a5454bc7d31e76688e091b799f3e945c7</anchor>
      <arglist>(String s, int startIdx=0, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a03c01231cd81a0968dec95f6805a0176</anchor>
      <arglist>(StringBuilder sb, int startIdx=0, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Clear</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8cca8f037a58d8c902e5c62fdf268981</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a2b494452543a0937c2aa02e610dfd338</anchor>
      <arglist>(MString ms)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a520924c33e02c369a79bc3505d6b1bb9</anchor>
      <arglist>(MString ms, int startIdx, int msLen=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a255a3c5a6dde8a5bce0f51a045a80813</anchor>
      <arglist>(String s)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8db3b5f44d23f46dd59309a110841d1b</anchor>
      <arglist>(String s, int startIdx, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a60c5ff3d1af6da3e81fe56119377f800</anchor>
      <arglist>(StringBuilder sb)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a7dc5aa41678b73f5804ec1b495b75398</anchor>
      <arglist>(StringBuilder sb, int startIdx, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab21f5f86df669f0764c1e809968f36b3</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa74042969432bcba1ad07be703692a3d</anchor>
      <arglist>(char c, int qty)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ae3f1df70f14511e2196ab4ebd9df1d9b</anchor>
      <arglist>(MString ms, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa804784ef5abf7b2df579f6a9b8994a2</anchor>
      <arglist>(String s, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a0c6136699e7412180f3238ddcde5963f</anchor>
      <arglist>(StringBuilder sb, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1deadd1a0c9e01f3ffa2b762297bbafe</anchor>
      <arglist>(MString ms, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a184ddcabc8947e76d0129e51b800a00c</anchor>
      <arglist>(String s, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a40135beebc742845318f70ac5e0fcb05</anchor>
      <arglist>(StringBuilder sb, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ac49b2542c49346829b394546bcb88ccb</anchor>
      <arglist>(MString ms, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a5bc8655f7f7805b80cded28287e49e90</anchor>
      <arglist>(String s, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>AppendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a75db68195c39e6202687a00b048ab6f7</anchor>
      <arglist>(StringBuilder sb, int fieldSize, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ac7733a055bde0c69bc0889a23d0b9773</anchor>
      <arglist>(int i, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9dd94ce7f8ddc5d9c8ed9e9dff03c5fa</anchor>
      <arglist>(uint i, int minDigits=1)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a7c99caa08088a638cc06399a858fbeee</anchor>
      <arglist>(double d, int minDigitsBeforeDot, int digitsAfterDot)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>Tab</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>adf7a4fc76ea4d91409928eab07f47fb0</anchor>
      <arglist>(int tabSize, int tabReference=0, int minPad=1, char padChar= &apos; &apos;)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>NewLine</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a07dec05976504a20ae6efd7b3f326327</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ContainsAt</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a15774fb77e5efd8bfb44bc2dad2a9c40</anchor>
      <arglist>(String s, int pos, bool ignoreCase=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>StartsWith</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a333af236691b446f1c84a9b9d5275908</anchor>
      <arglist>(String s)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EndsWith</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1d79da29d0eb3a40d4d8bb0479a64c9a</anchor>
      <arglist>(String s)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>IndexOf</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa2710664520cb638ed2c7b9abd9bd737</anchor>
      <arglist>(String s, int startIdx=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Replace</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a0cc4cc73d0ea81d71ca3f8ce5968bdb0</anchor>
      <arglist>(String searchStr, String newStr, int startIdx=0, int maxReplacements=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CompareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a308cbb147b4dc0a8ed794f84cc711a7c</anchor>
      <arglist>(Object cmp, bool ignoreCase=false, int sStartIdx=0, int sLen=int.MaxValue, int startIdx=0, int len=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>ConvertCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a064324913d1c968daaa9fbd8014ccf6b</anchor>
      <arglist>(bool toUpper, int substrStart=0, int substrLength=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>ToString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aaf2616ca6994c68d4e2cfaf97a257ee2</anchor>
      <arglist>(int startIdx, int length=int.MaxValue)</arglist>
    </member>
    <member kind="function">
      <type>override int</type>
      <name>GetHashCode</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a77e1afa2b6dee1ed3640da81d7407b42</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override bool</type>
      <name>Equals</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa68c8f722eb155e6928f0f0200df28d2</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EnsureCapacity</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1f729f876453fd5421e70846f5da8e44</anchor>
      <arglist>(int minLen)</arglist>
    </member>
    <member kind="variable">
      <type>char[]</type>
      <name>Buffer</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a0668121df5dd78af062bdddc4abedc9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Length</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9fde862c8bc443d7a6872a487ec265a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Hash</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>afbe49f33f22436054a3e57f77cec849f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>adjustRangeAndTestIfEmpty</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a70dc2e03ea9a1abfd185447e170023fb</anchor>
      <arglist>(int referenceLen, ref int startIdx, ref int len)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::ThreadLock</name>
    <filename>classcom_1_1aworx_1_1util_1_1ThreadLock.html</filename>
    <member kind="function">
      <type></type>
      <name>ThreadLock</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>ac633439ece63e381762e30fc8599c1a9</anchor>
      <arglist>(bool recursiveMode=true, bool setUnsafeMode=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Aquire</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a00a94cc394ebd68410e938195a5c4849</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Release</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a94c93747c8daa99d65c2a04c6be0748c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUnsafe</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>ae8c3cd592757e0998048abf426d2412c</anchor>
      <arglist>(bool setUnsafe)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsUnsafe</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>abf2bccd9812728e715f73c27dac06614</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>UseAssertions</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a7b9819e5cf7944efedca64a67c5adbfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>WaitALoxWarningLimit</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a09b8fc043406437eb58d55168c137af1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>RecursionWarningThreshold</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a2b35011c911bf00d065eba8af27620a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>recursiveMode</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a1ea15561e57893d4e2a4a16a366cdb68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>lockCount</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a7f41e1e3070abd18f7cdfdb9a95b3d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Thread</type>
      <name>owner</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a194df7b1414f1a1181802f255faff967</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Object</type>
      <name>mutex</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a4cc9273ae9737bab384e14ef7d4b5c7a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::Ticker</name>
    <filename>classcom_1_1aworx_1_1util_1_1Ticker.html</filename>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>Now</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ae68dc4a5a8a0d674950150fde5739e5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>Add</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a2ceae5c36e7ba0e6ae7851dd21347afd</anchor>
      <arglist>(long ticks, int days, int hours, int minutes, int seconds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>ToMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a1b8d0141a03d582c7a3854804d6792ef</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>ToMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a2150323c4282cd75791ceaa5ebda0a93</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>ToNanos</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a5ec078aefbcdf96e4394c90919ac7a21</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>FromMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ab80965005ac6ffa5c7b676f60abf9bc1</anchor>
      <arglist>(long millis)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>FromMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>af0da9284c84b48770e00a3c49fcec905</anchor>
      <arglist>(long micros)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>FromNanos</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a43b1f0d145027ca85981416e3063b4c6</anchor>
      <arglist>(long nanos)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>ToEpochMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a7bdeea953ac7baf70f9a23bbb9325226</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>FromEpochMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a45d3916fd9a582e8c6f724ad818882bb</anchor>
      <arglist>(long epochMillis)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>ToDotNetDateTimeTicks</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a64ee953996464063037bb75ffe9b1ca8</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>FromDotNetDateTime</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a4be41b088fb34facde4f0220237bf7a6</anchor>
      <arglist>(DateTime dateTime)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static DateTime</type>
      <name>ToDotNetDateTime</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ac12ba2167a5b57acd90ddbccbd9ca39b</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static readonly long</type>
      <name>InternalFrequency</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ae62f17585d560a30016408f33ace2912</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly long</type>
      <name>creationTimeTicks</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a4ca94541f535289b6d50b0eaf9469c11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly long</type>
      <name>dateTimeTicks19700101</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a9fece05bed075816cf25a02b44f72b57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly Stopwatch</type>
      <name>creationTimeStopWatch</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a58d43e7232052f1601bc2914babafb17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static readonly double</type>
      <name>convSWToDT</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ad91e3ebd169964f5636d6d006cd445fb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>com::aworx::util::TickTime</name>
    <filename>structcom_1_1aworx_1_1util_1_1TickTime.html</filename>
    <member kind="function">
      <type></type>
      <name>TickTime</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a9022faaf91a176798aee31f833e37e86</anchor>
      <arglist>(long otherTicks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickTime</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a172fa05048e619c3b735cc621440fcfb</anchor>
      <arglist>(TickTime copy)</arglist>
    </member>
    <member kind="function">
      <type>override String</type>
      <name>ToString</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a012fbb0f39e57c0a44ec83dd408fcda3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>Get</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a348b9c9e3aab0c6071a141554ee8d729</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTo</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>adaff9e91bf2bf109eb4238a7c6fb9ffe</anchor>
      <arglist>(long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetToNow</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>aaa9eaa4f0de081c6f34ff9557cc04e62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>aa71d36872f416feaa853788a7a7a7ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>Age</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a8e3b061c8b57d726eb28ab802ba726a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>AgeInMillis</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ad21421ac0f41df34b00002b86d883907</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>AgeInMicros</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a58635ae65c671f1a689a6cdca1d03b3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>Span</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a64970dbde62343cdb925ad205a6843c5</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>SpanInMillis</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a5a92e041a09e093bd25a65cc79b804f4</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>SpanInMicros</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a3595f896b2be83effc753c5ba84d70d3</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>Measure</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ab716e107dfc0bc62866ea53ebf9412a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMeasureCnt</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a5118e8ba97392f0a502bb6071186e10f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>GetCumulatedTicks</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a52a71158995d35b07a879b442c315487</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>GetAverageTicks</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a1fa5274db867ca0238223d0465cc231b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>GetAverageMillis</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a7f8b18091f0a38864a5ae2d90db80549</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverageHertz</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ab9c98526d11ded6856ba63b379255411</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>DateTime</type>
      <name>ToDotNetDateTime</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a1ed0e80fff0f351f58bf0b310320c2c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FromDotNetDateTimee</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a906085461ef493a2183d9b319e30db02</anchor>
      <arglist>(DateTime dotNetDateTime)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long</type>
      <name>ticks</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>af0b811e653c51fb98ab202e920af2afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long</type>
      <name>sum</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ad21ee1949296449cb2806778a7fc94de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>cntMeasures</name>
      <anchorfile>structcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a388aae1c6d770ab01965f0d01b2fdc1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>core</name>
    <path>I:/Dev/A-Worx/ALox/src/cs.alox/core/</path>
    <filename>dir_50600f49ab438504a80143b55c7c2004.html</filename>
    <file>CallerInfo.cs</file>
    <file>LogDomain.cs</file>
    <file>Logger.cs</file>
    <file>TextLogger.cs</file>
    <file>TextLoggerLineFormatter.cs</file>
    <file>TextLoggerObjectConverter.cs</file>
  </compound>
  <compound kind="dir">
    <name>cs.alox</name>
    <path>I:/Dev/A-Worx/ALox/src/cs.alox/</path>
    <filename>dir_fc6ab29db87cee32fc2f048db43c2136.html</filename>
    <dir>core</dir>
    <dir>loggers</dir>
    <file>Log.cs</file>
    <file>LogTools.cs</file>
    <file>Lox.cs</file>
  </compound>
  <compound kind="dir">
    <name>cs.aworx.util</name>
    <path>I:/Dev/A-Worx/ALox/src/cs.aworx.util/</path>
    <filename>dir_f156551c84c5444109bd2fea9878b405.html</filename>
    <file>AWXU.cs</file>
    <file>MString.cs</file>
    <file>ThreadLock.cs</file>
    <file>Ticker.cs</file>
  </compound>
  <compound kind="dir">
    <name>loggers</name>
    <path>I:/Dev/A-Worx/ALox/src/cs.alox/loggers/</path>
    <filename>dir_cf285cfc70250f5bcc2c291ec3c5dd43.html</filename>
    <file>ConsoleLogger.cs</file>
    <file>MemoryLogger.cs</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>C# Reference</title>
    <filename>index</filename>
  </compound>
</tagfile>
