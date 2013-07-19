<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>setup_projects_java</name>
    <title>Setup Eclipse for Java Projects</title>
    <filename>setup_projects_java</filename>
  </compound>
  <compound kind="page">
    <name>tutorial_java</name>
    <title>ALox for Java Tutorial</title>
    <filename>tutorial_java</filename>
    <docanchor file="tutorial_java" title="1. Hello ALox">tutjava_hello_alox</docanchor>
    <docanchor file="tutorial_java" title="1.1 Create a tutorial project or equip your current project with ALox">tutjava_createproject</docanchor>
    <docanchor file="tutorial_java" title="1.2. Create an instance of class &quot;ConsoleLogger&quot;">tutjava_ha1</docanchor>
    <docanchor file="tutorial_java" title="1.3. Add code to create and set a *log domain*">tutjava_ha_3</docanchor>
    <docanchor file="tutorial_java" title="1.4. Add log code">tutjava_ha_4</docanchor>
    <docanchor file="tutorial_java" title="1.5. Run your application">tutjava_ha_5</docanchor>
    <docanchor file="tutorial_java" title="2. Log levels and log domains">tutjava_llld</docanchor>
    <docanchor file="tutorial_java" title="2.1. Log code with different log levels">tutjava_llld_1</docanchor>
    <docanchor file="tutorial_java" title="2.2. Default domains">tutjava_llld_2</docanchor>
    <docanchor file="tutorial_java" title="2.3. Where to place ALox log code">tutjava_llld_3</docanchor>
    <docanchor file="tutorial_java" title="3. Some more Details">tutjava_more</docanchor>
    <docanchor file="tutorial_java" title="3.1 Stop reading here?">tutjava_more_1</docanchor>
    <docanchor file="tutorial_java" title="3.2 Conditional logging">tutjava_more_2</docanchor>
    <docanchor file="tutorial_java" title="3.3 LogTools: Log complex things easily">tutjava_more_3</docanchor>
    <docanchor file="tutorial_java" title="3.4 Indentation">tutjava_more_4</docanchor>
    <docanchor file="tutorial_java" title="3.5 Separating domain log levels in different loggers">tutjava_more_5</docanchor>
    <docanchor file="tutorial_java" title="3.6 ALox configuration and internal log messages">tutjava_more_6</docanchor>
    <docanchor file="tutorial_java" title="Further reading">tutjava_end</docanchor>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log</name>
    <filename>classcom_1_1aworx_1_1lox_1_1Log.html</filename>
    <class kind="enum">com::aworx::lox::Log::DomainLevel</class>
    <class kind="enum">com::aworx::lox::Log::Level</class>
    <class kind="enum">com::aworx::lox::Log::Scope</class>
    <member kind="function" static="yes">
      <type>static Logger</type>
      <name>getLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ac5188fd3597ba8f1821512f2e4453279</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>reset</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ab9d3f06dc4ef871fad50465095b5ea32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>addLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3327fc90660ebcb1cd8fd586536f5075</anchor>
      <arglist>(Logger logger)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>addLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a388b0b1dc9bfb04827e14b665dc26d28</anchor>
      <arglist>(Logger logger, Log.DomainLevel internalDomainLevel)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>removeLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af3d8e02c050826606c3e5b868deaaadd</anchor>
      <arglist>(String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>removeLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6804f40fbfc5683660ab0e4b3fcda298</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>regDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9e2d6bea9756b5764192c7be262633f1</anchor>
      <arglist>(String domain, Log.Scope scope)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a275bf5c822b593026a59279c2541a7cf</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, boolean recursive, String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3925268e62669f8ad67926a4d1b9fc30</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, boolean recursive)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a43fefb4b6e7eb349e51ba6267e2b07c5</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8be004629a67a8a263bc67918960c0b5</anchor>
      <arglist>(boolean disabled, String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a2e71ba1228c66d0956021f309bb77a63</anchor>
      <arglist>(boolean disabled)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>afddd20932f60d5ca1a4b40b559b7541f</anchor>
      <arglist>(Date startTime, String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a303216ca1c42817f4e38af0d1d1bef2c</anchor>
      <arglist>(Date startTime)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a39d73e995f7b61be1c9569481cbb1f2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>mapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a27ee41504fb6fa09f85be146153f63aa</anchor>
      <arglist>(String threadName, long id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>mapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aa903f41f5afd5721bf51364f3e43990b</anchor>
      <arglist>(String threadName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abc283df31cdf12ac52f8b1d261cccb9f</anchor>
      <arglist>(Object marker, Log.Scope scope)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>getMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9f46fb193ce5ef1c300ab11e770c2995</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>logConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a3d500fb540ea7d731003c91292a742cc</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>logConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a01a959146336e7f4211c1e2b788dda29</anchor>
      <arglist>(String domain, Log.Level level, String headLine)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>af3057efb28c59cca2a83abf0fc30c757</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aaf61c77dd78e6c9cfdae2ef45fec0747</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ae4a44a2b27bf655c541e1540e3a69132</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a721dadbbd6d493d62026fcf9a1ef5cde</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a708d83da58cf7eac55373101ed7fca02</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>acbf90a8c4639c26ee49091424a6b5ffb</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a907fbc10c60826cf5313876cb0c26d87</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a72ac623f948b57fb5238cba3d84088ae</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aedf486a4ad185f3affdef48fbb4c8262</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a6124ce1aa80c6dd14dfb6bbe32d5a41d</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9663b644aea091e0b98c2866e8c2e042</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a47ade1ce84e1f20bb16df3c74ac18e09</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>aa2e53c0784cea0a017e3338cd05836fe</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a28b11303d9a15e0d5684f712b6e83233</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a0ab444cbbf94592fc37f50c90a4e231f</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a5cf4eecdefd926fb4164e214ddd7c081</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ab802716eb51a321322610cdc31cd9b52</anchor>
      <arglist>(boolean trueOrLog, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a08f149f29b5d9b1516a7ca471e8150b3</anchor>
      <arglist>(boolean trueOrLog, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a7241c02d2c81a7a069557add2e7c75ce</anchor>
      <arglist>(boolean trueOrLog, String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ace80ea65c976c798d5660500b9fe574d</anchor>
      <arglist>(boolean trueOrLog, String domain, Object msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>adc661f4ad4b9a8a4e91f9447d702e754</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject, int indent, String loggerFilter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a8f85a19484c30bbd038b1f0e420df74a</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a12f510ef2506a53519d43768f989a829</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abd4a287a5c7699d03815f0a88be96cfc</anchor>
      <arglist>(String domain, Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>abd98bc9da70a9206bf6ab7267e995484</anchor>
      <arglist>(Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>ab54acd82ba516135608daa1caa1c6da0</anchor>
      <arglist>(Log.Level level, Object msgObject, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a459b3d136e4526487d4bc67bd4b49c11</anchor>
      <arglist>(Log.Level level, Object msgObject, int indent, String loggerFilter)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static Lox</type>
      <name>LOX</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a9291aece8829db000d6508daa16f67fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="package" static="yes">
      <type></type>
      <name>[static initializer]</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Log.html</anchorfile>
      <anchor>a2e87c5ede6b7235170d287cd2e254454</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log::DomainLevel</name>
    <filename>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</filename>
    <member kind="variable">
      <type></type>
      <name>OFF</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>aba437f58ad654d395b18d209a1a8c21c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>ERRORS</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>a622ccac4bed4b5ffcfd1acea83629286</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>WARNINGS_AND_ERRORS</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>a2e93b8db1cedcf3815016fe352b1b2f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>INFO_WARNINGS_AND_ERRORS</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>a9bbe14daf8eaa39934d9381b03eda2b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>ALL</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>aaff03f45544854747fa5e7821e84252e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>INHERIT</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1DomainLevel.html</anchorfile>
      <anchor>a8771f4952654026ffa7275448f8d7f76</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log::Level</name>
    <filename>enumcom_1_1aworx_1_1lox_1_1Log_1_1Level.html</filename>
    <member kind="variable">
      <type></type>
      <name>VERBOSE</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Level.html</anchorfile>
      <anchor>a03169c2c7e2ff706233c78422b0daf3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>INFO</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Level.html</anchorfile>
      <anchor>ab1764b91c3b44a5988564bbfe1d6e352</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>WARNING</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Level.html</anchorfile>
      <anchor>a1dfc73ab73898d3f4f348d462a5d126a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>ERROR</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Level.html</anchorfile>
      <anchor>a9eaada089c4de774cfc8b7aea4b9379a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Log::Scope</name>
    <filename>enumcom_1_1aworx_1_1lox_1_1Log_1_1Scope.html</filename>
    <member kind="variable">
      <type></type>
      <name>NONE</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Scope.html</anchorfile>
      <anchor>a899caa602e4fff675b17cdbab33607ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>PACKAGE</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Scope.html</anchorfile>
      <anchor>a79a5eb01dd38711dea806b59b432475e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>CLASS</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Scope.html</anchorfile>
      <anchor>ad5946acbc78d91b2bd0621fbf6a3c9a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>METHOD</name>
      <anchorfile>enumcom_1_1aworx_1_1lox_1_1Log_1_1Scope.html</anchorfile>
      <anchor>a980085812d120b3761817608d332fecd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::LogTools</name>
    <filename>classcom_1_1aworx_1_1lox_1_1LogTools.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a2eefb8683336b59a35278ccf0a0af407</anchor>
      <arglist>(String domain, Log.Level level, Exception e, String headline, int indent, Lox lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aee2dcd1cd6054ce0a3e3a150beb17d46</anchor>
      <arglist>(String domain, Log.Level level, Exception e, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a39e4b6c911f5917228620a521406183c</anchor>
      <arglist>(String domain, Log.Level level, Exception e, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1ff9b68ec7f5e482b68378cf1a1ba41f</anchor>
      <arglist>(String domain, Log.Level level, Exception e)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a9d466aba103eba05d942556dd37d2e63</anchor>
      <arglist>(Log.Level level, Exception e, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac0c84106c9b411de7a17de7eabfd471e</anchor>
      <arglist>(Log.Level level, Exception e, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ad457dd13412a755b99cf4a32b05456c2</anchor>
      <arglist>(Log.Level level, Exception e)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aed3f6ab2dd27d848acdc0503080dd52d</anchor>
      <arglist>(String domain, Log.Level level, String headline, int indent, Lox lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a512bd4e62b1e49e036de1fe0ba5571fa</anchor>
      <arglist>(String domain, Log.Level level, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa57d76aacbe828e51e6982442b393e7f</anchor>
      <arglist>(String domain, Log.Level level, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a4c3e962c3dae9b4dc17c387ae6b45c01</anchor>
      <arglist>(String domain, Log.Level level)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a94bec0fc3a3b806f2edb992ddf1fffed</anchor>
      <arglist>(Log.Level level, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aadc99123f5a7e3fe8e459280da99d6a6</anchor>
      <arglist>(Log.Level level, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>stackTrace</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a817e6e1f3fc55f4e24d9aeaad93700cd</anchor>
      <arglist>(Log.Level level)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a46eedcc7353667a139db8f4f70e6a20c</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion, String headline, int indent, Lox lox)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a91624d9df4759f974a7646e829171edc</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a93abcc02143b6f726f6a57c83487ed92</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac32aa2578833e9f22f41a7d1efb3a6b5</anchor>
      <arglist>(String domain, Log.Level level, Object o, int maxRecursion)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a843848812b37f0f95f74c75d02f2cf58</anchor>
      <arglist>(Log.Level level, Object o, int maxRecursion, String headline, int indent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ae8551bce5f762937be6ecf321531fb41</anchor>
      <arglist>(Log.Level level, Object o, int maxRecursion, String headline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>instance</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>abd08f03fc574e93cb8390391910bfcd7</anchor>
      <arglist>(Log.Level level, Object o, int maxRecursion)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtExcNull</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>abc979d386ae994bcf7341f1063bc78cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtExcStackTraceHeader</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a6fe2b194ed273ab7d5ecc60ff3cc8aa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstLineNoPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a498f4459ff785bf0a24247bc19c7c55b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstLineNoPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aaed3474ebecc6243c9d252b360f273a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstNull</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a6da3d133f457141b643c20b6ad94e785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstRecursionLimit</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>af83bbf104a660912464d892b385961dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstCycRefPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a50d1fc77d08b555d79412fafbf28d750</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstIterablePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a8bb73f0f637a1ac537a880f98b0abec2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstIterablePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ad26cae72fda492503609c596930f04a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstArrayPrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac31532e5ddf448a45d274b9804f7da32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstArrayPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1986f836d10cbdeae28a51a600f4f830</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstCycRefPostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a3e59f9e1612dd0790a17437ec412edbf</anchor>
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
      <name>fmtInstTypePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a86ef37db49c5ccdf1f39b25e1968142a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstTypePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>aa4a744d0f803fe83885f6cd05a18c721</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>fmtInstIndent</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a3cba09b083e1c4c9531791e6bc24b54a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>instValueTabStop</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ac586537acea9202be95f5cf793324550</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>instTypeTabStop</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1cfe4bbb4fae0ca0db99d3fe768ffa64</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>exception</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ae3629acd99b0a1b6bbdfd6ddf73bf164</anchor>
      <arglist>(Throwable e, String headline, int indent)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>nextTempBufLine</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a244989ac459538e944eba501842e5410</anchor>
      <arglist>()</arglist>
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
      <type>static boolean</type>
      <name>isWrapperType</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a9ac188ccdcf753a6e332b18b46fddca0</anchor>
      <arglist>(Object o)</arglist>
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
      <anchor>acd7df3d826274b4de6bfc27f71c91168</anchor>
      <arglist>(@SuppressWarnings(&quot;rawtypes&quot;) Class type)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static MString</type>
      <name>toolBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>ab2b7fd952d42f838905b7ce560f1e68e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static MString</type>
      <name>tempBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a570982a6045c2e2c409321b2e1a01898</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>tempLineStartIdx</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a93c641104eda6fb4550ce017b73430bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>tempLineEndIdx</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a3e071e391087b62155ccd1f5b3e3ab46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static int</type>
      <name>instLineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>acdb62e874751ec8a2090e30cbf1dba93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static HashMap&lt; Object, Integer &gt;</type>
      <name>instObject2LineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a7ee8cca5af9088eb964970b254b20078</anchor>
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
      <name>lock</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a77074852c5d95a31cab43e8c85871c64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static ByteArrayOutputStream</type>
      <name>exceptionBAOS</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a5737c70ed077c93996f8dc1b1a45afd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static PrintStream</type>
      <name>exceptionPS</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1LogTools.html</anchorfile>
      <anchor>a1faac34f3e6f3def40a11d8b59d9b00f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::Lox</name>
    <filename>classcom_1_1aworx_1_1lox_1_1Lox.html</filename>
    <member kind="function">
      <type>Logger</type>
      <name>getLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acaa486d7048bb92b36bf103fdea4518c</anchor>
      <arglist>(String loggerName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a11ce703948713f6ac0111873a8f09dc5</anchor>
      <arglist>(Logger logger)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9348b034cf3c349e591157487ddf5db5</anchor>
      <arglist>(Logger logger, Log.DomainLevel internalDomainLevel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1808df0a2b951b76d3ea1c524eabdbe2</anchor>
      <arglist>(String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeLoggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aad1238e9859b35d8dc7fc487f6db435f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>regDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a316dced3eca35079dfeba43492009bf2</anchor>
      <arglist>(String domain, Log.Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a147bdeebbc4d8f1ffbbd949017955ff4</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, boolean recursive, String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a90a909fa61ad8752183fe7a59e863d68</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel, boolean recursive)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acfea987a1279622cfb8a5e0393fe33d7</anchor>
      <arglist>(String domain, Log.DomainLevel domainLevel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac7f02904cf4373d6fae0d2adb1f01969</anchor>
      <arglist>(boolean disabled, String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a103c22d4e6858333fad2dcd3a6005389</anchor>
      <arglist>(boolean disabled)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a28ab0d0c7dc645cbc25043d6af7a81ef</anchor>
      <arglist>(Date startTime, String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acb3871b82a3733b10f82d53f22118154</anchor>
      <arglist>(Date startTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStartTime</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aba815d1968bdc45c7d69b6bbb449d12b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a8004a334af1a78b763447f2b06fafe12</anchor>
      <arglist>(String threadName, long id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mapThreadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab6682f7a60a28486a500f734209e845d</anchor>
      <arglist>(String threadName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ac22f5751d25bc89b3f8a93f330b0fdf7</anchor>
      <arglist>(Object marker, Log.Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getMarker</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ab8f5469df565f4ef0bcc50a0e13ecfdc</anchor>
      <arglist>(Object[] markerPointer, Log.Scope scope)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>logConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a78bb02ffe6a591b53a58b99e6d041495</anchor>
      <arglist>(String domain, Log.Level level, String headLine, String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>logConfig</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad84bd03ff5650d26ab52f576ea1407ad</anchor>
      <arglist>(String domain, Log.Level level, String headLine)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad55e8ca1d024bd9e1da15685c4b5b19f</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a08a4461d6fdc8f4f7defb37542876a2e</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae0096258c7f17ee885de682386294c28</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a4bad4d43b8ff70f38e648a73a4e9aa0e</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a43695b6a313e25c926b98f41ca74c501</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>acd7eef5b5a94377fa530ea9f930fee85</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a50744ad3358054e9cecf08616a3e9d8b</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>info</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ae189289c16615c865b799c67b6dc8350</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>adb50d51269bc686ca51b6102e169721c</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a054c4b2d956d70587cfc45b54d09d1c9</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a46b4fd3bac0dcbe7f4e7c60ac1cfdedc</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ade4c8701caa62459c0a849954fa655d2</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>afcfe66401e26f994706e6306e5886033</anchor>
      <arglist>(Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a143121b7aa73c57aed99b0d13b5b80d3</anchor>
      <arglist>(Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5c07ba41966a86bb50c30abbc50d1122</anchor>
      <arglist>(String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7df4f528e505be28800d4833b743ad73</anchor>
      <arglist>(String domain, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3f5fe881709ec9450b75a5a1932a01ae</anchor>
      <arglist>(boolean trueOrLog, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a03d363a00f068f432f0feabde6390210</anchor>
      <arglist>(boolean trueOrLog, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a3c93731a19b630ddf90e83d822941ff3</anchor>
      <arglist>(boolean trueOrLog, String domain, Object msg, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Assert</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a100809339cc3d8d12616e144489bc90c</anchor>
      <arglist>(boolean trueOrLog, String domain, Object msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a85dfa486fadf8eb0a5e91021d9626ae8</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject, int indent, String loggerFilter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>abad2865fd643d8cce3e06237579102d8</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a5be15f59b9d0e1b07076e615015b0fc9</anchor>
      <arglist>(boolean doLog, String domain, Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a97f9b7339462129066391369504b6bc4</anchor>
      <arglist>(String domain, Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a190fddfae44584eec3ee4e2da2e243d2</anchor>
      <arglist>(Log.Level level, Object msgObject)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9363c140ae2b54a1848ccbed47522e21</anchor>
      <arglist>(Log.Level level, Object msgObject, int indent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a63ffdc0eff99c9b8509b3a899e464379</anchor>
      <arglist>(Log.Level level, Object msgObject, int indent, String loggerFilter)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>cntLogCalls</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a898aebb032f3bceb8d879e7695f197d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ThreadLock</type>
      <name>lock</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a77074852c5d95a31cab43e8c85871c64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>internalDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a67901e9f160da1261843f911d9a0c7a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>omittablePackagePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a429a66aafea0971f02f2f5ccf21ca0d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>HashMap&lt; Long, String &gt;</type>
      <name>threadDictionary</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a28aec8792ccd6e67dd49f06d57c8a8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static final String</type>
      <name>version</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a9a2912077b542dacbc5d71e0b14c55b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>saveAndSet</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>ad363a9266cda3a71cfb9f8b378e5c900</anchor>
      <arglist>(boolean getResDomain, String domain)</arglist>
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
      <type>ArrayList&lt; Logger &gt;</type>
      <name>loggers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a7144a4b0aaac3ec84ce06a48b50d9911</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>HashMap&lt; MString, MString &gt;</type>
      <name>defaultDomains</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a1f8cd2c87e05902845318a8f345092e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>HashMap&lt; MString, Object &gt;</type>
      <name>markers</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>aee43ed362969e78ce53084fd361a7dfe</anchor>
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
      <type>static boolean</type>
      <name>simpleWildcardFilter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1Lox.html</anchorfile>
      <anchor>a2b24103f62da8cad52b51faea81dd5f4</anchor>
      <arglist>(Logger logger, String loggerFilter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::android::AndroidLogCatLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</filename>
    <base>com::aworx::lox::core::TextLogger</base>
    <member kind="function">
      <type></type>
      <name>AndroidLogCatLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>aa7915d73d58ff0fb3e6d8490096a2620</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AndroidLogCatLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>a2a54b3dc4c3c94110f82f1c6a875f7ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constructor</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>a20d184ae62fb81a0f1edd89a5be76231</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>logTag</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>ac2cdc5829603183d66f5e824ddc7af96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boolean</type>
      <name>verboseIsDebug</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>af4c546b140faad4e89c4ad7844c702f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TextLoggerObjectConverter</type>
      <name>objectConverter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aa9c3f8373c25b01fd386dc0ea32636db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TextLoggerLineFormatter</type>
      <name>lineFormatter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aa5e10d11120b3589e7b35e5ae709f9e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ArrayList&lt; String &gt;</type>
      <name>replacements</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>ac33de2423be274be480817abf43f445c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>multiLineMsgMode</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>accadd49b1318abe7fc5b7ae8dcb0f431</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>multiLineDelimiter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a927436a8c9c6474fc683bb0888f43b62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>multiLineDelimiterRepl</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a55f49a9dca5dd991ad7198b48307732b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>fmtMultiLineMsgHeadline</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aeddddadb6299e40585333c787194c0fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>fmtMultiLinePrefix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aecf89caaefb89a866f30dfe5c36394d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>fmtMultiLinePostfix</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a4a0d7c91d02a108e89817517dca908aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a9a2326f35466e54c36c070829245c557</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>cntLogs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a875cc7d46740caba1725c2f6580804e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>timeOfCreation</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a0216d25a6442fb3b0ec187632a00a7c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>timeOfLastLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a101380ea5d8e738d844f5562a39b5174</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boolean</type>
      <name>isDisabled</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>ad7073fb6d6486e166ea6116e36bbecf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LogDomain</type>
      <name>rootDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a92d0810f0bd233179da253ce5fcc4624</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>a7d0332030c6bce887e10e6156301da35</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>TextLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a922bc82585360a89568276c894e3631c</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>doLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>acc9afa8c3afaaacb3c3321d58037070c</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Logger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a42c27444187c8bea77c2b065a2ec183e</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>consoleBuffer</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1android_1_1AndroidLogCatLogger.html</anchorfile>
      <anchor>a13297cc2c876d3e5667e2c567efbb377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>MString</type>
      <name>logBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>aaf37e693e36d895e18bcc1f6037f5d9e</anchor>
      <arglist></arglist>
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
    <name>com::aworx::lox::core::CallerInfo</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</filename>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ab9d465ee41551f71b8a8dcae4951140e</anchor>
      <arglist>(HashMap&lt; Long, String &gt; threadDictionary, String skipablePackagePrefix)</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>packageName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>af16cbaa6964dd55894ea3c4d6b80b82a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>className</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>afc4f959391fb840db1b65ba194052bbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>methodName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>aed1d7183742d9041a94ac83312720f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>fileNameAndLineNumber</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a585c7b8d644e268e6823a4880c2b0e6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Thread</type>
      <name>thread</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ac99b75d10f465c1160242dea4544069a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>threadName</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>ae056441640c10bc77840301b2bd36142</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>threadID</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>a60a653746c2fc588e8da8d1a4b444bb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TickTime</type>
      <name>timeStamp</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1CallerInfo.html</anchorfile>
      <anchor>af11689f2da47b3d6082a1afd0a7a20ae</anchor>
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
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>ad146fa8579a5f8a876c4688cc5a68520</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Log.DomainLevel</type>
      <name>getLevel</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>acff162e8486d1c073b6ab88bf60c9c9b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLevel</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>af009b2b92be670c210501dfa30954941</anchor>
      <arglist>(Log.DomainLevel domainLevel, boolean recursive)</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>isActive</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a6d8ba3b2ebf63ea89e6cd80de592dcc4</anchor>
      <arglist>(Log.Level cmpLevel)</arglist>
    </member>
    <member kind="function">
      <type>LogDomain</type>
      <name>findOrCreate</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a0b41e0a6c5ca2c5d3a6e9ef780f979ed</anchor>
      <arglist>(MString domainPath, boolean createIfNotExistant)</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>name</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>a58b6f98bcc8eee5d75f0285a6356056f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LogDomain</type>
      <name>parent</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>ada8b2d06ffe61078828bc5a0dd05f2e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ArrayList&lt; LogDomain &gt;</type>
      <name>subDomains</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>acd8ad0c0db3b31ab2e67cd197767b908</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>domainSeparatorChars</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>aa25dea88ec319cb6f8954e150ec0c542</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>LogDomain</type>
      <name>findOrCreateInternal</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1LogDomain.html</anchorfile>
      <anchor>ae3d3e3f7f93758c28f1d33a9d8b2493e</anchor>
      <arglist>(MString domainPath, int dpStartIdx, boolean createIfNotExistant)</arglist>
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
      <name>createDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a0319dd98a95a91fdd063b2c7f506c82f</anchor>
      <arglist>(MString domainPath)</arglist>
    </member>
    <member kind="function">
      <type>LogDomain</type>
      <name>findDomain</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a239cbe55cec8d923cc407ff5a65c2e7c</anchor>
      <arglist>(MString domainPath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>line</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>a9548b32ca965f5b2c9bbd82cc44cf75d</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1Logger.html</anchorfile>
      <anchor>aae6d2874b82786019b36b4ac8ca9c647</anchor>
      <arglist>(MString domain, Log.Level level, Object msgObject, int indent, CallerInfo caller)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</filename>
    <base>com::aworx::lox::core::Logger</base>
    <member kind="function" protection="protected" virtualness="pure">
      <type>abstract void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLogger.html</anchorfile>
      <anchor>a1300bd920d9f44ebc751480932ed2585</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLoggerLineFormatter</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</filename>
    <member kind="variable">
      <type>MString</type>
      <name>format</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a192fd58992fe417f2e55725737fbb281</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int[]</type>
      <name>autoTabs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a81a1aa55e14721a198990dfe3f11eb6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>indentString</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>aa49de5c950d98088ddc25dbb15fe00b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>logLevelError</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ae8322b6ecc21496710ca2c4bb50d4cec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>logLevelWarning</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a6eacb25f7d4c74adb2ada7ccbcd36f3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>logLevelInfo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a15ed110e8ee4220103779d9df1d1d31a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>logLevelVerbose</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a43bbe77b119f7f752815048f0552d6ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>dateFormat</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a6b15b781aa433d02829c8c74e71c795f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeOfDayFormat</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ab07f305b621e1b1dce257bd84dd113d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeElapsedDays</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ada00d3322cceb4f8029c90415bece6dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffMicros</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ab09736328de999364378426c1815de02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffMillis</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>aed18be4469f8723bc9f5b2424de8f5ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffSecs</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>aa0d82c55bc5841dbce908bbc7418e3a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffMins</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a4e2226d8c28fb6cc3c0fee7ee568b890</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffHours</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a3a0833856bcad15fd363f3d85079af21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>timeDiffDays</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a1410aced7386eb84cc3da7ccbfdd2c96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>logNumberMinDigits</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ac083b4aac0faf389e3a70ef7f8212e54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>autoGrowThreadNameLength</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a084ad443a444da2d64d0d9fb45be458b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>autoGrowDomainNameLength</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>acfe088a5a7da895ae4ebe7c73d38299c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SimpleDateFormat</type>
      <name>dateFormatter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ae00c40256e7c69ef39832f0a602f8fdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SimpleDateFormat</type>
      <name>timeOfDayFormatter</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>aeb350e099bc2a47cf6c85fa0db340748</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>writeMetaInfo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>af4b23ead89f585c6aa6f53834d54cabd</anchor>
      <arglist>(Logger logger, MString buf, MString domain, Log.Level level, int indent, CallerInfo caller)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>processVariable</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a7d055940037fdff1e6b956f93a0bc69b</anchor>
      <arglist>(Logger logger, MString domain, Log.Level level, CallerInfo caller, MString buf, char[] formatString, int formatStringIdx)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>writeTimeDiff</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>ab61a682d25d6320be877e7ae1c5252de</anchor>
      <arglist>(MString buf, long diffMicros)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Date</type>
      <name>callerDateTimeDate</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a15c370a8d52b71bdf21b1fe8869a06fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GregorianCalendar</type>
      <name>callerDateTimeCal</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a7f3fbbf494fb72f94da86e9e541d0151</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>boolean</type>
      <name>dateInstanceSet</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a2799fc5b4b9bce013ac467ebad2d5dba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>boolean</type>
      <name>calInstanceSet</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>afd9a7b449b94e4b73ee04db72e27d384</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>StringBuffer</type>
      <name>tempSBuf</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>afe17394f84cf5bdb4891727e32f49300</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>FieldPosition</type>
      <name>fieldPositionZero</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a80d3b9e454f65277d0245306d9abd668</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>defaultfmtDate</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a917c9b55d2f0a57a7e467b01193f20f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>String</type>
      <name>defaultfmtTimeOfDay</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a7fcc81983c7adc0ded7cf48f504fe001</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>autoTabNo</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerLineFormatter.html</anchorfile>
      <anchor>a6baac125a9d8081f25ff930d5d90edbe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::lox::core::TextLoggerObjectConverter</name>
    <filename>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</filename>
    <member kind="function">
      <type>MString</type>
      <name>convertObject</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</anchorfile>
      <anchor>a397c20bbd61197c1353f6a19c2b71403</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>fmtNullObject</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1core_1_1TextLoggerObjectConverter.html</anchorfile>
      <anchor>a5b4240f9d910de65e0f07e5775ab6eef</anchor>
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
  <compound kind="class">
    <name>com::aworx::lox::loggers::ConsoleLogger</name>
    <filename>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</filename>
    <base>com::aworx::lox::core::TextLogger</base>
    <member kind="function">
      <type></type>
      <name>ConsoleLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>ad445eb256a79caeb8371bb5b7aee7a0a</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConsoleLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a7e74f8c298d3d48edb7da6f0c412aea6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>boolean</type>
      <name>useJAVA6ConsoleIfAvailable</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a928cae9186556dc86b9a6a09308f32dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1ConsoleLogger.html</anchorfile>
      <anchor>a7d0332030c6bce887e10e6156301da35</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
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
      <anchor>a24187e71fb1f31390f1fb25186940dd2</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryLogger</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a4199daf6e37271a11e2d47633768701a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>MString</type>
      <name>buffer</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>abb05cbb40d212c431ab82b3718ccfa04</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>doTextLog</name>
      <anchorfile>classcom_1_1aworx_1_1lox_1_1loggers_1_1MemoryLogger.html</anchorfile>
      <anchor>a7d0332030c6bce887e10e6156301da35</anchor>
      <arglist>(MString domain, Log.Level level, MString msg, int indent, CallerInfo caller, int lineNumber)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::AWXU</name>
    <filename>classcom_1_1aworx_1_1util_1_1AWXU.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>sleep</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1AWXU.html</anchorfile>
      <anchor>a681128635e507f1fc14c07e7541123d2</anchor>
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
    <name>com::aworx::util::MString</name>
    <filename>classcom_1_1aworx_1_1util_1_1MString.html</filename>
    <member kind="function">
      <type>char</type>
      <name>charAt</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a0df4313245971ee814410a5206d228ae</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a3d0f4ae571310c6ed081daa3985ecb47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>CharSequence</type>
      <name>subSequence</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a49ac9531628120dc6c0c6d29f25c2cb6</anchor>
      <arglist>(int beginIndex, int endIndex)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a6189a24ff8c9875071a28e74cdb98320</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a824015d5ca0548b90d383047023b02c2</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a2939e50fa2dacabe46eb325824756205</anchor>
      <arglist>(MString ms)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af4e33036b8bb5e8c59db12f72c53f6ad</anchor>
      <arglist>(MString ms, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8017ebd5348b33938aef1ab4754e0b9b</anchor>
      <arglist>(MString ms, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa0e2e1624b7884cae91d5b20cc8ba1e4</anchor>
      <arglist>(String s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>accaf73ff43ddf55bb8544cdcd96e5bcc</anchor>
      <arglist>(String s, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a18282ad5ba34ce013c40f8d606af0e3b</anchor>
      <arglist>(String s, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a49d52b558c4598159fbc936435f82197</anchor>
      <arglist>(StringBuffer s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a09aa1b552f3d84b6db1550514431a4ea</anchor>
      <arglist>(StringBuffer s, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a42289c2ad141f485edbca998f8651e71</anchor>
      <arglist>(StringBuffer s, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>clear</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9cc2838997e7d0381c645b2b9d7760e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aacf44a32afa22f36637e373a2ec1c052</anchor>
      <arglist>(MString ms)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a6baa4dd839d4ff0e3409afa4a64b6f0e</anchor>
      <arglist>(MString ms, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a6bb037ccf57a2504517bfd9049addcb1</anchor>
      <arglist>(MString ms, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a7de4550007dfdb646489e32a60033e94</anchor>
      <arglist>(String s)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aac4af74d0cddf80a2417045a3c74763d</anchor>
      <arglist>(String s, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a5b198d360de502abeaf32866648d9913</anchor>
      <arglist>(String s, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a16b8eb64822dffbebeb1618a0b7a0978</anchor>
      <arglist>(StringBuffer sb)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab2daf4d134d5e73b1ac8e0904ec0321b</anchor>
      <arglist>(StringBuffer sb, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>acf57a5bde2bec79a7bf19ef0eec48a51</anchor>
      <arglist>(StringBuffer sb, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a11ad3dc1422aaddb5ddc2ae77110b05d</anchor>
      <arglist>(StringBuilder sb)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a44b24f4e86bf78993ed792beed07e62d</anchor>
      <arglist>(StringBuilder sb, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a7578302ba1dd58026d0fa6b5ea74ab48</anchor>
      <arglist>(StringBuilder sb, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a2b26d77b79b8d8909ac4bebd22c7fff7</anchor>
      <arglist>(CharSequence sb)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>afd43e5c6fb471e50a9350927a08d8fc5</anchor>
      <arglist>(CharSequence sb, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a0c87965c50c3d5c25e6a8b57058202ec</anchor>
      <arglist>(CharSequence sb, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab6ba1126cb39496f762bd1ed83d89d84</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aaa7b239d517854be44927c23ea61c082</anchor>
      <arglist>(char c, int qty)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a5d5a364eda5a79373b9291247b7a9531</anchor>
      <arglist>(MString ms, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>abc8f8c5e394b5c0b36696b6868195ea3</anchor>
      <arglist>(MString ms, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ae5fe05bf22273dcdf8e0da0bd117edd9</anchor>
      <arglist>(String s, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a75b6ef69b0e03f878deb5571398db350</anchor>
      <arglist>(String s, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a98c496ea25d513d7a92907e5cc42b745</anchor>
      <arglist>(StringBuffer sb, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadRight</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aa1c74967306b231ce49ff8114c0bd9ec</anchor>
      <arglist>(StringBuffer sb, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a3d3297275126428712ff230d9f7b4c2d</anchor>
      <arglist>(MString ms, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a6c67a891632c9863f61c27983a7b3627</anchor>
      <arglist>(MString ms, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8715fd3fda610fce505e42c1936617b8</anchor>
      <arglist>(String s, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af73cea11a457365a0ec6155ec050d979</anchor>
      <arglist>(String s, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ac0b2f43d4caa34bfb7ffd1b357946671</anchor>
      <arglist>(StringBuffer sb, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadLeft</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a60b18a3076efb2f2987d594d8de49f9b</anchor>
      <arglist>(StringBuffer sb, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a2f34efe0efe2b52c3f7f36697c75e193</anchor>
      <arglist>(MString ms, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a79d2b8405c4a1b8b4e944a5a75bb6e13</anchor>
      <arglist>(MString ms, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a787696ffcf229d0700577414d39b75a4</anchor>
      <arglist>(String s, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a70b48774dc0a416fb347e642b4d0bd1d</anchor>
      <arglist>(String s, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a142c74d88ed00e607c7cf09b98e7f761</anchor>
      <arglist>(StringBuffer sb, int fieldSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>appendPadCenter</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af13aa96e6f99d6e491521efdc345d812</anchor>
      <arglist>(StringBuffer sb, int fieldSize, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aad87f0def7fc0813ad63710e29e153b8</anchor>
      <arglist>(int i, int minDigits)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a7857c70d8dc6cdb88d6862e7c706a527</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>append</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1b887bde0726c7e56caa12d4bf58da6f</anchor>
      <arglist>(double d, int minDigitsBeforeDot, int digitsAfterDot)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>tab</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9cc68303640d37c682c3ab798633764d</anchor>
      <arglist>(int tabSize)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>tab</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>abd3a46e407fd78e345735e4eed25ebfe</anchor>
      <arglist>(int tabSize, int tabReference)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>tab</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a252867e4b920b7eb8463351abf48e25c</anchor>
      <arglist>(int tabSize, int tabReference, int minPad)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>tab</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aca40b491a66d09efc3d897325da417d2</anchor>
      <arglist>(int tabSize, int tabReference, int minPad, char padChar)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>newLine</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab1e2422c154635464aee9c16c0493506</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>containsAt</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a5cfe24fea5a9f07bc3b411a5d5cf1222</anchor>
      <arglist>(CharSequence s, int pos, boolean ignoreCase)</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>containsAt</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a4fe1e46da5df87fefcacb81b6330bdc9</anchor>
      <arglist>(CharSequence s, int pos)</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>startsWith</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab316fed7f0f6497158869355aba96fbe</anchor>
      <arglist>(CharSequence s)</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>endsWith</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab0f4b2881454b063c7bb9fee6d58ded2</anchor>
      <arglist>(CharSequence s)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>indexOf</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1c43dcbb767f10f9a625ec20694999f6</anchor>
      <arglist>(CharSequence s, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>indexOf</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a3aaa0641d23c63ae7c0b45f4b14d5016</anchor>
      <arglist>(CharSequence s)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>replace</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af8542d4003ef95ad4e15f33c14e8b86b</anchor>
      <arglist>(CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>replace</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aaa8b790884ca485b8698cc624c7abdd7</anchor>
      <arglist>(CharSequence searchStr, CharSequence newStr, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>replace</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ac22fce57adf0f8170f2343c9d0a2901e</anchor>
      <arglist>(CharSequence searchStr, CharSequence newStr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af214887db1ff5c940a796209e4687231</anchor>
      <arglist>(CharSequence cmp)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ad95fecd8c81767b0cd6a1eab72388372</anchor>
      <arglist>(CharSequence cmp, boolean ignoreCase)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a15a4cc63cefdd926a2f7c0358b8f3ede</anchor>
      <arglist>(CharSequence cmp, boolean ignoreCase, int sStartIdx)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ae80efe75fdcb033dc6d8fdbf7306f2a5</anchor>
      <arglist>(CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>aeab16cc30f29931695223b601ae1682d</anchor>
      <arglist>(CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compareTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>af95a0dea99badea2ab30e30c3c05ce09</anchor>
      <arglist>(CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>convertCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a115c0fb7598d93ba9805c274fb6a5af1</anchor>
      <arglist>(boolean toUpper)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>convertCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a3e3cd5d434237e0cb37bc75f3f1dd1b5</anchor>
      <arglist>(boolean toUpper, int substrStart)</arglist>
    </member>
    <member kind="function">
      <type>MString</type>
      <name>convertCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a010a0b31f3d17d30a320311817035372</anchor>
      <arglist>(boolean toUpper, int substrStart, int substrLength)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ad146fa8579a5f8a876c4688cc5a68520</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ad6f084f891f7f8edebc1980b3b7c854d</anchor>
      <arglist>(int startIdx)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ae9b5b93abce1d30a3daddb12c1c81cff</anchor>
      <arglist>(int startIdx, int len)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>hashCode</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a077e18fe97323c7194e2665ffc766399</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>equals</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a39e5bc339e3b5924ec96de42fbb8f33f</anchor>
      <arglist>(Object o)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ensureCapacity</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>adc900259936e34e93cbbce4935566d59</anchor>
      <arglist>(int minLen)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static boolean</type>
      <name>isNullOrEmpty</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ad1bf539360860f3eeeb2f769f8e31294</anchor>
      <arglist>(CharSequence jString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>indexOfIgnoreCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8f74b4b0a6c644cd3996a9fb9d2e2eed</anchor>
      <arglist>(CharSequence sIn, CharSequence sFor, int startIdx)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>indexOfIgnoreCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab98838cbc0c190bd2596cbe2cdbb20f4</anchor>
      <arglist>(CharSequence sIn, CharSequence sFor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static boolean</type>
      <name>startsWithIgnoreCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a2f52faec3b749bc61c275bc9343da6b6</anchor>
      <arglist>(CharSequence s, CharSequence prefix)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static boolean</type>
      <name>endsWithIgnoreCase</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9725bfa39e4a751d10ee54f63a15173c</anchor>
      <arglist>(CharSequence s, CharSequence postfix)</arglist>
    </member>
    <member kind="variable">
      <type>char[]</type>
      <name>buffer</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a8317b33b8c004741d95935199d964be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>length</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a9f59b34b1f25fe00023291b678246bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>hash</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a6656561117ec1ab686401179004f53ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static String</type>
      <name>NEWLINE</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a48d5ec6061d7631c1714c0973519c1ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static final String</type>
      <name>empty</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a4161fdf6dff38fd6cd122809e65cd1f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>boolean</type>
      <name>adjustRangeAndTestIfEmpty</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a1918368be065312346393ae26ecfcf29</anchor>
      <arglist>(int referenceLen, int startIdx, int len)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>adjStartIdx</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>a667d47162b84e73a69f708245d7b41a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>adjLength</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1MString.html</anchorfile>
      <anchor>ab07f0e55b22a488c76165d3935ce794b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::ThreadLock</name>
    <filename>classcom_1_1aworx_1_1util_1_1ThreadLock.html</filename>
    <member kind="function">
      <type></type>
      <name>ThreadLock</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>ad866d94468fb30b56fc5cf53211eb2ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ThreadLock</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a6ad194bfa7eb71de47a06d7b79bf6031</anchor>
      <arglist>(boolean recursiveMode)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ThreadLock</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a6ccccd6435086e88a76c1000b26255dd</anchor>
      <arglist>(boolean recursiveMode, boolean setUnsafeMode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aquire</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a29ebe4f44772d276c34510a35a55db9e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a23b477d0e2d399f75d585d154c346591</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>ad146fa8579a5f8a876c4688cc5a68520</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnsafe</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a89682a610134dbf105652e33657e0ee8</anchor>
      <arglist>(boolean setUnsafe)</arglist>
    </member>
    <member kind="function">
      <type>boolean</type>
      <name>IsUnsafe</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a99c4577e8eea7adb5b986d8b87627a23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>boolean</type>
      <name>useAssertions</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a35bd0b44ad22dfa9d3dee392e19bab3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>waitALoxWarningLimit</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a5c735b5a34529619a34f5ae2455d27d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>recursionWarningThreshold</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>acad859886dc19036f76e572c2daf2caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>boolean</type>
      <name>recursiveMode</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>abf1029939cb8738404d78773ee98202f</anchor>
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
    <member kind="function" protection="package">
      <type>void</type>
      <name>constructor</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1ThreadLock.html</anchorfile>
      <anchor>a3e37532dae663660f404efd7c15c7b6a</anchor>
      <arglist>(boolean recursiveMode, boolean setUnsafeMode)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::Ticker</name>
    <filename>classcom_1_1aworx_1_1util_1_1Ticker.html</filename>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>now</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ac7a1ddfbc7d217670be03dc0722a5adc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>add</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a33236e3a6c290f0e035d5f9ac2a327d2</anchor>
      <arglist>(long ticks, int days, int hours, int minutes, int seconds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>toMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a40bc3e2129b61393b98cac6c59e48a07</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>toMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a3c5f77b7a3b2479ea95a51559b6bd83f</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>toNanos</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a3d2548f74dc7a245e0b29b54cf343144</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>afa6730c03c7b584a3a9a33be81ed125c</anchor>
      <arglist>(long millis)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>aef62101f449515145c8d4385dcc05dba</anchor>
      <arglist>(long micros)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromNanos</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ae6b08512aeb2693b992a65b5cf5024f9</anchor>
      <arglist>(long nanos)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>toEpochMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>aeaf55f47d939a3f22bb5a9504ad4e9ee</anchor>
      <arglist>(long ticks)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromEpochMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a1b13194fceedc227d1c20fb9d8a6cdf2</anchor>
      <arglist>(long epochMillis)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Calendar</type>
      <name>toJavaCalendar</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>ad02fa2a665aa5a1dc5bde3c031b1c6ec</anchor>
      <arglist>(long ticks, Calendar result)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromJavaCalendar</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a8d734b8327d43ad654119dbbfb1e6000</anchor>
      <arglist>(Calendar javaCalendar)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Date</type>
      <name>toJavaDate</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>afcec0f9a935c72f45d091bbfc584da00</anchor>
      <arglist>(long ticks, Date result)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long</type>
      <name>fromJavaDate</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a1769d8785b2654e8d67700c4d498a664</anchor>
      <arglist>(Date javaDate)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static long</type>
      <name>internalFrequency</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a2a566616ba261c3beb9433771cace0d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="package" static="yes">
      <type></type>
      <name>[static initializer]</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a2e87c5ede6b7235170d287cd2e254454</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static long</type>
      <name>creationTimeDateMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a8843ea79744d6cae8884ad2c81737d8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static long</type>
      <name>creationTimeSystemNanos</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1Ticker.html</anchorfile>
      <anchor>a17c2298e03748d9bff95cdf0fb8bcc6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>com::aworx::util::TickTime</name>
    <filename>classcom_1_1aworx_1_1util_1_1TickTime.html</filename>
    <member kind="function">
      <type></type>
      <name>TickTime</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ae5461afd32a2e7003cc4fd9c2023961c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickTime</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a9022faaf91a176798aee31f833e37e86</anchor>
      <arglist>(long otherTicks)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TickTime</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a172fa05048e619c3b735cc621440fcfb</anchor>
      <arglist>(TickTime copy)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>toString</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ad146fa8579a5f8a876c4688cc5a68520</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>get</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>aafbaa9527425920d5d8b4bebcc1b52f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTo</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a0d1c98da72b9583bac51cca4222144f8</anchor>
      <arglist>(long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setToNow</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a41bca45d4327378ef42f94b8989f3668</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ac8bb3912a3ce86b15842e79d0b421204</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>age</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a158e225e9da0876acf66ae1d77464602</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ageInMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ace4c36e466d4673cd72d59e3fae1091b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>ageInMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a49308e1a48c0789adc0ee0d8415f5d07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>span</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a516f3b5127b0a6c488d020aeaeac82ff</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>spanInMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a6219f6c6ab59823833c991db40bc090c</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>spanInMicros</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a1285289f877d818d8d77ca9747e99a7e</anchor>
      <arglist>(TickTime newerTime)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>measure</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>abf9fd74569722791feb30e8753fac913</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMeasureCnt</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a2b29f44eea2803f027425da1727c06d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>getCumulatedTicks</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>abde8cbbfb9bebc1df4342a19533f80fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>getAverageTicks</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a81cb93e52f174538391ce2de30e61f33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>getAverageMillis</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>aaf6deb8d992aabc669cf4267e9fc20a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getAverageHertz</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a211860211d10a188d68b9e2140e2b323</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Calendar</type>
      <name>toJavaCalendar</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a9a91fb3623e52ef75d2a53eec090d387</anchor>
      <arglist>(Calendar result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fromJavaCalendar</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a50aec3c06b9c2b9feb37474c9927c241</anchor>
      <arglist>(Calendar javaCalendar)</arglist>
    </member>
    <member kind="function">
      <type>Date</type>
      <name>toJavaDate</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ad3be90353f89cd4fedb44afd8911f296</anchor>
      <arglist>(Date result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fromJavaDate</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a7068a160754ab2fe6fe3fe924783b580</anchor>
      <arglist>(Date javaDate)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long</type>
      <name>ticks</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>af0b811e653c51fb98ab202e920af2afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long</type>
      <name>sum</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>ad21ee1949296449cb2806778a7fc94de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>cntMeasures</name>
      <anchorfile>classcom_1_1aworx_1_1util_1_1TickTime.html</anchorfile>
      <anchor>a388aae1c6d770ab01965f0d01b2fdc1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>android</name>
    <path>I:/Dev/A-Worx/ALox/src/java.android.alox/com/aworx/lox/android/</path>
    <filename>dir_d28425d157c348f7018eded18459016e.html</filename>
    <file>AndroidLogCatLogger.java</file>
  </compound>
  <compound kind="dir">
    <name>aworx</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/com/aworx/</path>
    <filename>dir_527a646d6d3f5e63c8ac1a7d94f230ff.html</filename>
    <dir>lox</dir>
  </compound>
  <compound kind="dir">
    <name>aworx</name>
    <path>I:/Dev/A-Worx/ALox/src/java.aworx.util/com/aworx/</path>
    <filename>dir_5baee507fe408fb605765496faa287dc.html</filename>
    <dir>util</dir>
  </compound>
  <compound kind="dir">
    <name>aworx</name>
    <path>I:/Dev/A-Worx/ALox/src/java.android.alox/com/aworx/</path>
    <filename>dir_7d2ef43db91fc793c6dcc7cce598a842.html</filename>
    <dir>lox</dir>
  </compound>
  <compound kind="dir">
    <name>com</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/com/</path>
    <filename>dir_7e8979bb178da02bf13561db78fca84b.html</filename>
    <dir>aworx</dir>
  </compound>
  <compound kind="dir">
    <name>com</name>
    <path>I:/Dev/A-Worx/ALox/src/java.aworx.util/com/</path>
    <filename>dir_07d3e0662593b654d95d369d392be957.html</filename>
    <dir>aworx</dir>
  </compound>
  <compound kind="dir">
    <name>com</name>
    <path>I:/Dev/A-Worx/ALox/src/java.android.alox/com/</path>
    <filename>dir_9679f9409499faea460b73118a35d0ef.html</filename>
    <dir>aworx</dir>
  </compound>
  <compound kind="dir">
    <name>core</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/com/aworx/lox/core/</path>
    <filename>dir_b0919465a7b95a50326a7a1ebb473739.html</filename>
    <file>CallerInfo.java</file>
    <file>LogDomain.java</file>
    <file>Logger.java</file>
    <file>TextLogger.java</file>
    <file>TextLoggerLineFormatter.java</file>
    <file>TextLoggerObjectConverter.java</file>
  </compound>
  <compound kind="dir">
    <name>java.alox</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/</path>
    <filename>dir_721a727a1bb4a56e00cd37e1132ce5a6.html</filename>
    <dir>com</dir>
  </compound>
  <compound kind="dir">
    <name>java.android.alox</name>
    <path>I:/Dev/A-Worx/ALox/src/java.android.alox/</path>
    <filename>dir_2cdf1f19e9b3119e75c76e311dc83261.html</filename>
    <dir>com</dir>
  </compound>
  <compound kind="dir">
    <name>java.aworx.util</name>
    <path>I:/Dev/A-Worx/ALox/src/java.aworx.util/</path>
    <filename>dir_a9c96eededc6019ab4e510d63028ac03.html</filename>
    <dir>com</dir>
  </compound>
  <compound kind="dir">
    <name>loggers</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/com/aworx/lox/loggers/</path>
    <filename>dir_f1e47fa4c3b9b8e09c452d1865919106.html</filename>
    <file>ConsoleLogger.java</file>
    <file>MemoryLogger.java</file>
  </compound>
  <compound kind="dir">
    <name>lox</name>
    <path>I:/Dev/A-Worx/ALox/src/java.alox/com/aworx/lox/</path>
    <filename>dir_ba7bd4677d8f851660031fa77b65d87f.html</filename>
    <dir>core</dir>
    <dir>loggers</dir>
    <file>Log.java</file>
    <file>LogTools.java</file>
    <file>Lox.java</file>
  </compound>
  <compound kind="dir">
    <name>lox</name>
    <path>I:/Dev/A-Worx/ALox/src/java.android.alox/com/aworx/lox/</path>
    <filename>dir_3e3f6916e2fad77f6df5843bebefe2d0.html</filename>
    <dir>android</dir>
  </compound>
  <compound kind="dir">
    <name>util</name>
    <path>I:/Dev/A-Worx/ALox/src/java.aworx.util/com/aworx/util/</path>
    <filename>dir_e682adee14e101f128e0a128ac337218.html</filename>
    <file>AWXU.java</file>
    <file>AWXUErrorHandler.java</file>
    <file>MString.java</file>
    <file>ThreadLock.java</file>
    <file>Ticker.java</file>
    <file>TickTime.java</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Java Reference</title>
    <filename>index</filename>
  </compound>
</tagfile>
