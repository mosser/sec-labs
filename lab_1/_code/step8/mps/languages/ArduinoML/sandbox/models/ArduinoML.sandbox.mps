<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:b251c7d0-ac64-49af-b69a-c69e277f307f(ArduinoML.sandbox)">
  <persistence version="9" />
  <languages>
    <use id="6d84bad7-eb04-4249-8d80-c9157947c3f2" name="ArduinoML" version="0" />
  </languages>
  <imports />
  <registry>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
    <language id="6d84bad7-eb04-4249-8d80-c9157947c3f2" name="ArduinoML">
      <concept id="2226540891595542468" name="ArduinoML.structure.State" flags="ng" index="3RykNw">
        <property id="2226540891595609450" name="isInitial" index="3R__pe" />
        <reference id="2226540891595542493" name="next" index="3RykNT" />
        <child id="2226540891595542489" name="actions" index="3RykNX" />
      </concept>
      <concept id="2226540891595542471" name="ArduinoML.structure.Action" flags="ng" index="3RykNz">
        <property id="2226540891595542496" name="signal" index="3RykN4" />
        <reference id="2226540891595542498" name="target" index="3RykN6" />
      </concept>
      <concept id="2226540891595542465" name="ArduinoML.structure.App" flags="ng" index="3RykN_">
        <child id="2226540891595542484" name="actuators" index="3RykNK" />
        <child id="2226540891595542482" name="states" index="3RykNQ" />
      </concept>
      <concept id="2226540891595542477" name="ArduinoML.structure.Actuator" flags="ng" index="3RykND">
        <property id="2226540891595542480" name="pin" index="3RykNO" />
      </concept>
    </language>
  </registry>
  <node concept="3RykN_" id="1VAgMjDs1ls">
    <property role="TrG5h" value="led" />
    <node concept="3RykNw" id="1VAgMjDs1lt" role="3RykNQ">
      <property role="TrG5h" value="on" />
      <property role="3R__pe" value="true" />
      <ref role="3RykNT" node="1VAgMjDs1lw" resolve="off" />
      <node concept="3RykNz" id="1VAgMjDs1lu" role="3RykNX">
        <ref role="3RykN6" node="1VAgMjDs1lv" resolve="theLed" />
      </node>
    </node>
    <node concept="3RykNw" id="1VAgMjDs1lw" role="3RykNQ">
      <property role="TrG5h" value="off" />
      <ref role="3RykNT" node="1VAgMjDs1lt" resolve="on" />
      <node concept="3RykNz" id="1VAgMjDs1lx" role="3RykNX">
        <property role="3RykN4" value="LOW" />
        <ref role="3RykN6" node="1VAgMjDs1lv" resolve="theLed" />
      </node>
    </node>
    <node concept="3RykND" id="1VAgMjDs1lv" role="3RykNK">
      <property role="TrG5h" value="theLed" />
      <property role="3RykNO" value="13" />
    </node>
  </node>
  <node concept="3RykN_" id="1VAgMjDtsRO">
    <property role="TrG5h" value="led2" />
    <node concept="3RykND" id="1VAgMjDtsRS" role="3RykNK">
      <property role="TrG5h" value="theLed2" />
      <property role="3RykNO" value="13" />
    </node>
    <node concept="3RykNw" id="1VAgMjDtsRP" role="3RykNQ">
      <property role="TrG5h" value="on2" />
      <property role="3R__pe" value="true" />
      <ref role="3RykNT" node="1VAgMjDtvD1" resolve="off2" />
      <node concept="3RykNz" id="1VAgMjDtvCY" role="3RykNX">
        <ref role="3RykN6" node="1VAgMjDtsRS" resolve="theLed2" />
      </node>
    </node>
    <node concept="3RykNw" id="1VAgMjDtvD1" role="3RykNQ">
      <property role="TrG5h" value="off2" />
      <ref role="3RykNT" node="1VAgMjDtsRP" resolve="on2" />
      <node concept="3RykNz" id="1VAgMjDtvD7" role="3RykNX">
        <property role="3RykN4" value="LOW" />
        <ref role="3RykN6" node="1VAgMjDtsRS" resolve="theLed2" />
      </node>
    </node>
  </node>
</model>

